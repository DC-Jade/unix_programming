#include <sys/wait.h>

#include "../include/apue.h"

void TestInterpreter() {
	pid_t pid;
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) { /* child  */
		if (execl("echo.sh", "echo", "myarg1", "MY ARG2", (char *) 0) < 0)
			err_sys("execl error");
	}
	if (waitpid(pid, NULL, 0) < 0)	/* parent */
		err_sys("waitpid error");
}

int main(void) {
	TestInterpreter();
	return 0;
}

