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

using namespace std;

// 分页显示教程，适合初学者分步阅读，支持前后翻页
void tutorial() {
    vector<string> pages;

    pages.push_back(R"(
================================================
          吉他换弦计算器及说明（1/3）
================================================

0. 这个计算器是干什么的？
  - 答：琴弦总长度由两部分组成：绕在弦钮上的缠绕长度与从弦钮到琴桥的伸直长度。
  - 直接从完全伸直状态上紧琴弦会导致缠绕圈数太少，音高严重偏高。
  - 本工具用于计算需要预留的长度，以便上紧后既能保证缠绕圈数也能保证伸直长度。

1. 公式说明：
  - 预留长度基于公式: L = (n - 0.5) × π × (弦钮直径 + 琴弦直径)。
  - 虽然真实缠绕为螺旋线，但将其近似为圆形误差通常可忽略不计。
  - 我们还提供通过比较品柱区间的"快速参考"方法，无需精确测量即可上弦。
)");

    pages.push_back(R"(
================================================
          吉他换弦计算器及说明（2/3）
================================================

2. 推荐品位区间使用方法（无需尺子测量）:
  - 推荐品位区间表示该区间的长度非常接近琴弦需要的预留长度。
  - 示例（1弦）推荐区间: 0-2 品：
    1) 右手捏住琴弦的弦枕位置；
    2) 右手将琴弦向后拉动，直到拉到第2品；
    3) 右手保持不动，左手折弯自由端并反绕锁弦。
  - 其他琴弦同理，优先选择靠近弦枕的区间（更易操作与观察）。

3. 换弦基本步骤
  - 将琴弦穿过弦钮孔并拉直；
  - 按推荐区间后拉非自由端并保持，在弦钮孔出口处折弯自由端；
  - 将自由端从琴头内侧贴紧弦钮绕到非自由端下方，反绕并勾住非自由端，上紧并修剪多余琴弦；
  - 用调音器调至标准音高。
)");

    pages.push_back(R"(
================================================
          吉他换弦计算器及说明（3/3）
================================================

4. 安全与维护提示
  - 修剪多余琴弦时请佩戴护目镜或侧头避免飞溅；
  - 换弦后轻拉每根琴弦促使应力释放，新弦通常需 24-48 小时稳定；
  - 多次调音是正常过程，耐心等待稳定。

小贴士：实际操作几次后，您会习得手感，届时可减少查表依赖。

祝您换弦顺利，琴技进步！
)");

    int currentPage = 0;
    int totalPages = pages.size();

    while (true) {
        system("cls");
        cout << pages[currentPage] << endl;

        // 显示导航提示
        if (currentPage == 0) {
            cout << "\n[第 " << currentPage + 1 << "/" << totalPages << " 页] ";
            cout << "按 N 或 Enter 下一页，按 Q 返回主菜单" << endl;
        }
        else if (currentPage == totalPages - 1) {
            cout << "\n[第 " << currentPage + 1 << "/" << totalPages << " 页] ";
            cout << "按 P 上一页，按 Q 或 Enter 返回主菜单" << endl;
        }
        else {
            cout << "\n[第 " << currentPage + 1 << "/" << totalPages << " 页] ";
            cout << "按 P 上一页，按 N 或 Enter 下一页，按 Q 返回主菜单" << endl;
        }

        // 获取用户输入
        string input;
        getline(cin, input);

        // 处理用户输入
        if (input == "N" || input == "n") {
            if (currentPage < totalPages - 1) {
                currentPage++;
            }
        }
        else if (input == "P" || input == "p") {
            if (currentPage > 0) {
                currentPage--;
            }
        }
        else if (input == "Q" || input == "q" || (input.empty() && currentPage == totalPages - 1)) {
            break; // 在最后一页时，Q 或 Enter 都可以退出
        }
        // 兼容原来的回车继续（下一页），但仅限于非最后一页
        else if (input.empty() && currentPage < totalPages - 1) {
            currentPage++;
        }
    }
}
