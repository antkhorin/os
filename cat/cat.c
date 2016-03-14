#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	ssize_t count;
	void *buf;
	const size_t BUF_SIZE = 256;
	buf = malloc(BUF_SIZE * sizeof(char));
	while (count = read(STDIN_FILENO, buf, BUF_SIZE))
	{
		write(STDOUT_FILENO, buf, count);
	}
	close(STDOUT_FILENO);
	free(buf);
	return 0;
}