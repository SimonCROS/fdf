#include "fdf.h"

t_vertex	get_vertex(t_vertex_map *map, int x, int y)
{
	return (map->vertexs[x + y * map->width]);
}

int	ft_atohex_full(char *str, int *result)
{
	int	ret;

	ret = 0;
	if (ft_starts_with(str, "0x"))
		str += 2;
	while ((*str >= '0' && *str <= '9') || (*str >= 'a' && *str <= 'f'))
	{
		ret *= 16;
		if (*str >= 'a')
			ret += *str - 'a' + 10;
		else
			ret += *str - '0';
		if (ret < 0)
			return (0);
		str++;
	}
	*result = ret;
	return (!(*str));
}

char	**ft_split_first(char *s, char c)
{
	char	**parts;
	int		i;

	parts = malloc(sizeof(*parts) * 2);
	if (!parts)
		return (NULL);
	i = ft_strindex_of(s, c);
	parts[1] = NULL;
	if (i == -1)
	{
		parts[0] = ft_strdup(s);
		if (!parts[0])
			free(parts);
	}
	else
	{
		parts[0] = ft_substr(s, 0, i);
		parts[1] = ft_strdup(s + i + 1);
		if (!parts[0] || !parts[1])
		{
			free(parts[0]);
			free(parts[1]);
			free(parts);
			return (NULL);
		}
	}
	return (parts);
}
