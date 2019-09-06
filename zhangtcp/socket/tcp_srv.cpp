/*=============================================================== 
*   Copyright (C) . All rights reserved.")
*   文件名称： 
*   创 建 者：zhang
*   创建日期：
*   描    述：基于封装的TcpSocket，实现tcp服务端程序 
*       1. 创建套接字
*       2. 为套接字绑定地址信息
*       3. 开始监听
*       while(1) {
*           4. 从已完成连接队列，获取新建的客户端连接socket
*           5. 通过新建的客户端连接socket，与指定的客户端进行通信，recv
*           6. send
*       }
*       7. 关闭套接字
================================================================*/

#include "tcpsocket.hpp"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout<<"./tcp_srv 192.168.122.132 9000\n";
        return -1;
    }
    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    TcpSocket sock;

    CHECK_RET(sock.Socket());
    CHECK_RET(sock.Bind(ip, port));
    CHECK_RET(sock.Listen());
    while(1) {
        TcpSocket clisock;
        std::string cliip;
        uint16_t cliport;
        if (sock.Accept(clisock, cliip, cliport) == false){
            continue;
        }
        std::cout<<"new client:"<<cliip<<":"<<cliport<<std::endl;

        std::string buf;
        clisock.Recv(buf);
        std::cout<<"client say:"<<buf<<std::endl;

        buf.clear();
        std::cout<< "server say:";
        fflush(stdout);
        std::cin >> buf;
        clisock.Send(buf);
    }
    sock.Close();
}
