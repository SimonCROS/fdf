#include <stdio.h>

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vertex_map	*map;

	if (argc != 2)
	{
		perror("Error\nUnable to parse program arguments");
		exit(EXIT_FAILURE);
	}
	map = parse(argv[1]);
	if (!map)
	{
		perror("Error\nAn error occurred while parsing the file");
		exit(EXIT_FAILURE);
	}
	init_window(argv[1], map);
	exit(EXIT_SUCCESS);
}
