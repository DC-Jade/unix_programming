#include "../include/apue.h"

int globvar = 6;
char buf[] = "a write to stdout\n";

void TestFork() {
	int var;
	pid_t pid;
	var = 88;
	if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
		err_sys("write error");
	printf("before fork\n");
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {	/* child  */
		++globvar;
		++var;
	} else {
		sleep(2);							/* parent */
	}
	printf("pid = %ld, glob = %d, var = %d\n", (long) getpid(), globvar, var);
}

static void charatatime(char *str);

void TestFork2() {
	pid_t pid;
	if ((pid = fork()) < 0) { err_sys("fork error"); }
	else if (pid == 0) { charatatime("ouput from child\n"); }
	else { charatatime("output from parent\n"); }
}

void charatatime(char *str) {
	char *ptr;
	int c;
	setbuf(stdout, NULL);				/* set unbuffered */
	for (ptr = str; (c = *ptr++) != 0; )
		putc(c, stdout);
}

int main(void) {
	// TestFork();
	TestFork2();
}
