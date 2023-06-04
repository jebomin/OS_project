#include "../Header/main.h"

//stack
//stack function
int IsEmpty(Stack* dirStack)
{
    if(dirStack->TopNode == NULL){
        return -1;
    }
    return 0;
}

Stack* InitializeStack()
{
    Stack* returnStack = (Stack*)malloc(sizeof(Stack));

    if(returnStack == NULL){
        printf("error occurred, returnStack.\n");
        return NULL;
    }
    //initialize Stack
    returnStack->TopNode = NULL;
    return returnStack;
}

int Push(Stack* dirStack, char* dirName)
{
    StackNode* dirNode = (StackNode*)malloc(sizeof(StackNode));

    if(dirStack == NULL){
        printf("error occurred, dirStack.\n");
        return -1;
    }
    if(dirNode == NULL){
        printf("error occurred, dirNode.\n");
        return -1;
    }
    //set dirNode
    strncpy(dirNode->name, dirName, MAX_NAME);
    dirNode->LinkNode = dirStack->TopNode;
    //set dirStack
    dirStack->TopNode = dirNode;
    return 0;
}

char* Pop(Stack* dirStack)
{
    StackNode* returnNode = NULL;
    if(dirStack == NULL){
        printf("error occurred, dirStack.\n");
        return NULL;
    }
    if(IsEmpty(dirStack) == -1){
        printf("Stack Empty.\n");
        return NULL;
    }
    returnNode = dirStack->TopNode;
    dirStack->TopNode = returnNode->LinkNode;

    return returnNode->name;
}