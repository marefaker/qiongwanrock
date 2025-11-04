#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <tuple>
#include <map>
#include <sstream>
#include <cstring>
#include <Windows.h>
#include "fast_fret_reference.h"

using namespace std;

int main() {
    
    // SetConsoleOutputCP(65001);

    while (1) {
	    system("cls"); // 清屏
        cout << "感谢您使用换弦计算器" << endl;
        cout << "本项目完全开源，使用者可在源码中自定义琴弦规格，亦可添加对七弦吉他、贝斯、尤克里里的支持" << endl;
        cout << "按 T 显示教程，按 C 计算，按 Q 或 Enter 退出..." << endl;
        char operation = getchar();
        if (operation == 'T' || operation == 't') {
		    system("cls"); // 清屏
            cin.ignore(65535, '\n'); // 清除输入缓冲区
            tutorial();
            continue;
        }
        else if (operation == 'Q' || operation == 'q' || operation == '\n') {
            break;
        }
        else if (operation == 'C' || operation == 'c') {
            system("cls"); // 清屏
            cin.ignore(65535, '\n'); // 清除输入缓冲区
            calculate();
            continue; 
        }  
        else {        
            cout << "无效输入，请重新选择。" << endl;
            cin.ignore(65535, '\n'); // 清除输入缓冲区
            continue;
        }
    }
	
    return 0;
}