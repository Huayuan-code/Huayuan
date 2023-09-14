// 论文查重.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <fstream>  
#include <codecvt>  
#include <locale> 
#include <stdio.h>
#include <iomanip>
using namespace std;




//      参数数量   参数
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    locale::global(locale(locale(), new codecvt_utf8<wchar_t>));

    //设置三个路径
    string orig_path = argv[1];
    string add_path = argv[2];
    string ans_path = argv[3];

    //orig_path = "D:\\university\\5大三上\\软件工程\\作业2\\111.txt";
    //add_path = "D:\\university\\5大三上\\软件工程\\作业2\\222.txt";


    wstring buf;
    //读入原文件
    wifstream forigin;
    forigin.open(orig_path, ios::in);
    wstring origin = L" ";
    while (forigin >> buf) origin += buf;
    forigin.close();
    //读入修改文件
    wifstream fadd;
    fadd.open(add_path, ios::in);
    wstring add = L" ";
    while (fadd >> buf) add += buf;
    fadd.close();
    /*
    printf("size=%d\n", (int)add.size());
    wcout << add << endl;*/
    
    //最长公共子序列查重
    int dp[2][100005];
    memset(dp, 0, sizeof(dp));
    int cur = 0, pre = 1;
    int originsize = origin.size();
    int addsize = add.size();
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

    //整理答案
    int ans = dp[cur][addsize - 1];
    double rate = (double)ans / (double)originsize;

    printf("osize=%d asize=%d\n", originsize, addsize);
    printf("nums=%d, %.2lf", ans, rate);

    ofstream fans(ans_path);
    fans  << fixed << setprecision(2) << rate;
   
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
