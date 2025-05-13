#ifndef PARSER_H
    #define PARSER_H

# include "./Libft/libft.h"
# include <stdio.h>

typedef struct s_data
{
    int     ants;
    char    *start;
    char    *end;
    char    *rooms;
    char    **names;
    int     **links;
    size_t    table_size;
}   t_data;

void ft_test(void);

#endif
