#include "../Header/main.h"

int cat(DirectoryTree* dirTree, char* cmd)
{
    TreeNode* currentNode = NULL;
    TreeNode* tmpNode = NULL;
    TreeNode* tmpNode2 = NULL;
    ThreadNode threadTree[MAX_THREAD];
    pthread_t threadPool[MAX_THREAD];
    int count = 0;
    char* str;
    char tmp[MAX_DIR];
    char tmp2[MAX_DIR];
    char tmp3[MAX_DIR];
    int val;
    /*
        cat0: write, EOF to save
        cat1: read
        cat2: read w/ line number
    */

    if(cmd == NULL){
        long size;
        unsigned char c;
        size = read(0, &c, 1);
        while(size != 0) {
            write(1, &c, size);
            size = read(0, &c, 1);
        }
        rewind(stdin);
        return 0;
    }
    currentNode = dirTree->current;

    if(strcmp(cmd, ">") == 0){  // > 옵션 사용 했을 때
        str = strtok(NULL, " ");
        if(str == NULL){
            printf("cat: Invalid option\n");
            printf("Try 'cat --help' for more information.\n");
            return -1;
        }
        strncpy(tmp, str, MAX_DIR);
        if(strstr(str, "/") == NULL){
            if(HasPermission(dirTree->current, 'w') != 0){ // 쓰기권환인지 확인
                printf("cat: Can not create file '%s': No permission\n", dirTree->current->name);
                return -1;
            }
            tmpNode = IsExistDir(dirTree, str, 'd'); //쓰기권환이 있으면 IsExistDIR실행
            if(tmpNode != NULL){
                printf("cat: '%s': Is a directory\n", str);
                return -1;
            }
            else Concatenate(dirTree, str, 0);
        }
        else{
            strncpy(tmp2, getDir(str), MAX_DIR);
            val = MovePath(dirTree, tmp2);
            if(val){
                printf("cat: '%s': no such file or directory\n", tmp2);
                return -1;
            }
            str = strtok(tmp, "/");
            while(str){
                strncpy(tmp3, str, MAX_NAME);
                str = strtok(NULL, "/");
            }
            if(HasPermission(dirTree->current, 'w')){
                printf("cat: Can not create file '%s': No permission.\n", dirTree->current->name);
                dirTree->current = currentNode;
                return -1;
            }
            tmpNode = IsExistDir(dirTree, tmp3, 'd');
            if(tmpNode){
                printf("cat: '%s': Is a directory\n", tmp3);
                dirTree->current = currentNode;
                return -1;
            }
            else Concatenate(dirTree, tmp3, 0);
            dirTree->current = currentNode;
        }
        return 0;
    }
    else if(cmd[0] == '-'){
        if (!strcmp(cmd, "-n")) {
            str = strtok(NULL, " ");
            if (!str) {
               char *buf = NULL;
                int lineCount = 1;
                size_t inputSize = 0;
                ssize_t readSize;

                while ((readSize = getline(&buf, &inputSize, stdin)) != -1) {
                printf("%6d  %s", lineCount++, buf);
            }
                rewind(stdin);
                free(buf);
                return -1;
            }
            while (str) {
                threadTree[count].threadTree = dirTree;
                threadTree[count].option = 1;
                threadTree[count++].cmd = str;
                str = strtok(NULL, " ");
            }
        } else if(strcmp(cmd, "--help") == 0) {
            printf("Usage: cat [OPTION]... [FILE]...\n");
            printf("Concatenate FILE(s) to standard output.\n\n");
            printf("With no FILE, or when FILE is -, read standard input.\n\n");
            printf("  -n, --number             number all output lines\n");
            printf("  -b, --number-nonblank    number nonempty output lines, overrides -n\n");
            printf("      --help     display this help and exit\n");
            return -1;
        } else {
            str = strtok(cmd, "-");
            if(!str) {
                printf("cat: Invalid option\n");
                printf("Try 'cat --help' for more information.\n");
                return -1;
            } else {
                printf("cat: Unrecognized option -- '%s'\n", str);
                printf("Try 'cat --help' for more information.\n");
                return -1;
            }
        }
    } else {
        if (!strcmp(cmd, "/etc/password")) {
            Concatenate(dirTree, "password", 4);
            return 0;
        }
        if (!cmd) {
            printf("cat: Invalid option\n");
            printf("Try 'rm --help' for more information.\n");
            return -1;
        }
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
        pthread_create(&threadPool[i], NULL, catThread, (void*)&threadTree[i]);
        pthread_join(threadPool[i], NULL);
    }
    return 1;
}

//cat
int Concatenate(DirectoryTree* dirTree, char* fName, int type)
{
    UserNode* tmpUser = NULL;
    TreeNode* tmpNode = NULL;
    FILE* fp;
    char buf[MAX_BUFFER];
    char tmpName[MAX_NAME];
    char* str;
    int tmpSIZE = 0;
    int cnt = 1;

    //file read
    if(type){
        if(type == 4){
            tmpUser = usrList->head;
            while(tmpUser != NULL){
                printf("%s:x:%d:%d:%s:%s\n", tmpUser->name, tmpUser->UID, tmpUser->GID, tmpUser->name, tmpUser->dir);
                tmpUser = tmpUser->LinkNode;
            }
            return 0;
        }
        tmpNode = IsExistDir(dirTree,fName, 'f');

        if(tmpNode == NULL) return -1;
        fp = fopen(fName, "r");

        while(feof(fp) == 0){
            fgets(buf, sizeof(buf), fp);
            if(feof(fp) != 0) break;
            if(type == 2){
                if(buf[strlen(buf)-1] == '\n'){
                    printf("     %d ",cnt);
                    cnt++;
                }
            }
            else if(type == 3){
                if(buf[strlen(buf)-1] == '\n' && buf[0] != '\n'){
                    printf("     %d ",cnt);
                    cnt++;
                }
            }
            fputs(buf, stdout);
        }
        fclose(fp);
    }
    else{
        fp = fopen(fName, "w");
            
            while(fgets(buf, sizeof(buf), stdin)){
                fputs(buf, fp);
                tmpSIZE += strlen(buf)-1;
        }

        rewind(stdin);
        fclose(fp);
        
        tmpNode = IsExistDir(dirTree, fName, 'f');
        if(tmpNode){
            time(&ltime);
            today = localtime(&ltime);

            tmpNode->month = today->tm_mon + 1;
            tmpNode->day = today->tm_mday;
            tmpNode->hour = today->tm_hour;
            tmpNode->minute = today->tm_min;
        }
        else{
            MakeDir(dirTree, fName, 'f');
        }
        tmpNode = IsExistDir(dirTree, fName, 'f');
        tmpNode->SIZE = tmpSIZE;
    }
    return 0;
}