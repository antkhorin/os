#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	ssize_t count;
	void *buf;
	const size_t BUF_SIZE = 256;
	buf = malloc(BUF_SIZE * sizeof(char));
	int target = STDIN_FILENO;
	if (argv[1] != NULL){
		target = open(argv[1], O_RDONLY);
		if(target == -1) target = STDIN_FILENO;
	}
	while (count = read(target, buf, BUF_SIZE))
	{
		if (count == -1 && errno == EINTR) continue;
		else if (count <= 0) break;
		ssize_t written;
		while (written = write(STDOUT_FILENO, buf, count)){
			if (written == -1 && errno == EINTR) continue;
			else if (written <= 0) break;
			else if(written == count) break;
		}
	}
	close(STDOUT_FILENO);
	free(buf);
	return 0;
}