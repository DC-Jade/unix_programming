#include <fcntl.h>

#include "../include/apue.h"

// void TestAccess(const int &argc, const char * &argv[]) {
// void TestAccess(int &argc, char* &argv[]) {
// void TestAccess(const int argc, const char* argv[]) {
// void TestAccess(const int argc, const char** argv) {
void TestAccess(int argc, char* argv[]) {
	if (argc != 2) 
		err_quit("usage: ../bin/access <pathname>");
	if (access(argv[1], R_OK) < 0)
		err_ret("access error for %s", argv[1]);
	else 
		printf("read access OK\n");
	if (open(argv[1], O_RDONLY) < 0)
		err_ret("open error %s", argv[1]);
	else
		printf("open for reading OK\n");
}

// int main(int argc, char *argv[]) {
int main(int argc, char **argv) {
	TestAccess(argc, argv);
	exit(0);
}


