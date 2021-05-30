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
	{
		errno = -1;
		return (READ_ERROR);
	}
	if (result == 0)
		return (READ_EOF);
	return (READ_SUCCESS);
}

static int	read_lines(t_list *nodes, char *file, int fd)
{
	t_read_status	result;
	int				reading;

	result = READ_SUCCESS;
	reading = 0;
	while (result == READ_SUCCESS)
	{
		if (!(reading % 1000))
		{
			log_msg_arg(INFO, "\033[33m< Reading\033[0m %s...", file);
			log_prev_line();
		}
		reading++;
		result = read_line(nodes, fd);
	}
	return (result != READ_ERROR);
}

int	read_file(char *file, t_list *nodes)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0 || !read_lines(nodes, file, fd))
	{
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}
