#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "../include/apue.3e/include/apue.h"

void TestLseek() {
	if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) 
		printf("cannot seek\n");
	else 
		printf("seek OK\n");
	exit(0);
}

void TestCreate() {
	char buf1[] = "abcdefghij";
	char buf2[] = "ABCDEFGHIJ";
	int fd;
	if ((fd = creat("file.hole", FILE_MODE)) < 0)
		err_sys("creat error");
	
	if (write(fd, buf1, 10) != 10)
		err_sys("buf1 write error");
	/* offset now = 10 */

	if (lseek(fd, 16384, SEEK_SET) == -1) 
		err_sys("lseek error");
	/* offset now = 16384 */

	if (write(fd, buf2, 10) != 10) 
		err_sys("buf2 write error");
	/* offset now = 16394 */

	exit(0);
}

int main() {
	TestLseek();
	TestCreate();
}
