#include "fdf.h"

int	mouse_pressed_hook(int b, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (!vars->camera)
		return (0);
	if (b == SCROLL_UP || b == SCROLL_DOWN)
	{
		if (b == SCROLL_DOWN)
			vars->scroll_direction = -1;
		else if (b == SCROLL_UP)
			vars->scroll_direction = 1;
		on_scroll(vars, vars->scroll_direction);
	}
	return (1);
}
