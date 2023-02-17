#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";

int main(int argc, char * argv[])
{
	int		fd;

	if ((fd = creat("file.hole", 0600)) < 0)
		perror("creat error");

	if (write(fd, buf1, 10) != 10)
		perror("buf1 write error");
	/* offset now = 10 */

	if (lseek(fd, 16384, SEEK_SET) == -1)
		perror("lseek error");
	/* offset now = 16384 */

	if (write(fd, buf2, 10) != 10)
		perror("buf2 write error");
	/* offset now = 16394 */

	exit(0);
}

