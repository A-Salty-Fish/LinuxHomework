#include <iostream>
#include<string>
#include <unistd.h>
#include <sys/wait.h>
#include<errno.h>
#include<vector>
#include <cstring>

using namespace std;

const string START_SIGNIAL = ">";
const char * BUSYBOX_PATH = "./busybox-1.32.0/busybox";

class Command
{
private:
    vector<string> argsStrVec;//命令参数字符串
public:
    Command();//构造函数
    void AddArgsStr(string arg);//添加参数字符串
    char ** GetArgs();//生成参数char数组
    void Execute();//执行
};

Command::Command()
{
}

void Command::AddArgsStr(string arg)
{
    argsStrVec.push_back(arg);
}

char ** Command::GetArgs()
{
    int argsNum = argsStrVec.size();
    char **args = (char**) malloc( sizeof(char*) * argsNum );
    for (int i = 0; i < argsNum; i++)
    {
        char *arg = new char[argsStrVec[i].length() + 1];
        strcpy(arg, argsStrVec[i].c_str());
        args[i] = arg;
    }
    return args;
}

void Command::Execute()
{
    int rtOfSon;//子进程返回值
    if (fork() == 0)
    {   
        char **_argvs = GetArgs();
        execv(BUSYBOX_PATH,_argvs);
        perror(BUSYBOX_PATH);
        exit(errno);
    }
    else
    {
        wait(&rtOfSon);
        cout << "child process return " << rtOfSon << endl;
    }    
}

class MyShell{
public:
    void RunMyShell();
};

void MyShell::RunMyShell()
{
    int rtOfSon;//子进程返回值
    while(true)
    {
        cout << START_SIGNIAL;
        Command command;
        string cmd;
        cin >> cmd;
        command.AddArgsStr(cmd);
        while(cin.get() != '\n')
        {
            cin >> cmd;
            command.AddArgsStr(cmd);
        }
        command.Execute();
    }
}

int main()
{
    MyShell myshell;
    myshell.RunMyShell();
    return 0;
}