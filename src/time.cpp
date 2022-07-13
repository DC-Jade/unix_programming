#include <fcntl.h>
#include <time.h>

#include "../include/apue.h"

void TestTime(int argc, char *argv[]) {
	int fd;
	struct stat statbuf;
	struct timespec times[2];

	for (int i = 1; i < argc; ++i) {
		if (stat(argv[i], &statbuf) < 0) { /* fetch cyrrent time */
			err_ret("%s: stat error", argv[i]);
			continue;
		}
		if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) { /* truncate  */
			err_ret("%s: open error", argv[i]);
			continue;
		}
		times[0] = statbuf.st_atim;
		times[1] = statbuf.st_mtim;
		if (futimens(fd, times) < 0) /* reset times */
			err_ret("%s: futimens error", argv[i]);
		close(fd);
	}
}

void TestTime2() {
	time_t t;
	printf("time = %s\n", time(&t));
}

int main(int argc, char *argv[]) {
	// TestTime(argc, argv);
	TestTime2();
	return 0;
}
