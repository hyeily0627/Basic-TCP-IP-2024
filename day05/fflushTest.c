#include <stdio.h>

int main()
{
	FILE *file = fopen("test.txt", "W"); 
	if(fike == NULL) {
		printf("파일열기실패\n"); 
		return 1; 
}

	fprintf(file, "hello world\n");
	if(fflush(file) == 0) {
		printd("버퍼키우기 성공\n"); 
	} else {
		printf("버퍼키우기 실패\n");
	}

	fclose(file);

	return 0; 
