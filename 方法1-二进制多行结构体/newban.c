#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct word{
    char line1[500];
    char line2[500];
    char line3[500];
    char line4[500];
    char line5[500];
    char line6[500];
    char line7[500];
    char line8[500];
} *p_word,*out_word;

int width=80,num_word=1,flag,num_space;
FILE *p_file;
char alignment='l',filename[20]="nancyj.data",Type[63][8][20],Text[100];
    //width用来存放字符宽度；alignment用来存放对其方式；filename用来存放字体类型文件名
    //flag用于确定字符在文件中的位置
    //Type用来存放从字体文件中读取的形状
    //Text用来储存用户输入的文字;num_word储存单词个数
    //p_word用于储存单词；out_word作为存放要输出的一行；
    //num_space用于存放要在左端输出的空格数

int out_type();   //用于控制输出的格式
void make_word();  //用于把每个单词输入到动态数组里
void put_out();    //用于输出

int main(int argc,char* argv[]){
    int i,j;
    i=1;
    while(i<argc){
        if((*(argv[i])=='-')&&(*(argv[i]+1)=='w')){
            i++;
            width=atoi(argv[i]);
        }
        if((*(argv[i])=='-')&&(*(argv[i]+1)=='r')) alignment='r';
        if((*(argv[i])=='-')&&(*(argv[i]+1)=='c')) alignment='c';
        if((*(argv[i])=='-')&&(*(argv[i]+1)=='f')){
            i++;
            strcpy(filename,argv[i]);
        }
        i++;
    }
    p_file=fopen(filename,"rb");
    fread(Type,sizeof(char),10080,p_file);
    for(;;){
        gets(Text);
        if(strcmp(Text,"quit")==0) exit(0);
        for(i=0;i<strlen(Text);i++){
            if(Text[i]==' ') num_word++;
        }
        out_word=(struct word*)malloc(sizeof(struct word));
        p_word=(struct word *)calloc(num_word,sizeof(struct word));
        make_word();
        strcpy(out_word->line1,p_word->line1);
        strcpy(out_word->line2,p_word->line2);
        strcpy(out_word->line3,p_word->line3);
        strcpy(out_word->line4,p_word->line4);
        strcpy(out_word->line5,p_word->line5);
        strcpy(out_word->line6,p_word->line6);
        strcpy(out_word->line7,p_word->line7);
        strcpy(out_word->line8,p_word->line8);
        if(num_word==1){
            put_out();
        }else{
            for(i=1;i<num_word;i++){
                if((strlen(out_word->line1)+strlen((p_word+i)->line1)+strlen(Type[62][0]))<=width){
                    strcat(out_word->line1,Type[62][0]);
                    strcat(out_word->line2,Type[62][1]);
                    strcat(out_word->line3,Type[62][2]);
                    strcat(out_word->line4,Type[62][3]);
                    strcat(out_word->line5,Type[62][4]);
                    strcat(out_word->line6,Type[62][5]);
                    strcat(out_word->line7,Type[62][6]);
                    strcat(out_word->line8,Type[62][7]);
                    strcat(out_word->line1,(p_word+i)->line1);
                    strcat(out_word->line2,(p_word+i)->line2);
                    strcat(out_word->line3,(p_word+i)->line3);
                    strcat(out_word->line4,(p_word+i)->line4);
                    strcat(out_word->line5,(p_word+i)->line5);
                    strcat(out_word->line6,(p_word+i)->line6);
                    strcat(out_word->line7,(p_word+i)->line7);
                    strcat(out_word->line8,(p_word+i)->line8);
                }else{
                    put_out();
                    strcpy(out_word->line1,(p_word+i)->line1);
                    strcpy(out_word->line2,(p_word+i)->line2);
                    strcpy(out_word->line3,(p_word+i)->line3);
                    strcpy(out_word->line4,(p_word+i)->line4);
                    strcpy(out_word->line5,(p_word+i)->line5);
                    strcpy(out_word->line6,(p_word+i)->line6);
                    strcpy(out_word->line7,(p_word+i)->line7);
                    strcpy(out_word->line8,(p_word+i)->line8);
                }
            }
            put_out();
        }
        free(out_word);
        free(p_word);
        num_word=1;
    }
    fclose(p_file);
    return 0;
}

int out_type()
{
    if(alignment=='l') return 0;
    if(alignment=='c') return (width-strlen(out_word->line1))/2;
    if(alignment=='r') return (width-strlen(out_word->line1));
}

void make_word()
{
    int i,j;
    j=0;
    for(i=0;i<strlen(Text);i++){
        if(Text[i]==' '){
            j++;
        }else{
            if(Text[i]>='a'&&Text[i]<='z') flag=(int)Text[i]-97;
            if(Text[i]>='A'&&Text[i]<='Z') flag=(int)Text[i]-39;
            if(Text[i]>='0'&&Text[i]<='9') flag=(int)Text[i]+4;
            strcat((p_word+j)->line1,Type[flag][0]);
            strcat((p_word+j)->line2,Type[flag][1]);
            strcat((p_word+j)->line3,Type[flag][2]);
            strcat((p_word+j)->line4,Type[flag][3]);
            strcat((p_word+j)->line5,Type[flag][4]);
            strcat((p_word+j)->line6,Type[flag][5]);
            strcat((p_word+j)->line7,Type[flag][6]);
            strcat((p_word+j)->line8,Type[flag][7]);
        }
    }
}

void put_out()
{
    int j;
    num_space=out_type();
    for(j=0;j<num_space;j++){
        printf(" ");
    }
    puts(out_word->line1);
    for(j=0;j<num_space;j++){
        printf(" ");
    }
    puts(out_word->line2);
    for(j=0;j<num_space;j++){
        printf(" ");
    }
    puts(out_word->line3);
    for(j=0;j<num_space;j++){
        printf(" ");
    }
    puts(out_word->line4);
    for(j=0;j<num_space;j++){
        printf(" ");
    }
    puts(out_word->line5);
    for(j=0;j<num_space;j++){
        printf(" ");
    }
    puts(out_word->line6);
    for(j=0;j<num_space;j++){
        printf(" ");
    }
    puts(out_word->line7);
    for(j=0;j<num_space;j++){
        printf(" ");
    }
    puts(out_word->line8);
}
