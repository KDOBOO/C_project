#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <softPwm.h>
#include <wiringPi.h>
#include <pthread.h>

#define MAX_BUFFER_SIZE 1024
#define SERVER_PORT 2382
#define PIN 3

int LED1=0,LED2=0;

void *threadFuncA(void *ptr);

void *threadFuncB(void *ptr);
pthread_mutex_t mutexA;
pthread_mutex_t mutexB;

int main() {
    //소켓 함수 정의
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen;
    char buffer[MAX_BUFFER_SIZE];
    char buffer2[MAX_BUFFER_SIZE];
    char *message = "싫어\n";
    char *message2 = "좋아\n";
    //소켓 생성
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }
    //프로토콜,포트
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(SERVER_PORT);
    //소켓 바인드
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 1) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server started. Waiting for connection\n");
    //연결
    clientAddrLen = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == -1) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }


    //Thread


    pthread_t threadA;
    pthread_t threadB;
    int iretA,iretB;

    if(pthread_mutex_init(&mutexA,NULL) != 0){
        printf("mutex init failed\n");
        return 1;
    }
    if(pthread_mutex_init(&mutexB,NULL) != 0){
        printf("mutex init failed\n");
        return 1;
    }
    iretA = pthread_create(&threadA,NULL,threadFuncA,NULL);
    iretB = pthread_create(&threadB,NULL,threadFuncB,NULL);

    printf("Client connected\n");
    // 서브모터 셋팅
    if (wiringPiSetup() == -1) {
        return 1;
    }
    //LED
    pinMode(0,OUTPUT);
    pinMode(2,OUTPUT);

    // PWM제어
    if (softPwmCreate(PIN, 0, 200) == -1) {
        perror("softPwmCreate failed");
        exit(EXIT_FAILURE);
    }

    size_t bytesSend = 0;
    size_t bytesRead;
    int stopMotor = 0;

    while ((bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1))) {
        buffer[bytesRead] = '\0';
        buffer2[0] = '\0';

        if (strstr(buffer, "선풍기 켜줘") != NULL) {
            bytesSend = send(clientSocket, message, strlen(message), 0);
            stopMotor = 0;


            while (!stopMotor) {
                softPwmWrite(PIN, 10);
                delay(500);
                softPwmWrite(PIN, 25);
                delay(500);

                bytesRead = read(clientSocket, buffer2, sizeof(buffer2) - 1);
                if (bytesRead == -1) {
                    perror("Read failed");
                    close(clientSocket);
                    close(serverSocket);
                    exit(EXIT_FAILURE);
                }

                buffer2[bytesRead] = '\0';


                if (strstr(buffer2, "선풍기 꺼줘") != NULL) {
                    bytesSend = send(clientSocket, message2, strlen(message2), 0);
                    LED2 = 6;
                    stopMotor = 1;
                    softPwmWrite(PIN, 0); // Stop the motor
                }
            }
        }

        if (bytesSend == -1) {
            perror("Send error");
            close(clientSocket);
            close(serverSocket);
            exit(EXIT_FAILURE);
        }
    }
    close(clientSocket);
    close(serverSocket);

    return 0;
}

void *threadFuncA(void *ptr)
{

    digitalWrite(0,HIGH);
     if(LED1 == 6){

    }digitalWrite(0,LOW);




    return NULL;
}
void *threadFuncB(void *ptr)
{



    digitalWrite(2,HIGH);

    if(LED1 == 8){

    }digitalWrite(2,LOW);




    return NULL;
}

