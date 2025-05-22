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

void    add_nodes_to_path(t_data *data)
{
    while (data->paths)
    {
        t_path  *tmp = (t_path *)data->paths->content;
        unsigned int    last = tmp->nodes[tmp->len -1];
        printf("last: %u\n", last);
        unsigned int    *nexts = next_node(data, tmp->nodes[tmp->len -1]);
        unsigned int    i = 1;
        while (i <= nexts[0])
        {
            printf("node[%u]\n", nexts[i]);
            i++;
        }
        if (last == data->p_end)
        {
            printf("here!\n");
            continue;
        }
        unsigned int    j = 1;
        while (j <= nexts[0])
        {
            if (contain_pos(tmp->nodes, nexts[j], tmp->len) == 0)
            {
                j++;
                continue;
            }
            t_path  *new = malloc(sizeof(t_path) * 1);
            new->len = tmp->len +1;
            new->nodes = malloc(sizeof(unsigned int) * new->len);
            i = 0;
            while (i < tmp->len)
            {
                new->nodes[i] = tmp->nodes[i];
                i++;
            }
            new->nodes[i] = nexts[j];
            ft_lstadd_back(&data->paths, ft_lstnew(new));
                j++;
        }
        data->paths = data->paths->next;
    }
}