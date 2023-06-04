#include "../Header/main.h"

int MoveCurrent(DirectoryTree* dirTree, char* dirPath)
{
    TreeNode* tmpNode = NULL;
    if(strcmp(dirPath,".") == 0){
    }
    else if(strcmp(dirPath,"..") == 0){
        if(dirTree->current != dirTree->root){
            dirTree->current = dirTree->current->Parent;
        }
    }
    else{

        tmpNode = IsExistDir(dirTree, dirPath, 'd');
        if(tmpNode != NULL){
            dirTree->current = tmpNode;
        }
        else
            return -1;
    }
    return 0;
}

int MovePath(DirectoryTree* dirTree, char* dirPath)
{
    TreeNode* tmpNode = NULL;
    char tmpPath[MAX_DIR];
    char* str = NULL;
    int val = 0;

    strncpy(tmpPath, dirPath, MAX_DIR);
    tmpNode = dirTree->current;
    //if input is root
    if(strcmp(dirPath, "/") == 0){
        dirTree->current = dirTree->root;
    }
    else{
        //if input is absolute path
        if(strncmp(dirPath, "/",1) == 0){
            if(strtok(dirPath, "/") == NULL){
                return -1;
            }
            dirTree->current = dirTree->root;
        }
        //if input is relative path
        str = strtok(tmpPath, "/");
        while(str != NULL){
            val = MoveCurrent(dirTree, str);
            //if input path doesn't exist
            if(val != 0){
                dirTree->current = tmpNode;
                return -1;
            }
            str = strtok( NULL, "/");
        }
    }
    return 0;
}

int cd(DirectoryTree* dirTree, char* cmd)
{
    TreeNode* tmpNode = NULL;
    char* str = NULL;
    char tmp[MAX_DIR];
    int val;

    if(cmd == NULL){
        strcpy(tmp, usrList->current->dir);
        MovePath(dirTree, tmp);
    }
    else if(cmd[0] == '-'){
        if(strcmp(cmd, "--help") == 0){
            printf("사용법: cd 디렉터리...\n");
            printf("  Change the shell working directory.\n\n");
            printf("  Options:\n");
            printf("        --help\t 이 도움말을 표시하고 끝냅니다\n");
            return -1;
        }
        else{
            str = strtok(cmd, "-");
            if(str == NULL){
                printf("cd: 잘못된 연산자\n");
                printf("Try 'cd --help' for more information.\n");
                return -1;
            }
            else{
            printf("cd: 부적절한 옵션 -- '%s'\n", str);
            printf("Try 'cd --help' for more information.\n");

            return -1;
            }
        }
    }
    else{
        tmpNode = IsExistDir(dirTree, cmd, 'd');
        if(tmpNode != NULL){
            if(HasPermission(tmpNode, 'r') != 0){
                printf("-bash: cd: '%s': 허가거부\n", cmd);
                return -1;
            }
        }
        tmpNode = IsExistDir(dirTree, cmd,  'f');
        if(tmpNode != NULL){
            printf("-bash: cd: '%s': 디렉터리가 아닙니다\n", cmd);
            return -1;
        }
        val = MovePath(dirTree, cmd);
        if(val != 0)
            printf("-bash: cd: '%s': no such file or directory\n", cmd);
    }
    return 0;
}