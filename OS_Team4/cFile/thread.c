#include "../Header/main.h"

//catThread
void *catThread(void *arg) {
    ThreadTree *threadTree = (ThreadTree *)arg;
    DirectoryTree *dirTree = threadTree->threadTree;
    DirectoryTree *tmpTree;
    char *cmd = threadTree->cmd;
    TreeNode *currentNode = dirTree->current;
    TreeNode *tmpNode = NULL;
    TreeNode *tmpNode2 = NULL;
    char tmp[MAX_DIR];
    char tmp2[MAX_DIR];
    char tmp3[MAX_DIR];
    char *str;
    int option = threadTree->option;
    int val;

    strncpy(tmp, cmd, MAX_DIR);

    if (option == 1) {
        if (!strstr(tmp, "/")) {
            if (HasPermission(dirTree->current, 'w')) {
                printf("cat: Can not create file '%s': Permission denied\n", dirTree->current->name);
                return NULL;
            }
            
            tmpNode = IsExistDir(dirTree, cmd, 'd');
            tmpNode2 = IsExistDir(dirTree, cmd, 'f');

            if (!tmpNode && !tmpNode2) {
                printf("cat: '%s': No such file or directory.\n", cmd);
                return NULL;
            } else if (tmpNode && !tmpNode2) {
                printf("cat: '%s': Is a directory\n", cmd);
                return NULL;
            } else if (tmpNode2 && HasPermission(tmpNode2, 'r')) {
                printf("cat: Can not open file '%s': Permission denied\n", tmpNode2->name);
                return NULL;
            } else {
                Concatenate(dirTree, cmd, 2);
            }
        } else {
            strncpy(tmp2, getDir(tmp), MAX_DIR);
            val = MovePath(dirTree, tmp2);
            if (val) {
                printf("cat: '%s': No such file or directory.\n", tmp2);
                return NULL;
            }
            str = strtok(tmp, "/");
            while (str) {
                strncpy(tmp3, str, MAX_NAME);
                str = strtok(NULL, "/");
            }
            tmpNode = IsExistDir(dirTree, tmp3, 'd');
            tmpNode2 = IsExistDir(dirTree, tmp3, 'f');
            if(!tmpNode && !tmpNode2) {
                printf("cat: '%s': No such file or directory.\n", tmp3);
                dirTree->current = currentNode;
                return NULL;
            } else if (tmpNode && !tmpNode2) {
                printf("cat: '%s': Is a directory\n", tmp3);
                dirTree->current = currentNode;
                return NULL;
            } else if (tmpNode2 && HasPermission(tmpNode2, 'r')) {
                printf("cat: Can not open file '%s': Permission denied\n", tmpNode2->name);
                dirTree->current = currentNode;
                return NULL;
            } else {
                Concatenate(dirTree, tmp3, 2);
            }
            dirTree->current = currentNode;
        }
    } else {
        if (!strstr(tmp, "/")) {
            if (HasPermission(dirTree->current, 'w')) {
                printf("cat: Can not create file '%s': Permission denied\n", dirTree->current->name);
                return NULL;
            }
            tmpNode = IsExistDir(dirTree, cmd, 'd');
            tmpNode2 = IsExistDir(dirTree, cmd, 'f');
            if (!tmpNode && !tmpNode2) {
                printf("cat: '%s': No such file or directory.\n", cmd);
                return NULL;
            } else if (tmpNode && !tmpNode2) {
                printf("cat: '%s': Is a directory\n", cmd);
                return NULL;
            } else if (tmpNode2 && HasPermission(tmpNode2, 'r')) {
                printf("cat: Can not open file '%s': Permission denied\n", tmpNode2->name);
                return NULL;
            } else Concatenate(dirTree, cmd, 1);
        } else {
            strncpy(tmp2, getDir(tmp), MAX_DIR);
            val = MovePath(dirTree, tmp2);
            if (val) {
                printf("cat: '%s': No such file or directory.\n", tmp2);
                return NULL;
            }
            str = strtok(tmp, "/");
            while (str) {
                strncpy(tmp3, str, MAX_NAME);
                str = strtok(NULL, "/");
            }
            tmpNode = IsExistDir(dirTree, tmp3, 'd');
            tmpNode2 = IsExistDir(dirTree, tmp3, 'f');
            if(!tmpNode && !tmpNode2) {
                printf("cat: '%s': No such file or directory.\n", tmp3);
                dirTree->current = currentNode;
                return NULL;
            } else if (tmpNode && !tmpNode2) {
                printf("cat: '%s': Is a directory\n", tmp3);
                dirTree->current = currentNode;
                return NULL;
            } else if (tmpNode2 && HasPermission(tmpNode2, 'r')) {
                printf("cat: Can not open file '%s': Permission denied\n", tmpNode2->name);
                dirTree->current = currentNode;
                return NULL;
            } else Concatenate(dirTree, tmp3, 1);
            dirTree->current = currentNode;
        }
    }
    pthread_exit(NULL);
}

//mkdirThread
void *mkdirThread(void *arg) {
    ThreadTree *threadTree = ((ThreadTree *)arg);
    DirectoryTree *dirTree = threadTree->threadTree;
    DirectoryTree *p_preTree;
    char *cmd = threadTree->cmd;

    TreeNode *tmpNode = dirTree->current;
    char tmp[MAX_DIR];
    char pStr[MAX_DIR];
    char tmpStr[MAX_DIR];
    char directoryName[MAX_DIR];
    int directoryLength = 0;
    int directoryExist;

    strncpy(tmp, cmd, MAX_DIR);

    if (strstr(cmd, "/") == NULL) {
        MakeDir(dirTree, cmd, 'd');
    } else if (threadTree->option == 1) {
        int tmpLen = strlen(tmp);
        int flag = 0;
        if (tmp[0] == '/') {
            dirTree->current = dirTree->root;
            flag = 1;
        }
        if (tmp[tmpLen - 1] == '/') {
            tmpLen -= 1;
        }
        for (; flag < tmpLen; flag++) {
            pStr[flag] = tmp[flag];
            pStr[flag + 1] = 0;
            directoryName[directoryLength++] = tmp[flag];
            if (tmp[flag] == '/') {
                directoryName[--directoryLength] = 0;
                strncpy(tmpStr, pStr, flag - 1);
                directoryExist = MoveCurrent(dirTree, directoryName);
                if (directoryExist == -1) {
                    MakeDir(dirTree, directoryName, 'd');
                    directoryExist = MoveCurrent(dirTree, directoryName);
                }
                directoryLength = 0;
            }
        }
        directoryName[directoryLength] = 0;
        MakeDir(dirTree, directoryName, 'd');
        dirTree->current = tmpNode;
    } 
    else {
        char *p_directory = getDir(cmd);
        directoryExist = MovePath(dirTree, p_directory);
        if (directoryExist != 0) {
            printf("mkdir: '%s': No such file or directory.\n", p_directory);
        } else {
            char *str = strtok(tmp, "/");
            char *p_directory_name;
            while (str != NULL) {
                p_directory_name = str;
                str = strtok(NULL, "/");
            }
            MakeDir(dirTree, p_directory_name, 'd');
            dirTree->current = tmpNode;
        }
    }
    pthread_exit(NULL);
}

//chownThread
void *chownThread(void *arg) {
    ThreadTree *threadTree = (ThreadTree *)arg;
    DirectoryTree *dirTree = threadTree->threadTree;
    char *cmd = threadTree->cmd;
    char *tmp = threadTree->usrName;
    char *str;

    if (!strstr(tmp, ":")) ChangeOwner(dirTree, tmp, cmd, 0);
    else {
        char tmp2[MAX_NAME];
        strncpy(tmp2, tmp, MAX_NAME);
        char *str2 = strtok(tmp, ":");
        if (str2 && strcmp(tmp, tmp2)) {
            ChangeOwner(dirTree, str2, cmd, 0);
            str2 = strtok(NULL, " ");
            if (str2) ChangeOwner(dirTree, str2, cmd, 1);
        }
        else if (str2 && !strcmp(tmp, tmp2)) ChangeOwner(dirTree, str2, cmd, 1);
    }
    pthread_exit(NULL);
}

//chmodThread
void *chmodThread(void *arg) {
    ThreadTree *threadTree = (ThreadTree *) arg;
    DirectoryTree *dirTree = threadTree->threadTree;
    int mode = threadTree->mode;
    char *cmd = threadTree->cmd;
    
    ChangeMode(dirTree, mode, cmd);
    pthread_exit(NULL);
}

//grepThread
void *grepThread(void *arg){
    ThreadTree *threadTree = (ThreadTree *)arg;
    DirectoryTree *dirTree = threadTree->threadTree;
    char *cmd = threadTree->cmd;
    char *userContent = threadTree->content;
    TreeNode *currentNode = dirTree->current;
    TreeNode *tmpNode = NULL;
    TreeNode *tmpNode2 = NULL;
    char tmp[MAX_DIR];
    char tmp2[MAX_DIR];
    char tmp3[MAX_DIR];
    char *str;
    int option = threadTree->option;
    int val;

    strncpy(tmp, cmd, MAX_DIR);

    if (strstr(tmp, "/") == NULL) {

        tmpNode = IsExistDir(dirTree, cmd, 'd');
        tmpNode2 = IsExistDir(dirTree, cmd, 'f');

        if (tmpNode == NULL && tmpNode2 == NULL) {
            printf("grep: '%s': No such file or directory.\n", cmd);
            return 0;
        } else if (tmpNode != NULL && tmpNode2 == NULL) {
            printf("grep: '%s': Is a directory\n", cmd);
            return 0;
        } else if (tmpNode2 != NULL && HasPermission(tmpNode2, 'r') != 0) {
            printf("grep: '%s': Permission denied\n", tmpNode2->name);
            return 0;
        } else 
            grepPrint(dirTree, userContent, cmd, option);
    } else {
        strncpy(tmp2, getDir(tmp), MAX_DIR);
        val = MovePath(dirTree, tmp2);
        if (val != 0) {
            printf("grep: '%s': No such file or directory.\n", tmp2);
            return 0;
        }
        str = strtok(tmp, "/");
        while (str != NULL) {
            strncpy(tmp3, str, MAX_NAME);
            str = strtok(NULL, "/");
        }
        tmpNode = IsExistDir(dirTree, tmp3, 'd');
        tmpNode2 = IsExistDir(dirTree, tmp3, 'f');
        if(tmpNode == NULL && tmpNode2 == NULL) {
            printf("grep: '%s': No such file or directory.\n", tmp3);
            dirTree->current = currentNode;
            return 0;
        } else if (tmpNode != NULL && tmpNode2 == NULL) {
            printf("grep: '%s': Is a directory\n", tmp3);
            dirTree->current = currentNode;
            return 0;
        } else if (tmpNode2 != NULL && HasPermission(tmpNode2, 'r') != 0) {
            printf("grep: '%s': Permission denied\n", tmpNode2->name);
            dirTree->current = currentNode;
            return 0;
        } else 
            grepPrint(dirTree, userContent, cmd, option);
        dirTree->current = currentNode;
    }
    pthread_exit(NULL);
}