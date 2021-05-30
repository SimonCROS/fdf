#include "fdf.h"

int	render(t_vars *vars)
{
	t_vertex_map	*map;

	map = vars->map;
	(void)map;
	t_vec3f v1 = vec3_new(0,0,0);
	t_vec3f v2 = vec3_new(2,0,0);
	t_vec3f v3 = vec3_new(2,0,2);
	t_color co = color_new(255, 255, 255);
	project(vars, (t_vertex){v1, co}, (t_vertex){v2, co});
	project(vars, (t_vertex){v2, co}, (t_vertex){v3, co});
	vars->on_finished(vars, vars->render);
	return (0);
}
