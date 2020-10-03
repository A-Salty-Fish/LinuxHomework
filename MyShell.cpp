#include <iostream>
#include<string>
#include <unistd.h>
#include <sys/wait.h>
#include<errno.h>

using namespace std;

const string START_SIGNIAL = ">";
const char * BUSYBOX_PATH = "./busybox-1.32.0/busybox";

class MyShell{
public:
    string command;
    void RunMyShell()
    {
        int rtOfSon;//子进程返回值
        while(true)
        {
            cout << START_SIGNIAL;
            cin >> command;
            if (fork() == 0)
            {
                const char * charCommand = command.c_str();
                char **_argvs = (char**) malloc( sizeof(char*) * 10 );
                _argvs[0] = (char *) "ls";
                _argvs[1] = NULL;
                execv(charCommand,_argvs);
                perror(charCommand);
                exit(errno);
            }
            else
            {
                wait(&rtOfSon);
                cout << "child process return " << rtOfSon << endl;
            }
            
        }
    }
};

int main()
{
    MyShell myshell;
    myshell.RunMyShell();
    return 0;
}