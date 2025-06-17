#include "lem_in.h"

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
    init_weights(data, i);
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

void    free_data(t_data *data)
{
    size_t i = 0;
    while (i < data->table_size)
    {
        free(data->names[i]);
        free(data->links[i]);
        i++;
    }
    free(data->names);
    free(data->links);
    free(data->rooms);
    free(data->start);
    free(data->end);
}

void print_int(int i)
{
    printf("i = %d", i);
}


int main(void)
{
    char    *str;
    //char    *link_str;
    char    *tmp;
    int     start;
    int     end;
    int     create_table;
    size_t  i = 0;
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
            data.p_start = i;
            start++;
        }
        //check end
        if (end == 0 && ft_strncmp(str, "##end\n", 7) == 0)
            end++;
        else if (end == 1)
        {
            data.end = ft_strdup(str);
            data.p_end = i;
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
            i++;
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
    printf("start pos: %d, end pos: %d\n", data.p_start, data.p_end);

    //find paths
    //t_list *paths = NULL;
    data.paths = NULL;
    t_path *path = malloc(sizeof(t_path));
    path->len = 1;
    path->nodes = malloc(sizeof(unsigned int) * path->len); 
    path->nodes[0] = data.p_start;
    //t_list *node = ft_lstnew(path);
    ft_lstadd_back(&data.paths, ft_lstnew(path));
    //print last node
    //t_path *p = (t_path *)data.paths->content;
    //printf("len: %d\n", p->nodes[0]);
    //next
    //unsigned int *nexts = next_node(&data, path->nodes[path->len -1]);
    //printf("next len: %u\n", nexts[0]);
    //add_nodes_to_path(&data);
    assign_weight(&data);
    print_weight(&data);
    weight_table(&data);
    print_weights_table(data);
    number_of_paths(&data);
    printf("paths: %u\n", data.n_paths);
    //assing_multiplier(&data);
    //print_multipliers(data);
    path_finding(&data);
    free_data(&data);
    return (0);
}

