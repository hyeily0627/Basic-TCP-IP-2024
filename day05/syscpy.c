#include <stdio.h>
#include <fcntl.h>
#define BUF_SIZE 3 // 배열의 길이를 최소한으로 구성

int main(int argc, char *argv[])
{
	int fd1, fd2;
	int len;
	char buf[BUF_SIZE];

	fd1=open("news.txt", O_RDONLY);
	fd2=open("cpy.txt", O_WRONLY|ORDONLY|O_TRUNC);

	while((len=read(fd1m, buf, sizeof(buf)))>0)
		write(fd2, buf, len); 

	close(fd1);
	close(fd2);
	return 0;
}


