#include "../Header/main.h"

int RemoveDir(DirectoryTree* dirTree, char* dirName)
{
    TreeNode* DelNode = NULL;
    TreeNode* tmpNode = NULL;
    TreeNode* prevNode = NULL;

    tmpNode = dirTree->current->LeftChild;

    if(tmpNode == NULL){
        printf("rm: '%s'를 지울 수 없음: no such file or directory\n", dirName);
        return -1;
    }

    if(strcmp(tmpNode->name, dirName) == 0){
        dirTree->current->LeftChild = tmpNode->RightSibling;
        DelNode = tmpNode;
        if(DelNode->LeftChild != NULL)
            DestroyDir(DelNode->LeftChild);
        remove(DelNode->name);
        DestroyNode(DelNode);
    }
    else{
        while(tmpNode != NULL){
            if(strcmp(tmpNode->name, dirName) == 0){
                DelNode = tmpNode;
                break;
            }
            prevNode = tmpNode;
            tmpNode = tmpNode->RightSibling;
        }
        if(DelNode != NULL){
            prevNode->RightSibling = DelNode->RightSibling;

            if(DelNode->LeftChild != NULL)
                DestroyDir(DelNode->LeftChild);
            remove(DelNode->name);
            DestroyNode(DelNode);
        }
        else{
            printf("rm: '%s'를 지울 수 없음: no such file or directory\n", dirName);
            return -1;
        }
    }
    return 0;
}

int rm(DirectoryTree* dirTree, char* cmd)
{
    TreeNode* currentNode = NULL;
    TreeNode* tmpNode = NULL;
    TreeNode* tmpNode2 = NULL;
    char* str;
    char tmp[MAX_DIR];
    char tmp2[MAX_DIR];
    char tmp3[MAX_DIR];
    int val;

    if (cmd == NULL) {
        printf("Try 'rm --help' for more information.\n");
        return -1;
    }
    currentNode = dirTree->current;
    if (cmd[0] == '-') {
        if (strcmp(cmd, "-r") == 0) {
            str = strtok(NULL, " ");
            if (str == NULL) {
                printf("Try 'rm --help' for more information.\n");
                return -1;
            }
            strncpy(tmp, str, MAX_DIR);
            if (strstr(str, "/") == NULL) {
                tmpNode = IsExistDir(dirTree, str, 'd');
                if (tmpNode == NULL) {
                    tmpNode = IsExistDir(dirTree, str, 'f');
                    if (tmpNode == NULL) {
                        printf("rm: '%s'를 지울 수 없음: no such file or directory\n", str);
                        return -1;
                    }
                    else {
                        if (HasPermission(dirTree->current, 'w') != 0 || HasPermission(tmpNode, 'w') != 0) {
                            printf("rm: '%s' : Permission denied\n", str);
                            return -1;
                        }
                        RemoveDir(dirTree, str);
                    }
                }
                else {
                    if (HasPermission(dirTree->current, 'w') != 0 || HasPermission(tmpNode, 'w') != 0) {
                        printf("rm: '%s' : Permission denied\n", str);
                        return -1;
                    }
                    RemoveDir(dirTree, str);
                }
            }
            else {
                strncpy(tmp2, getDir(str), MAX_DIR);
                val = MovePath(dirTree, tmp2);
                if (val != 0) {
                    printf("rm: '%s': no such file or directory\n", tmp2);
                    return -1;
                }
                str = strtok(tmp, "/");
                while (str != NULL) {
                    strncpy(tmp3, str, MAX_NAME);
                    str = strtok(NULL, "/");
                }
                tmpNode = IsExistDir(dirTree, tmp3, 'd');
                if (tmpNode == NULL) {
                    tmpNode = IsExistDir(dirTree, tmp3, 'f');
                    if (tmpNode == NULL) {
                        printf("rm: '%s'를 지울 수 없음: no such file or directory\n", tmp3);
                        dirTree->current = currentNode;
                        return -1;
                    }
                    else {
                        if (HasPermission(dirTree->current, 'w') != 0 || HasPermission(tmpNode, 'w') != 0) {
                            printf("rm: '%s' : Permission denied\n", tmp3);
                            dirTree->current = currentNode;
                            return -1;
                        }
                        RemoveDir(dirTree, tmp3);
                    }
                }
                else {
                    if (HasPermission(dirTree->current, 'w') != 0 || HasPermission(tmpNode, 'w') != 0) {
                        printf("rm: '%s' : Permission denied\n", tmp3);
                        dirTree->current = currentNode;
                        return -1;
                    }
                    RemoveDir(dirTree, tmp3);
                }
                dirTree->current = currentNode;
            }
        }
        else if (strcmp(cmd, "-f") == 0) {
            str = strtok(NULL, " ");
            if (str == NULL) {
                return -1;
            }
            strncpy(tmp, str, MAX_DIR);
            if (strstr(str, "/") == NULL) {
                tmpNode = IsExistDir(dirTree, str, 'f');
                tmpNode2 = IsExistDir(dirTree, str, 'd');

                if (tmpNode2 != NULL) {
                    return -1;
                }
                if (tmpNode == NULL) {
                    return -1;
                }
                else {
                    if (HasPermission(dirTree->current, 'w') != 0 || HasPermission(tmpNode, 'w') != 0) {
                        return -1;
                    }
                    RemoveDir(dirTree, str);
                }
            }
            else {
                strncpy(tmp2, getDir(str), MAX_DIR);
                val = MovePath(dirTree, tmp2);
                if (val != 0) {
                    return -1;
                }
                str = strtok(tmp, "/");
                while (str != NULL) {
                    strncpy(tmp3, str, MAX_NAME);
                    str = strtok(NULL, "/");
                }
                tmpNode = IsExistDir(dirTree, tmp3, 'f');
                tmpNode2 = IsExistDir(dirTree, tmp3, 'd');

                if (tmpNode2 != NULL) {
                    dirTree->current = currentNode;
                    return -1;
                }
                if (tmpNode == NULL) {
                    dirTree->current = currentNode;
                    return -1;
                }
                else {
                    if (HasPermission(dirTree->current, 'w') != 0 || HasPermission(tmpNode, 'w') != 0) {
                        dirTree->current = currentNode;
                        return -1;
                    }
                    RemoveDir(dirTree, tmp3);
                }
                dirTree->current = currentNode;
            }
        }
        else if (strcmp(cmd, "-rf") == 0) {
            str = strtok(NULL, " ");
            if (str == NULL) {
                return -1;
            }
            strncpy(tmp, str, MAX_DIR);
            if (strstr(str, "/") == NULL) {
                tmpNode = IsExistDir(dirTree, str, 'f');
                tmpNode = (IsExistDir(dirTree, str, 'd') == NULL) ? tmpNode : IsExistDir(dirTree, str, 'd');
                if (tmpNode == NULL) {
                    return -1;
                }
                else {
                    if (HasPermission(dirTree->current, 'w') != 0 || HasPermission(tmpNode, 'w') != 0) {
                        return -1;
                    }
                    RemoveDir(dirTree, str);
                }
            }
            else {
                strncpy(tmp2, getDir(str), MAX_DIR);
                val = MovePath(dirTree, tmp2);
                if (val != 0) {
                    return -1;
                }
                str = strtok(tmp, "/");
                while (str != NULL) {
                    strncpy(tmp3, str, MAX_NAME);
                    str = strtok(NULL, "/");
                }
                tmpNode = IsExistDir(dirTree, tmp3, 'd');
                if (tmpNode == NULL) {
                    dirTree->current = currentNode;
                    return -1;
                }
                else {
                    if (HasPermission(dirTree->current, 'w') != 0 || HasPermission(tmpNode, 'w') != 0) {
                        dirTree->current = currentNode;
                        return -1;
                    }
                    RemoveDir(dirTree, tmp3);
                }
                dirTree->current = currentNode;
            }
        }
        else if (strcmp(cmd, "--help") == 0) {
            printf("사용법: rm [<옵션>]... [<파일>]...\n");
            printf("  Remove (unlink) the FILE(s).\n\n");
            printf("  Options:\n");
            printf("    -f, --force    \t ignore nonexistent files and arguments, never prompt\n");
            printf("    -r, --recursive\t remove directories and their contents recursively\n");
            printf("        --help\t 이 도움말을 표시하고 끝냅니다\n");
            return -1;
        }
        else {
            str = strtok(cmd, "-");
            if (str == NULL) {
                printf("rm: 잘못된 연산자\n");
                printf("Try 'rm --help' for more information.\n");
                return -1;
            }
            else {
                printf("rm: 부적절한 옵션 -- '%s'\n", str);
                printf("Try 'rm --help' for more information.\n");
                return -1;
            }
        }
    }
    else {
        strncpy(tmp, cmd, MAX_DIR);
        if (strstr(cmd, "/") == NULL) {
            tmpNode = IsExistDir(dirTree, cmd, 'f');
            tmpNode2 = IsExistDir(dirTree, cmd, 'd');

            if (tmpNode2 != NULL) {
                printf("rm:'%s'를 지울 수 없음: Is a directory\n", cmd);
                return -1;
            }
            if (tmpNode == NULL) {
                printf("rm: '%s'를 지울 수 없음: no such file or directory\n", cmd);
                return -1;
            }
            else {
                if (HasPermission(dirTree->current, 'w') != 0 || HasPermission(tmpNode, 'w') != 0) {
                    printf("rm: '%s'디렉터리 또는 파일을 지울 수 없습니다: 허가거부\n", cmd);
                    return -1;
                }
                RemoveDir(dirTree, cmd);
            }
        }
        else {
            strncpy(tmp2, getDir(cmd), MAX_DIR);
            val = MovePath(dirTree, tmp2);
            if (val != 0) {
                printf("rm: '%s': no such file or directory\n", tmp2);
                return -1;
            }
            str = strtok(tmp, "/");
            while (str != NULL) {
                strncpy(tmp3, str, MAX_NAME);
                str = strtok(NULL, "/");
            }
            tmpNode = IsExistDir(dirTree, tmp3, 'f');
            tmpNode2 = IsExistDir(dirTree, tmp3, 'd');

            if (tmpNode2 != NULL) {
                printf("rm:'%s'를 지울 수 없음: Is a directory\n", tmp3);
                dirTree->current = currentNode;
                return -1;
            }
            if (tmpNode == NULL) {
                printf("rm: '%s'를 지울 수 없음: no such file or directory\n", tmp3);
                dirTree->current = currentNode;
                return -1;
            }
            else {
                if (HasPermission(dirTree->current, 'w') != 0 || HasPermission(tmpNode, 'w') != 0) {
                    printf("rm: '%s'디렉터리 또는 파일을 지울 수 없습니다: 허가거부\n", tmp3);
                    dirTree->current = currentNode;
                    return -1;
                }
                RemoveDir(dirTree, tmp3);
            }
            dirTree->current = currentNode;
        }
    }
    return 0;
}

void DestroyNode(TreeNode* dirNode)
{
    free(dirNode);
}

void DestroyDir(TreeNode* dirNode)
{
    if(dirNode->RightSibling != NULL){
        DestroyDir(dirNode->RightSibling);
    }
    if(dirNode->LeftChild != NULL){
        DestroyDir(dirNode->LeftChild);
    }

    dirNode->LeftChild = NULL;
    dirNode->RightSibling = NULL;
    DestroyNode(dirNode);
}