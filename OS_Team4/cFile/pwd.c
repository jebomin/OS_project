#include "../Header/main.h"

//pwd
int PrintPath(DirectoryTree* dirTree, Stack* dirStack)
{

    TreeNode* tmpNode = NULL;
    tmpNode = dirTree->current;
    //if current directory is root
    if(tmpNode == dirTree->root){
        printf("/");
    }
    else{
        //until current directory is root, repeat Push
        while(tmpNode->Parent != NULL){
            Push(dirStack, tmpNode->name);
            tmpNode = tmpNode->Parent;
        }
    //until stack is empty, repeat Pop
        while(IsEmpty(dirStack) == 0){
            printf("/");
            printf("%s",Pop(dirStack));
        }
    }
    printf("\n");
    return 0;
}

int pwd(DirectoryTree* dirTree, Stack* dirStack, char* cmd)
{
    char* str = NULL;
    if(cmd == NULL){
        PrintPath(dirTree, dirStack);
    }
    else if(cmd[0] == '-'){
        if(strcmp(cmd, "--help") == 0){
            printf("사용법: pwd\n");
            printf("  Print the name of the current working directory.\n\n");
            printf("  Options:\n");
            printf("        --help\t 이 도움말을 표시하고 끝냅니다\n");
            return -1;
        }
        else{
            str = strtok(cmd, "-");
            if(str == NULL){
                printf("pwd: 잘못된 연산자\n");
                printf("Try 'pwd --help' for more information.\n");
                return -1;
            }
            else{
            printf("pwd: 부적절한 옵션 -- '%s'\n", str);
            printf("Try 'pwd --help' for more information.\n");
            return -1;
            }
        }
    }

    return 0;
}