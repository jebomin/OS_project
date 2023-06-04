#include "../Header/main.h"

void Login(UserList* userList, DirectoryTree* dirTree)
{
    UserNode* tmpUser = NULL;
    char userName[MAX_NAME];
    char tmp[MAX_DIR];

    tmpUser= userList->head;

    printf("Users: ");
    while(tmpUser != NULL){
        printf("%s ", tmpUser->name);
        tmpUser = tmpUser->LinkNode;
    }
    printf("\n");

    while(1){
        printf("Login as: ");
        fgets(userName, sizeof(userName), stdin);
        userName[strlen(userName)-1] = '\0';
        if(strcmp(userName, "exit") == 0){
            exit(0);
        }
        tmpUser = IsExistUser(userList, userName);
        if(tmpUser != NULL){
            userList->current = tmpUser;
            break;
        }
        printf("'%s' 유저가 존재하지 않습니다\n", userName);
    }
    strcpy(tmp, userList->current->dir);
    MovePath(dirTree, tmp);
}

void PrintHead(DirectoryTree* dirTree, Stack* dirStack)
{
    TreeNode* tmpNode = NULL;
    char tmp[MAX_DIR] = "";
    char tmp2[MAX_DIR] = "";
    char usr;

    if(usrList->current == usrList->head)
        usr = '#';
    else
        usr = '$';

    printf("%s@os-Virtualbox", usrList->current->name);
    DEFAULT;
    printf(":");
    tmpNode = dirTree->current;

    if(tmpNode == dirTree->root){
        strcpy(tmp, "/");
    }
    else{
        while(tmpNode->Parent != NULL){
            Push(dirStack, tmpNode->name);
            tmpNode = tmpNode->Parent;
        }
        while(IsEmpty(dirStack) == 0){
                strcat(tmp, "/");
                strcat(tmp ,Pop(dirStack));
        }
    }

    strncpy(tmp2, tmp, strlen(usrList->current->dir));

    if(usrList->current == usrList->head){
        printf("%s", tmp);
    }
    else if(strcmp(usrList->current->dir, tmp2) != 0){
        printf("%s", tmp);
    }
    else{
        tmpNode = dirTree->current;
        while(tmpNode->Parent != NULL){
            Push(dirStack, tmpNode->name);
            tmpNode = tmpNode->Parent;
        }
        Pop(dirStack);
        Pop(dirStack);
        printf("~");
        while(IsEmpty(dirStack) == 0){
            printf("/");
            printf("%s",Pop(dirStack));
        }
    }
    DEFAULT;
    printf("%c ", usr);
}