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
    size_t  j = 0;
    int incomplete = 1;
    while (incomplete)
        while (j < data->table_size)
        {
            if (data->weights[j] != -1)
            {
                size_t  i = 0;
                while (i < data->table_size)
                {
                    if (data->links[j][i] == 1 && (data->weights[i] > data->weights[j] 
                        || data->weights[i] == -1))
                        data->weights[i] = data->weights[j];
                    i++;
                }
            }
            j++;
        }
}