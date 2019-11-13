//通过这个程序使用mysql API 实现数据插入的功能
//

#include<cstdio>
#include<cstdlib>
//编译器默认从/uer/include目录中查找头文件，但是mysql.h在一个mysql的目录中，所以要写详细的头文件
#include<mysql/mysql.h>

int main()
{
  //1.创建一个数据库连接句柄
  MYSQL* connect_fd = mysql_init(NULL);

  //2.和数据库建立连接(和TCP的区分开，这个是在应用层建立连接的)
  //连接过程需要指定一些必要的信息
  //a)连接句柄
  //b)服务器ip地址
  //d)用户名
  //e)密码
  //f)数据库名(blog_system2)
  //c)服务器端口号
  //g)unix_sock NULL 套接字
  //h)client_flag 0 标记位 
  
  if (mysql_real_connect(connect_fd,"127.0.0.1","root","","blog_system2",3306,NULL,0) == NULL)
  {
    printf("连接失败! %s\n",mysql_error(connect_fd));  //mysql_error将错误码翻译成我们能够看懂的
    return 1;
  }
  printf("连接成功!\n");


  //3.设置编码方式
  // mysql server 部分最初安装的时候已经设置成了utf8
  // 也得在客户端这边设置成utf8
  mysql_set_character_set(connect_fd,"utf8");

  //4.拼接sql语句
  char sql[1024*4] = {0};
  char title[] = "立一个flag";
  char content[] = "我要拿30W年薪";
  int tag_id = 1;
  char date[] = "2019/07/25";
  sprintf(sql,"insert into blog_table values(null,'%s','%s',%d,'%s')",title,content,tag_id,date);
  printf("sql:%s\n",sql);
  
  //5.让数据库服务器执行 sql 
  int ret = mysql_query(connect_fd,sql);
  if(ret < 0)
  {
    printf("执行sql失败! %s\n",mysql_error(connect_fd));
    mysql_close(connect_fd);
    return 1;
  }
  printf("插入成功!\n");

  //6.断开连接
  mysql_close(connect_fd);
  return 0;
}

