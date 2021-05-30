#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vertex_map	*map;

	log_msg(INFO, "Starting program...");
	if (argc != 2)
	{
		errno = EINVAL;
		perror("Error\nUnable to parse program arguments");
		exit(EXIT_FAILURE);
	}
	map = parse(argv[1]);
	if (!map)
	{
		log_msg(FATAL, "An error occurred while parsing the file");
		perror("Error\nAn error occurred while parsing the file");
		exit(EXIT_FAILURE);
	}
	log_msg(INFO, "Parsing finished");
	init_window(argv[1], map);
	exit(EXIT_SUCCESS);
}
