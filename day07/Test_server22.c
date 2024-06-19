#include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #include <sys/socket.h>
  #include <sys/stat.h>
  #include <fcntl.h>
  #include <sys/sendfile.h>

 #define  TRUE  1

 char webpage[] = "HTTP/1.1 200 OK\r\n"  // 상태 라인
                   "Server:Linux Web Server\r\n"
                  "Content-Type: text/html; charset=UTF-8\r\n\r\n"  //메세지더
                  "<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Hyejin's Portfolio</title>
    <link rel="icon" href="data:,">
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #f4f4f4;
        }
        header {
            background-color: #333;
            color: #fff;
            padding: 20px 0;
            text-align: center;
        }
        header h1 {
            margin: 0;
        }
        nav {
            background-color: #444;
            color: #fff;
            padding: 10px 0;
            text-align: center;
        }
        nav a {
            color: #fff;
            margin: 0 15px;
            text-decoration: none;
        }
        .container {
            max-width: 1000px;
            margin: 0 auto;
            padding: 20px;
        }
        .about {
            text-align: center;
        }
        .about img {
            border-radius: 50%;
            width: 150px;
            height: 150px;
        }
        .about h2 {
            margin-top: 10px;
        }
        .projects {
            display: flex;
            flex-wrap: wrap;
            gap: 20px;
        }
        .project {
            background-color: #fff;
            border: 1px solid #ddd;
            border-radius: 5px;
            flex: 1 1 calc(33% - 20px);
            margin-bottom: 20px;
            padding: 15px;
            text-align: center;
            box-shadow: 0 2px 5px rgba(0,0,0,0.1);
        }
        .project img {
            width: 100%;
            height: 200px;
            object-fit: cover;
            border-radius: 5px;
        }
        .project h3 {
            margin: 15px 0 10px;
        }
        .footer {
            background-color: #333;
            color: #fff;
            text-align: center;
            padding: 10px 0;
            margin-top: 20px;
        }
    </style>
</head>
<body>
    <header>
        <h1>Hyejin's Portfolio</h1>
    </header>
    <nav>
        <a href="#about">About</a>
        <a href="#projects">Projects</a>
        <a href="#contact">Contact</a>
    </nav>
    <div class="container">
        <section id="about" class="about">
            <img src="profile.jpg" alt="Hyejin's Profile Picture">
            <h2>About Me</h2>
            <p>Hello! I'm Hyejin, a web developer with a passion for creating beautiful and functional websites.</p>
        </section>
        <section id="projects" class="projects">
            <h2>Projects</h2>
            <div class="project">
                <img src="project1.jpg" alt="Project 1">
                <h3>Project 1</h3>
                <p>Brief description of Project 1.</p>
            </div>
            <div class="project">
                <img src="project2.jpg" alt="Project 2">
                <h3>Project 2</h3>
                <p>Brief description of Project 2.</p>
            </div>
            <div class="project">
                <img src="project3.jpg" alt="Project 3">
                <h3>Project 3</h3>
                <p>Brief description of Project 3.</p>
            </div>
        </section>
    </div>
    <footer class="footer">
        <p>Contact: hyejin@example.com</p>
    </footer>
</body>
</html>
"
 int main(int argc, char *argv[])
 {
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t sin_len = sizeof(clnt_addr);
    int serv_sock, clnt_sock;
    char buf[2048];
    int fdimg, img_size;
    int option = TRUE;
    char img_buf[700000];

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    /* 주소 재할당 */
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
       perror("bind() error!!");
    if(listen(serv_sock, 5) == -1) perror("listen() error!!");

    while(1) {
       clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &sin_len);
       puts("New client connection.....");
       read(clnt_sock, buf, 2047);
       printf("%s\n", buf);

       if(strstr(buf, "GET /game.jpg") != NULL) {
       fdimg = open("game.jpg", O_RDONLY);
          if((img_size = read(fdimg, img_buf, sizeof(img_buf))) == -1) puts("file read error!!");
          close(fdimg);

          sprintf(buf, "HTTP/1.1 200 OK\r\n"
           "Server: Linux Web Server\r\n"
           "Content-Type: image/jpeg\r\n"
           "Content-Length: %ld\r\n\r\n", img_size);
          /* 헤더전송 */
       if(write(clnt_sock, buf, strlen(buf)) < 0) puts("file write error!!");
          /* 이미지전송*/
          if(write(clnt_sock, img_buf, img_size) < 0) puts("file write error!!");

          close(clnt_sock);
       }
       else
          //send(clnt_sock, webpage, sizeof(webpage), 0);
          if(write(clnt_sock, webpage, sizeof(webpage)) == -1) puts("file write error!!");
          puts("closing.....");
          close(clnt_sock);
       }
       close(serv_sock);
       return 0;
 }
