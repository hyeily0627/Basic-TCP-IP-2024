#include <stdio.h>

int main(int argc, char* argv[])
{
	printf("전달하는 인자 갯수: %d\n", argc);
	printf("실행파일 : %s\n", argv[0]);
	
	for(int i = 1; i < argc ; i++) {
		printf(" 전달인자 : %s\n", argv[i]);
		}

	return 0;
}
/*
출력값 

 ./mainT 1 2 3 4 5
 
전달하는 인자 갯수: 6
실행파일 : ./mainT
 전달인자 : 1
 전달인자 : 2
 전달인자 : 3
 전달인자 : 4
 전달인자 : 5
*/
