#include "lem_in.h"

unsigned int *next_node(t_data * data, int pos)
{
    unsigned int    i = 0;
    unsigned int    len = 0;
    unsigned int    *nodes = NULL;

    while (i < data->table_size)
    {
        if (data->links[pos][i] == 1)
            len++;
        i++;
    }
    nodes = malloc(sizeof(unsigned int) * (len + 1));
    if (!nodes)
        return (NULL);
    nodes[0] = len;
    i = 0;
    len = 0;
    while (i < data->table_size)
    {
        if (data->links[pos][i] == 1)
        {
            len++;
            nodes[len] = i;
        }
        i++;
    }
    return (nodes);
}

int contain_pos(unsigned int *positions, unsigned int pos, size_t len)
{
    size_t i = 0;
    while (i < len)
    {
        if (positions[i] == pos)
            return (1);
        i++;
    }
    return (0);
}