//实现封装一个udpsocket类，向外提供方便的套接字操作接口
#include<stdio.h>
#include<unistd.h>
#include<string>
#include<errno.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<iostream>
#include<arpa/inet.h>
#include<stdlib.h>
//宏代码用来检查类中的函数是否成功
#define CHECK_RET(q) if ((q)==false){return -1;}
using namespace std;

class udpsocket
{
public:
 	//构造函数
	udpsocket():_sockfd(-1)
	{}
	//析构函数
	~udpsocket()
	{
		close(_sockfd);
	}
	//创建套接字
	bool SOCKET()
	{
		//int socket(int domain, int type, int protocol);
		_sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
		//创建套接字，第一个参数说明使用的是ipv4地址域
		//第二个参数说明提供流式数据报传输（默认使用upd协议）
		//第三个参数说明使用udp协议
		//返回值位创建好的套接字描述符
		if(_sockfd < 0)
		{
			perror("socket error");
			return false; 
		}
		return true;
	}
	//绑定地址信息
	bool BIND(string &ip,uint16_t port)
	{
		//因为我们使用的是ipv4就不使用通用的结构体了
		//我们就直接使用ipv4地址结构体
		//sockaddr_in   ipv4地址结构
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		//uint16_t htons(uint16_t hostshort);
		//将16位的数据从主机字节序转换为网络字节序
		addr.sin_port = htons(port);
		//in_addr_t inet_addr(const char *cp);
		//将字符串点分十进制ip地址转换为网络字节序ip地址
		//又因为函数内部参数为char*类再对IP进行c_str()转换
		addr.sin_addr.s_addr = inet_addr(ip.c_str());
		//int bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen);
		socklen_t len = sizeof(struct sockaddr_in);
		//第二个参数进行了类型强转根据原函数可知
		//这里的参数是sockaddr*类型的，但是我们没有用通用的地址结构
		//所以我们在这里进行了类型强转 
		int ret = bind(_sockfd,(sockaddr*)&addr,len);
		if (ret < 0)
		{
			perror("bind error");
			return false;
		}
		return true;
	}
	bool RECV(string &buf,string &ip,uint16_t &port)
	{
		//ssize_t recvfrom(int sockfd, void *buf, size_t len
		//,int flags,struct sockaddr *src_addr, socklen_t *addrlen);
		char tmp[4096]={0};
		struct sockaddr_in addr;
		socklen_t len = sizeof(struct sockaddr_in);
		int ret = recvfrom(_sockfd,tmp,4096,0,(sockaddr*)&addr,&len);
		if (ret < 0)
		{
			perror ("recv error");
			return false;
		}
		//从tmp中截取ret长的数据放到buf中
		buf.assign(tmp,ret);
		//再把网络字节序ip地址转换成点分十进制IP地址
		ip = inet_ntoa(addr.sin_addr);
		//将16位的数据从网络字节序转换为主机字节序
		port = ntohs(addr.sin_port);
		return true;
	}
	bool SEND(string &buf,string &ip,uint16_t port )
	{
		//ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,const struct sockaddr *dest_addr, socklen_t addrlen);		
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		//uint16_t htons(uint16_t hostshort);
		//将16位的数据从主机字节序转换为网络字节序
		addr.sin_port = htons(port);
		//in_addr_t inet_addr(const char *cp);
		//将字符串点分十进制ip地址转换为网络字节序ip地址
		addr.sin_addr.s_addr = inet_addr(ip.c_str());
		//int bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen);
		socklen_t len = sizeof(struct sockaddr_in);
		int ret=sendto(_sockfd,buf.c_str(),buf.size(),0,(struct sockaddr*)&addr,len);
		if (ret < 0)
		{
			perror("send error");
			return false;
		}
		return true;
	}
	bool CLOSE()
	{
		if (_sockfd >= 0)
		{
			close(_sockfd);
			_sockfd = -1;
		}
	}
private:
	int _sockfd;
};

