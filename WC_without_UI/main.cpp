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
    bool s,c,w,l,a;//ѡ�����
};

class Twc{
private:
    int num_of_characters;//�ַ�����
    int num_of_words;//����
    int num_of_rows;//����
    int num_of_codeLines;//��������
    int num_of_blankLines;//�հ�����
    int num_of_commentLines;//ע������
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
};

bool IsCharacter(char ch){//�����жϳ��Ʊ�����ո񡢻س�֮��ɼ����ַ�
    if(ch=='\t'||ch==' '||ch=='\n')return false;
    else return true;
};

bool IsCharacter_(char ch){//�����ж�Ӣ����ĸ
    if(ch>='0'&&ch<='9')return true;
    if(ch>='a'&&ch<='z')return true;
    if(ch>='A'&&ch<='Z')return true;
    return false;
};

void Twc::CalRows(FILE *fp){//��������
    char flag=0;int count=0;
    while(!feof(fp)){
        flag=fgetc(fp);
        if(flag=='\n')
            count++;
    }
    num_of_rows=count+1;
    cout<<"the number of rows is "<<num_of_rows<<endl;
    rewind(fp);//�����ļ�ָ�뵽�ļ���ͷ׼��������һ������
    return;
}

void Twc::CalCharacters(FILE *fp){//�����ַ���
    char flag=0;int count=0;
    while(!feof(fp)){
        flag=fgetc(fp);
        if(IsCharacter(flag))
            count++;
    }
    num_of_characters=count-1;
    cout<<"the number of characters is "<<num_of_characters<<endl;
    rewind(fp);
    return;
}

void Twc::CalWords(FILE*fp){//�������
    char str[bufsize];
    int len;//ÿ�е��ַ���
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
    cout<<"the number of words is "<<num_of_words<<endl;
    rewind(fp);
    return;
}

void Twc::CalCodelines(FILE*fp){//������������Ϳ���
    char str[bufsize];
    int len;
    int show_code,code_line,blank_line;//ÿ�пɼ��ַ���
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
        show_code=0;//���㣬������һ��
    }
    num_of_codeLines=code_line;
    num_of_blankLines=blank_line;
    cout<<"the number of code lines is "<<num_of_codeLines<<endl;
    cout<<"the number of blank lines is "<<num_of_blankLines<<endl;
    rewind(fp);
    return;
}

void Twc::CalCommentlines(FILE*fp){//����ע����
    char str[bufsize];
    int len;//ÿ�е��ַ���
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
    cout<<"the number of comment lines is "<<num_of_commentLines<<endl;
    rewind(fp);
    return;
}

void Twc::Work(char *filename) {//���к���
    if(opt.s== true){
        string mode = filename;
        string path=".\\";
        ListFiles(path,mode);
        return;
    }
    FILE *fp=fopen(filename,"r");
    if(fp==NULL){
        cout<<"open file error!"<<endl;
        cout<<"Press any key to continue"<<endl;
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

void Twc::ListFiles(string path,string mode){//�ݹ鴦��Ŀ¼�·����������ļ�
    _finddata_t file;
    intptr_t HANDLE;
    string Onepath = path + mode;
    HANDLE = _findfirst(Onepath.c_str(), &file);
    if (HANDLE == -1L)
    {
        cout << "can not match the folder path" << endl;
        system("pause");
    }
    do {
        //�ж��Ƿ�����Ŀ¼
        if (file.attrib & _A_SUBDIR)
        {
            //�ж��Ƿ�Ϊ"."��ǰĿ¼��".."��һ��Ŀ¼
            if ((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0))
            {
                string newPath = path +"\\" + file.name;
                ListFiles(newPath,mode);
            }
        }
        else
        {
            cout << file.name << " " << endl;
            FILE *fp=fopen(&file.name[0],"r");
            if(fp==NULL){
                cout<<"open file error!"<<endl;
                cout<<"Press any key to continue"<<endl;
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
            cout<<"------------------------------"<<endl;
        }
    } while (_findnext(HANDLE, &file) == 0);
    _findclose(HANDLE);
}

void Twc::Choose(int argc,char*argv[]){//����ѡ��
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
int main(int argc,char*argv[]){
    char filename[maxlen_filename];
    strcpy(filename,argv[argc-1]);
    Twc filefp;
    filefp.Choose(argc,argv);
    filefp.Work(filename);
    return 0;
}