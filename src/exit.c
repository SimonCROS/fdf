#include "fdf.h"

void	exit_fdf(t_vars *vars, int __status)
{
	if (vars->render)
		vars->free_image(vars->render, vars);
	free(vars->z_buffer);
	free(vars->camera);
	vars->on_exit(vars);
	free_map(vars->map);
	exit(__status);
}
