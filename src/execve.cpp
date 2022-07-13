#include <sys/wait.h>

#include "../include/apue.h"

char *env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

void TestExecve() {
	pid_t pid;
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {	/* specify pathname, specify environment */
		if (execle("/bin/echo", "echo", "myarg1",
						"MY ARG2", (char *) 0, env_init) < 0) 
			err_sys("wait error");
	}

	if (waitpid(pid, NULL, 0) < 0) err_sys("wait error");
	if ((pid = fork()) < 0) err_sys("fork error");
	else if (pid == 0) {	/* specify filename, inherit envrionment */
		if (execlp("echo", "echo", "only 1 arg", (char *) 0) < 0)
			err_sys("execlp error");
	}
}

void TestParameter(int argc, char *argv[]) {
	int i;
	char **ptr;
	extern char **environ;
	for (i = 0; i < argc; ++i) { printf("argv[%d] = %s\n", i, argv[i]); }
	for (ptr = environ; *ptr != 0; ++ptr) 
		printf("environ: %s\n", *ptr);
}

int main(int argc, char *argv[]) {
	// TestExecve();
	TestParameter(argc, argv);
	return 0;
}
