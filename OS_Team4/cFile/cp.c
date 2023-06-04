#include "../Header/main.h"

int mycp(DirectoryTree* dirTree,char* sName, char* oName){

    //printf("source : %s\n",sName);
    //printf("object : %s\n\n",oName);

    char buf[1024];
    int in, out;
    int nread;

    if(access(sName,F_OK) != 0) {
        printf("원본 파일이 존재하지 않습니다.\n");
        return -1;
    }
    if(strcmp(sName,oName) == 0) {
        printf("원본과 대상이 같습니다.\n");
        return -1;
    }

    in = open(sName,O_RDONLY); //원본파일
    out = open(oName, O_WRONLY| O_CREAT, S_IRUSR| S_IWUSR);//만들파일
    nread = read(in,buf,sizeof(buf)); //읽은만큼 nread가 올라가고
    write(out,buf,nread);          //read만큼 쓴다.

    MakeDir(dirTree, oName, 'f');

   return 0;
}