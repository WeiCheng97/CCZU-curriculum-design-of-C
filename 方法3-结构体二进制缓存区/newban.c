#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//Êä³ö¿ØÖÆ¸Ä
struct fonts{
    char letter;
    char sharp[8][20];
} line[63];

int kuandu=80,flag,qizhi=0;
char qianming[100],wenjian[30]="nancyj_fancy.data",duiqi='l';
FILE *p;
char huancun[8][400],mudi[8][400];

void duqu();
void shuru();
int dingwei(char a);
void chucun();
void shuchu();
void huancun_mudi();

int main(int argc,char *argv[])
{
    int i=1;
    while(i<argc){
        if(strcmp(argv[i],"-r")==0) duiqi='r';
        if(strcmp(argv[i],"-c")==0) duiqi='c';
        if(strcmp(argv[i],"-w")==0){
            i++;
            kuandu=atoi(argv[i]);
        }
        if(strcmp(argv[i],"-f")==0){
            i++;
            strcpy(wenjian,argv[i]);
        }
        i++;
    }
    duqu();
    for(;;){
        for(i=0;i<8;i++){
            memset(huancun[i],0,400);
            memset(mudi[i],0,400);
        }
        qizhi=0;
        shuru();
        chucun();
    }
    return 0;
}

void duqu()
{
    p=fopen(wenjian,"rb");
    fread(line,sizeof(struct fonts),63,p);
    fclose(p);
}

void shuru()
{
    gets(qianming);
    if(strcmp(qianming,"quit")==0) exit(0);
}

int dingwei(char a)
{
    int i;
    for(i=0;i<63;i++){
        if(a==line[i].letter) return i;
    }
}

void chucun()
{
    int i,j,n;
    n=strlen(qianming);
    for(i=0;i<n;i++){
        flag=dingwei(qianming[i]);
        if(qianming[i]==' '){
            huancun_mudi();
        }else{
            if((strlen(huancun[0])+strlen(line[flag].sharp[0]))>kuandu){
                huancun_mudi();
                for(j=0;j<8;j++){
                    strcpy(huancun[j],line[flag].sharp[j]);
                }
            }else{
                for(j=0;j<8;j++){
                    strcat(huancun[j],line[flag].sharp[j]);
                }
            }
        }
    }
    huancun_mudi();
    shuchu();
}

void huancun_mudi()
{
    int i;
    qizhi++;
    if(strlen(mudi[0])+strlen(line[62].sharp[0])+strlen(huancun[0])>kuandu){
        shuchu();
        for(i=0;i<8;i++){
            strcpy(mudi[i],huancun[i]);
            memset(huancun[i],0,400);
        }
    }else{
        for(i=0;i<8;i++){
            if(qizhi!=1) strcat(mudi[i],line[62].sharp[i]);
            strcat(mudi[i],huancun[i]);
            memset(huancun[i],0,400);
        }
    }
}

void shuchu()
{
    int i,j,konggeshu;
    if(duiqi=='l') konggeshu=0;
    if(duiqi=='c') konggeshu=(kuandu-strlen(mudi[0]))/2;
    if(duiqi=='r') konggeshu=kuandu-strlen(mudi[0]);
    for(i=0;i<8;i++){
        for(j=0;j<konggeshu;j++){
            printf(" ");
        }
        puts(mudi[i]);
    }
}
