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
    size_t  i;
    size_t  dash;

    i = 0;
    dash = 0;
    if (str[i] == ' ' || str[i] == '-')
        return (0);
    while (str[i]) 
    {
        if (str[i] == '-' && dash == 0)
        {
            dash++;
            //check room name
        }
        i++;
    }
    if (dash != 1)
        return (0);

    return (1);
}

char *get_name(char *room)
{
    char    *name;
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    while (room[i] != ' ')
        i++;
    name = malloc((i + 1) * sizeof(char));
    while (j < i)
    {
        name[j] = room[j];
        j++;
    }
    name[j] = 0;
    printf("get name: %s\n", name);
    return (name);
}

void make_table(t_data *data)
{
    char **rooms = ft_split(data->rooms, '\n');
    int i = 0;
    printf("create table\n");
    while (rooms[i])
    {
        printf("room: %s\n", rooms[i]);
        i++;
    }
    printf("total rooms: %i\n", i);
    data->names = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (rooms[i])
    {
        data->names[i] = get_name(rooms[i]);
        printf("stored: %s\n", data->names[i]);
        i++;
    }
    data->names[i] = '\0';
    printf("table 0: %s\n", data->names[0]);
    printf("table 1: %s\n", data->names[1]);
    printf("table 2: %s\n", data->names[2]);
}

int main(void)
{
    char    *str;
    char    *link_str;
    int     start;
    int     end;
    int     create_table;
    t_data  data;


    data.rooms = ft_strdup("");
    data.links = NULL;
    start = 0;
    end = 0;
    create_table = 0;
    str = get_next_line(0);
    link_str = ft_strdup("");
    if (is_int(str))
        data.ants = ft_atoi(str);
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
            data.start = ft_strdup(str);
            start++;
        }
        //check end
        if (end == 0 && ft_strncmp(str, "##end\n", 7) == 0)
            end++;
        else if (end == 1)
        {
            data.end = ft_strdup(str);
            end++;
        }
        ft_putstr_fd(str, 1);
        //check room
        if (is_room(str))
            data.rooms = ft_strjoin(data.rooms, str);
        //check link
        if (is_link(str))
        {
            create_table++;
            if (create_table == 1)
            {
                make_table(&data);
            }
            link_str = ft_strjoin(link_str, str);

        }
        free(str);
        str = get_next_line(0);
    }
    printf("\nAnts: %d\n", data.ants);
    printf("Start: %s", data.start);
    printf("End: %s", data.end);
    printf("Rooms:\n%s", data.rooms);
    printf("Links:\n%s\n", link_str);
    printf("data->names:\n");
    int i = 0;
    while (data.names[i])
    {
        printf("%s.\n", data.names[i]);
        i++;
    }
    printf("%s\n", data.names[0]);
    printf("%s\n", data.names[1]);
    printf("%s\n", data.names[2]);
    return (0);
}