#include "fdf.h"

int	render(t_vars *vars)
{
	int				x;
	int				y;
	t_vertex		vertex;
	t_vertex_map	*map;

	map = vars->map;
	y = 0;
	while (y < map->height - 1)
	{
		x = 0;
		while (x < map->width - 1)
		{
			vertex = get_vertex(map, x, y);
			project(vars, vertex, get_vertex(map, x + 1, y));
			project(vars, vertex, get_vertex(map, x, y + 1));
			x++;
		}
		y++;
	}
	vars->on_finished(vars, vars->render);
	return (0);
}
