#include <math.h>

#include "fdf.h"

static int	convert_to_raster(t_vec2f *vertexRaster, t_camera *camera, t_vec3f vertexWorld)
{
	t_vec3f	vertexView;
	t_vec3f	vertexCamera;
	t_vec2f	vertexScreen;
	t_vec2f	vertexNDC;
	int		behind;

	vertexView = vec3_normalize(vec3_sub(camera->position, vertexWorld));
	vertexCamera = mat44_mul_vec(camera->w2c, vertexView);
	behind = vertexCamera.z < 0;
	vertexCamera.z = fabsf(vertexCamera.z);
	vertexScreen.x = -vertexCamera.x / camera->hlen / (WIDTH
			/ (float)HEIGHT) / vertexCamera.z;
	vertexScreen.y = -vertexCamera.y / camera->hlen / vertexCamera.z;
	vertexNDC.x = (vertexScreen.x + 1) * 0.5;
	vertexNDC.y = (vertexScreen.y - 1) * -0.5;
	vertexRaster->x = vertexNDC.x * WIDTH - 0.5;
	vertexRaster->y = vertexNDC.y * HEIGHT - 0.5;
	return (behind);
}

void	project(t_vars *vars, t_vertex v1, t_vertex v2)
{
	t_vec2f			p[3];
	t_camera		*cam;
	t_bounding_box	box;
	int				behind;

	cam = vars->camera;
	behind = convert_to_raster(p, vars->camera, v1.position) || convert_to_raster(p + 1, vars->camera, v2.position);
	if (behind)
		return ;
	box = bounding_box_fromf(p[0], p[1]);
	if (bounding_box_intersects(box, vars->screen))
		draw_line(vars, line_fromf(p[0], p[1]), v1.color);
}
