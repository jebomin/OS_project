#include "../Header/main.h"

DirectoryTree* InitializeTree()
{
    DirectoryTree* dirTree = (DirectoryTree*)malloc(sizeof(DirectoryTree));
    TreeNode* NewNode = (TreeNode*)malloc(sizeof(TreeNode));

    time(&ltime);
    today = localtime(&ltime);
    strncpy(NewNode->name, "/", MAX_NAME);

    NewNode->type ='d';
    NewNode->mode = 755;
    Mode2Permission(NewNode);
    NewNode->UID = usrList->head->UID;
    NewNode->GID = usrList->head->GID;
    NewNode->SIZE = 4096;
    NewNode->month = today->tm_mon+1;
    NewNode->day = today->tm_mday;
    NewNode->hour = today->tm_hour;
    NewNode->minute = today->tm_min;
    NewNode->Parent = NULL;
    NewNode->LeftChild = NULL;
    NewNode->RightSibling = NULL;

    dirTree->root = NewNode;
    dirTree->current = dirTree->root;

    return dirTree;
}

void SaveDir(DirectoryTree* dirTree, Stack* dirStack)
{
    Dir = fopen("Directory.txt", "w");
    WriteNode(dirTree, dirTree->root, dirStack);
    fclose(Dir);
}

DirectoryTree* LoadDir()
{
    DirectoryTree* dirTree = (DirectoryTree*)malloc(sizeof(DirectoryTree));
    char tmp[MAX_LENGTH];
    Dir = fopen("Directory.txt", "r");

    while(fgets(tmp, MAX_LENGTH, Dir) != NULL){
        ReadNode(dirTree, tmp);
    }

    fclose(Dir);
    dirTree->current = dirTree->root;
    return dirTree;
}