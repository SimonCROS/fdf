#include <fcntl.h>

#include "fdf.h"

void	*free_map(t_vertex_map *map)
{
	if (map)
		free(map->vertexs);
	free(map);
	return (NULL);
}

static int	parse_vertex_attrs(int *color, int *y, char *str)
{
	int		success;
	char	**parts;

	success = TRUE;
	if (ft_strcnt(str, ',') > 1)
		return (FALSE);
	parts = ft_split_first(str, ',');
	if (!parts)
		return (FALSE);
	if (!ft_atoi_full(parts[0], y))
		success = FALSE;
	if (!parts[1])
		*color = 0xffffff;
	else
	{
		ft_strtolower(parts[1]);
		if (!ft_starts_with(parts[1], "0x") || ft_strlen(parts[1]) != 8
			|| !ft_atohex_full(parts[1], color))
			success = FALSE;
	}
	free(parts[0]);
	free(parts[1]);
	free(parts);
	return (success);
}

static void	*to_vertex(char *str)
{
	int			y;
	int			color;
	t_vertex	*vertex;

	if (!parse_vertex_attrs(&color, &y, str))
	{
		free(str);
		return (NULL);
	}
	free(str);
	vertex = malloc(sizeof(t_vertex));
	if (!vertex)
		return (NULL);
	vertex->position.y = y;
	vertex->color = color_from_hex(color);
	return (vertex);
}

static int	fill_map(t_vertex_map *map, t_list *nodes, int width)
{
	t_list		*line;
	t_iterator	iter_y;
	t_iterator	iter_x;
	int			x;
	int			y;

	map->width = width;
	map->height = nodes->size;
	map->vertexs = malloc(sizeof(t_vertex) * map->width * map->height);
	if (!map->vertexs)
		return (FALSE);
	iter_y = iterator_new(nodes);
	y = map->height;
	while (iterator_has_next(&iter_y))
	{
		line = (t_list *)iterator_next(&iter_y);
		iter_x = iterator_new(line);
		y--;
		x = 0;
		while (iterator_has_next(&iter_x))
		{
			map->vertexs[x + y * width] = *(t_vertex *)iterator_next(&iter_x);
			map->vertexs[x + y * width].position.x = x;
			map->vertexs[x + y * width].position.z = y;
			x++;
		}
	}
	return (TRUE);
}

static int	parse_map(t_vertex_map *map, t_list *nodes)
{
	t_list		*line;
	t_iterator	iterator;
	int			width;
	int			success;

	iterator = iterator_new(nodes);
	success = 1;
	line = 0;
	width = 0;
	while (success && iterator_has_next(&iterator))
	{
		line = (t_list *)iterator_next(&iterator);
		if (width && width != line->size)
			return (FALSE);
		width = line->size;
		lst_map_in(line, (t_fun)to_vertex, free);
		success = !lst_contains(line, NULL, NULL);
	}
	lst_filter_in(nodes, (t_pre)lst_not_empty);
	if (success && width)
		success = fill_map(map, nodes, width);
	return (success && width);
}

static int	parse_file(t_vertex_map *map, char *file)
{
	t_list		*nodes;
	int			success;

	nodes = lst_new((t_con)lst_destroy);
	if (!nodes)
		return (FALSE);
	success = read_file(file, nodes) && parse_map(map, nodes);
	lst_destroy(nodes);
	return (success);
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
