//客户端程序
#include"udpsocket.hpp"
int main (int argc,char* argv[])
{
	if (argc!=3)
	{
		cout<<"./udp_cli ip port\n";
		return -1;
	}
	string srv_ip = argv[1];
	uint16_t srv_port = atoi(argv[2]);
	udpsocket sock;
	CHECK_RET(sock.SOCKET());
	while (1)
	{
		string buf;
		cout<<"client say:";
		fflush(stdout);
		cin>>buf;
		sock.SEND(buf,srv_ip,srv_port);
		buf.clear();
		sock.RECV(buf,srv_ip,srv_port);
		cout<<"server say:"<<buf<<endl;
	}
	sock.CLOSE();
	return 0;
}
