#ifndef PARSER_H
    #define PARSER_H

# include "./Libft/libft.h"
# include <stdio.h>

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
    size_t          table_size;
}   t_data;

typedef struct s_path
{
    size_t          len;
    unsigned int    *nodes;
}   t_path;


void ft_test(void);

#endif
