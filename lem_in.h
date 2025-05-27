#ifndef LEM_IN_H
    #define LEM_IN_H

# include "./Libft/libft.h"
# include <stdio.h> //debug

typedef struct s_data
{
    int             ants;
    char            *start;
    char            *end;
    unsigned int    p_start;
    unsigned int    p_end;
    char            *rooms;
    char            **names;
    int             **links;
    int             *weights;
    size_t          table_size;
    t_list          *paths;
}   t_data;

typedef struct s_path
{
    size_t          len;
    unsigned int    *nodes;
}   t_path;

/**
 * next_node - Retrieves the indices of nodes directly connected to a given node.
 * @data: Pointer to the t_data structure containing the adjacency matrix (links) and table size.
 * @pos: Index of the current node in the adjacency matrix.
 * 
 * This function scans the adjacency matrix row corresponding to `pos`, counts the number
 * of directly connected nodes (where link == 1), and returns a dynamically allocated array
 * of unsigned ints. The first element of the array contains the number of connected nodes,
 * followed by the indices of those nodes.
 * 
 * Return: A pointer to an array of unsigned int where:
 *         - [0] = number of connected nodes
 *         - [1..n] = indices of connected nodes
 *         The caller is responsible for freeing the returned array.
 */
unsigned int    *next_node(t_data * data, int pos);

int             contain_pos(unsigned int *positions, unsigned int pos, size_t len);
void            add_nodes_to_path(t_data *data);

//node_weight
void            init_weights(t_data *data, size_t size);
void            assign_weight(t_data *data);

//parser
int             is_int(char *str);
int             is_room(char *str);
int             is_link(char *str);


#endif
