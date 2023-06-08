#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <pthread.h>
#ifndef MAIN_H_
#define MAIN_H_
#define DEFAULT printf("%c[%dm", 0x1B, 0)
#define MAX_BUFFER 512
#define MAX_LENGTH 200
#define MAX_DIR 50
#define MAX_NAME 20
#define MAX_THREAD 50

//User
typedef struct tagUserNode{
    char name[MAX_NAME];
    char dir[MAX_DIR];
    int UID;
    int GID;
    int year;
    int month;
    int wday;
    int day;
    int hour;
    int minute;
    int sec;
    struct tagUserNode* LinkNode;
}UserNode;

typedef struct tagUser{
    int topUID;
    int topGID;
    UserNode* head;
    UserNode* tail;
    UserNode* current;
}UserList;


//Directory
typedef struct tagTreeNode{
    char name[MAX_NAME];
    char type;
    int mode;
    int permission[9];
    int SIZE;
    int UID;
    int GID;
    int month;
    int day;
    int hour;
    int minute;
    struct tagTreeNode* Parent;
    struct tagTreeNode* LeftChild;
    struct tagTreeNode* RightSibling;
}TreeNode;

typedef struct tagDirectoryTree{
    TreeNode* root;
    TreeNode* current;
}DirectoryTree;


//stack using linked list
typedef struct tagStackNode{
    char name[MAX_NAME];
    struct tagStackNode* LinkNode;
}StackNode;


typedef struct tagStack{
    StackNode* TopNode;
}Stack;

//thread
typedef struct threadTreeNode {
    DirectoryTree *threadTree;
    DirectoryTree *fName;
    char *cmd;
    char *usrName;
    char *content;
    int mode;
    int option;
} ThreadNode;

time_t ltime;
struct tm *today;

// thread
void *catThread(void *arg);
void *mkdirThread(void *arg);
void *chownThread(void *arg);
void *chmodThread(void *arg);
void *grepThread(void *arg);

// instruction
void Instruction(DirectoryTree* dirTree, char* cmd);

// getInformation
void Login(UserList* userList, DirectoryTree* dirTree);
void PrintStart();
void PrintHead(DirectoryTree* dirTree, Stack* dirStack);

//grep
int grep(DirectoryTree* dirTree, char* cmd);    //완료
int grepPrint(DirectoryTree* dirTree, char *search, char* fName, int type);

//directory
TreeNode* IsExistDir(DirectoryTree* dirTree, char* dirName, char type);
char* getDir(char* dirPath);
void getPath(DirectoryTree* dirTree, TreeNode* dirNode, Stack* dirStack);
void WriteNode(DirectoryTree* dirTree, TreeNode* dirNode, Stack* dirStack);
int ReadNode(DirectoryTree* dirTree, char* tmp);

// directorytree
DirectoryTree* InitializeTree();
void SaveDir(DirectoryTree* dirTree, Stack* dirStack);
DirectoryTree* LoadDir();

//mycp
int mycp(DirectoryTree* dirTree,char* sName,char* oName);

//mkdir
int MakeDir(DirectoryTree* dirTree, char* dirName, char type);
int Mkdir(DirectoryTree* dirTree, char* cmd);

//rm
int RemoveDir(DirectoryTree* dirTree, char* dirName);
int rm(DirectoryTree* dirTree, char* cmd);
void DestroyNode(TreeNode* dirNode);
void DestroyDir(TreeNode* dirNode);

//cd
int MoveCurrent(DirectoryTree* dirTree, char* dirPath);
int MovePath(DirectoryTree* dirTree, char* dirPath);
int cd(DirectoryTree* dirTree, char* cmd);


//pwd
int PrintPath(DirectoryTree* dirTree, Stack* dirStack);
int pwd(DirectoryTree* dirTree, Stack* dirStack, char* cmd);

//ls
void ls(DirectoryTree* dirTree);
void ls_a(DirectoryTree* dirTree);
void ls_l(DirectoryTree* dirTree);
void ls_al(DirectoryTree* dirTree);
char *get_UID(TreeNode *dirNode);
char *get_GID(TreeNode *dirNode);

//cat
int Concatenate(DirectoryTree* dirTree, char* fName, int type);
int cat(DirectoryTree* dirTree, char* cmd);

//chmod
int ChangeMode(DirectoryTree* dirTree, int mode, char* dirName);
int chmod_(DirectoryTree* dirTree, char* cmd);

//chown
int ChangeOwner(DirectoryTree* dirTree, char* userName, char* dirName, int flag);
int chown_(DirectoryTree* dirTree, char* cmd);

//find
int ReadDir(DirectoryTree* dirTree, char* tmp, char* dirName, int o);
void FindDir(DirectoryTree* dirTree, char* dirName, int o);
int find_(DirectoryTree* dirTree, char* cmd);

//user
void WriteUser(UserList* userList, UserNode* userNode);
void SaveUserList(UserList* userList);
int ReadUser(UserList* userList, char* tmp);
UserList* LoadUserList();
UserNode* IsExistUser(UserList* userList, char* userName);

//permisson
int HasPermission(TreeNode* dirNode, char o);
int Mode2Permission(TreeNode* dirNode);
void PrintPermission(TreeNode* dirNode);

//stack
int IsEmpty(Stack* dirStack);
Stack* InitializeStack();
int Push(Stack* dirStack, char* dirName);
char* Pop(Stack* dirStack);

//time
void GetMonth(int i);
void GetWeekday(int i);

//global variable
DirectoryTree* Linux;
Stack* dStack;
UserList* usrList;
FILE* Dir;
FILE* User;

#endif