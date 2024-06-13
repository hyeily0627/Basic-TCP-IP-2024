#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4 // 피연산자 바이트 수 상수화
#define OPSZ 4 // 연산결과 바이트 수 상수화 
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	char opmsg[BUF_SIZE]; //데이터 송수신을 위한 메모리 공간 = 배열이 좋음!
	int result, opnd_cnt, i;
	struct sockaddr_in serv_adr;
	if(argc!=3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	sock=socket(PF_INET, SOCK_STREAM, 0);   
	if(sock==-1)
		error_handling("socket() error");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));
	
	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("connect() error!");
	else
		puts("Connected...........");

	fputs("Operand count: ", stdout);
	/*피연산자의 개수정보 입력 받은 후 배열 opmsg 저장
	char로의 형변환은 '피연산자의 개수정보를 1바이트 정수형태로 전달한다'
	라고 정의한 프로토콜에 근거한 형변환이다.
	때문에 1바이트로 표현 불가능한 범위의 정수가 입력되면 안된다 */
	scanf("%d", &opnd_cnt); 
	opmsg[0]=(char)opnd_cnt;

	// 프로그램 사용자로부터 정수를 입력 받아서 배열 opmsg에 이어서 저장 
	// char형 배열에 4바이트 int형 정수를 저장해야하기 때문에 int형 포인터로
	// 형변환을 하고 있다. 
	for(i=0; i<opnd_cnt; i++)
	{
		printf("Operand %d: ", i+1);
		scanf("%d", (int*)&opmsg[i*OPSZ+1]);
	}
	fgetc(stdin); // 55행에서 문자를 입력 받아야하는데, 앞서 버퍼에 남아있는
	// \n문자의 삭제를 위해 호출된 함수 
	fputs("Operator: ", stdout);
	scanf("%c", &opmsg[opnd_cnt*OPSZ+1]); // 연산자 정보를 입력받아 배열 opmsg에 저장	
	write(sock, opmsg, opnd_cnt*OPSZ+2);
	 /* write 함수 호출을 통해서 opmsg에 저장되어있는 연산과 관련된 정보를 한번에 전송
*/
	//서버가 전송해주는 연산과정의 저장 
	read(sock, &result, RLT_SIZE);
	
	printf("Operation result: %d \n", result);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

