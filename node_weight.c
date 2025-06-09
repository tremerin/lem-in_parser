#include "lem_in.h"

void init_weights(t_data *data, size_t size)
{
    size_t  i = 0;
    data->weights = malloc(sizeof(int *) * size);
    while(i < size)
    {
        data->weights[i] = -1;
        i++;
    }
}

void assign_weight(t_data *data)
{
    data->weights[data->p_start] = 0;
    unsigned int    checks = 0;
    while (checks < data->table_size)
    {
        size_t  j = 0;
        checks = 0;
        while (j < data->table_size)
        {
            if (data->weights[j] != -1)
            {
                size_t  i = 0;
                while (i < data->table_size)
                {
                    if (data->links[j][i] == 1 && (data->weights[i] > data->weights[j] 
                        || data->weights[i] == -1))
                        data->weights[i] = data->weights[j] +1;
                    i++;
                }
                checks++;
            }
            j++;
        }
    }
}

void print_weight(t_data *data)
{
    size_t  i = 0;
    while (i < data->table_size)
    {
        printf("node[%s]: %u\n", data->names[i], data->weights[i]);
        i++;
    }
}

void weight_table(t_data *data)
{
    data->weight_table = malloc(sizeof(unsigned int *) * data->table_size);
    unsigned int i = 0;
    while (i < data->table_size)
    {
        data->weight_table[i] = malloc(sizeof(unsigned int) * data->table_size);
        unsigned int j = 0;
        while (j < data->table_size)
        {
            if (data->links[i][j] == 1 && data->weights[i] <= data->weights[j])
                data->weight_table[i][j] = 1;
            else
                data->weight_table[i][j] = 0;
            j++;
        }
        i++;
    }
}

void    number_of_paths(t_data *data)
{
    unsigned int paths = 1;
    unsigned int checks;
    size_t      i = 0;
    while (i < data->table_size)
    {
        size_t  j = 0;
        checks = 0;
        while (j < data->table_size)
        {
            if (data->weight_table[j][i] == 1)
                checks++;
            j++;
        }
        paths += (checks -1);
        i++;
    }
    data->n_paths = paths + 2;
    data->all_paths = malloc(sizeof(t_path) * data->n_paths);
    //calculate max path len
    i = 0;
    while (i < data->n_paths)
    {
        data->all_paths[i].len = 0;
        data->all_paths[i].nodes = malloc(sizeof(unsigned int) * data->table_size);
        i++;
    }
}

void print_paths(t_data *data, unsigned int paths)
{
    size_t i = 0;
    while (i < paths)
    {
        size_t j = 0;
        printf("Path[%lu] ", i);
        while (j < data->all_paths[i].len)
        {
            printf("%s ", data->names[data->all_paths[i].nodes[j]]);
            j++;
        }
        printf("\n");
        i++;
    }
}

void path_finding(t_data *data)
{
    //init all_paths
    data->all_paths[0].nodes[0] = data->p_start;
    data->all_paths[0].len = 1;
    //acutal number of paths
    unsigned int *nexts;
    unsigned int paths = 1;
    unsigned int pos;
    //while paths are imcompletes
    int incomplete = 1;
    while (incomplete)
    {
        print_paths(data, paths);
        printf("\n");
        size_t i = 0;
        incomplete = 0;
        while (i < paths)
        {
            pos = data->all_paths[i].nodes[data->all_paths[i].len -1];
            //printf("i:%lu\n", i);
            //printf("len: %lu\n", data->all_paths[i].len);
            //printf("pos: %u\n", pos);
            //printf("path: %u\n", paths);
            //ha terminado en la salida
            if (pos == data->p_end)
            {
                printf("exit\n");
                i++;
                continue;
            }
            //unsigned int *nexts = next_node2(data, pos);
            nexts = next_node3(data, pos, i);
            size_t n = 1;
            printf("nexts path[%lu] ", i);
            while (n <= nexts[0])
            {
                printf("%s ", data->names[nexts[n]]);
                n++;
            }
            printf("\n");
            //printf("nexts[0] path[%lu]: %u\n", i, nexts[0]);
            //ha terminado sin salida
            if (nexts[0] == 0)
            {
                //free(nexts);
                printf("no exit\n");
                i++;
                continue;
            }
            //continua el camino
            size_t j = 1;
            while (j <= nexts[0])
            {
                incomplete = 1;
                //añade otro nodo al camino actual
                if (j == 1)
                {
                    data->all_paths[i].nodes[data->all_paths[i].len] = nexts[j];
                    data->all_paths[i].len += 1;
                }
                //se bifurca
                else
                {
                    size_t cp = 0;
                    while (cp < data->all_paths[i].len)
                    {
                        //printf("%i\n", paths);
                        data->all_paths[paths].nodes[cp] = data->all_paths[i].nodes[cp];
                        cp++;
                    }
                    data->all_paths[paths].nodes[cp -1] = nexts[j];
                    data->all_paths[paths].len = data->all_paths[i].len;
                    paths++;
                }
                j++;
            }
            i++;
        }
    }
}