#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    if(argc < 2)
    {
       char gorod[] = "Moscow";
       char pogoda[] = "curl -sLo file8.txt https://wttr.in/Moscow?format=j1";
       char pogoda_Paris[] = "curl -sLo file9.txt https://wttr.in/Paris?format=j1";
       char enter_gorod[] = "curl -sLo file10.txt https://wttr.in/London?format=j1";
       system("help");
       system("cd");
       //system("CHCP 1251");
       system("CHCP ");
       system("cd C:");
       system("cd /D G:\English");
       //system("cmd");
       //system("help cd");
       //system("CMD");
       system("curl --help");
       system("curl -OL https://wttr.in/Moscow?format=j1");
       system("curl -sLo file1.txt https://wttr.in/Moscow?format=j1");
       system("curl -sLo file2.txt https://wttr.in/city?format=j1");
       system("curl -sLo file3.txt https://wttr.in/ogorod?format=j1");
       system("curl -sLo file4.txt https://wttr.in/54?format=j1");
       system("curl -sLo file5.txt https://wttr.in/200?format=j1");
       system("curl -sLo file6.txt https://wttr.in/params=gorod?format=j1");
       system("curl -sLo file7.txt https://wttr.in/params={gorod}?format=j1");
       //system("pause");
       //_wsystem("");
       system(pogoda);
       system(pogoda_Paris);
       system(enter_gorod);
    }
    if(argc >= 2)
    {
       system("curl -sLo file7.txt https://wttr.in/params=argv[1]?format=j1");
    }
    printf("Hello world!\n");
    return 0;
}
