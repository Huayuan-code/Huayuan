#include <iostream>
#include <string>
#include <fstream>  
#include <codecvt>  
#include <locale> 
#include <stdio.h>
#include <iomanip>
#include "header.h"
using namespace std;

//最大处理长度
const int maxx = 100005;

int dp[2][maxx];
wstring origin = L" ";
wstring add = L" ";

//将核心代码提出来方便单元测试
int lcs()
{
    memset(dp, 0, sizeof(dp));
    int cur = 0, pre = 1;;
    for (int i = 1; i < origin.size(); i++)
    {
        cur = i & 1;
        pre = cur ^ 1;
        for (int j = 1; j < add.size(); j++)
        {
            if (origin[i] == add[j]) dp[cur][j] = dp[pre][j - 1] + 1;
            else dp[cur][j] = max(dp[pre][j], dp[cur][j - 1]);
        }
    }

    return dp[cur][add.size() - 1];
}


//      参数数量   参数
int main(int argc, char* argv[])
{
    //一些基本设置
    setlocale(LC_ALL, "");
    locale::global(locale(locale(), new codecvt_utf8<wchar_t>));

    //获取三个路径
    string orig_path = argv[1];
    string add_path = argv[2];
    string ans_path = argv[3];

    //orig_path = "D:\\university\\5大三上\\软件工程\\作业2\\111.txt";
    //add_path = "D:\\university\\5大三上\\软件工程\\作业2\\222.txt";

    
    wstring buf; //暂存读入的数据

    //读入原文件
    wifstream forigin;
    forigin.open(orig_path, ios::in);
    
    while (forigin >> buf)
    {
        if (buf.size() > maxx)
        {
            printf("origin is too long!\n");
            forigin.close();
            return 0;
        }
        origin += buf;
        if (origin.size() > maxx)
        {
            printf("origin is too long!\n");
            forigin.close();
            return 0;
        }
    }
    forigin.close();
    if (origin.size() == 1)
    {
        printf("origin is empty\n");
        return 0;
    }

    //读入修改文件
    wifstream fadd;
    fadd.open(add_path, ios::in);
    
    while (fadd >> buf)
    {
        if (buf.size() > maxx)
        {
            printf("add is too long!\n");
            fadd.close();
            return 0;
        }
        add += buf;
        if (add.size() > maxx)
        {
            printf("add is too long!\n");
            fadd.close();
            return 0;
        }
    }
    fadd.close();
    if (add.size() == 1)
    {
        printf("add is empty\n");
        return 0;
    }

    int originsize = origin.size();
    int addsize = add.size();

    //整理答案
    int ans = lcs();  //最长公共子序列获取重复的字符数
    double rate = (double)ans / (double)addsize;    //重复率


    printf("osize = %d\nasize = %d\n", originsize, addsize);
    printf("same character = %d\n rate = %.2lf\n", ans, rate);

    ofstream fans(ans_path);
    fans << fixed << setprecision(2) << rate;

    return 0;
}

