#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int wid=80,n_flag=0,flag[50];
char ali='l',fil[30]="kcsj.data",a[63][6][30],T[500],put[6][500];
FILE *p;
//wid为规定宽度
//ali为对齐方式
//fil为字体文件

void putin();
int cat(char x);
void sign();
void make();
void putout();

int main(int argc,char* argv[]){
    int i,j;
    i=1;
    while(i<argc){
        if((*(argv[i])=='-')&&(*(argv[i]+1)=='w')){
            i++;
            wid=atoi(argv[i]);
        }
        if((*(argv[i])=='-')&&(*(argv[i]+1)=='r')) ali='r';
        if((*(argv[i])=='-')&&(*(argv[i]+1)=='c')) ali='c';
        if((*(argv[i])=='-')&&(*(argv[i]+1)=='f')){
            i++;
            strcpy(fil,argv[i]);
        }
        i++;
    }
    p=fopen(fil,"rb");
    fread(a,sizeof(char),11340,p);
    fclose(p);
    for(;;){
        putin();
        sign();
        make();
    }
    return 0;
}

void putin()
{
    gets(T);
    if(strcmp(T,"quit")==0) exit(0);
}

int cat(char x){
    int k;
    if(x>='a'&&x<='z') k=(int)x-97;
    if(x>='A'&&x<='Z') k=(int)x-39;
    if(x>='0'&&x<='9') k=(int)x+4;
    if(x==' ') k=62;
    return k;
}

void sign()
{
    int i,j,k,qizhi=0,diwei,k_set;
    char use[500];
    memset(use,0,500);
    for(i=0;i<strlen(T);i++){
        k=cat(T[i]);
        if((strlen(use)+strlen(a[k][0]))<=wid){
            if(T[i]==' '){
                qizhi=1;
                diwei=i-1;
            }
            strcat(use,a[k][0]);
        }else{
            if(qizhi==1){
                if(T[i]==' '){
                    flag[n_flag]=i-1;
                    n_flag++;
                    memset(use,0,500);
                }else{
                    flag[n_flag]=diwei;
                    n_flag++;
                    memset(use,0,500);
                    for(j=diwei+2;j<=i;j++){
                        k_set=cat(T[j]);
                        strcat(use,a[k_set][0]);
                    }
                }
            }else{
                flag[n_flag]=i-1;
                n_flag++;
                memset(use,0,500);
            }
            qizhi=0;
        }
    }
    flag[n_flag]=strlen(T)-1;
    n_flag++;
}

void make()
{
    int i,j,z,k,m=0,n;
    for(j=0;j<6;j++){
        memset(put[j],0,500);
    }
    for(i=0;i<n_flag;i++){
        for(j=m;j<=flag[i];j++){
            k=cat(T[j]);
            for(z=0;z<6;z++){
                strcat(put[z],a[k][z]);
            }
        }
        putout();
        for(z=0;z<6;z++){
            memset(put[z],0,500);
        }
        m=flag[i]+1;
        if(T[j]==' ') m++;
    }
}

void putout()
{
    int i,j,k;
    if(ali=='l') k=0;
    if(ali=='c') k=(wid-strlen(put[0]))/2;
    if(ali=='r') k=(wid-strlen(put[0]));
    for(i=0;i<6;i++){
        for(j=0;j<k;j++){
            printf(" ");
        }
        puts(put[i]);
    }
}
