int	ft_isascii(int c)
{
	if (c < 0 || c > 127)
		return (0);
	return (1);
}
