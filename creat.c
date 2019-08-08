#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<mxml.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
	//文件头
	mxml_node_t *root = mxmlNewXML("1.0");///""里面的是版本号
	//根标签
	//根标签的父节点就是文件头创建的结点
	mxml_node_t* china = mxmlNewElement(root,"china");//第一个参数就是父节点，第二个参数就是标签的名称
	//子标签 ---city
	mxml_node_t* city = mxmlNewElement(china,"city");//第一个参数就是父节点名称，第二个就是新建的这个的标签名称
	mxml_node_t* info = mxmlNewElement(china,"name");
	//标签赋值
	mxmlNewText (info,0,"北京");//第一个参数结点地址也就是名称，这里定义的函数传的是指针，可以查看原函数，第二个参数是否空白，第三个参数就是内容
	//设置节点属性名和属性值
	mxmlElementSetAttr(info,"isbig","YES");// 被设置属性的节点,节点的属性名,属性值
	//面积
	info = mxmlNewElement(city,"area");
	mxmlNewText (info,0,"16410平方公里");
	//人口
	info = mxmlNewElement(city,"population");
	mxmlNewText (info,0,"2170万");
	//人均GDP
	info = mxmlNewElement(city,"GDP");
	mxmlNewText (info,0,"24541亿");
	//东京
	city = mxmlNewElement(china,"city");
	info = mxmlNewElement(china,"name");
	mxmlNewText (info,0,"东京");
	mxmlElementSetAttr(info,"isbig","TRUR");
	info = mxmlNewElement(city,"area");
	mxmlNewText (info,0,"164平方公里");
	info = mxmlNewElement(city,"population");
    mxmlNewText (info,0,"21万");
	info = mxmlNewElement(city,"GDP");
	mxmlNewText (info,0,"24541亿");

	//数据保存到磁盘文件
	FILE * fd = fopen("china.xml","w");
	mxmlSaveFile(root,fd,MXML_NO_CALLBACK);
	fclose(fd);
	mxmlDelete(root);//只需要删除根节点就可以了
	return 0;
}
