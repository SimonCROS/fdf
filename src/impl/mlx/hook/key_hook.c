#include "fdf.h"

int	key_pressed_hook(int i, t_vars *vars)
{
	if (i == K_ESC)
		exit_fdf(vars, EXIT_SUCCESS);
	if (i == K_W)
		vars->forward = 1;
	else if (i == K_S)
		vars->backward = 1;
	else if (i == K_A)
		vars->left = 1;
	else if (i == K_D)
		vars->right = 1;
	else if (i == K_ESP)
		vars->up = 1;
	else if (i == K_LSHIFT)
		vars->down = 1;
	else if (i == K_LEFT)
		vars->cam_left = 1;
	else if (i == K_RIGHT)
		vars->cam_right = 1;
	else if (i == K_UP)
		vars->cam_up = 1;
	else if (i == K_DOWN)
		vars->cam_down = 1;
	return (0);
}

int	key_released_hook(int i, t_vars *vars)
{
	if (i == K_W)
		vars->forward = 0;
	else if (i == K_S)
		vars->backward = 0;
	else if (i == K_A)
		vars->left = 0;
	else if (i == K_D)
		vars->right = 0;
	else if (i == K_ESP)
		vars->up = 0;
	else if (i == K_LSHIFT)
		vars->down = 0;
	else if (i == K_LEFT)
		vars->cam_left = 0;
	else if (i == K_RIGHT)
		vars->cam_right = 0;
	else if (i == K_UP)
		vars->cam_up = 0;
	else if (i == K_DOWN)
		vars->cam_down = 0;
	return (0);
}
