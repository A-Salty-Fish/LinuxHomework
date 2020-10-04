#include<iostream>
#include<string>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<vector>
#include<cstring>
#include<map>

using namespace std;

const string START_SIGNIAL = "Dzy's Shell:";//Shell提示符
const char * BUSYBOX_PATH = "./busybox-1.32.0/busybox";//BusyBox路径

enum ValidInput {//判断合法输入的枚举
                EmUndefined, 
                EmLS, 
                EmGREP,
                EmDIFF
                };
map<string, ValidInput> mapStringInputs;//string到Enum的Map

class Command
{
private:
    vector<string> argsStrVec;//命令参数字符串
public:
    void AddArgsStr(string arg);//添加参数字符串
    char ** GetArgs();//生成参数char数组
    void Execute();//执行
};

void Command::AddArgsStr(string arg)
{
    argsStrVec.push_back(arg);
}

char ** Command::GetArgs()
{
    int argsNum = argsStrVec.size();
    char **args = (char**) malloc( sizeof(char*) * argsNum + 1);
    for (int i = 0; i < argsNum; i++)
    {
        char *arg = new char[argsStrVec[i].length() + 1];
        strcpy(arg, argsStrVec[i].c_str());
        args[i] = arg;
    }
    args[argsNum] = NULL;
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
    void InitialMap();
    bool IsInputValid(string input);
};

void MyShell::InitialMap()
{
    mapStringInputs["ls"] = EmLS;
    mapStringInputs["grep"] = EmGREP;
    mapStringInputs["diff"] = EmDIFF;
}

bool MyShell::IsInputValid(string input)
{
    switch(mapStringInputs[input])
    {
        case EmLS:
            cout<<"Running ls"<<endl;
            break;
        case EmDIFF:
            cout<<"Running diff"<<endl;
            break;
        case EmGREP:
            cout<<"Running grep"<<endl;
            break;
        default:
            cout<<"Invalid input"<<endl;
            return false;
    }
    return true;
}

void MyShell::RunMyShell()
{
    while(true)
    {
        InitialMap();
        cout << START_SIGNIAL;
        Command command;
        string cmd;
        cin >> cmd;
        if (IsInputValid(cmd))
            command.AddArgsStr(cmd);
        else
            continue;
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