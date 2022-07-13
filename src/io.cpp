#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

// #include "../include/apue.3e/include/apue.h"
#include "../include/apue.h"

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

void TestIo() {
	int c;
	while ((c = getc(stdin)) != EOF)
		if (putc(c, stdout) == EOF)
			err_sys("output error");
	if (ferror(stdin))
		err_sys("input error");
}

void TestIo2() {
	char buf[MAXLINE];
	printf("MAXLINE = %d\n", MAXLINE);
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (fputs(buf, stdout) == EOF) 
			err_sys("ouput error");
		if (ferror(stdin))
			err_sys("input error");
	}
}

void pr_stdio(const char *name, FILE *fp);
int is_unbuffered(FILE *fp);
int is_linebuffered(FILE *fp);
int buffer_size(FILE *fp);

void TestIo3() {
	FILE *fp;
	fputs("enter any character\n", stdout);
	if (getchar() == EOF) err_sys("getchar error");
	fputs("one line to standard error\n", stderr);
	pr_stdio("stdin", stdin);
	pr_stdio("stdout", stdout);
	pr_stdio("stderr", stderr);

	if ((fp = fopen("/etc/passwd", "r")) == NULL) err_sys("fopen error");
	if (getc(fp) == EOF)	err_sys("getchar error");
	pr_stdio("/etc/passwd", fp);
}

void pr_stdio(const char *name, FILE *fp) {
	printf("stream = %s, ", name);
	if (is_unbuffered(fp)) printf("unbuffered");
	else if (is_linebuffered(fp)) printf("line buffered");
	else printf("fully buffered");
	printf(", buffer size = %d\n", buffer_size(fp));
}

/* 
 * The following is nonportable
 */

#if defined(_IO_UNBUFFERED)

int is_unbuffered(FILE *fp) {
	return (fp->_flags & _IO_UNBUFFERED);
}

int is_linebuffered(FILE *fp) {
	return (fp->_flags & _IO_LINE_BUF);
}

int buffer_size(FILE *fp) {
	return (fp->_IO_buf_end - fp->_IO_buf_base);
}

#elif defined(_SNBF)

int is_unbuffered(FILE *fp) {
	return (fp->_flags & _SNBF);
}

int is_linebuffered(FILE *fp) {
	return (fp->_flags & _SLBF);
}

int buffer_size(FILE *fp) {
	return (fp->_bf._size);
}

#elif defined(_IONBF) 

#ifdef _LP64
#define _flag _pad[4];
#define _ptr _pad[1];
#define _base _pad[2];
#endif

int is_unbuffered(FILE *fp) {
	return (fp->_flag & _IOLBF);
}

int buffer_size(FILE *fp) {
#ifdef _LP64
	return (fp->_base - fp->_ptr);
#else
	return (BUFSIZ);
#endif
}

#else

#error unknown stdio implementation

#endif

void TestTempfile() {
	char name[L_tmpnam], line[MAXLINE];
	FILE *fp;
	printf("%s\n", tmpnam(NULL));				/* first temp name */
	tmpnam(name);												/* second temp name */
	printf("%s\n", name);

	if ((fp = tmpfile()) == NULL)				/* create temp file */
		err_sys("tmpfile error");
	fputs("one line of output\n", fp);	/* write to temp file */
	rewind(fp);													/* then read it back */
	if (fgets(line, sizeof(line), fp) == NULL)
		err_sys("fgets error");
	fputs(line, stdout);								/* printf the line we wrote */
}

void TestMemstream() {
#define BSZ 48
	FILE *fp;
	char buf[BSZ];
	memset(buf, 'a', BSZ - 2);
	buf[BSZ - 2] = '\0';
	buf[BSZ - 1] = 'X';
	if ((fp = fmemopen(buf, BSZ, "w+")) == NULL) err_sys("fmemopen failed");
	printf("initial buffer contents: %s\n", buf);
	fprintf(fp, "hello, world");
	printf("before flush: %s\n", buf);
	fflush(fp);
	printf("after fflush: %s\n", buf);
	printf("len of string in buf = %ld\n", (long) strlen(buf));
	
	memset(buf, 'b', BSZ - 2);
	buf[BSZ - 2] = '\0';
	buf[BSZ - 1] = 'X';
	fprintf(fp, "hello world");
	fseek(fp, 0, SEEK_SET);
	printf("after fseek: %s\n", buf);
	printf("len of string in buf = %ld\n", (long) strlen(buf));
	
	memset(buf, 'c', BSZ - 2);
	buf[BSZ - 2] = '\0';
	buf[BSZ - 1] = 'X';
	fprintf(fp, "hello world");
	fclose(fp);
	printf("after fclose: %s\n", buf);
	printf("len of string in buf = %ld\n", (long) strlen(buf));
}

int main() {
	// TestLseek();
	// TestCreate();
	// TestIo();
	// TestIo2();
	// TestIo3();
	// TestTempfile();
	TestMemstream();
	return 0;
}
