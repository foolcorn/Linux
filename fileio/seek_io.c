#include<sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

//-实现一个小功能，读取命令行类似./seek_io testfile s100000 wabc
//-意思是，指定testfile文件，lseek到100000的偏移量，然后写入abc
//-对于Rxxx和rxxx，都是读取xxxlength的字节，但是r以文本形式输出，R以16进制输出
int seek_io(int argc,char*argv[]){
    size_t len;//-指定R和r读的字节数
    off_t offset;//-指定偏移量
    int fd;//-文件描述符
    int ap;//-读取命令行的指针
    int j;//-读取字符串中字符的指针
    char *buf;
    ssize_t numRead,numWritten;//-系统调用read，write的返回值
    //-没有读取到合法命令行参数，或者用户调用了 --help
    //-给予提示信息应输入格式类似于“wxxx”，“rxxx”，“Rxxx”,“sxxx”
    if(argc < 3||strcmp(argv[1],"--help")==0){
        usageErr("%s input arg param seem like wxxx,rxxx,Rxxx,sxxx",argv[0]);
    }
    fd = open(argv[1],O_RDWR | O_CREAT,666);
    if(fd == -1){
        errExit("open");
    }
    for(ap = 2;ap<argc;++ap){
        //-根据参数的首字符就可以判断要干啥
        switch(argv[ap][0]){
            case 'r': //-合并r和R的标志，同样处理
            case 'R':
                len = getLong(&argv[ap][1],GN_ANY_BASE,argv[ap]);
                buf = malloc(len);
                if(buf == NULL){
                    errExit("malloc");
                }
                //-从fd读取len长度的字节到buf中
                numRead = read(fd,buf,len);
                if(numRead == -1){
                    errExit("read");
                }
                if(numRead == 0){//-如果在读取指定len之前就读完了所有文件，进行提示
                    fprintf(stdout,"%s: read all\n",argv[ap]);
                }else{
                    //-否则将buf里的字节按顺序打印在屏幕上
                    fprintf(stdout,"%s: ",argv[ap]);
                    for(j = 0;j<numRead;++j){
                        if(argv[ap][0] == 'r'){
                            //-按字节打印
                            fprintf(stdout,"%c",isprint((unsigned char)buf[j])?buf[j]:'?');
                        }else{
                            //-按16进制打印
                            fprintf(stdout,"%02x ",(unsigned int)buf[j]);
                        }
                    }
                    printf("\n");
                }
                //-把临时空间销毁
                free(buf);
                break;
            case 'w':
                //-把wxxx的xxx全部写入fd
                numWritten = write(fd,&argv[ap][1],strlen(&argv[ap][1]));
                if(numWritten == -1){
                    errExit("write");
                }
                //-若写入成功输出写了多少个字节
                fprintf(stdout,"%s wrote %ld bytes",argv[ap],(long)numWritten);
                break;
            case 's':
                offset = getLong(&argv[ap][1],GN_ANY_BASE,argv[ap]);
                if(lseek(fd,offset,SEEK_SET) == -1){
                    errExit("lseek");
                }
                //-偏移成功进行提示
                fprintf(stdout, "%s seek success\n",argv[ap]);
                break;
            default:
                //-提示错误，输入的命令行不按规定格式
                cmdLineErr("Arg param must start with [R,r,s,w]:%s\n",argv[ap]);
        }

    }
    exit(EXIT_SUCCESS);
}
