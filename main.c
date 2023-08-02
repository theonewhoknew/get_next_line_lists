#include "get_next_line.h"

int main(void)
{
	int fd;
	char *next;

	fd = open("txat", O_RDONLY);
	next = get_next_line(fd);
	printf("%s", next);
	free(next);
	close(fd);
}