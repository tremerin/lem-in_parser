void assing_multiplier(t_data *data)
{
    int    max_weigth = 0;
    int incomplete = 1;
    int deep = 1;
    size_t i = 0;
    data->multiplier = malloc(sizeof(int) * data->table_size);
    while (i < data->table_size)
    {
        data->multiplier[i] = 0;
        if (data->weights[i] > max_weigth)
            max_weigth = data->weights[i];
        i++;
    }
    data->multiplier[data->p_start] = 1;
    while (deep < max_weigth)
    {
        while (incomplete)
        {
            i = 0;
            incomplete = 0;
            while (i < data->table_size)
            {
                // busca hermanos
                // busca herederos
                if (data->weights[i] == deep -1)
                {
                    printf("look for heirs");
                }
                if (data->weights[i] == deep && data->multiplier[i] == 0) 
                    incomplete = 1;
                i++;
            }
        }
        deep++;
    }
}