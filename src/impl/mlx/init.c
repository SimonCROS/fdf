#include <math.h>

#include "mlx.h"

#include "fdf.h"

static int	init_mlx(t_vars *vars, char *file)
{
	char	*name;

	vars->mlx = mlx_init();
	vars->win = NULL;
	if (!vars->mlx)
		return (FALSE);
	init_window_size(vars);
	name = ft_strjoin("FdF - ", file);
	if (!name)
		return (FALSE);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, name);
	free(name);
	if (!vars->win)
		return (FALSE);
	return (TRUE);
}

void	reset_keys(t_vars *vars)
{
	vars->up = 0;
	vars->down = 0;
	vars->left = 0;
	vars->right = 0;
	vars->forward = 0;
	vars->backward = 0;
	vars->cam_up = 0;
	vars->cam_down = 0;
	vars->cam_left = 0;
	vars->cam_right = 0;
	vars->scroll_direction = 0;
}

void	init_window(char *file, t_vertex_map *map)
{
	t_vars	vars;

	vars.on_exit = (t_con)mlx_exit;
	vars.map = map;
	if (!init_mlx(&vars, file))
	{
		errno = -1;
		perror("Error\nCan't generate the frame");
		exit_fdf(&vars, NULL, EXIT_FAILURE);
		return ;
	}
	vars.init_image = (t_fun)mlx_init_image;
	vars.set_pixel = (t_pixel_writer)mlx_set_pixel;
	vars.on_finished = (t_bicon)force_put_image;
	vars.free_image = (t_bicon)mlx_free_image;
	vars.flush = 1;
	vars.camera = NULL;
	vars.render = NULL;
	launch_game(&vars);
}
