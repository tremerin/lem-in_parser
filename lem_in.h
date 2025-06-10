#ifndef LEM_IN_H
    #define LEM_IN_H

# include "./Libft/libft.h"
# include <stdio.h> //debug

typedef struct s_path
{
    size_t          len;
    unsigned int    *nodes;
}   t_path;

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
    unsigned int    **weight_table;
    size_t          table_size;
    t_list          *paths;
    t_path          *all_paths;
    unsigned int    n_paths; //max paths
}   t_data;

//pathfinding
unsigned int    *next_node(t_data * data, int pos, size_t path);
int             contain_pos(unsigned int *positions, unsigned int pos, size_t len);

//node_weight
void            init_weights(t_data *data, size_t size);
void            assign_weight(t_data *data);
void            print_weight(t_data *data);
void            weight_table(t_data *data);
void            print_weights_table(t_data data);
void            number_of_paths(t_data *data);
void            path_finding(t_data *data);

//parser
int             is_int(char *str);
int             is_room(char *str);
int             is_link(char *str);


#endif
