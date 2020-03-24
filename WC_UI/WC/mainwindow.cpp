#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int num_of_codeLines;
int num_of_blankLines;
#define bufsize 200
#define maxlen_filename 100


bool IsCharacterUI(char ch){//用于判断除制表符、空格、回车之外可见的字符
    if(ch=='\t'||ch==' '||ch=='\n')return false;
    else return true;
};

bool IsCharacter_UI(char ch){//用于判断英文字母
    if(ch>='0'&&ch<='9')return true;
    if(ch>='a'&&ch<='z')return true;
    if(ch>='A'&&ch<='Z')return true;
    return false;
};

int CalRows(FILE *fp){//计算行数
    char flag=0;int count=0;
    while(!feof(fp)){
        flag=fgetc(fp);
        if(flag=='\n')
            count++;
    }
    int num_of_rows=count+1;
    rewind(fp);//重置文件指针到文件开头准备进行下一步操作
    return num_of_rows;
}

int CalCharacters(FILE *fp){//计算字符数
    char flag=0;int count=0;
    while(!feof(fp)){
        flag=fgetc(fp);
        if(IsCharacterUI(flag))
            count++;
    }
    int num_of_characters=count-1;
    rewind(fp);
    return num_of_characters;
}

int CalWords(FILE*fp){//计算词数
    char str[bufsize];
    int len;//每行的字符数
    int count=0;
    while(!feof(fp)){
        fgets(str,bufsize,fp);
        len=strlen(str);
        for(int i=0;i<len;i++)
        {
            if(IsCharacter_UI(str[i])){
                if(i==0||!IsCharacter_UI(str[i-1]))
                    count++;
            }
        }
    }
    int num_of_words=count;
    rewind(fp);
    return num_of_words;
}

void CalCodelines(FILE*fp){//计算代码行数和空行
    char str[bufsize];
    int len;
    int show_code,code_line,blank_line;//每行可见字符数
    show_code=code_line=blank_line=0;
    while(!feof(fp)){
        fgets(str,bufsize,fp);
        len=strlen(str);
        for(int i=0;i<len;i++){
            if(IsCharacterUI(str[i]))
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
    rewind(fp);
    return;
}

int CalCommentlines(FILE*fp){//计算注释行
    char str[bufsize];
    int len;//每行的字符数
    int count=0;
    int show_comment=0;
    bool is_commentline= false;
    while(!feof(fp)){
        fgets(str,bufsize,fp);
        len=strlen(str);
        for(int i=0;i<len;i++){
            if(IsCharacterUI(str[i])){
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
    int num_of_commentLines =count;
    rewind(fp);
    return num_of_commentLines;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename =QFileDialog::getOpenFileName(this,tr("请选择想要查询的文件"),"C:",tr("代码文件(*cpp *c);;""文本文件(*txt)"));
    ui->lineEdit->setText(filename);
}


void MainWindow::on_pushButton_2_clicked()
{
    QString filename=ui->lineEdit->text();
    if(filename.isEmpty()){
        return;
    }
    QByteArray ba = filename.toLatin1(); // must
    char*name=ba.data();
    FILE *fp=fopen(name,"r");
    if(fp==NULL){
        ui->textBrowser->append(tr("无法打开文件！"));
        return;
    }
    ui->textBrowser->append(tr(name));
    ui->textBrowser->append(tr("文件行数为 %1").arg(QString::number(CalRows(fp))));
    ui->textBrowser->append(tr("文件字符数为 %1").arg(QString::number(CalCharacters(fp))));
    ui->textBrowser->append(tr("文件词数为 %1").arg(QString::number(CalWords(fp))));
    CalCodelines(fp);
    ui->textBrowser->append(tr("文件代码行数为 %1").arg(QString::number(num_of_codeLines)));
    ui->textBrowser->append(tr("文件空行数为 %1").arg(QString::number(num_of_blankLines)));
    ui->textBrowser->append(tr("文件注释数为 %1").arg(QString::number(CalCommentlines(fp))));
    ui->textBrowser->append(tr("\n"));
}
