#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_list
{
	char *str;
	struct s_list *next;
}		t_list;

char *get_next_line(int fd);

void	append(t_list **list, char *buf);
int find_newline(t_list *list);
t_list *find_last(t_list *list);
int newline_len(t_list *list);
void copy(t_list *list, char *line);
void dealloc(t_list **list, t_list *clean, char *buf);

#endif
