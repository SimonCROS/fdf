#include <fcntl.h>

#include "fdf.h"

static t_read_status	read_line(t_list *nds, int fd)
{
	int		result;
	char	*buffer;

	buffer = NULL;
	result = get_next_line(fd, &buffer);
	if (result < 0)
		return (READ_ERROR);
	else if (!lst_unshift(nds, as_listf((void **)ft_splitf(buffer, ' '), free)))
		return (READ_ERROR);
	if (result == 0)
		return (READ_EOF);
	return (READ_SUCCESS);
}

static int	read_lines(t_list *nodes, int fd)
{
	t_read_status	result;
	int				reading;

	result = READ_SUCCESS;
	reading = 0;
	while (result == READ_SUCCESS)
	{
		reading++;
		result = read_line(nodes, fd);
	}
	return (result != READ_ERROR);
}

int	read_file(char *file, t_list *nodes)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0 || !read_lines(nodes, fd))
	{
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}
