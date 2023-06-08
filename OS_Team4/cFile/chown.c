#include "../Header/main.h"

//chown
int ChangeOwner(DirectoryTree* dirTree, char* userName, char* dirName, int flag)
{
    TreeNode* tmpNode = NULL;
    TreeNode* tmpNode2 = NULL;
    UserNode* tmpUser = NULL;

    tmpNode = IsExistDir(dirTree, dirName, 'd');
    tmpNode2 = IsExistDir(dirTree, dirName, 'f');


    if(tmpNode != NULL){
        if(HasPermission(tmpNode, 'w') != 0){
            printf("chown: Can not modify file '%s': Permission denied\n", dirName);
            return -1;
        }
        tmpUser = IsExistUser(usrList, userName);
        if(tmpUser != NULL){
            if (!flag)
                tmpNode->UID = tmpUser->UID;
            else
                tmpNode->GID = tmpUser->GID;
        }
        else{
            printf("chown: %s: illegal user name\n", userName);
            printf("Try 'chown --help' for more information.\n");
            return -1;
        }
    }
    else if(tmpNode2 != NULL){
        if(HasPermission(tmpNode2, 'w') != 0){
            printf("chown: %s: Operation not permitted\n", dirName);
            return -1;
        }
        tmpUser = IsExistUser(usrList, userName);
        if(tmpUser != NULL){
            if (!flag)
                tmpNode2->UID = tmpUser->UID;
            else
                tmpNode2->GID = tmpUser->GID;
        }
        else{
            printf("chown: %s: illegal user name\n", userName);
            printf("Try 'chown —help' for more information.\n");
            return -1;
        }
    }
    else{
        printf("chown: %s: No such file or directory\n", dirName);
        return -1;
    }

    return 0;
}

int chown_(DirectoryTree* dirTree, char* cmd)
{
    TreeNode* tmpNode = NULL;
    ThreadNode threadTree[MAX_THREAD];
    pthread_t threadPool[MAX_THREAD];
    char tmp[MAX_NAME];
    int count = 0;
    UserNode* tmpUser = NULL;
    char *str;

    if (cmd == NULL) {
        printf("chown: Invalid option\n");
        printf("Try 'chown --help' for more information.\n");
        return -1;
    }
    if (cmd[0] == '-') {
        if(!strcmp(cmd, "--help")) {
            printf("Usage: chown [OPTION]... [OWNER] FILE...\n");
            printf("Change the owner of each FILE to OWNER.\n\n");
            printf("  Options:\n");
            printf("  -R, --recursive        operate on files and directories recursively\n");
            printf("      --help     display this help and exit\n");
            return -1;
        } else {
            str = strtok(cmd, "-");
            if (!str) {
                printf("chown: Invalid option\n");
                printf("Try 'chown --help' for more information.\n");
                return -1;
            } else {
                printf("chown: Unrecognized option -- '%s'\n", str);
                printf("Try 'chown --help' for more information.\n");
                return -1;
            }
        }
    } else {
        strncpy(tmp, cmd, MAX_NAME);
        str = strtok(NULL, " ");
        if (!str) {
            printf("chown: Invalid option\n");
            printf("Try 'chown --help' for more information.\n");
            return -1;
        } else {
            threadTree[count].threadTree = dirTree;
            threadTree[count].usrName = tmp;
            threadTree[count++].cmd = str;
            while (str) {
                threadTree[count].threadTree = dirTree;
                threadTree[count].usrName = tmp;
                threadTree[count++].cmd = str;
                str = strtok(NULL, " ");
            }
        }
    }
    for (int i = 0; i < count; i++) {
        pthread_create(&threadPool[i], NULL, chownThread, (void*)&threadTree[i]);
        pthread_join(threadPool[i], NULL);
    }
    return 0;
}