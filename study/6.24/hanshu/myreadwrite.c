#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
int main(int argc,char*argv[])
{
    if (argc!=2)
    {
        char buf[20]="./filename\n";
        write(STDOUT_FILENO,buf,sizeof(buf));
        return -1;
    }
    int fd = open(argv[1],O_RDWR|O_CREAT,0666);
    //打开一个文件，若这个文件不存在则创建，创建出来的文件权限为666&~权限掩码umask
    //用一个文件描述符指向这个文件
    write(fd,"helloworld\n",12);
    //write函数写入helloword,在这个文件描述符指向，大小12个字节
    lseek(fd,0,SEEK_SET);
    //由于写入了helloworld，所以这个文件的的读写位置指到了文件末尾
    //要是这个时候直接进行读取的话时读不到内容的，因为读写位置已经指到了末尾
    char buf1[256];
    int ret = read(fd,buf1,sizeof(buf1));
    //文件读写位置调整之后，再对文件进行读操作，读取长度为sizeof（buf1），内容存到缓冲区
    //返回值为读到的长度ret
    if (ret)
    {
        write(STDOUT_FILENO,buf1,ret);
    }
    //如果读到内容则就进行输出
    close(fd);
    return 0; 
}
