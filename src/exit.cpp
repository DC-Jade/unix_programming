#include "../include/apue.h"

static void my_exit1(void);
static void my_exit2(void);
static void my_exit3(void);

void TestExit() {
	if (atexit(my_exit1) != 0) err_sys("can't register my_exit1");
	if (atexit(my_exit2) != 0) err_sys("can't register my_exit2");
	if (atexit(my_exit3) != 0) err_sys("can't register my_exit1");
	printf("TestExit done\n");
}

static void my_exit1(void) { printf("first exit handler\n"); }
static void my_exit2(void) { printf("second exit handler\n"); }
static void my_exit3(void) { printf("third exit handler\n"); }

void TestParameter(int argc, char *argv[]) {
	for (int i = 0; i < argc; ++i) {
		printf("argv[%d]: %s\n", i, argv[i]);
	}
}

int main(int argc, char *argv[]) {
	// printf("hello world\n");
	// TestExit();
	TestParameter(argc, argv);
	return 0;
}
