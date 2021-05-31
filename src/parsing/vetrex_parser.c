#include "fdf.h"

static int	parse_vertex_attrs(int *color, int *y, char *str)
{
	int		success;
	char	**parts;

	success = TRUE;
	if (ft_strcnt(str, ',') > 1)
		return (FALSE);
	parts = ft_split_first(str, ',');
	if (!parts)
		return (FALSE);
	if (!ft_atoi_full(parts[0], y))
		success = FALSE;
	if (!parts[1])
		*color = 0xffffff;
	else
	{
		ft_strtolower(parts[1]);
		if (!ft_starts_with(parts[1], "0x") || ft_strlen(parts[1]) != 8
			|| !ft_atohex_full(parts[1], color))
			success = FALSE;
	}
	free(parts[0]);
	free(parts[1]);
	free(parts);
	return (success);
}

void	*to_vertex(char *str)
{
	int			y;
	int			color;
	t_vertex	*vertex;

	if (!parse_vertex_attrs(&color, &y, str))
	{
		free(str);
		return (NULL);
	}
	free(str);
	vertex = malloc(sizeof(t_vertex));
	if (!vertex)
		return (NULL);
	vertex->position.y = y;
	vertex->color = color_from_hex(color);
	return (vertex);
}
