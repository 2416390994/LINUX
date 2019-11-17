#include"db.hpp"
//使用这个程序测试封装的MYSQL操作是否正确
void TestBlogTable()
{
  Json::StyledWriter write; //将查找结果来给我们格式化生成的东西

  MYSQL* mysql = blog_system::MySQLInit();
  blog_system::BlogTable blog_table(mysql);
  //测试插入
  Json::Value blog;
  blog["title"] = "我的第一篇博客";
  blog["content"] = "我要好好学习";
  blog["tag_id"] = 1;
  blog["create_time"] = "2019/07/28";
  bool ret = blog_table.Insert(blog);
  printf("insert:%d\n",ret);
  
  //测试查找所有
  //Json::Value blogs;
  //int ret = blog_table.SelectAll(&blogs);
  //printf("selct all %d\n",ret);
  //printf("blogs = %s\n",write.write(blogs).c_str());

  //测试查找单个博客
  //Json::Value blog;
  //int  ret = blog_table.SelectOne(1,&blog);
  //printf("select ont %d\n",ret);
  //printf("blog: %s\n",write.write(blog).c_str());
  
  //测试修改博客
  //Json::Value blog;
  //blog["blog_id"] = 1;
  //blog["title"] = "明天就礼拜五了";
  //blog["tag_id"] = 10;
  //blog["content"] = "1.明天吃个好的\n,2.洗个头，'要有洗头膏";
  //int ret = blog_table.Update(blog);
  //printf("update %d\n",ret);
  
  //测试删除
  //int ret = blog_table.Delect(2);
  //printf("delete %d\n",ret);

  //销毁句柄
  blog_system::MySQLRelease(mysql);
}
void TestTagTable()
{
  Json::StyledWriter write;  //用这个将输出结果序列化

  MYSQL* mysql = blog_system::MySQLInit();
  blog_system::TagTable tag_table(mysql);
  
  //测试插入
  Json::Value tag;
  tag["tag_name"] = "C语言";
  bool ret = tag_table.Insert(tag);
  printf("Insert %d",ret);

  //测试查找
  //Json::Value tags;
  //bool ret = tag_table.SelectAll(&tags);
  //printf("select all %d\n",ret);
  //printf("tags: %s\n",write.write(tags).c_str());
  
  //测试删除
  //bool ret = tag_table.Delect(1);
  //printf("delete %d\n",ret);
  //blog_system::MySQLRelease(mysql);
}
int main()
{
  TestBlogTable();
  //TestTagTable();
  return 0;
}
