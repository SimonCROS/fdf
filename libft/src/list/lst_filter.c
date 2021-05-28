#include "libft.h"

t_list	*lst_filter(t_list *list, t_predicate filter)
{
	t_entry	*entry;
	t_list	*copy;

	copy = lst_new(list->del);
	if (!copy)
		return (NULL);
	if (lst_is_empty(list))
		return (copy);
	entry = list->first;
	if (filter(entry->value))
		lst_push(copy, entry->value);
	while (entry->next)
	{
		entry = entry->next;
		if (filter(entry->value))
			lst_push(copy, entry->value);
	}
	return (copy);
}

t_list	*lst_filter_in(t_list *list, t_predicate filter)
{
	t_entry	*entry;
	t_list	tmp;

	if (lst_is_empty(list))
		return (list);
	tmp = *list;
	list->size = 0;
	list->first = NULL;
	entry = tmp.first;
	if (filter(entry->value))
	{
		lst_push(list, entry->value);
		entry->value = NULL;
	}
	while (entry->next)
	{
		entry = entry->next;
		if (filter(entry->value))
		{
			lst_push(list, entry->value);
			entry->value = NULL;
		}
	}
	lst_clear(&tmp);
	return (list);
}
