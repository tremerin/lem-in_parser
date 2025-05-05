# include "parser.h"

int is_int(char *str)
{
    while (*str && *str != '\n')
    {
        if (!ft_isdigit(*str))
                return (0);
        str++;
    }
    return (1);
}

int is_room(char *str)
{
    size_t  i;
    size_t  space_one;
    size_t  space_two;

    i = space_one = space_two = 0;
    if (str[0] == 'L' || str[0] == '#' || str[0] == ' ')
        return (0);
    while (str[i] && str[i] != '\n')
    {
        if (str[i] == ' ')
        {
            if (space_one == 0)
                space_one = i + 1;
            else if (space_two == 0)
                space_two = i + 1;
            else
                return (0);
        } 
        i++;
    }
    if (space_two == 0)
        return (0);
    char * num_one = ft_substr(str, space_one, (space_two - space_one) -1);
    char * num_two = ft_substr(str, space_two, (ft_strlen(str) - space_two) -1);
    printf("num1: %s,num2: %s\n", num_one, num_two);
    if (!is_int(num_one) || !is_int(num_two))
    {
        free(num_one);
        free(num_two);
        return (0);
    }
    return (1);
}

int is_link(char *str)
{
    printf("%s", str);
    return (1);
}

int main(void)
{
    char    *str;
    int     start;
    int     end;
    t_data  *data;

    data = malloc(sizeof(t_data));
    data->rooms = ft_strdup("");
    data->links = NULL;
    start = 0;
    end = 0;
    str = get_next_line(0);
    if (is_int(str))
        data->ants = ft_atoi(str);
    while (str)
    {
        //void line
        if (ft_strlen(str) == 1)
            break ;
        //check start
        if (start == 0 && ft_strncmp(str, "##start\n", 9) == 0)
            start++;
        else if (start == 1)
        {
            data->start = ft_strdup(str);
            start++;
        }
        //check end
        if (end == 0 && ft_strncmp(str, "##end\n", 7) == 0)
            end++;
        else if (end == 1)
        {
            data->end = ft_strdup(str);
            end++;
        }
        ft_putstr_fd(str, 1);
        //check room
        if (is_room(str))
            data->rooms = ft_strjoin(data->rooms, str);
        //check link
        if (is_link(str))
            printf("link ");
        free(str);
        str = get_next_line(0);
    }
    printf("\nAnts: %d\n", data->ants);
    printf("Start: %s", data->start);
    printf("End: %s", data->end);
    printf("Rooms: %s", data->rooms);
    return (0);
}