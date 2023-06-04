#include "../Header/main.h"

void ls(DirectoryTree* dirTree){
    int count = 1;
    TreeNode* tmpNode = dirTree->current;
    if(tmpNode->LeftChild==NULL)
        printf("directory empt\n");
    else{
        tmpNode=tmpNode->LeftChild;
        while(tmpNode->RightSibling!=NULL){
            if(strlen(tmpNode->name)<8)
                printf("%s\t\t",tmpNode->name);
            else
                printf("%s\t",tmpNode->name);
            tmpNode=tmpNode->RightSibling;
            if(count%5==0)
                printf("\n");
            count++;
        }
        printf("%s\t\n",tmpNode->name);
    }
}
void ls_a(DirectoryTree* dirTree){
    int count = 1;
    TreeNode* tmpNode = dirTree->current;
    if(tmpNode->LeftChild==NULL){
        printf(".\t\t..\n");
    }
    else{
        printf(".\t\t..\t\t");
        count = count + 2;
        tmpNode=tmpNode->LeftChild;
        while(tmpNode->RightSibling!=NULL){
            if(strlen(tmpNode->name)<8)
                printf("%s\t\t",tmpNode->name);
            else
                printf("%s\t",tmpNode->name);
            tmpNode=tmpNode->RightSibling;
            if(count%5==0)
                printf("\n");
            count++;
        }
        printf("%s\t\n",tmpNode->name);
    }
}
void ls_l(DirectoryTree* dirTree){
    time_t timer;
    TreeNode* tmpNode = dirTree->current;
    timer = time(NULL);
    if(tmpNode->LeftChild==NULL)
        printf("directory empty\n");
    else{
        tmpNode=tmpNode->LeftChild;
        while(tmpNode->RightSibling!=NULL){
                printf("%c",tmpNode->type);
                PrintPermission(tmpNode);
                printf(" %d %d %d",tmpNode->SIZE,tmpNode->UID,tmpNode->GID);
                printf(" %d(month) %d(day) %d(hour) %d(min) ",tmpNode->month,tmpNode->day,tmpNode->hour,tmpNode->minute);
                printf("%s\n",tmpNode->name);
                tmpNode=tmpNode->RightSibling;
        }
        printf("%c",tmpNode->type);
        PrintPermission(tmpNode);
        printf(" %d %d %d",tmpNode->SIZE,tmpNode->UID,tmpNode->GID);
        printf(" %d(month) %d(day) %d(hour) %d(min) ",tmpNode->month,tmpNode->day,tmpNode->hour,tmpNode->minute);
        printf("%s\n",tmpNode->name);
    }
}
void ls_al(DirectoryTree* dirTree){
    time_t timer;
    TreeNode* tmpNode = dirTree->current;
    timer = time(NULL);
    if(tmpNode->LeftChild==NULL){
        //.
        printf("%c",dirTree->current->type);
        PrintPermission(dirTree->current);
        printf(" %d %d %d",dirTree->current->SIZE,dirTree->current->UID,dirTree->current->GID);
        printf(" %d(month) %d(day) %d(hour) %d(min) ",dirTree->current->month,dirTree->current->day,dirTree->current->hour,dirTree->current->minute);
        printf(".\n");
        //..
        if(strcmp(dirTree->current->name,"/")==0){
            printf("%c",dirTree->current->type);
            PrintPermission(dirTree->current);
            printf(" %d %d %d",dirTree->current->SIZE,dirTree->current->UID,dirTree->current->GID);
            printf(" %d(month) %d(day) %d(hour) %d(min) ",dirTree->current->month,dirTree->current->day,dirTree->current->hour,dirTree->current->minute);
            printf("..\n");
        }
        else{
            printf("%c",tmpNode->Parent->type);
            PrintPermission(tmpNode->Parent);
            printf(" %d %d %d",tmpNode->Parent->SIZE,tmpNode->Parent->UID,tmpNode->Parent->GID);
            printf(" %d(month) %d(day) %d(hour) %d(min) ",tmpNode->Parent->month,tmpNode->Parent->day,tmpNode->Parent->hour,tmpNode->Parent->minute);
            printf("..\n");
        }
    }
    else{
        //.
        printf("%c",dirTree->current->type);
        PrintPermission(dirTree->current);
        printf(" %d %d %d",dirTree->current->SIZE,dirTree->current->UID,dirTree->current->GID);
        printf(" %d(month) %d(day) %d(hour) %d(min) ",dirTree->current->month,dirTree->current->day,dirTree->current->hour,dirTree->current->minute);
        printf(".\n");
        //..
        if(strcmp(dirTree->current->name,"/")==0){
            printf("%c",dirTree->current->type);
            PrintPermission(dirTree->current);
            printf(" %d %d %d",dirTree->current->SIZE,dirTree->current->UID,dirTree->current->GID);
            printf(" %d(month) %d(day) %d(hour) %d(min) ",dirTree->current->month,dirTree->current->day,dirTree->current->hour,dirTree->current->minute);
            printf("..\n");
        }
        else{
            printf("%c",tmpNode->Parent->type);
            PrintPermission(tmpNode->Parent);
            printf(" %d %d %d",tmpNode->Parent->SIZE,tmpNode->Parent->UID,tmpNode->Parent->GID);
            printf(" %d(month) %d(day) %d(hour) %d(min) ",tmpNode->Parent->month,tmpNode->Parent->day,tmpNode->Parent->hour,tmpNode->Parent->minute);
            printf("..\n");
        }


        tmpNode=tmpNode->LeftChild;
        while(tmpNode->RightSibling!=NULL){
                printf("%c",tmpNode->type);
                PrintPermission(tmpNode);
                printf(" %d %d %d",tmpNode->SIZE,tmpNode->UID,tmpNode->GID);
                printf(" %d(month) %d(day) %d(hour) %d(min) ",tmpNode->month,tmpNode->day,tmpNode->hour,tmpNode->minute);
                printf("%s\n",tmpNode->name);
                tmpNode=tmpNode->RightSibling;
        }
        printf("%c",tmpNode->type);
        PrintPermission(tmpNode);
        printf(" %d %d %d",tmpNode->SIZE,tmpNode->UID,tmpNode->GID);
        printf(" %d(month) %d(day) %d(hour) %d(min) ",tmpNode->month,tmpNode->day,tmpNode->hour,tmpNode->minute);
        printf("%s\n",tmpNode->name);
    }
}