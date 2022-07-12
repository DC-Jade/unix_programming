#include <cstdio>
#include <cstdlib>

#include <unistd.h>
#include <errno.h>
#include <string.h>

void TestGetpid() {
	printf("hello world from process ID %ld\n", (long) getpid());
}

void TestStrerror(char *argv[]) {
	fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
	errno = ENOENT;
	perror(argv[0]);
	exit(0);
}

// extern "C" int TestGetid() {
int TestGetid() {
	printf("uid = %d, gid = %d\n", getuid(), getgid());
	exit(0);
}


int main(char *argv[]) {
	// TestGetpid();
	// TestStrerror(argv);
	TestGetid();
}
