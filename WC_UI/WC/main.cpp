#include "mainwindow.h"
#include<qdebug.h>
#include <QApplication>

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <io.h>

#define bufsize 200
#define maxlen_filename 100

using namespace std;

struct Topt
{
    bool s,c,w,l,a;//选择参数
};

class Twc{
private:
    int num_of_characters;//字符数量
    int num_of_words;//词数
    int num_of_rows;//行数
    int num_of_codeLines;//代码行数
    int num_of_blankLines;//空白行数
    int num_of_commentLines;//注释行数
    struct Topt opt;
public:
    Twc(){
        num_of_characters=num_of_words=num_of_rows=num_of_codeLines=num_of_blankLines=num_of_commentLines=0;
        opt.s=opt.c=opt.w=opt.l=opt.a=false;
    };
    void CalRows(FILE *fp);
    void CalCharacters(FILE*fp);
    void CalWords(FILE*fp);
    void CalCodelines(FILE*fp);
    void CalCommentlines(FILE*fp);
    void ListFiles(string path,string mode);
    void Work(char*filename);
    void Choose(int argc,char*argv[]);
    bool SomethingTrue();
};

bool IsCharacter(char ch){//用于判断除制表符、空格、回车之外可见的字符
    if(ch=='\t'||ch==' '||ch=='\n')return false;
    else return true;
};

bool IsCharacter_(char ch){//用于判断英文字母
    if(ch>='0'&&ch<='9')return true;
    if(ch>='a'&&ch<='z')return true;
    if(ch>='A'&&ch<='Z')return true;
    return false;
};

void Twc::CalRows(FILE *fp){//计算行数
    char flag=0;int count=0;
    while(!feof(fp)){
        flag=fgetc(fp);
        if(flag=='\n')
            count++;
    }
    num_of_rows=count+1;
    qDebug()<<"the number of rows is "<<num_of_rows<<endl;
    rewind(fp);//重置文件指针到文件开头准备进行下一步操作
    return;
}

void Twc::CalCharacters(FILE *fp){//计算字符数
    char flag=0;int count=0;
    while(!feof(fp)){
        flag=fgetc(fp);
        if(IsCharacter(flag))
            count++;
    }
    num_of_characters=count-1;
    qDebug()<<"the number of characters is "<<num_of_characters<<endl;
    rewind(fp);
    return;
}

void Twc::CalWords(FILE*fp){//计算词数
    char str[bufsize];
    int len;//每行的字符数
    int count=0;
    while(!feof(fp)){
        fgets(str,bufsize,fp);
        len=strlen(str);
        for(int i=0;i<len;i++)
        {
            if(IsCharacter_(str[i])){
                if(i==0||!IsCharacter_(str[i-1]))
                    count++;
            }
        }
    }
    num_of_words=count;
    qDebug()<<"the number of words is "<<num_of_words<<endl;
    rewind(fp);
    return;
}

void Twc::CalCodelines(FILE*fp){//计算代码行数和空行
    char str[bufsize];
    int len;
    int show_code,code_line,blank_line;//每行可见字符数
    show_code=code_line=blank_line=0;
    while(!feof(fp)){
        fgets(str,bufsize,fp);
        len=strlen(str);
        for(int i=0;i<len;i++){
            if(IsCharacter(str[i]))
                show_code++;
        }
        if(show_code>1)
            code_line++;
        else
            blank_line++;
        show_code=0;//置零，计算下一行
    }
    num_of_codeLines=code_line;
    num_of_blankLines=blank_line;
    qDebug()<<"the number of code lines is "<<num_of_codeLines<<endl;
    qDebug()<<"the number of blank lines is "<<num_of_blankLines<<endl;
    rewind(fp);
    return;
}

void Twc::CalCommentlines(FILE*fp){//计算注释行
    char str[bufsize];
    int len;//每行的字符数
    int count=0;
    int show_comment=0;
    bool is_commentline= false;
    while(!feof(fp)){
        fgets(str,bufsize,fp);
        len=strlen(str);
        for(int i=0;i<len;i++){
            if(IsCharacter(str[i])){
                show_comment++;
                if(str[i]=='/'){
                    if(i+1<len&&str[i+1]=='/')
                        is_commentline= true;
                    break;
                }
                if(show_comment>1)
                    break;
            }
        }
        if(is_commentline==true)
            count++;
    }
    num_of_commentLines =count;
    qDebug()<<"the number of comment lines is "<<num_of_commentLines<<endl;
    rewind(fp);
    return;
}

void Twc::Work(char *filename) {//运行函数
    if(opt.s== true){
        string mode = filename;
        string path=".\\";
        ListFiles(path,mode);
        return;
    }
    FILE *fp=fopen(filename,"r");
    if(fp==NULL){
        qDebug()<<"open file error!"<<endl;
        qDebug()<<"Press any key to continue"<<endl;
        getchar();
        exit(0);
    }
    if(opt.l==true){
        CalRows(fp);
    }
    if(opt.c== true){
        CalCharacters(fp);
    }
    if(opt.a==true){
        CalCodelines(fp);
        CalCommentlines(fp);
    }
    if(opt.w== true){
        CalWords(fp);
    }
}

void Twc::ListFiles(string path,string mode){//递归处理目录下符合条件的文件
    _finddata_t file;
    intptr_t HANDLE;
    string Onepath = path + mode;
    HANDLE = _findfirst(Onepath.c_str(), &file);
    if (HANDLE == -1L)
    {
        qDebug() << "can not match the folder path" << endl;
        system("pause");
    }
    do {
        //判断是否有子目录
        if (file.attrib & _A_SUBDIR)
        {
            //判断是否为"."当前目录，".."上一层目录
            if ((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0))
            {
                string newPath = path +"\\" + file.name;
                ListFiles(newPath,mode);
            }
        }
        else
        {
            qDebug() << file.name << " " << endl;
            FILE *fp=fopen(&file.name[0],"r");
            if(fp==NULL){
                qDebug()<<"open file error!"<<endl;
                qDebug()<<"Press any key to continue"<<endl;
                getchar();
                exit(0);
            }
            if(opt.l==true){
                CalRows(fp);
            }
            if(opt.c== true){
                CalCharacters(fp);
            }
            if(opt.a==true){
                CalCodelines(fp);
                CalCommentlines(fp);
            }
            if(opt.w== true){
                CalWords(fp);
            }
            qDebug()<<"------------------------------"<<endl;
        }
    } while (_findnext(HANDLE, &file) == 0);
    _findclose(HANDLE);
}

void Twc::Choose(int argc,char*argv[]){//参数选择
    for(int i=0;i<argc-1;i++){

        if(strcmp(argv[i],"-s")==0){
            opt.s=true;
        }
        if(strcmp(argv[i],"-c")==0){
            opt.c=true;
        }
        if(strcmp(argv[i],"-w")==0){
            opt.w=true;
        }
        if(strcmp(argv[i],"-l")==0){
            opt.l=true;
        }
        if(strcmp(argv[i],"-a")==0){
            opt.a=true;
        }
    }
}
bool Twc::SomethingTrue(){
    if(opt.a||opt.c||opt.l||opt.s||opt.w)
        return true;
    else return false;
}
int main(int argc, char *argv[])
{
    char filename[maxlen_filename];
    strcpy(filename,argv[argc-1]);
    Twc filefp;
    filefp.Choose(argc,argv);
    if(filefp.SomethingTrue()){
    filefp.Work(filename);
    return 0;
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString("word count"));
    w.show();
    w.setAutoFillBackground(true);
    QPalette palette=w.palette();
    palette.setBrush(QPalette::Window,QBrush(QPixmap("C:\\Users\\24277\\Documents\\WC\\a.PNG").scaled(w.size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    w.setPalette(palette);
    return a.exec();
}
