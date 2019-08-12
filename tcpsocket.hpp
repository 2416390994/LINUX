//封装tcpsocket类，向外提供更加轻便的接口
//1.创建套接字
//2.绑定地址信息
//3.服务端开始监听，客户端向服务端发起请求
//4.服务端回去已完成i按揭的客户端新的socket
//5.接收数据
//6.发送数据
//7.关闭套接字
#include<iostream>
#include<string>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<error.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define CHECK(p) if((p) == false){return -1;}
using namespace std;
class Tcpsocket
{
public:
	Tcpsocket()
	{}
	~Tcpsocket()
	{}
	bool Socket()
	{
		_sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		if(_sockfd < 0)
		{
			perror("socket error\n");
			return false;
		}
		return true;
	}
	bool Bind(string &ip,uint16_t port)
	{
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(ip.c_str());
		socklen_t len = sizeof(struct sockaddr_in);
		int ret = bind (_sockfd,(sockaddr*) &addr,len);
		if(ret < 0)
		{
			perror("bind error\n");
			return false;
		}
		return true;
	}
	bool Listen(int backlog = 5)
	{
		 //int listen(int socket, int backlog);
		 //socket:套接字描述符
		 //backlog:最大并发连接数，决定内核中已完成连接队列节点的个数
		 //backlog：决定的不是服务端能接受的客户端最大上限，而是同一时间最大的接受的上限，类似于同一时间创建几个小桃红来接待客人
		 int ret = listen(_sockfd,backlog);
		 if(ret < 0)
		 {
			perror("listen error\n");
			return false;
		 }
		 return true;
	}
	bool Accept(Tcpsocket &cli ,string &cliip,uint16_t cliport)
	{
		//int accept(int s, struct sockaddr *addr,socklen_t *addrlen);
		//s:套接字描述符
		//addr: 请求连接的客户端地址信息长度
		//addrlen:新建客户端的地址信息长度
		struct sockaddr_in addr;
		socklen_t len = sizeof(addr);
		int sockfd = accept(_sockfd,(struct sockaddr*) &addr,&len);
		if(sockfd < 0)
		{
			perror("accept error\n");
			return false;
		}
		cli.SetFd(sockfd);
		cliip = inet_ntoa(addr.sin_addr);
		cliport = ntohs(addr.sin_port);
		return true;
	}
	void SetFd(int sockfd)
	{
		_sockfd  = sockfd;
	}
	bool Connect(string &srv_ip,uint16_t srv_port)
	{
		//int connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
		//socket: 客户端那边主机建立的套接字描述符
		//addr: 服务端的地址信息
		//addrlen: 服务端地址信息长度
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(srv_port);
		addr.sin_addr.s_addr = inet_addr (srv_ip.c_str());
		socklen_t len = sizeof(addr);
		int ret = connect(_sockfd,(struct sockaddr*)&addr,len);
		if(ret < 0)
		{
			perror("connect error\n");
			return false;
		}
		return true;
	}
	bool Recv(string &buf)
	{
		//ssize_t recv(int sockfd, void *buf, size_t len, int flags);
		//socket:服务端为客户端新建的socket描述符
		//flags: 0 默认阻塞接受，没有数据就一直等待
		//		MSG_PEEK接收数据，但是数据并不从接收缓冲区移除，用于探测性接受，因为tcp面对的是流式数据，可能会接受的不会是一条完整的数据，所以需要探测性的接受，探测数据是否完整
		//返回值：实际接受的字节长度：出错返回-1，若连接断开则返回0
		//recv默认是阻塞的，意味着没有数据则一直等，不会返回0，返回0只有一种情况，那就是连接断开，不再继续通信
		char tmp[4096] = {0};//这里可以不要这个tmp吗，直接使用buf应该也可以吧！
		int ret = recv(_sockfd,tmp,4096,0);
		if(ret < 0)
		{
			perror("recv error");
			return false;
		}
		else if(ret == 0)
		{
			perror("peer shutdown");
			return true;
		}
			buf.assign(tmp,ret);//把缓冲区中实际接收到的长度内容放到buf中传出去
			return true;
	}
	bool Send(string &buf)
	{
		// int send(int s, const void *msg, size_t len, int flags);
		int ret = (_sockfd,buf.c_str(),buf.size(),0);
		if(ret < 0)
		{
			perror("error send");//触发异常
			return false;
		}
		return true;
	}
	bool Close()
	{
		close(_sockfd);
		return true;
	}
private:
	int _sockfd;
};
