#include "../Header/main.h"

void Instruction(DirectoryTree* dirTree, char* cmd)
{
    char* str;
    char* str1;
    char* str2;
    char* option1;
    char* option2;
    char* searching_word;
    char* file_name;
    int ignore_case = 0;
    int invert_match = 0;
    int val;
    if(strcmp(cmd, "") == 0 || cmd[0] == ' '){
        return;
    }
    str = strtok(cmd, " ");
//cmd를 띄어쓰기 기준으로 나눠줌
    if(strcmp(str, "mkdir") == 0){
        str = strtok(NULL, " ");
        val = Mkdir(dirTree, str);
        if(val == 0){
            SaveDir(dirTree, dStack);
        }
    }
    else if(strcmp(str, "cp") == 0){
        str = strtok(NULL, " ");
        str1 = strtok(NULL, " ");
        val=mycp(dirTree,str,str1);
        if(val == 0){
            SaveDir(dirTree, dStack);
        }
    }
    else if(strcmp(str, "rm") == 0){
        str = strtok(NULL, " ");
        val = rm(dirTree, str);
        if(val == 0){
            SaveDir(dirTree, dStack);
        }
    }
    else if(strcmp(str, "cd") == 0){
        str = strtok(NULL, " ");
        cd(dirTree, str);
    }
    else if(strcmp(str, "pwd") == 0){
        str = strtok(NULL, " ");
        pwd(dirTree, dStack, str);
    }
    else if(strcmp(str, "ls") == 0){
        str = strtok(NULL, " ");
        if(str==NULL)
            ls(dirTree);
        else if(strcmp(str,"-a")==0)
            ls_a(dirTree);
        else if(strcmp(str,"-l")==0)
            ls_l(dirTree);
        else
            ls_al(dirTree);
    }
    else if(strcmp(str, "cat") == 0){
        str = strtok(NULL, " ");
        val = cat(dirTree, str);
        if(val == 0){
            SaveDir(dirTree, dStack);
        }
    }
    else if(strcmp(str, "chmod") == 0){
        str = strtok(NULL, " ");
        val = chmod_(dirTree, str);
        if(val == 0){
            SaveDir(dirTree, dStack);
        }
    }
    else if(strcmp(str, "chown") == 0){
        str = strtok(NULL, " ");
        val = chown_(dirTree, str);
        if(val == 0){
            SaveDir(dirTree, dStack);
        }
    }
    else if(strcmp(str, "find") == 0){
        str = strtok(NULL, " ");
        find_(dirTree, str);
    }
    else if(strcmp(cmd, "exit") == 0){
            printf("로그아웃\n");
            exit(0);
    }
    else if(strcmp(str, "grep") == 0){
            str = strtok(NULL, " ");
            grep(dirTree, str);
         }
    else{
        printf("'%s': 명령을 찾을 수 없습니다\n", cmd);
    }
    return;
}