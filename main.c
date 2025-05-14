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
    //printf("num1: %s,num2: %s\n", num_one, num_two);
    if (!is_int(num_one) || !is_int(num_two))
    {
        free(num_one);
        free(num_two);
        return (0);
    }
    free(num_one);
    free(num_two);
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
    return (name);
}

//adjacency matrix
void make_table(t_data *data)
{
    char **rooms = ft_split(data->rooms, '\n');
    size_t i = 0;
    size_t j = 0;

    while (rooms[i])
    {
        //printf("room: %s\n", rooms[i]);
        i++;
    }
    data->names = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (rooms[i])
    {
        data->names[i] = get_name(rooms[i]);
        i++;
    }
    data->names[i] = '\0';
    data->table_size = i;
    data->links = malloc(sizeof(int *) * i);
    i = 0;
    while (i < data->table_size)
    {
        j = 0;
        data->links[i] = malloc(sizeof(int) * data->table_size);
        while (j < data->table_size)
        {
            data->links[i][j] = 0;
            j++;
        }
        i++;
    }
    i = 0;
    while (rooms[i])
    {
        free(rooms[i]);
        i++;
    }
    free(rooms);
}

void print_table(t_data data)
{
    size_t i;
    size_t j;
    size_t len = 0;
    i = 0;
    //printf("print table\n");
    len += printf("      | ");
    while (i < data.table_size)
    {
        len += printf("%-6s", data.names[i]);
        i++;
    }
    printf("\n");
    i = 0;
    while (i < len)
    {
        printf("=");
        i++;
    }
    printf("\n");
    i = 0;
    while (i < data.table_size)
    {
        j = 0;
        //printf("size %ld\n", data.table_size);
        printf("%-5s | ", data.names[i]);
        while (j < data.table_size)
        {
            printf("%-5d ", data.links[i][j]);
            j++;
        }
        i++;
        printf("\n");
    }
}

void read_link(t_data *data, char *link)
{
    //printf("read link: %s", link);
    char    *node_one;
    char    *node_two;
    size_t  i = 0;
    size_t  len = ft_strlen(link);
    int     pos_name_one;
    int     pos_name_two;

    if (link[len -1] == '\n')
        len--;
    while (link[i])
    {
        if (link[i] == '-')
        {
            node_one = ft_substr(link, 0, i);
            node_two = ft_substr(link, i + 1, len - (i+1));
        }
        i++;
    }
    //printf("one: %s$\ntwo: %s$\n", node_one, node_two);
    i = 0;
    while (i < data->table_size)
    {
        if (ft_strncmp(data->names[i], node_one, ft_strlen(node_one)) == 0)
            pos_name_one = i;
        else if (ft_strncmp(data->names[i], node_two, ft_strlen(node_two)) == 0)
            pos_name_two = i;
        i++;
    }
    //printf("one: %d, two: %d\n", pos_name_one, pos_name_two);
    data->links[pos_name_one][pos_name_two] = 1;
    data->links[pos_name_two][pos_name_one] = 1;
    free(node_one);
    free(node_two);
}

int main(void)
{
    char    *str;
    //char    *link_str;
    char    *tmp;
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
    //link_str = ft_strdup("");
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
        //ft_putstr_fd(str, 1);
        //check room

        if (is_room(str))
        {
            tmp = ft_strdup(data.rooms);
            free(data.rooms);
            data.rooms = ft_strjoin(tmp, str);
            free(tmp);
        }
        //check link
        if (is_link(str))
        {
            create_table++;
            if (create_table == 1)
            {
                make_table(&data);
            }
            //link_str = ft_strjoin(link_str, str);
            //read link
            read_link(&data, str);
        }
        free(str);
        str = get_next_line(0);
    }
    // printf("\nAnts: %d\n", data.ants);
    // printf("Start: %s", data.start);
    // printf("End: %s", data.end);
    // printf("Rooms:\n%s", data.rooms);
    // printf("Links:\n%s\n", link_str);
    // printf("data->names:\n");
    // int i = 0;
    // while (data.names[i])
    // {
    //     printf("%s$\n", data.names[i]);
    //     i++;
    // }
    print_table(data);
    size_t  i = 0;
    while (i < data.table_size)
    {
        free(data.links[i]);
        free(data.names[i]);
        i++;
    }
    free(data.links);
    free(data.names);
    free(data.rooms);
    free(data.start);
    free(data.end);

    return (0);
}