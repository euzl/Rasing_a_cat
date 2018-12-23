#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "udp.h"

/*===============================================================
[Program Name] : Butler
[Description]  : 
	- client 역할을 함
[Input]        :
[Output]       :
[Calls]        :	        
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
		
int
main(int argc, char *argv[])
{
	int					sockfd, n, peerAddrLen;
	char				cName[32];
	struct sockaddr_in	servAddr, peerAddr;
	MsgType				msg;

	// 소켓 생성UDP
	if ((sockfd = socket(PF_INET,SOCK_DGRAM,0))<0)  { //PF_INE : ipv4 프로토콜
		perror("socket");
		exit(1);
	}

	// servAddr 초기화
	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
	servAddr.sin_port = htons(SERV_UDP_PORT);

	// 시작하면 고양이의 이름 지정
	msg.type = MSG_START;
	printf("Set Cat's Name>");
	scanf("%s", msg.data);
	strcpy(cName, msg.data); // 고양이 이름 저장
	// 보내기
	if (sendto(sockfd, (char*)&msg, sizeof(msg), 0, (struct sockaddr*)&servAddr, sizeof(servAddr))<0){
		perror("sendto");
		exit(1);
	}

	//응답
	peerAddrLen = sizeof(peerAddr);
	// 고양이키우기 시작
	// 매뉴얼
	printf("1. Hand(+2)\n2. High five(+3)\n3. Feed(+5)\n4. Play(+4)\n5. Pat(+5)\n6. Snack(+7)\n0. Exit(Shut down)\n");
	while(1){
		if(recvfrom(sockfd, (char*)&msg, sizeof(msg), 0, (struct sockaddr*)&peerAddr, &peerAddrLen)<0){
			perror("recvfrom");
			exit(1);
		}

		if(msg.type == MSG_REPLY){
			printf("%s", msg.data);
		}

		printf("Do> ");
		scanf("%s", msg.data);
		msg.type = MSG_KEEP;

		// server로 보내기
		if(sendto(sockfd, (char *)&msg, sizeof(msg), 0, (struct sockaddr*)&servAddr, sizeof(servAddr))<0){
			perror("sendto");
			exit(1);
		}

		// 종료
		if(msg.data[0] == '0'){
			break;
		}
	}
	close(sockfd);
}
