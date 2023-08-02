#include "get_next_line.h"

void dealloc(t_list **list, t_list *clean, char *buf)
{
	t_list *tmp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean)
	{
		if (clean->str[0])
			*list = clean;
		else
		{
			free(buf);
			free(clean);
		}
	}
}

void copy(t_list *list, char *line)
{	
	int i;
	int j;

	if (list == NULL || line == NULL)
		return ;
	
	j = 0;
	while (list)
	{
		i = 0;
		while (list->str[i])
		{
			if (list->str[i] == '\n')
			{
				line[j] = list->str[i];
				j++;
				line[j] = '\0';
				return ;
			}
			line[j] = list->str[i];
			j++;
			i++;
		}
		list = list->next;
	}
	line[j] = '\0';
}

int newline_len(t_list *list)
{
	int len;
	int i;
	t_list *curr;
	
	if (list == NULL)
		return (0);
	curr = list;
	len = 0;
	while(curr)
	{
		i = 0;
		while (curr->str[i])
		{
			if (curr->str[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		curr = curr->next;
	}
	return (len);
}

int find_newline(t_list *list)
{
	t_list *curr;
	int i;
	
	i = 0;
	curr = list;
	if (curr == NULL)
		return (0);
	while(curr)
	{
		while (curr->str[i])
		{
			if (curr->str[i] == '\n')
				return (1);
			i++;
		}
		curr = curr->next;
		i = 0;
	}
	return (0);
}

t_list *find_last(t_list *list)
{
	t_list *curr;
	
	curr = list;
	if (curr == NULL)
		return (NULL);
	while (curr->next != NULL)
		curr = curr->next;
	return (curr);
}

void	append(t_list **list, char *buf)
{
	t_list *new;
	t_list *last;

	last = find_last(*list);
	new = (t_list *)malloc(sizeof (t_list));
	if (new == NULL)
		return ;
	if (last == NULL)
		*list = new;
	else
		last->next = new;
	new->str = buf;
	new->next = NULL;
}


