#include "parser.h"

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