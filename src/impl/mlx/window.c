#include "mlx.h"

#include "fdf.h"

#if defined __APPLE__

void	mlx_exit(t_vars *vars)
{
	if (vars->mlx)
		if (vars->win)
			mlx_destroy_window(vars->mlx, vars->win);
}

#elif defined __linux__

void	mlx_exit(t_vars *vars)
{
	if (vars->mlx)
	{
		if (vars->win)
			mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
}

#endif

void	init_window_size(t_vars *vars)
{
	int		max_width;
	int		max_height;

	mlx_get_screen_size(vars->mlx, &max_width, &max_height);
	vars->screen = bounding_box_from((t_vec2i){}, (t_vec2i){WIDTH, HEIGHT});
}
