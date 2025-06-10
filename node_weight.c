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

void print_weights_table(t_data data)
{
    size_t  i = 0;
    while (i < data.table_size)
    {
        size_t  j = 0;
        while (j < data.table_size)
        {
            printf("%u ", data.weight_table[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

