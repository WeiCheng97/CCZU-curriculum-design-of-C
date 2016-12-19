#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct lined {
    char line[400];
}*Type,*p_word,*out_word,*isover,*alter1,*alter2,*alter3,*copy;
//用于存放行，加上确定行的大小

int width=80,num_word=1,flag,num_space,high;
FILE *p_file;
char alignment='l',filename[20]="nancyj.data",Text[100],highc[30];
//high用于确定文件中每个字母的高度
//width用来存放字符宽度；alignment用来存放对其方式；filename用来存放字体类型文件名
//flag用于确定字符在文件中的位置
//Type用来存放从字体文件中读取的形状
//Text用来储存用户输入的文字;num_word储存单词个数
//p_word用于储存单词；out_word作为存放要输出的一行
//isover用于在判断单词长度是否越界时存放单词
//num_space用于存放要在左端输出的空格数
//alter1,alter2,alter3,copy用于实现相邻字母共用相同字符

void read();       //用于从文件中读取图形信息
void put_in();     //用于用户输入，并计算单词数
void buffer();     //用于处理连接，判断何时输出
int out_type();    //用于控制输出的格式
void iswordover(); //用于判断单个单词是否超出了长度，并改变单词歌词个数num_word
void make_word();  //用于把每个单词输入到动态数组里
void put_out();    //用于输出
int issame(int j); //用于判断一个单词中相邻的字母的相接处是否一样
void alter(int j);      //用于改变单词相邻两个字母的连接处

int main(int argc,char* argv[])
{
    int i;
    i=1;
    while(i<argc) {
        if((*(argv[i])=='-')&&(*(argv[i]+1)=='w')) {
            i++;
            width=atoi(argv[i]);
        }
        if((*(argv[i])=='-')&&(*(argv[i]+1)=='r')) alignment='r';
        if((*(argv[i])=='-')&&(*(argv[i]+1)=='c')) alignment='c';
        if((*(argv[i])=='-')&&(*(argv[i]+1)=='f')) {
            i++;
            strcpy(filename,argv[i]);
        }
        i++;
    }
    read();
    for(;;){
        put_in();
        make_word();
        buffer();
        num_word=1;
        free(p_word);
    }
	return 0;
}

void read()
{
    int i,j;
    p_file=fopen(filename,"r");
    fgets(highc,30,p_file);
    high=atoi(highc);
    Type=(struct lined *)calloc((63*high),sizeof(struct lined));
    for(i=0; i<63; i++) {
        for(j=0; j<high; j++) {
            fgets((Type+(i*high)+j)->line,30,p_file);
            (Type+(i*high)+j)->line[strlen((Type+(i*high)+j)->line)-1]=(Type+(i*high)+j)->line[strlen((Type+(i*high)+j)->line)];
        }
    }
    fclose(p_file);
}

void put_in()
{
    int i;
    gets(Text);
    if(strcmp(Text,"quit")==0) exit(0);
    for(i=0; i<strlen(Text); i++) {
        if(Text[i]==' ') num_word++;
    }
    iswordover();
}

void buffer(){
    int i,j;
    out_word=(struct lined*)calloc(high,sizeof(struct lined));
    for(i=0; i<high; i++) {
            strcpy((out_word+i)->line,(p_word+i)->line);
        }
    if(num_word==1) {
        put_out();
    } else {
        for(i=1; i<num_word; i++) {
            if(strlen(out_word->line)+strlen((p_word+(i*high))->line)+strlen((Type+(62*high))->line)<=width) {
                for(j=0; j<high; j++) {
                    strcat((out_word+j)->line,(Type+(62*high)+j)->line);
                }
                for(j=0; j<high; j++) {
                    strcat((out_word+j)->line,(p_word+(i*high)+j)->line);
                }
            } else {
                put_out();
                for(j=0; j<high; j++) {
                    strcpy((out_word+j)->line,(p_word+(i*high)+j)->line);
                }
            }
        }
        put_out();
    }
    free(out_word);
}

int out_type()
{
    if(alignment=='l') return 0;
    if(alignment=='c') return (width-strlen(out_word->line))/2;
    if(alignment=='r') return (width-strlen(out_word->line));
}

void iswordover()
{
    int i,j,n,m,k;
    isover=(struct lined*)calloc(high,sizeof(struct lined));
    for(i=0; i<strlen(Text); i++) {
        if(Text[i]!=' ') {
            if(Text[i]>='a'&&Text[i]<='z') k=(int)Text[i]-97;
            if(Text[i]>='A'&&Text[i]<='Z') k=(int)Text[i]-39;
            if(Text[i]>='0'&&Text[i]<='9') k=(int)Text[i]+4;
            for(j=0; j<high; j++) {
                strcat((isover+j)->line,(Type+k*high+j)->line);
            }
        } else {
            n=strlen(isover->line);
            m=(int)(n/width);
            num_word+=m;
            for(j=0; j<high; j++) {
                memset((isover+j)->line,0,30);
            }
        }
    }
    n=strlen(isover->line);
    m=(int)(n/width);
    num_word+=m;
    free(isover);
}


void make_word()
{
    int i,j,k;
    p_word=(struct lined *)calloc((num_word*high),sizeof(struct lined));
    j=0;
    for(i=0; i<strlen(Text); i++) {
        if((Text[i]==' ')||(strlen((p_word+j*high)->line)>width)) {
            j++;
            if(strlen((p_word+(j-1)*high)->line)>width) {
                if(Text[i]>='a'&&Text[i]<='z') flag=(int)Text[i]-97;
                if(Text[i]>='A'&&Text[i]<='Z') flag=(int)Text[i]-39;
                if(Text[i]>='0'&&Text[i]<='9') flag=(int)Text[i]+4;
                for(k=0; k<high; k++) {
                    strcat((p_word+j*high+k)->line,(Type+flag*high+k)->line);
                }
            }
        } else {
            if(Text[i]>='a'&&Text[i]<='z') flag=(int)Text[i]-97;
            if(Text[i]>='A'&&Text[i]<='Z') flag=(int)Text[i]-39;
            if(Text[i]>='0'&&Text[i]<='9') flag=(int)Text[i]+4;
            if(issame(j)&&strlen((p_word+j*high)->line)>1) {
                alter(j);
            } else {
                for(k=0; k<high; k++) {
                    strcat((p_word+j*high+k)->line,(Type+flag*high+k)->line);
                }
            }
        }
    }
}

void put_out()
{
    int j,k;
    num_space=out_type();
    for(k=0; k<high; k++) {
        for(j=0; j<num_space; j++) {
            printf(" ");
        }
        puts((out_word+k)->line);
    }
}

int issame(int j)
{
    int i,m=1;
    for(i=0; i<high; i++) {
        if(((p_word+j*high+i)->line[strlen((p_word+j*high+i)->line)-1]!=(Type+flag*high+i)->line[0])
                &&((p_word+j*high+i)->line[strlen((p_word+j*high+i)->line)-1]!=' ')
                &&((Type+flag*high+i)->line[0]!=' ')) {
            m=0;
        }
    }
    return m;
}

void alter(int j)
{
    int i,k;
    char a[5],b[5],c[30];
    alter1=(struct lined*)calloc(high,sizeof(struct lined));
    alter2=(struct lined*)calloc(high,sizeof(struct lined));
    alter3=(struct lined*)calloc(high,sizeof(struct lined));
    copy=(struct lined*)calloc(high,sizeof(struct lined));
    for(i=0; i<high; i++) {
        strcpy((copy+i)->line,(Type+flag*high+i)->line);
    }
    for(i=0; i<high; i++) {
        a[0]=(p_word+j*high+i)->line[strlen((p_word+j*high+i)->line)-1];
        a[1]='\0';
        b[0]=(copy+i)->line[0];
        b[1]='\0';
        strcpy((alter1+i)->line,a);
        strcpy((alter2+i)->line,b);
    }
    for(i=0; i<high; i++) {
        if(strcmp((alter1+i)->line,(alter2+i)->line)==0) {
            strcpy((alter3+i)->line,(alter1+i)->line);
        } else if((strcmp((alter1+i)->line," ")==0)&&(strcmp((alter2+i)->line," ")!=0)) {
            strcpy((alter3+i)->line,(alter2+i)->line);
        } else if((strcmp((alter2+i)->line," ")==0)&&(strcmp((alter1+i)->line," ")!=0)) {
            strcpy((alter3+i)->line,(alter1+i)->line);
        }
    }
    for(i=0; i<high; i++) {
        (p_word+j*high+i)->line[strlen((p_word+j*high+i)->line)-1]=(p_word+j*high+i)->line[strlen((p_word+j*high+i)->line)];
        for(k=0; k<strlen((copy+i)->line)-1; k++) {
            c[k]=(copy+i)->line[k+1];
        }
        c[strlen((copy+i)->line)-1]='\0';
        strcpy((copy+i)->line,c);
    }
    for(i=0; i<high; i++) {
        strcat((p_word+j*high+i)->line,(alter3+i)->line);
        strcat((p_word+j*high+i)->line,(copy+i)->line);
    }
    free(copy);
    free(alter1);
    free(alter2);
    free(alter3);
}