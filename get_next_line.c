#include <stdio.h>
#include "get_next_line.h"

static void	create_list(t_list **list, int fd)
{
	int read_bytes;
	char *buf;

	while(!find_newline(*list))
	{	
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (!read_bytes)
		{
			free(buf);
			return ;
		}
		buf[read_bytes] = '\0';
		append(list, buf);
	}
}

static char *get_line(t_list *list)
{
	int len;
	char *line;

	len = newline_len(list);
	line = (char *)malloc(sizeof (char) * (len + 1));
	if (line  == NULL)
		return (NULL);
	copy(list, line);
	return (line);
}

static void	clear_list(t_list **list)
{	
	t_list *last;
	t_list *clean;
	char *buf;
	int i;
	int j;

	clean = malloc(sizeof (t_list));
	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL || clean == NULL)
		return ;
	last = find_last(*list);
	i = 0;
	j = 0;
	while (last->str[i] != '\n' && last->str[i] != '\0')
		i++;
	while (last->str[i] != '\0' && last->str[++i])
		buf[j++] = last->str[i];
	buf[j] = '\0';
	clean->str = buf;
	clean->next = NULL;
	dealloc(list, clean, buf);
}

char *get_next_line(int fd)
{
	static	t_list *list = NULL;
	char *line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, line, 0) < 0)
	{
		dealloc(&list, NULL, line);
		return (NULL);
	}
	create_list(&list, fd);	
	if (list == NULL)
		return (NULL);
	line =	get_line(list);
	if (line == NULL)
		return (NULL);
	clear_list(&list);
	return (line);
}
