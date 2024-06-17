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
- 일방적인 연결 종료의 문제점   
    - close 및 closesocket 함수의 기능
        - 소켓의 완전 소멸을 의미한다.
        - 소켓이 소멸되므로 더 이상의 입출력은 불가능하다.
        - 상대방의 상태에 상관 없이 일방적인 종료의 형태를 띤다.
        - 때문에 상대 호스트의 데이터 송수신이 아직 완료되지 않은 상황이라면, 문제가 발생할 수 있다.
        - 이러한 문제의 대안으로 Half-close 기법이 존재한다.
- Half-close
    - 종료를 원한다는 것은, 더 이상 전송할 데이터가 존재하지 않는 상황이다.
    - 따라서 출력 스트림은 종료를 시켜도 된다.
    - 다만 상대방도 종료를 원하는지 확인되지 않은 상황이므로, 출력 스트림은 종료시
    키지 않을 필요가 있다.
    - 때문에 일반적으로 Half-close라 하면, 입력 스트림만 종료하는 것을 의미한다.
    - Half-close를 가리켜 ‘우아한 종료’라고도 한다.

- 도메인 이름 
    - IP를 대신하는 서버의 주소 (ex) www.naver.com
    - 실제 접속에 사용되는 주소는 아니다. 이 정보는 IP로 변환이 되어야 접속이 가능하다.
- DNS 서버
    - 도메인 이름을 IP로 변환해주는 서버
    - DNS는 일종의 분산 데이터베이스 시스템이다.

![도메인](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/006.png)

- 소켓의 다양한 옵션 

- Time-Wait의 이해 
    - 서버, 클라이언트에 상관없이 TCP 소켓에서 연결의 종료를 목적으로 Four-way handshaking의 첫 번째 메시지를 젂달하는 호스트의 소켓은 Time-wait 상태를 거친다. 
    - Time-wait 상태 동안에는 해당 소켓이 소멸되지않아서 할당 받은 Port를 다른 소켓이 할당할 수 없다.
- Time-wait의 존재이유
    - 아래 그림에서 호스트 A의 마지막 ACK가 소멸되는 상황을 대비해서 Time-wait 상태가 필요하다. 호스트 A의 마지막 ACK가 소멸되면, 호스트 B는 계속해서 FIN 메시지를 호스트 A에 전달하게 된다.
    ![Time-wait](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/007.png)

- Nagle 알고리즘(212p)
    - 인터넷의 과도한 트래픽과 그로 인한 젂송속도의 저하를 막기 위해서 디자인 된 알고리즘이 Nagle 알고리즘이다.
    - 이러한 Nagle 알고리즘은 그 목적이 명확한 경우가 아니면 중단하지 말아야 하며, 소켓은 기본적으로 Nagle 알고리즘을 적용해서 데이터를 송수신한다.

- 프로세스
    - 간단하게는 **실행 중인 프로그램**을 뜻한다.
    - 실행중인 프로그램에 관련된 메모리, 리소스 등을 총칭하는 의미이다.
    - 멀티프로세스 운영체제는 둘 이상의 프로세스를 동시에 생성 가능하다.
- 프로세스 ID
    - 운영제제는 생성되는 모든 프로세스에 ID를 할당한다.
- 리눅스에서 프로세스 확인해보기 

![리눅스프로세스](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/008.png)


- fork 함수의 호출을 통한 프로세스의 생성 
    - fork 함수가 호출되면, 호출한 프로세스가 복사되어 fork 함수 호출 이후를 각각의 프로세스가 독립적으로 실행하게 된다.
```c
#include <unistd.h>

pid_t fork(void); 
// 성공시 프로세스 ID, 실패시 -1 반환 
```
![fork함수](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/009.png)

- 좀비 프로세스 
    - 실행이 완료되었음에도 불구하고, 소멸되지 않은 프로세스
    - 프로세스도 main 함수가 반환되면 소멸되어야 한다.
    - 소멸되지 않았다는 것은 프로세스가 사용한 리소스가 메모리 공간에 여전히 존재한다는 의미이다.
- 좀비 프로세스의 생성 원인
    - 자식 프로세스가 종료되면서 반환하는 상태 값이 부모 프로세스에게 전달되지 않으면 해당 프로세스는 소멸되지 않고 좀비가 된다.
        - 인자를 전달하면서 exit를 호출하는 경우
        - main 함수에서 return 문을 실행하면서 값을 반환하는 경우 
        => 해당 자식 프로세스를 생성한 부모 프로세스에게 exit의 함수 인자 값이나 return문의 반환값이 전달 되어야한다!! 
    ```c
    #include <stdio.h>
    #include <unistd.h>

    int main(int argc, char *argv[])
    {
        pid_t pid=fork();
        
        if(pid==0)     // if Child Process
        {
            puts("Hi I'am a child process");
        }
        else
        {
            printf("Child Process ID: %d \n", pid);
            sleep(30);     // Sleep 30 sec.
        }

        if(pid==0)
            puts("End child process");
        else
            puts("End parent process");
        return 0;
    }
    ```

    ![좀비](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/010.png)


# 4일차 (2024-06-14)
- 좀비 프로세스의 소멸: 
    - wait 함수의 사용
        - wait 함수의 경우 자식 프로세스가 종료되지 않은 상황에서는 반환하지 않고 블로킹 상태에 놓인다는 특징
    - waitpid 함수의 사용
        - wait 함수는 블로킹 상태에 빠질 수 있는 반면, waitpid 함수는 블로킹 상태에 놓이지 않게끔 할 수 있다는 장점
    
    ![waitpid](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/011.png)

- 시그널이란? 
    - 특정 상황이 되었을 때 운영체제가 프로세스에게 해당 상황이 발생했음을 알리는 일종의 메시지를 가리켜 시그널이라 한다.
    - 등록 가능한 시그널의 예
        - SIGALRM alarm 함수호출을 통해서 등록된 시간이 된 시간
        - SIGINT CTRL + C 가 입력된 상황
        - SIGCHLD 자식프로세스가 종료된 상황
- 시그널 등록이란 
    - 특정 상황에서 운영체제로부터 프로세스가 시그널을 받기 위해서는 해당 상황에 대해서 등록의 과정을 거쳐야 한다.
- 시그널과 시그널 함수 

![시그널](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/012.png)

- sigaction 함수
    - 시그널 함수와 유사하고 대체 가능하며 훨씬 더 안정적임
    - 유닉스 체제별로 동작방식 차이가 있는 시그널 함수를 이용하여 프로그램 작성 x 

![sigaction](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/013.png)

- 프로세스 기반 다중접속 서버 모델

    ![다중접속 서버 모델](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/014.png)

    - 핵심은 연결이 하나 생성될 때마다 프로세스를 생성해서 해당 클라이언트에 대해 서비스를 제공하는 것이다.
    - 1단계 : 에코서버(부모 프로세스)는 accept 함수 호출연결을 통해 연결요청 수락
    - 2단계 : 이때 얻게되는 소켓의 파일 디스크립터를 자식 프로세스를 생성하여 넘겨줌
    - 3단계 : 자식 프로세스는 전달받은 파일 디스크립터를 바탕으로 서비스 제공

    ![fork 함수호출을 통한 디스크립터의 복사](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/015.png)

- 입출력 루틴 분할의 이점과 의미
    - 프로그램의 구현이 한결 쉬워짐
        - 프로세스 생성이후에 부모프로세스가 실행하는 영역은 데이터의 수신과 관련해서만 코드작성
        - 자식프로세스가 실행하는 영역은 데이터의 송신과 관련해서만 코드 작성하면 되기때문 
    - 데이터 송수신이 잦은 경우, 프로그램 성능향상 

    ![입출력 루틴](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/016.png)

    - 하단 이미지 왼쪽은 이전 에코 클라이언트 데이터 송수신 방식, 오른쪽은 입출력루틴을 분리시킨 에코 클라이언트의 데이터 송수신 방식  

- 프로세스간 통신
    - 두 프로세스 사이에서의 데이터 전달
    - 두 프로세스 사이에서의 데이터 전달이 가능 하려면, 두 프로세스가 함께 공유하는 메모리가 존재해야 한다.
- 프로세스간 통신의 어려움
    모든 프로세스는 자싞만의 메모리 공간을 독립적으로 구성한다.
    - 즉, A 프로세스는 B 프로세스의 메모리 공간에 접근이 불가능하고, B 프로세스는 A 프로세스의 메모리 공간 접근이 불가능하다.
    - 따라서 운영체제가 별도의 메모리 공간을 마련해 줘야 프로세스간 통싞이 가능하다.

    ![파이프프로세스통신](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/017.png)

- 멀티 프로세스 서버의 단점
    - 프로세스의 빈번한 생성은 성능의 저하로 이어진다.
    - 멀티 프로세스의 흐름을 고려해서 구현해야 하기 때문에 구현이 쉽지 않다.
    - 프로세스간 통신이 필요한 상황에서는 서버의 구현이 더 복잡해진다.
- 멀티 플렉싱이란? 
    - 하나의 통신채널을 통해서 둘 이상의 데이터(시그널)를 전송하는데 사용되는 기술
    - 물리적 장치의 효율성을 높이기 위해서 최소한의 물리적인 요소만 사용해서 최대한의 데이터를 전달하기 위해 사용되는 기술 
- 멀티 프로세스 서버의 대안
    - 하나의 프로세스가 다수의 클라이언트에게 서비스를 할 수 있도록 한다.
    - 이를 위해서는 하나의 프로세스가 여러 개의 소켓을 핸들링 할 수 있는 방법이 존재해야 한다.
    - 바로 이것이 IO 멀티플렉싱이다.

- select 함수의 기능과 호출순서(276P)
    - 고전적인 방법 
    - select 함수를 이용하면 배열에 저장된 다수의 파일 디스크립터를 대상으로 이와 같은 질문을 던질 수 있다.
        - 수신한 데이터를 지니고 있는 소켓이 존재하는가?
        - 블로킹되지 않고 데이터의 전송이 가능한 소켓은 무엇인가?
        - 예외상황이 발생한 소켓은 무엇인가? 
    - 호출순서 

    ![select](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/018.png)

    - 관찰 항목 각각을 가리켜 '이벤트'라 한다. 
- select 함수호출 이후의 결과확인

![select결과확인](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/019.png)


# 5일차 (2024-06-17)
- 리눅스에서의 send & recv
  ![send & recv](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/020.png)
  
  - 마지막 매개변수에 전달할 수 있는 옵션(이 외에 더 있음)
    1. MSG_OOB : 긴급데이터(Out-of-band data)의 전송을 위한 옵션 
    ```c
    // oob_send.c 코드일부
    write(sock, "123", strlen("123"));
    send(sock, "4", strlen("4"), MSG_OOB);
    write(sock, "567", strlen("567"));
    send(sock, "890", strlen("890"), MSG_OOB);

    /*
    ./ recv 
    123 
    Urgent message : 4
    567
    Urgent message : 0
    89
    */
    ```
    - 실행결과의 판단
        - MSG_OOB 메시지라고 해서 더 빨리 전송되지 않는다.
        - 긴급으로 보낸 메시지의 양에 상관 없이 1바이트만 반환이 된다.

    - oob.recv.c 내 함수 호출문장 분석
    ```c
    fcntl(recv_sock, F_SETOWN, getpid()); 
    ```
    - 파일 디스크립터 recv_sock이 가리키는 소켓의 소유자(F_SETOWN)를 getpid 함수가 반환하는 ID 의 프로세스로 변경시키겠다. 
    - 또는 파일 디스크립터 recv_sock이 가리키는 소켓에 의해 발생하는 SIGURG 시그널을 처리하는 프로세스를 getpid 함수가 반환하는 ID의 프로세스로 변경시키겠다로 이해! 

- 표준 입출력함수의 두가지 장점
    1. 표준 입출력함수는 이식성이 좋다
        - ANSI C 기반의 표준 입출력 함수는 모든 컴파일러에서 지원을 하기 때문
    2. 표준 입출력함수는 버퍼링을 통한 성능의 향샹에 도움이 된다

    ![버퍼링](https://raw.githubusercontent.com/hyeily0627/Basic-TCP-IP-2024/main/images/021.png)

- 버퍼링을 하면 성능이 좋아지는가?
    - 두가지 관점에서의 성능의 우월함 : 전송 데이터의 양이 많으면 많을수록!
        1. 전송하는 데이터 양
        2. 출력버퍼로의 데이터 이동 횟수 
    - ex, 1바이트를 10회  40 x 10 = 400바이트
          10바이트를 1회  40 x 1 = 40바이트 

- 표준 입출력 함수의 사용에 있어서 불편사항
    - 양방향 통신이 쉽지 않다.
    - 상황에 따라서 fflush 함수의 호출이 빈번히 등장할 수 있다.
    - 파일 디스크립터를 FILE 구조체의 포인터로 변환해야한다. 
    -  fopen 함수 호출 시 반환되는 File 구조체의 포인터를 대상으로 입출력을 진행할 경우, 입력과 출력이 동시에 짂행되게 하는 것은 갂단하지 않다. 데이터가 버퍼링 되기 때문
    - 소켓 생성시 반환되는 것은 파일 디스크립터이다. 그런데 표준 C 함수에서 요구하는 것은
FILE 구조체의 포인터이다. 따라서 파일 디스크립터를 FILE 구조체의 포인터로 변환해야한다.



