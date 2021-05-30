#include "mlx.h"

#include "fdf.h"

void	force_put_image(t_vars *vars, t_image *image)
{
	mlx_put_image_to_window(vars->mlx, vars->win, image->img, 0, 0);
	mlx_do_sync(vars->mlx);
}
