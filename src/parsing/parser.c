#include <fcntl.h>

#include "fdf.h"

static void	*free_map(t_vertex_map *map)
{
	int	line;

	line = 0;
	if (map)
	{
		if (map->vertexs)
			while (line < map->height)
				free(map->vertexs[line++]);
		free(map->vertexs);
	}
	free(map);
	return (NULL);
}

static t_read_status	read_line(t_list *lne, int fd)
{
	int		result;
	char	*buffer;

	buffer = NULL;
	result = get_next_line(fd, &buffer);
	if (result < 0)
		return (READ_ERROR);
	if (*buffer == '#')
		free(buffer);
	else if (!lst_unshift(lne, as_listf((void **)ft_splitf(buffer, ' '), free)))
	{
		errno = -1;
		return (READ_ERROR);
	}
	if (result == 0)
		return (READ_EOF);
	return (READ_SUCCESS);
}

static int	parse_lines(t_list **vertexs, int fd)
{
	int	width;

	width = 0;
	while (get_next_line())
	{
		/* code */
	}
	
}

static int	parse_file(t_vertex_map *map, char *file)
{
	int		fd;
	t_list	**vertexs;

	vertexs = lst_new(lst_destroy);
	if (vertexs)
		return (FALSE);
	fd = open(file, O_RDONLY);
	if (fd < 0 || !parse_lines(vertexs, fd))
	{
		lst_destroy(vertexs);
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

t_vertex_map	*parse(char *file)
{
	t_vertex_map	*map;

	if (ft_strlen(file) < 5 || !ft_ends_with(file, ".fdf"))
	{
		errno = -1;
		log_msg(ERROR, "File is not a \".fdf\" file.");
		return (NULL);
	}
	if (!file)
		return (NULL);
	map = malloc(sizeof(t_vertex_map));
	if (!map)
		return (NULL);
	map->vertexs = NULL;
	if (!parse_file(map, file))
		return (free_map(map));
	return (map);
}
