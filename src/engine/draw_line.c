#include "fdf.h"
#include "graphics.h"

void	draw_line(t_vars *vars, t_line ln, t_color color, float dist)
{
	t_vec2i	d;
	t_vec2i	s;
	int		err;
	int		e2;
	float	*buf;

	d = (t_vec2i){abs(ln.to.x - ln.from.x), -abs(ln.to.y - ln.from.y)};
	s = (t_vec2i){2 * (ln.from.x < ln.to.x) - 1, 2 * (ln.from.y < ln.to.y) - 1};
	err = d.x + d.y;
	while (ln.from.x != ln.to.x || ln.from.y != ln.to.y)
	{
		if (ln.from.x >= 0 && ln.from.x < WIDTH
			&& ln.from.y >= 0 && ln.from.y < HEIGHT)
		{
			buf = get_z_buffer_value(vars->z_buffer, ln.from.x, ln.from.y,
					WIDTH);
			if (*buf > dist)
			{
				*buf = dist;
				vars->set_pixel(vars->render, ln.from.x, ln.from.y, color);
			}
		}
		e2 = 2 * err;
		if (e2 >= d.y)
		{
			err += d.y;
			ln.from.x += s.x;
		}
		if (e2 <= d.x)
		{
			err += d.x;
			ln.from.y += s.y;
		}
	}
}
