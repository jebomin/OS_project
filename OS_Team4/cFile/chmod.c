#include "../Header/main.h"

//chmod
int ChangeMode(DirectoryTree* dirTree, int mode, char* dirName)
{
    TreeNode* tmpNode = NULL;
    TreeNode* tmpNode2 = NULL;

    tmpNode = IsExistDir(dirTree, dirName, 'd');
    tmpNode2 = IsExistDir(dirTree, dirName, 'f');

    if(tmpNode != NULL){
        if(HasPermission(tmpNode, 'w') != 0){
            printf("chmod: Can't modify file '%s': Permission denied\n", dirName);
            return -1;
        }
        tmpNode->mode = mode;
        Mode2Permission(tmpNode);
    }
    else if(tmpNode2 != NULL){
        if(HasPermission(tmpNode2, 'w') != 0){
            printf("chmod: Can not modify file '%s': Permission denied\n", dirName);
            return -1;
        }
        tmpNode2->mode = mode;
        Mode2Permission(tmpNode2);
    }
    else{
        printf("chmod: '%s에 접근할 수 없습니다: no such file or directory\n", dirName);
        return -1;
    }
    return 0;
}

int chmod_(DirectoryTree* dirTree, char* cmd)
{
    TreeNode* tmpNode = NULL;
    ThreadTree threadTree[MAX_THREAD];
    pthread_t threadPool[MAX_THREAD];
    int count = 0;
    char* str;
    int tmp;

    if (cmd == NULL) {
        printf("chmod: Invalid option\n");
        printf("Try 'chmod --help' for more information.\n");
        return -1;
    }
    if(cmd[0] == '-') {
        if (!strcmp(cmd, "--help")) {
            printf("Usage: chmod [OPTION]... OCTAL-MODE FILE...\n");
            printf("Change the mode of each FILE to MODE.\n\n");
            printf("  Options:\n");
            printf("  -R, --recursive        change files and directories recursively\n");
            printf("      --help\t Display this help and exit\n");
            return -1;
        } else {
            str = strtok(cmd, "-");
            if (!str) {
                printf("chmod: Invalid option\n");
                printf("Try 'chmod --help' for more information.\n");
                return -1;
            } else {
                printf("chmod: Unrecognized option -- '%s'\n", str);
                printf("Try 'chmod --help' for more information.\n");
                return -1;
            }
        }
    } else {
        if (cmd[0] - '0' < 8 && cmd[1] - '0' < 8 && cmd[2] - '0' < 8 && strlen(cmd) == 3) {
            tmp = atoi(cmd);
            str = strtok(NULL, " ");
            if (!str) {
                printf("chmod: Invalid option\n");
                printf("Try 'chmod --help' for more information.\n");
                return -1;
            }
            threadTree[count].threadTree = dirTree;
            threadTree[count].cmd = str;
            threadTree[count++].mode = tmp;
            while (str) {
                threadTree[count].threadTree = dirTree;
                threadTree[count].cmd = str;
                threadTree[count++].mode = tmp;
                str = strtok(NULL, " ");
            }
        } else {
            printf("chmod: Invalid Mode: '%s'\n", cmd);
            printf("Try 'chmod --help' for more information.\n");
            return -1;
        }
    }

    for (int i = 0; i < count; i++) {
        pthread_create(&threadPool[i], NULL, chmodThread, (void*)&threadTree[i]);
        pthread_join(threadPool[i], NULL);
    }
    return 0;
}