# Basic-TCP-IP-2024
부경대학교 2024 IoT 개발자 과정 - TCP/IP 학습 리포지토리 (안성주 T)

# 교재 
윤성우의 열혈 TCP/IP 소켓 프로그래밍 

# 1일차 (2024-06-11)
- IP란? (64p)
    - 명령 프롬프트 -> ipconfig 
        ```cmd
            Windows IP 구성


            이더넷 어댑터 이더넷 2:

            연결별 DNS 접미사. . . . :
            링크-로컬 IPv6 주소 . . . . : fe80::b5dd:8507:d5aa:70f4%4
            IPv4 주소 . . . . . . . . . : 192.168.5.2
            서브넷 마스크 . . . . . . . : 255.255.255.0
            기본 게이트웨이 . . . . . . : 192.168.5.1
        ```
        - IPv4 : 4바이트로 구성 
        - IPv6 : 16바이트로 구성
- TCP란? (94p)
    - 전송하는 방식(두 개의 호스트를 연결하고 데이터 스트림을 교환하게 해주는 중요한 네트워크 프로토콜) 
    - 데이터의 송수신을 담당(전송계층)
    - 전송방식 
        TCP : 데이터를 잃어버리면 안되는 경우
        UDP : 데이터를 한 두개정도는 손실해도 되는 경우 

**암기** 네트워크 프로세스 
- 소 : 소켓(Socket) - 전화기 
    - 소켓이란 : 물리적으로 연결된 네트워크상에서의 데이터 송수신에 사용할 수 있는 소프트웨어적 장치
- 말 : 바인더(bind) - 전화번호 할당
    - 소켓의 주소정보에 해당하는 IP와 포트번호 할당
- 리 : 리슨(listen) - 전화기 개통 
    - 연결요청 상태로 변경
- 아 : 엑셉트(accept) - 수화기를 드는 일 
    - 연결요청에 대한 수락

- 서버와 소켓의 구현 
    - 컴파일 파일 ./hello_sv / ./hello_clnt 파일 생성
    - ./hello_sv 9090 하고 서버 열림 확인 
    - **새 라즈베리파이 열어서** 경로 다 들어간다음에 -> ./hello_clnt 127.0.0.1 
    - 출력 내용 확인

- 파일 열기 
    - 하드디스크에 파일을 RAM으로 올려야 사용 가능 => 그래서 경로 필요 
    ```c
    int open(const char *path, int flag);
    // 성공시 파일 디스크립터, 실패 시 -1 반환
    /*
    path : 파일 이름을 나타내는 문자열의 주소 값 전달 
    flag : 파일의 오픈 모드 정보 전달  
    */
    ```

- 파일 닫기 
    - 파일은 사용 후 반드시 닫아야함 
    ```c
    int close(int fd);
    // 성공시 0, 실패 시 -1 반환 
    // id : 닫고자 하는 파일 도는 소켓의 파일 디스크립터 전달 
    ```

- 파일 쓰기 
    - write 함수 : 파일에 데이터를 **출력(전송)**하는 함수
    ```c
    ssize_t write(int fd, const void * buf, size_t nbytes);
    // 성공시 0, 실패 시 -1 반환 
    /*
    fd : 데이터 전송 대상을 나타내는 파일 디스크립터 전달
    buf : 전송할 데이터가 저장된 버퍼의 주소 값 전달 
    nbytes : 전송할 데이터의 바이트 수 전달  
    */
    ```
    - <typedef 선언을 통해 정의>size_t = unsigned int / ssize_t = signed int
*
- 까먹어버린 리눅스 명령어 (╯︿╰)
    - cd work/C : work 안에 있는 C 폴더 접근
    - nano 파일명 : 파일 열기(콘솔창) or 신규이름일시 새 창
    - **컴파일** gcc hello_client.c -o hello_clnt
    - ./컴파일명 : 출력파일의 내용 출력
    - mv 기존이름 바꿀이름: 이름 수정이나 이동시 사용
    - rm(remove) -fr Work: Work 디렉터리 삭제

- 참고
```c
    // 파일 생성 및 소켓 생성까지 (fd_seri.c)
    int main(void)
    {	
        int fd1, fd2, fd3;
        fd1=socket(PF_INET, SOCK_STREAM, 0);
        fd2=open("test.dat", O_CREAT|O_WRONLY|O_TRUNC);
        fd3=socket(PF_INET, SOCK_DGRAM, 0);
        
        printf("file descriptor 1: %d\n", fd1);
        printf("file descriptor 2: %d\n", fd2);
        printf("file descriptor 3: %d\n", fd3);
        
        close(fd1);
        close(fd2);
        close(fd3);
        return 0;
    }
    /* 
    <출력> 
    file descriptor 1: 3
    file descriptor 2: 4
    file descriptor 3: 5 
    
    디스크럽터가 3부터 시작하는 이유는 운영체제에서 0 1 2는 표준 입출력에 사용했기때문! 
    0 : 입력 1 : 출력 2 : 에러 
    */
```