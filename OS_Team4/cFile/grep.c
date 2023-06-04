#include "../Header/main.h"

int grep(DirectoryTree* dirTree, char* cmd)        //완료
{
    TreeNode* currentNode = NULL;
    TreeNode* tmpNode = NULL;
    TreeNode* tmpNode2 = NULL;
    pthread_t threadPool[MAX_THREAD];
    ThreadTree threadTree[MAX_THREAD];

    int count = 0;
    char* str;
    char userContent[MAX_BUFFER];
    char tmp[MAX_DIR];
    char tmp2[MAX_DIR];
    char tmp3[MAX_DIR];
    int val;

    if(cmd == NULL){
        printf("Try 'grep --help' for more information.\n");
        return -1;
    }

    currentNode = dirTree->current;
    if(cmd[0] == '-'){
        if(strcmp(cmd, "-n")== 0){
            str = strtok(NULL, " ");
            strncpy(userContent, str, MAX_BUFFER);
            str = strtok(NULL, " ");
            if (str == NULL) {
                printf("grep: Invalid option\n");
                printf("Try 'grep --help' for more information.\n");
                return -1;
            }
            while (str != NULL) {
                threadTree[count].threadTree = dirTree;
                threadTree[count].option = 1;
                threadTree[count].content = userContent;
                threadTree[count++].cmd = str;
                str = strtok(NULL, " ");
            }
        }
        else if(strcmp(cmd, "-v")== 0){
            str = strtok(NULL, " ");
            strncpy(userContent, str, MAX_BUFFER);
            str = strtok(NULL, " ");
            if (str == NULL) {
                printf("grep: Invalid option\n");
                printf("Try 'grep --help' for more information.\n");
                return -1;
            }
            while (str != NULL) {
                threadTree[count].threadTree = dirTree;
                threadTree[count].option = 2;
                threadTree[count].content = userContent;
                threadTree[count++].cmd = str;
                str = strtok(NULL, " ");
            }
        }
        else if(strcmp(cmd, "-i")== 0){
            str = strtok(NULL, " ");
            strncpy(userContent, str, MAX_BUFFER);
            str = strtok(NULL, " ");
            if (str == NULL) {
                printf("grep: Invalåid option\n");
                printf("Try 'grep --help' for more information.\n");
                return -1;
            }
            while (str != NULL) {
                threadTree[count].threadTree = dirTree;
                threadTree[count].option = 3;
                threadTree[count].content = userContent;
                threadTree[count++].cmd = str;
                str = strtok(NULL, " ");
            }
        }
        else if(strcmp(cmd, "-nv")== 0 || strcmp(cmd, "-vn") == 0){
            str = strtok(NULL, " ");
            strncpy(userContent, str, MAX_BUFFER);
            str = strtok(NULL, " ");
            if (str == NULL) {
                printf("grep: Invalid option\n");
                printf("Try 'grep --help' for more information.\n");
                return -1;
            }
            while (str != NULL) {
                threadTree[count].threadTree = dirTree;
                threadTree[count].option = 4;
                threadTree[count].content = userContent;
                threadTree[count++].cmd = str;
                str = strtok(NULL, " ");
            }
        }
        else if(strcmp(cmd, "-ni")== 0 || strcmp(cmd, "-in") == 0){
            str = strtok(NULL, " ");
            strncpy(userContent, str, MAX_BUFFER);
            str = strtok(NULL, " ");
            if (str == NULL) {
                printf("grep: Invalid option\n");
                printf("Try 'grep --help' for more information.\n");
                return -1;
            }
            while (str != NULL) {
                threadTree[count].threadTree = dirTree;
                threadTree[count].option = 5;
                threadTree[count].content = userContent;
                threadTree[count++].cmd = str;
                str = strtok(NULL, " ");
            }
        }
        else if(strcmp(cmd, "-vi")== 0 || strcmp(cmd, "-iv") == 0){
            str = strtok(NULL, " ");
            strncpy(userContent, str, MAX_BUFFER);
            str = strtok(NULL, " ");
            if (str == NULL) {
                printf("grep: Invalid option\n");
                printf("Try 'grep --help' for more information.\n");
                return -1;
            }
            while (str != NULL) {
                threadTree[count].threadTree = dirTree;
                threadTree[count].option = 6;
                threadTree[count].content = userContent;
                threadTree[count++].cmd = str;
                str = strtok(NULL, " ");
            }
        }
        else if(strcmp(cmd, "-inv")== 0 || strcmp(cmd, "-ivn") == 0 || strcmp(cmd, "-niv") == 0 || strcmp(cmd, "-nvi") == 0 || strcmp(cmd, "-vin") == 0 || strcmp(cmd, "-vni") == 0){
            str = strtok(NULL, " ");
            strncpy(userContent, str, MAX_BUFFER);
            str = strtok(NULL, " ");
            if (str == NULL) {
                printf("grep: Invalid option\n");
                printf("Try 'grep --help' for more information.\n");
                return -1;
            }
            while (str != NULL) {
                threadTree[count].threadTree = dirTree;
                threadTree[count].option = 7;
                threadTree[count].content = userContent;
                threadTree[count++].cmd = str;
                str = strtok(NULL, " ");
            }
        }
        else if(strcmp(cmd, "--help") == 0){
            printf("사용법: grep [<옵션>]... [<파일>]...\n");
            printf("  FILE(들)을 합쳐서 표준 출력으로 보낸다.\n\n");
            printf("  Options:\n");
            printf("    -n, --number         \t number all output line\n");
            printf("        --help\t 이 도움말을 표시하고 끝냅니다\n");
            return -1;
        }
        else{
            printf("Try 'grep --help' for more information.\n");
            return -1;
        }
    }
    else{
        strncpy(userContent, cmd, MAX_BUFFER);
        str = strtok(NULL, " ");
        if (str == NULL){
            printf("Try 'grep --help' for more information.\n");
            return -1;
        }
        while (str != NULL) {
            threadTree[count].threadTree = dirTree;
            threadTree[count].option = 0;
            threadTree[count].content = userContent;
            threadTree[count++].cmd = str;
            str = strtok(NULL, " ");
        }
    }
    for (int i = 0; i < count; i++) {
        pthread_create(&threadPool[i], NULL, grepThread, (void*)&threadTree[i]);
        pthread_join(threadPool[i], NULL);
    }
    return 1;
}

int grepPrint(DirectoryTree* dirTree, char *search, char* fName, int type)
{
    UserNode* tmpUser = NULL;
    TreeNode* tmpNode = NULL;
    FILE* fp;
    char buf[MAX_BUFFER];
    char tmpName[MAX_NAME];
    char* str;
    int tmpSIZE = 0;
    int count = 1;

    //file read
    tmpNode = IsExistDir(dirTree,fName, 'f');

    if(tmpNode == NULL){
        return -1;
    }

    fp = fopen(fName, "r");

    while(feof(fp) == 0){
        fgets(buf, sizeof(buf), fp);
        if(feof(fp) != 0){
            break;
        }
        else if (type == 0)
        {
            if (strstr(buf, search) != NULL)
                printf("%s",buf);
        }
        else if (type == 1)
        {
            if (strstr(buf, search) != NULL)
                printf("%d:%s ", count, buf);
        }
        else if (type == 2)
        {
            if (strstr(buf, search) == NULL)
                printf("%s", buf);
        }
        else if (type == 3)
        {
            if (strcasestr(buf, search) != NULL)
                printf("%s", buf);
        }
        else if (type == 4)
        {
            if (strstr(buf, search) == NULL)
                printf("%s", buf);
            else
                printf("\n");
        }
        else if (type == 5)
        {
            if (strcasestr(buf, search) != NULL)
                printf("%d:%s", count, buf);
        }
        else if (type == 6)
        {
            if (strcasestr(buf, search) == NULL)
                printf("%s", buf);
        }
        else if(type == 7){
            if (strcasestr(buf, search) == NULL)
                printf("%d:%s", count, buf);
        }
        count++;
    }
    fclose(fp);

    return 0;
}
