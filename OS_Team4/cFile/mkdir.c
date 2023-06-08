#include "../Header/main.h"

int MakeDir(DirectoryTree* dirTree, char* dirName, char type)
{
    TreeNode* NewNode = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* tmpNode = NULL;

    if(HasPermission(dirTree->current, 'w') != 0){
        printf("mkdir: '%s' Can not create directory: Permission denied.\n", dirName);
        free(NewNode);
        return -1;
    }
    if(strcmp(dirName, ".") == 0 || strcmp(dirName, "..") == 0){
        printf("mkdir: '%s' Can not create directory.\n", dirName);
        free(NewNode);
        return -1;
    }
    tmpNode = IsExistDir(dirTree, dirName, type);
    if(tmpNode != NULL && tmpNode->type == 'd'){
        printf("mkdir: '%s' Can not create directory: File exists \n", dirName);
        free(NewNode);
        return -1;
    }
    time(&ltime);
    today = localtime(&ltime);

    NewNode->LeftChild = NULL;
    NewNode->RightSibling = NULL;

    strncpy(NewNode->name, dirName, MAX_NAME);
    if(dirName[0] == '.'){
        NewNode->type = 'd';
        //rwx------
        NewNode->mode = 700;
        NewNode->SIZE = 4096;
    }
    else if(type == 'd'){
        NewNode->type = 'd';
        //rwxr-xr-x
        NewNode->mode = 755;
        NewNode->SIZE = 4096;
    }
    else{
        NewNode->type = 'f';
        //rw-r--r--
        NewNode->mode = 644;
        NewNode->SIZE = 0;
    }
    Mode2Permission(NewNode);
    NewNode->UID = usrList->current->UID;
    NewNode->GID = usrList->current->GID;
    NewNode->month = today->tm_mon + 1;
    NewNode->day = today->tm_mday;
    NewNode->hour = today->tm_hour;
    NewNode->minute = today->tm_min;
    NewNode->Parent = dirTree->current;

    if(dirTree->current->LeftChild == NULL){
        dirTree->current->LeftChild = NewNode;
    }
    else{
        tmpNode = dirTree->current->LeftChild;

        while(tmpNode->RightSibling!= NULL){
            tmpNode = tmpNode->RightSibling;
        }
        tmpNode->RightSibling = NewNode;
    }

    return 0;
}

int Mkdir(DirectoryTree* dirTree, char* cmd)
{
    TreeNode *tmpNode = NULL;
    char *str;
    int isDirectoryExist;
    int tmpMode;
    int count = 0;

    if (!cmd) {
        printf("mkdir: Invalid option\n");
        printf("Try 'mkdir --help' for more information.\n");
        return -1;
    }
    
    pthread_t threadPool[MAX_THREAD];
    ThreadNode threadTree[MAX_THREAD];
    tmpNode = dirTree->current;

    if (cmd[0] == '-') {
        if (!strcmp(cmd, "-p")) {
            str = strtok(NULL, " ");
            if (!str) {
                printf("mkdir: Invalid option\n");
                printf("Try 'mkdir --help' for more information.\n");
                return -1;
            }
            while (str) {
                threadTree[count].threadTree = dirTree;
                threadTree[count].option = 1;
                threadTree[count++].cmd = str;
                str = strtok(NULL, " ");
            }
        } else if (!strcmp(cmd, "--help")) {
            printf("Usage: mkdir [option]... [directory]...\n");
            printf("  Create the DIRECTORY(ies), if they do not already exists.\n\n");
            printf("  Options:\n");
            printf("    -p, --parents  \t no error if existing, make parent directories as needed\n");
            printf("      --help\t Display this help and exit\n");
            return -1;
        } else {
            str = strtok(cmd, "-");
            if (!str) {
                printf("mkdir: Invalid option\n");
                printf("Try 'mkdir --help' for more information.\n");
                return -1;
            } else {
                printf("mkdir: Unrecognized option -- '%s'\n", str);
                printf("Try 'mkdir --help' for more information.\n");
                return -1;
            }
        }
    } else {
        str = strtok(NULL, " ");
        threadTree[count].threadTree = dirTree;
        threadTree[count].option = 0;
        threadTree[count++].cmd = cmd;
        while (str) {
            threadTree[count].threadTree = dirTree;
            threadTree[count].option = 0;
            threadTree[count++].cmd = str;
            str = strtok(NULL, " ");
        }
    }
    for (int i = 0; i < count; i++) {
        pthread_create(&threadPool[i], NULL, mkdirThread, (void *)&threadTree[i]);
        pthread_join(threadPool[i], NULL);
    }
    return 0;
}

