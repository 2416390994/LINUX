//服务端程序
#include"udpsocket.hpp"
int main (int argc,char* argv[])
{
	if (argc!=3)
	{
		printf ("./udp_srv ip port\n");
		return -1;
	}
	//第2个参数是IP号
	string srv_ip = argv[1];
	//第3个参数是端口
	//atoi字符串转数字
	uint16_t srv_port = atoi(argv[2]);
	udpsocket sock;
	CHECK_RET(sock.SOCKET());
	CHECK_RET(sock.BIND(srv_ip,srv_port));
	while(1)
	{
		string cli_ip;
		uint16_t cli_port;
		string buf;
		sock.RECV(buf,cli_ip,cli_port);
		printf ("client-[%s:%d]--say:%s\n",cli_ip.c_str(),cli_port,buf.c_str());
		//前面接受完数据，然后将缓冲区清空
		buf.clear();
		printf ("server say:");
		fflush(stdout);
		//再由用户输入数据
		cin>>buf;
		//再发生送过去
		sock.SEND(buf,cli_ip,cli_port);
	}
	return 0;
}
