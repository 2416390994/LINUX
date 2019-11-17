//创建一些相关的类来封装数据库的操作
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<memory>
#include<mysql/mysql.h>
#include<jsoncpp/json/json.h>
namespace blog_system
{
  static MYSQL* MySQLInit()
  {
    //初始化一个MySQL句柄并且建立连接
    //1.先创建一个句柄
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
      return NULL;
    }
    //3.设置编码方式
    // mysql server 部分最初安装的时候已经设置成了utf8
    // 也得在客户端这边设置成utf8
    mysql_set_character_set(connect_fd,"utf8");
    return connect_fd;
  }
  //释放句柄，并断开连接
  static void MySQLRelease(MYSQL* connect_fd)
  {
    //释放句柄并断开连接
    mysql_close(connect_fd);
  }
  //创建一个类，用于操作博客表的类
  //当然是通过构造函数获取到数据库的操作句柄来操作数据库的
  class BlogTable
  {
  public:
    BlogTable(MYSQL* connect_fd):mysql_(connect_fd)
    {
      //通过这个构造函数获取到一个数据库的操做句柄
           
    }
    //以下操作的相关参数都统一使用json的方式
    //Json::Value jsoncpp中最核心的类
    //Json::Value  就表示一个具体的json对象
    //形如
    //{
    //  title:"博客内容",
    //  content:"博客正文",
    //  create_time:"创建时间",
    //  tag_id:"标签id"
    //}
    bool Insert(const Json::Value& blog)  //插入数据
    {
      const std::string& content = blog["content"].asString();
      //char* to = new char[content.size()*2+1];//为啥长度是*2+1，这个是官方文档的要求
      std::unique_ptr<char>to (new char[content.size() * 2+ 1]); //搞了这个之后就不用手动释放申请的空间了
      mysql_real_escape_string(mysql_,to.get(),content.c_str(),content.size());
      //上面的步骤to里面就是包含了转义之后的内容
      
      //核心就是拼装sql语句
      std::unique_ptr<char> sql(new char[content.size()* 2 + 4096]);
      // mysql_real_escape_string 使用API进行转义，防止插入的内容本身就有单引号.
      sprintf(sql.get(),"insert into blog_table values(null,'%s','%s',%d,'%s')",
          blog["title"].asCString(),
          to.get(),
          blog["tag_id"].asInt(),
          blog["create_time"].asCString());
      int ret = mysql_query(mysql_,sql.get());
      if(ret != 0)
      {
        printf("执行插入博客失败! %s\n",mysql_error(mysql_));
        return false;
      }
      ///执行插入博客成功
      printf("插入博客成功\n");
      return true;
    }
    //blogs作为一个传出参数，要包含最终的查找结果
    bool SelectAll(Json::Value* blogs,const std::string& tag_id = "")  //获取所有的博客数据
    {
      //查找不需要太长，所以可以不需要太大的长度
      char sql[1024 * 4] = {0};
      if(tag_id == "")
      {
        //此时不需要按照tag_id来筛选
        sprintf(sql,"select blog_id,title,tag_id,creat_time from blog_table");
      }
      else
      {
        //此时按照tag来筛选
        sprintf(sql,"select blog_id,title,tag_id,creat_time from blog_table where tag_id = %d",std::stoi(tag_id));
      }
      int ret = mysql_query(mysql_,sql);
      if(ret != 0)
      {
        printf("执行查找所有博客失败! %s\n",mysql_error(mysql_));
        return false;
      }
      //执行查找所有博客成功
      printf("执行查找所有博客成功!\n");
      MYSQL_RES* result = mysql_store_result(mysql_);
      int rows = mysql_num_rows(result);
      //编列结果集合，然后吧结果集合
      for(int i = 0; i < rows; ++i)
      {
        MYSQL_ROW row = mysql_fetch_row(result);
        Json::Value blog;
        //row[]中的下标和上面的select中的语句中的列是相关联的 
        blog["blog_id"] = atoi(row[0]);
        blog["title"] = row[1];
        blog["tag_id"] = atoi(row[2]);
        blog["create_time"] = row[3];
        //把数据添加到最后要传出的参数里面
        blogs->append(blog);
      }
      //mysql查询的结果集合需要及时释放
      mysql_free_result(result);
      printf("执行查找所有博客成功! 共查找的 %d 条博客\n",rows);
      return true;
    }
    //blog是一个输出型参数
    bool SelectOne(int32_t blog_id,Json::Value* blog)  //查看一个博客的数据
    {
      char sql[1024] = {0};
      sprintf(sql,"select blog_id,title,content,tag_id,creat_time from blog_table where blog_id = %d",blog_id);
      int ret = mysql_query(mysql_,sql);
      if(ret != 0)
      {
        printf("执行查找博客失败!%s\n",mysql_error(mysql_));
        return false;
      }
      MYSQL_RES* result = mysql_store_result(mysql_);
      int rows = mysql_num_rows(result);
      if(rows != 1)
      {
        printf("查找到的博客不是只有一条! 实际有%d条\n",rows);
        return false;
      }
      MYSQL_ROW row = mysql_fetch_row(result);
      (*blog)["blog_id"] = atoi(row[0]);
      (*blog)["title"] = row[1];
      (*blog)["content"] = row[2];
      (*blog)["tag_id"] = atoi(row[3]);
      (*blog)["create_time"] = row[4];
      return true;
    }
    bool Update(const Json::Value& blog) //更新博客数据
    {
       const std::string& content = blog["content"].asString();
      //char* to = new char[content.size()*2+1];//为啥长度是*2+1，这个是官方文档的要求
      std::unique_ptr<char>to (new char[content.size() * 2+ 1]); //搞了这个之后就不用手动释放申请的空间了
      mysql_real_escape_string(mysql_,to.get(),content.c_str(),content.size());
      //上面的步骤to里面就是包含了转义之后的内容
      
      //核心就是拼装sql语句
      std::unique_ptr<char> sql(new char[content.size()* 2 + 4096]);     

      sprintf(sql.get(),"update blog_table set title='%s',content='%s',tag_id=%d where blog_id = %d",
          blog["title"].asCString(),
          to.get(),
          blog["tag_id"].asInt(),
          blog["blog_id"].asInt());
      int ret = mysql_query(mysql_,sql.get());
      if(ret != 0)
      {
        printf("更新博客失败! %s\n",mysql_error(mysql_));
        return false;
      }
      printf("更新博客成功");
      return true;
    }
    bool Delect(int32_t blog_id) //删除博客数据
    {
      char sql[1024 * 4] = {0};
      sprintf(sql,"delete from blog_table where blog_id = %d",blog_id);
      int  ret = mysql_query(mysql_,sql);
      if(ret != 0)
      {
        printf("删除博客失败! %s\n",mysql_error(mysql_));
        return false;
      }
      return true;
    }
  private:
    MYSQL* mysql_;
  };
  class TagTable
  {
  public:
    TagTable(MYSQL* mysql):mysql_(mysql)
    {}
    bool Insert(const Json::Value& tag)
    {
      char sql[1024 * 4];
      sprintf(sql,"insert into tag_table values(null,'%s')",
          tag["tag_name"].asCString());
      int ret = mysql_query(mysql_,sql);
      if (ret != 0)
      {
        printf("插入标签失败！%s\n",mysql_error(mysql_));
        return false;
      }
      printf("插入标签成功\n");
      return true;
    }
    bool Delect(int32_t tag_id)
    {
      char sql[1024*4] = {0};
      sprintf(sql,"delete from tag_table where tag_id = %d",tag_id);
      int ret = mysql_query(mysql_,sql);
      if(ret != 0)
      {
        printf("删除失败! %s\n",mysql_error(mysql_));
        return false;
      }
      printf("删除标签成功\n");
      return true;
    }
    bool SelectAll(Json::Value* tags)
    {
      char sql[1024 *4] = {0} ;
      sprintf(sql,"select tag_id,tag_name from tag_table");
      int ret = mysql_query(mysql_,sql);
      if(ret != 0)
      {
        printf("查找标签失败！%s\n",mysql_error(mysql_));
        return false;
      }
      MYSQL_RES* result = mysql_store_result(mysql_);
      int rows = mysql_num_rows(result);
      for(int i = 0; i< rows; ++i)
      {
        MYSQL_ROW row = mysql_fetch_row(result);
        Json::Value tag;
        tag["tag_id"]  = atoi(row[0]);
        tag["tag_name"] = row[1];
        tags->append(tag);
      }
      printf("查找标签成功! 共找到%d\n",rows);
      return true;
    }
  private:
    MYSQL* mysql_;
  };
} //结束
