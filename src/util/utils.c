#include "fdf.h"

t_vertex	get_vertex(t_vertex_map *map, int x, int y)
{
	return (map->vertexs[x + y * map->width]);
}
