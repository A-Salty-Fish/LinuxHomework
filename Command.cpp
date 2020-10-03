#include<string>
#include<vector>
using namespace std;
class Command
{
private:
    string cmdStr;//命令
    vector<string> argsStrVec;//参数字符串
public:
    Command(string cmd = "null");//构造函数
    void AddArgsStr(string arg);//添加参数字符串
    int Execute();//执行
};

Command::Command(string cmd = "null")
{
    this->cmdStr = cmd;
}

void Command::AddArgsStr(string arg)
{

}

int Command::Execute()
{
    return 1;
}
