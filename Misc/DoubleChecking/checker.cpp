#include <cstdlib> // for system()
#include <iostream>
using namespace std;

int main() {
    int testCount = 1000;

    for (int t = 1; t <= testCount; ++t) {
        cout << "Test #" << t << ": ";

        // 编译阶段（适配 Windows，注意使用 mingw）
        system("g++ gen.cpp -o gen.exe -std=c++11 -O2");
        system("g++ std.cpp -o std.exe -std=c++11 -O2");
        system("g++ sol.cpp -o sol.exe -std=c++11 -O2");

        // 数据生成
        system("gen.exe > input.txt");

        // 运行程序
        system("std.exe < input.txt > std_output.txt");
        system("sol.exe < input.txt > sol_output.txt");

        // 比较结果（使用 Windows 下的 fc 命令）
        int diffResult = system("fc std_output.txt sol_output.txt > nul");

        if (diffResult != 0) {
            cout << "---------Wrong Answer!\n";
            cout << "Input:\n";
            system("type input.txt");
            cout << "\nExpected Output (std):\n";
            system("type std_output.txt");
            cout << "\nYour Output (sol):\n";
            system("type sol_output.txt");
            break;
        } else {
            cout << "OK\n";
        }
    }

    return 0;
}
