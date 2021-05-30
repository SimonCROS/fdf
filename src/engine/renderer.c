#include "fdf.h"

int	render(t_vars *vars)
{
	int				x;
	int				y;
	t_vertex		vertex;
	t_vertex_map	*map;

	map = vars->map;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			vertex = get_vertex(map, x, y);
			if (x < map->width - 1)
				project(vars, vertex, get_vertex(map, x + 1, y));
			if (y < map->height - 1)
				project(vars, vertex, get_vertex(map, x, y + 1));
			x++;
		}
		y++;
	}
	vars->on_finished(vars, vars->render);
	return (0);
}
