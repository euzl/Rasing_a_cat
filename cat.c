#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "udp.h"


int	Sockfd;

// 서버닫기
void
CloseServer()
{
	close(Sockfd);
	exit(0);
}

/*===============================================================
[Program Name] : Cat
[Description]  : 
	- server 역학을 함
[Input]        :
[Output]       :
[Calls]        :	        
	CloseServer()	// 서버 닫기용 함수
[특기사항]     : cat과 butler 프로그램을 동시에 실행시켜
		 		 통신하며 게임이 진행된다.
==================================================================*/

int
main(int argc, char *argv[])
{
	int					newSockfd, cliAddrLen, n, closep, level;
	printf("I'm the only one who doesn't have a cat.\n\n");
	char				cName[32]; // 고양이 이름 저장
	struct sockaddr_in	cliAddr, servAddr;
	MsgType				msg;

	signal(SIGINT, CloseServer);

	if ((Sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	// bzero: 바이트스트림을 0으로 채움
	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_UDP_PORT);

	if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}

	printf("Wait for adoption...\n");
	
	cliAddrLen = sizeof(cliAddr);

	while (1)  {
		// UDP 이용
		if ((n = recvfrom(Sockfd, (char*) &msg, sizeof(msg),0, (struct sockaddr*)&cliAddr, &cliAddrLen)) <0){
			perror("recvfrom");
			exit(1);
		}
		
		if(msg.type == MSG_START){
			// 고양이 이름 저장
			strcpy(cName, msg.data);

			//점수, 레벨 초기화
			closep = 0;
			level = 1;

			sprintf(msg.data, "[!!]I have adopted a cat.\n");
			msg.type = MSG_REPLY;
		}
		else if(msg.type == MSG_KEEP){
			if(msg.data[0] == '0'){
				printf("--The End--\n");
				printf("My Level is %d", level);
				break;
			}
			else if(msg.data[0] == '1'){
				printf("I joined hands with the cat.\n");
				closep += 2;
				// 고양이의 답변 (골골)
				sprintf(msg.data, "[%s]Purr.\n", cName);
				msg.type = MSG_REPLY;
			}
			else if(msg.data[0] == '2'){
				printf("I had a high five with the cat.\n");
				closep += 3;
				// 고양이의 답변 (골골)
				sprintf(msg.data, "[%s]Purr.\n", cName);
				msg.type = MSG_REPLY;
			}
			else if(msg.data[0] == '3'){
				printf("I fed the cat.\n");
				closep += 5;
				// 고양이의 답변 (골골)
				sprintf(msg.data, "[%s]Pur Purr\n", cName);
				msg.type = MSG_REPLY;
			}
			else if(msg.data[0] == '4'){
				printf("I played with the cat.\n");
				closep += 4;
				// 고양이의 답변 (골골)
				sprintf(msg.data, "[%s]Pur Purr\n", cName);
				msg.type = MSG_REPLY;
			}
			else if(msg.data[0] == '5'){
				printf("I patted the cat.\n");
				closep += 5;
				// 고양이의 답변 (골골)
				sprintf(msg.data, "[%s]Purrr Purrr...\n", cName);
				msg.type = MSG_REPLY;
			}
			else if(msg.data[0] == '6'){
				printf("I gave the cat a snack.\n");
				closep += 7;
				// 고양이의 답변 (골골)
				sprintf(msg.data, "[%s]Purrr Purrr...\n", cName);
				msg.type = MSG_REPLY;
			}
		}
		printf("확인");
		// 답변 전송
		if (sendto(Sockfd, (void*)&msg, sizeof(msg), 0, (struct sockaddr*)&cliAddr, cliAddrLen) < 0 ) {
			perror("sendto");
			exit(1);
		}
		// 레벨 업
		if(closep > 15){
			level++;
			closep -= 15;
		}
		
		// 현재상황 출력
		printf("[%s] Close: %d   Level : %d  \n", cName, closep, level);

		usleep(10000);
	}
}
