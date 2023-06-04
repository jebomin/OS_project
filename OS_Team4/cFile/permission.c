#include "../Header/main.h"

int HasPermission(TreeNode* dirNode, char o)
{
    if(usrList->current->UID == 0)
        return 0;

    if(usrList->current->UID == dirNode->UID){
        if(o == 'r'){
            if(dirNode->permission[0] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'w'){
            if(dirNode->permission[1] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'x'){
            if(dirNode->permission[2] == 0)
                return -1;
            else
                return 0;
        }
    }
    else if(usrList->current->GID == dirNode->GID){
        if(o == 'r'){
            if(dirNode->permission[3] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'w'){
            if(dirNode->permission[4] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'x'){
            if(dirNode->permission[5] == 0)
                return -1;
            else
                return 0;
        }
    }
    else{
        if(o == 'r'){
            if(dirNode->permission[6] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'w'){
            if(dirNode->permission[7] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'x'){
            if(dirNode->permission[8] == 0)
                return -1;
            else
                return 0;
        }
    }
    return -1;
}

int Mode2Permission(TreeNode* dirNode)
{
    char buf[4];
    int tmp;
    int j;

    for(int i=0;i<9;i++)
        dirNode->permission[i] = 0;

    sprintf(buf, "%d", dirNode->mode);

    for(int i=0;i<3;i++){
        tmp = buf[i] - '0';
        j = 2;

        while(tmp != 0){
        dirNode->permission[3*i+j] = tmp%2;
        tmp/=2;
        j--;
        }
    }
    return 0;
}

void PrintPermission(TreeNode* dirNode)
{
    char rwx[4] = "rwx";

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(dirNode->permission[3*i+j] == 1)
                printf("%c", rwx[j]);
            else
                printf("-");
        }
    }
}