#include "fdf.h"

int	log_prev_line(void)
{
	return (printf("\033[A\33[2K\r"));
}

int	log_cr(void)
{
	return (printf("\033[0m\r"));
}

int	log_nl(void)
{
	return (printf("\033[0m\n"));
}

int	log_msg(t_log_type type, char *str)
{
	int		len;

	if (type == INFO)
		len = printf("\033[0m[INFO]: ");
	else if (type == WARN)
		len = printf("\033[33m[WARN]: ");
	else if (type == ERROR)
		len = printf("\033[1;31m[ERROR]: ");
	else if (type == FATAL)
		len = printf("\033[31m[FATAL]: ");
	else
		return (0);
	if (str)
		len += printf("%s\033[0m\n", str);
	return (len);
}

int	log_msg_arg(t_log_type type, char *str, const char *arg)
{
	int		len;

	if (type == INFO)
		len = printf("\033[0m[INFO]: ");
	else if (type == WARN)
		len = printf("\033[33m[WARN]: ");
	else if (type == ERROR)
		len = printf("\033[1;31m[ERROR]: ");
	else if (type == FATAL)
		len = printf("\033[31m[FATAL]: ");
	else
		return (0);
	if (str)
		len += printf(str, arg);
	log_nl();
	return (len);
}
