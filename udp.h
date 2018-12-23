#define MY_ID	33

#define	SERV_UDP_PORT	(8000 + MY_ID)
#define	SERV_HOST_ADDR	"127.0.0.1"

#define MSG_START		1
#define	MSG_KEEP		2
#define MSG_REPLY		3

typedef struct  {
	int		type;
	char	data[128];
}
	MsgType;
