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
- 말 : 바인더(Bind) - 전화번호 할당
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
    - 참고(30p)
        - size_t = unsigned int / ssize_t = signed int
        - typedef 선언을 통해 정의 
        - unsigned 는 양수범위 
        - 확장성을 고려한 결과(int32_t 자료형은 4바이트 자료형임을 보장, 자료형 int가 64비트로 표현되는 날이 오더라도!)
    *
- 까먹어버린 리눅스 명령어 (╯︿╰)
    - mkdir work : work 디렉토리 생성
    - cd work/C : work 안에 있는 C 폴더 접근
    - cd(공백).. : 상위 폴더로 빠져나감
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

- 프로토콜이란?(50p)
    - 컴퓨터 상호간 대화에 필요한 통신규약(= 데이터를 주고 받기 위한 약속)
    - 프로토콜 체계 : PF_INET (IPv4 인터넷 프로토콜 체계) 

- 소켓의 타입(type) : 소켓의 데이터 전송방식
    1. 연결지향형 소켓 = TCP
        - 데이터가 소멸 되지 않음을 보장
        - 데이터의 경계가 존재하지 않음 
        - 소켓 대 소켓의 연결은 반드시 1대1이어야 한다
        => 신뢰성 있는 순차적인 바이트 기반의 연결지향 데이터 전송 방식의 소켓 
    2. 비 연결지향형 소켓 = UDP 
        - 전송 순서와 상관 없이 빠른 전송 지향
        - 데이터의 경계가 존재
        - 한번에 전송할 수 있는 데이터의 크기가 제한 
        = 신뢰성과 순차적 데이터 전송을 보장하지 않는, 고속의 데이터 전송을 목적으로 하는 소켓 

- 클래스 별 네트워크 주소와 호스트 주소(66p)
    - 주소의 형태에 따라 A,B,C,D,E 클래스로 분류
    - A 클래스 바이트 범위 : 0 ~ 127 이하 (첫번쨰 비트는 항상 0 으로 시작)
    - B 클래스 바이트 범위 : 128 ~ 191 이하 (첫 두 비트는 항상 10으로 시작)
    - A 클래스 바이트 범위 : 192 ~ 223 이하 (첫 세 비트는 항상 110으로 시작)

- 포트번호 : 하나의 운영체제내에서 소켓을 구분하는 목적 
    - 하나의 운영체제에서 동일한 포트번호 부여 불가
    - 16비트로 표현 (2byte)
    - 번호 범위 : 0 ~ 65535(단, 0 ~ 1023은 특정 프로그램에 할당하기로 약속 -> 그 외 사용인데, 10000번 이상으로 쓸 수 있다라고 알면 된대❗)

- 바이트 순서와 네트워크 바이트 순서(72p)
    - 빅 엔디안(Big Endian) : 상위 바이트의 값을 작은 번지수에 저장 
    - 리틀 엔디안(Little Endian) : 상위 바이트의 값을 큰 번지수에 저장 

    ![엔디안](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/001.jpg)

    - 네트워크 바이트 순서 : 빅 엔디안 방식으로 통일

        
# 2일차 (2024-06-12)
- TCP 서버의 함수 호출 순서
    소켓 생성 socket()  
    -> 소켓주소 할당 bind()
    -> 연결요청 대기상태 listen()
    -> 연결허용 accept()
    -> 데이터 송수신 read()/write
    -> 연결종료 close() 

-  TCP 클라이언트의 기본적인 함수호출 순서 
    소켓 생성 socket()
     -> 연결요청 connect()
     -> 데이터 송수신 read()/write
     -> 연결종료 close() 
    - 서버와 차이점 : 연결요청 - 클라이언트 소켓을 생성한 후에 서버로 연결을 요청하는 과정 

![서버클라이언트관계](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/002.png)

- 에코클라이언트 

- TCP 소켓에 존재하는 입출력 버퍼
    • 입출력 버퍼는 TCP 소켓 각각에 대해 별도로 존재한다.
    • 입출력 버퍼는 소켓생성시 자동으로 생성된다.
    • 소켓을 닫아도 출력버퍼에 남아있는 데이터는 계속해서 전송이 이뤄진다.
    • 소켓을 닫으면 입력버퍼에 남아있는 데이터는 소멸되어버린다.

    - 슬라이딩 윈도우 프로토콜
    소켓 A 야 50바이트까지는 보내도 괜찮아!
    소켓 B OK!
    소켓 A 내가 20바이트 비웠으니까 70바이트까지 괜찮아
    소켓 B OK!
    => 이와 같은 버퍼가 존재하기 때문에 데이터의 슬라이딩 윈도우 프로토콜의 적용이 가능하고, 이로 인해서 버퍼가 차고 넘치는 상황은 발생하지 않는다.

- TCP의 내부동작 원리(126p)
    1. 상대 소켓과의 연결

    - ![소켓연결](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/003.png)

    2. 상대 소켓과의 데이터 송수신

    - ![데이터송수신](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/004.png)

    3. 상대 소켓과의 연결종료

    - ![연결종료FIN](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/005.png)

- UDP 소켓과 TCP 소켓의 데이터 송수신 비교
    - UDP 소켓은 SEQ, ACK와 같은 메시지 전달을 하지 않는다(Flow Control 없음).
    - 그리고 연결의 설정과 해제의 과정도 존재하지 않는다.
    - 때문에 데이터의 분실 및 손실의 위험이 있다.
    - 그러나 확인의 과정이 존재하지 않기 때문에 데이터의 전송이 빠르다.
    - 따라서 안전성보다 성능이 중요시 될 때에는 UDP를 사용한다.

# 3일차 (2024-06-13)

# 4일차 (2024-06-14)