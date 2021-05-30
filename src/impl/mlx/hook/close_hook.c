#include "fdf.h"

int	close_hook(t_vars *vars)
{
	exit_fdf(vars, EXIT_SUCCESS);
	return (TRUE);
}
