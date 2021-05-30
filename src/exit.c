#include "fdf.h"

void	exit_fdf(t_vars *vars, void *other, int __status)
{
	if (vars->render)
		vars->free_image(vars->render, vars);
	free(vars->camera);
	vars->on_exit(vars);
	free_map(vars->map);
	free(other);
	exit(__status);
}
