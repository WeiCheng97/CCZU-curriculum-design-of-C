#include<stdio.h>

struct fonts {
    char a;
    char sharp[8][20];
};

int main()
{
    struct fonts line[63]= {
        {'a',"        ","        ",".d8888b.","88'  `88","88.  .88","`88888P8","        ","        "},
        {'b',"dP      ","88      ","88d888b.","88'  `88","88.  .88","88Y8888'","        ","        "},
        {'c',"        ","        ",".d8888b.","88'  `\"\"","88.  ...","`88888P'","        ","        "},
        {'d',"      dP","      88",".d888b88","88'  `88","88.  .88","`88888P8","        ","        "},
        {'e',"        ","        ",".d8888b.","88ooood8","88.  ...","`88888P'","        ","        "},
        {'f',".8888b","88   \"","88aaa ","88    ","88    ","dP    ","      ","      "},
        {'g',"        ","        ",".d8888b.","88'  `88","88.  .88","`8888P88","    0.88"," d8888P "},
        {'h',"dP      ","88      ","88d888b.","88'  `88","88    88","dP    dP","        ","        "},
        {'i',"oo","  ","dP","88","88","dP","  ","  "},
        {'j',"oo","  ","dP","88","88","88","88","dP"},
        {'k',"dP      ","88      ","88  .dP ","88888\"  ","88  `8b.","dP   `YP","        ","        "},
        {'l',"dP","88","88","88","88","dP","  ","  "},
        {'m',"          ","          ","88d8b.d8b.","88'`88'`88","88  88  88","dP  dP  dP","          ","          "},
        {'n',"        ","        ","88d888b.","88'  `88","88    88","dP    dP","        ","        "},
        {'o',"        ","        ",".d8888b.","88'  `88","88.  .88","`88888P'","        ","        "},
        {'p',"        ","        ","88d888b.","88'  `88","88.  .88","88Y888P'","88      ","dP      "},
        {'q',"        ","        ",".d8888b.","88'  `88","88.  .88","`8888P88","      88","      dP"},
        {'r',"        ","        ","88d888b.","88'  `88","88      ","dP      ","        ","        "},
        {'s',"        ","        ",".d8888b.","Y8ooooo.","88      ","`88888P'","        ","        "},
        {'t',"  dP  ","  88  ","d8888P","  88  ","  88  ","  dP  ","      ","      "},
        {'u',"        ","        ","dP    dP","88    88","88.  .88","`88888P'","        ","        "},
        {'v',"        ","        ","dP   .dP","88   d8'","88 .88' ","8888P'  ","        ","        "},
        {'w',"          ","          ","dP  dP  dP","88  88  88","88.88b.88'","8888P Y8P ","          ","          "},
        {'x',"        ","        ","dP.  .dP"," `8bd8' "," .d88b. ","dP'  `dP","        ","        "},
        {'y',"        ","        ","dP    dP","88    88","88.  .88","`8888P88","    0.88"," d8888P "},
        {'z',"        ","        ","d888888b","   .d8P'"," .Y8P   ","d888888P","        ","        "},
        {'A',"MMP\"\"\"\"\"\"\"MM","M' .mmmm  MM","M         `M","M  MMMMM  MM","M  MMMMM  MM","M  MMMMM  MM","MMMMMMMMMMMM","            "},
        {'B',"M#\"\"\"\"\"\"\"'M ","##  mmmm. `M","#'        .M","M#  MMMb.'YM","M#  MMMM'  M","M#       .;M","M#########M ","            "},
        {'C',"MM'\"\"\"\"'YMM","M' .mmm. `M","M  MMMMMooM","M  MMMMMMMM","M. `MMM' .M","MM.     .dM","MMMMMMMMMMM","           "},
        {'D',"M\"\"\"\"\"\"'YMM","M  mmmm. `M","M  MMMMM  M","M  MMMMM  M","M  MMMM' .M","M       .MM","MMMMMMMMMMM","           "},
        {'E',"MM\"\"\"\"\"\"\"\"`M","MM  mmmmmmmM","M`      MMMM","MM  MMMMMMMM","MM  MMMMMMMM","MM        .M","MMMMMMMMMMMM","            "},
        {'F',"MM\"\"\"\"\"\"\"\"`M","MM  mmmmmmmM","M'      MMMM","MM  MMMMMMMM","MM  MMMMMMMM","MM  MMMMMMMM","MMMMMMMMMMMM","            "},
        {'G',"MM'\"\"\"\"\"`MM","M' .mmm. `M","M  MMMMMMMM","M  MMM   `M","M. `MMM' .M","MM.     .MM","MMMMMMMMMMM","           "},
        {'H',"M\"\"MMMMM\"\"MM","M  MMMMM  MM","M         `M","M  MMMMM  MM","M  MMMMM  MM","M  MMMMM  MM","MMMMMMMMMMMM","            "},
        {'I',"M\"\"M","M  M","M  M","M  M","M  M","M  M","MMMM","    "},
        {'J',"MMMMMMMM\"\"M","MMMMMMMM  M","MMMMMMMM  M","MMMMMMMM  M","M. `MMM' .M","MM.     .MM","MMMMMMMMMMM","           "},
        {'K',"M\"\"MMMMM\"\"M","M  MMMM' .M","M       .MM","M  MMMb. YM","M  MMMMb  M","M  MMMMM  M","MMMMMMMMMMM","           "},
        {'L',"M\"\"MMMMMMMM","M  MMMMMMMM","M  MMMMMMMM","M  MMMMMMMM","M  MMMMMMMM","M         M","MMMMMMMMMMM","           "},
        {'M',"M\"\"\"\"\"`'\"\"\"`YM","M  mm.  mm.  M","M  MMM  MMM  M","M  MMM  MMM  M","M  MMM  MMM  M","M  MMM  MMM  M","MMMMMMMMMMMMMM","              "},
        {'N',"M\"\"\"\"\"\"\"`YM","M  mmmm.  M","M  MMMMM  M","M  MMMMM  M","M  MMMMM  M","M  MMMMM  M","MMMMMMMMMMM","           "},
        {'O',"MMP\"\"\"\"\"YMM","M' .mmm. `M","M  MMMMM  M","M  MMMMM  M","M. `MMM' .M","MMb     dMM","MMMMMMMMMMM","           "},
        {'P',"MM\"\"\"\"\"\"\"`YM","MM  mmmmm  M","M'        .M","MM  MMMMMMMM","MM  MMMMMMMM","MM  MMMMMMMM","MMMMMMMMMMMM","            "},
        {'Q',"MM'\"\"\"\"\"`MMM","M  .mmm,  MM","M  MMMMM  MM","M  MM  M  MM","M  `MM    MM","MM.    .. `M","MMMMMMMMMMMM","            "},
        {'R',"MM\"\"\"\"\"\"\"`MM","MM  mmmm,  M","M'        .M","MM  MMMb. \"M","MM  MMMMM  M","MM  MMMMM  M","MMMMMMMMMMMM","            "},
        {'S',"MP\"\"\"\"\"\"`MM","M  mmmmm..M","M.      `YM","MMMMMMM.  M","M. .MMM'  M","Mb.     .dM","MMMMMMMMMMM","           "},
        {'T',"M\"\"\"\"\"\"\"\"M","Mmmm  mmmM","MMMM  MMMM","MMMM  MMMM","MMMM  MMMM","MMMM  MMMM","MMMMMMMMMM","          "},
        {'U',"M\"\"MMMMM\"\"M","M  MMMMM  M","M  MMMMM  M","M  MMMMM  M","M  `MMM'  M","Mb       dM","MMMMMMMMMMM","           "},
        {'V',"M\"\"MMMMM\"\"M","M  MMMMM  M","M  MMMMP  M","M  MMMM' .M","M  MMP' .MM","M     .dMMM","MMMMMMMMMMM","           "},
        {'W',"M\"\"MMM""MMM\"\"M","M  MMM  MMM  M","M  MMP  MMP  M","M  MM'  MM' .M","M  `' . '' .MM","M    .d  .dMMM","MMMMMMMMMMMMMM","              "},
        {'X',"M\"\"MMMM\"\"M","M  `MM'  M","MM.    .MM","M  .mm.  M","M  MMMM  M","M  MMMM  M","MMMMMMMMMM","          "},
        {'Y',"M\"\"MMMM\"\"M","M. `MM' .M","MM.    .MM","MMMb  dMMM","MMMM  MMMM","MMMM  MMMM","MMMMMMMMMM","          "},
        {'Z',"M\"\"\"\"\"\"\"\"`M","Mmmmmm   .M","MMMMP  .MMM","MMP  .MMMMM","M' .MMMMMMM","M         M","MMMMMMMMMMM","           "},
        {'0'," a8888a ","d8' ..8b","88 .P 88","88 d' 88","Y8'' .8P"," Y8888P ","        ","        "},
        {'1',"d88 "," 88 "," 88 "," 88 "," 88 ","d88P","    ","    "},
        {'2',"d8888b.","    `88",".aaadP'","88'    ","88     ","Y88888P","       ","       "},
        {'3',"d8888b.","    `88"," aaad8'","    `88","   0.88","d88888P","       ","       "},
        {'4',"dP   dP","88   88","88aaa88","     88","     88","     dP","       ","       "},
        {'5',"888888P","88'    ","88baaa.","    `88","     88","d88888P","       ","       "},
        {'6',".d8888P","88'    ","88baaa.","88` `88","8b. .d8","`Y888P'","       ","       "},
        {'7',"d88888P","    d8'","   d8' ","  d8'  "," d8'   ","d8'    ","       ","       "},
        {'8',".d888b.","Y8' `8P","d8bad8b","88` `88","8b. .88","Y88888P","       ","       "},
        {'9',".d888b.","Y8' `88","`8bad88","    `88","d.  .88","`8888P ","       ","       "},
        {' ',"    ","    ","    ","    ","    ","    ","    ","    "}
        };
        FILE *p;
        p=fopen("nancyj_fancy.data","wb");
        fwrite(line,sizeof(struct fonts),63,p);
        fclose(p);
        return 0;
    }
