#include "libft.h"

t_list	*as_list(void **array, t_consumer del)
{
	t_list	*list;

	if (!array)
		return (NULL);
	list = lst_new(del);
	if (!list)
		return (NULL);
	while (*array)
		lst_push(list, *(array++));
	return (list);
}

t_list	*as_listf(void **array, t_consumer del)
{
	t_list	*list;

	if (!array)
		return (NULL);
	list = as_list(array, del);
	if (!list)
		while (*array)
			del(*(array++));
	free(array);
	return (list);
}
