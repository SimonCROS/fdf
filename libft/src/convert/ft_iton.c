#include "libft.h"

char	*ft_itoa(int n)
{
	long int	len;
	long int	nbr;
	char		*str;

	nbr = n;
	len = ft_intlen(nbr) + 1;
	str = malloc(len);
	if (!str)
		return (NULL);
	if (n < 0)
		nbr *= -1;
	str[--len] = 0;
	while (1)
	{
		str[--len] = (nbr % 10) + '0';
		if (!nbr)
			break ;
		nbr /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

char	*ft_uitoa(unsigned int n)
{
	int		len;
	char	*str;

	len = ft_intlen(n) + 1;
	str = malloc(len);
	if (!str)
		return (NULL);
	str[len] = 0;
	return (ft_uitoa_to(n, str));
}

char	*ft_itohex(unsigned int n, int prefix)
{
	int		len;
	char	*str;

	len = ft_intlen_hex(n, prefix, 0) + 1;
	str = malloc(len);
	if (!str)
		return (NULL);
	str[len] = 0;
	return (ft_itohex_to(n, str, prefix));
}

char	*ft_itooctal(unsigned int n)
{
	int		len;
	char	*str;

	len = ft_intlen_octal(n) + 1;
	str = malloc(len);
	if (!str)
		return (NULL);
	str[len] = 0;
	return (ft_itooctal_to(n, str));
}
