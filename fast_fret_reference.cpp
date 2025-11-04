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

// 计算品柱位置的函数
double calculateFretPosition(int fret, double scaleLength) {
    return scaleLength * (1.0 - pow(2.0, -fret / 12.0));
}

// 位置分段惩罚函数 - 只考虑结束品位j的位置
double calculatePositionPenalty(int j) {
    if (j <= 7) {
        return 0.0;      // j不超过7，惩罚值为0
    }
    else if (j <= 12) {
        return 0.3;      // j不超过12，惩罚值为0.3
    }
    else if (j <= 17) {
        return 0.7;      // j不超过17，惩罚值为0.7
    }
    else {
        return 1.0;      // j超过17，惩罚值为1
    }
}

// 误差分段惩罚函数 - 根据绝对误差大小
double calculateErrorPenalty(double error) {
    double absError = abs(error);
    if (absError <= 1.0) {
        return 0.0;      // 误差不超过1mm，惩罚值为0
    }
    else if (absError <= 2.0) {
        return 0.3;      // 误差不超过2mm，惩罚值为0.3
    }
    else if (absError <= 3.0) {
        return 0.7;      // 误差不超过3mm，惩罚值为0.7
    }
    else {
        return 1.0;      // 误差超过3mm，惩罚值为1
    }
}

// 计算综合评分（位置惩罚 + 误差惩罚）
double calculateScore(double positionPenalty, double errorPenalty,
    double positionWeight = 0.5, double errorWeight = 0.5) {
    // 综合评分 = 位置惩罚 * 位置权重 + 误差惩罚 * 误差权重
    return positionPenalty * positionWeight + errorPenalty * errorWeight;
}

// 计算预留长度 - 使用double类型的n参数
double calculateReservedLength(double n, double D, double d) {
    const double PI = 3.14159265358979323846;
    return (n - 0.5) * PI * (D + d);
}

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

// 辅助函数：将double转换为指定精度的字符串
string to_string_with_precision(double value, int precision) {
    stringstream ss;
    ss << fixed << setprecision(precision) << value;
    return ss.str();
}

void calculate() {
    system("cls"); // 清屏

    // 默认参数
    double defaultScaleLength = 628.65; // 默认弦长628.65mm
    double defaultTuningPostDiameter = 4.5; // 默认弦钮直径4.5mm
    string defaultStringGauge = "010E"; // 默认琴弦规格

    // 琴弦规格映射 - 使用新命名规则
    map<string, vector<double>> stringGauges = {
        // 电吉他琴弦规格 (E = Electric)
        {"008E", {0.008, 0.010, 0.015, 0.021, 0.030, 0.038}},  // 超轻规格
        {"009E", {0.009, 0.011, 0.016, 0.024, 0.032, 0.042}},  // 标准轻规格
        {"010E", {0.010, 0.013, 0.017, 0.026, 0.036, 0.046}},  // 标准规格
        {"011E", {0.011, 0.014, 0.018, 0.028, 0.038, 0.049}},  // 中等规格
        {"012E", {0.012, 0.016, 0.024, 0.032, 0.042, 0.054}},  // 重型规格
        {"013E", {0.013, 0.017, 0.026, 0.036, 0.046, 0.056}},  // 超重型规格

        // 民谣吉他琴弦规格 (A = Acoustic)
        {"011A", {0.011, 0.015, 0.023, 0.032, 0.042, 0.052}},  // 民谣轻规格
        {"012A", {0.012, 0.016, 0.025, 0.032, 0.042, 0.053}},  // 民谣标准轻规格
        {"013A", {0.013, 0.017, 0.025, 0.032, 0.045, 0.056}},  // 民谣标准规格
        {"014A", {0.014, 0.018, 0.027, 0.039, 0.049, 0.059}},  // 民谣中型规格
    };

    // 推荐缠绕圈数 - 使用double类型
    vector<double> recommendedTurns = { 5.0, 4.5, 4.0, 3.0, 2.5, 2.0 };
    vector<string> stringNames = { "1弦", "2弦", "3弦", "4弦", "5弦", "6弦" };

    // 获取用户输入
    double scaleLength;
    double tuningPostDiameter;
    string stringGauge;

    cout << "本计算器支持以下规格的琴弦:" << endl;
    cout << "电吉他(E): 008E, 009E, 010E, 011E, 012E, 013E" << endl;
    cout << "民谣吉他(A): 011A, 012A, 013A, 014A" << endl;
    cout << "请按提示输入您的吉他参数（直接回车使用默认值，默认值适用于装备010琴弦的Les Paul型电吉他）:" << endl;
    cout << "----------------------------------------" << endl;
    cout << "吉他弦长 (mm) [默认: " << defaultScaleLength << "]: ";
    string input;
    getline(cin, input);
    if (input.empty()) {
        scaleLength = defaultScaleLength;
    }
    else {
        scaleLength = stod(input);
    }

    cout << "弦钮直径 (mm) [默认: " << defaultTuningPostDiameter << "]: ";
    getline(cin, input);
    if (input.empty()) {
        tuningPostDiameter = defaultTuningPostDiameter;
    }
    else {
        tuningPostDiameter = stod(input);
    }

    cout << "琴弦规格 [默认: " << defaultStringGauge << "]: ";
    getline(cin, input);
    if (input.empty()) {
        stringGauge = defaultStringGauge;
    }
    else {
        stringGauge = input;
    }

    // 检查琴弦规格是否有效
    if (stringGauges.find(stringGauge) == stringGauges.end()) {
        cout << "无效的琴弦规格，使用默认值 010E" << endl;
        stringGauge = "010E";
    }

    // 计算预留长度
    vector<double> reservedLengths;
    const double INCH_TO_MM = 25.4;

    // 计算预留长度
    for (int i = 0; i < 6; i++) {
        double stringDiameterInch = stringGauges[stringGauge][i];
        double stringDiameterMM = stringDiameterInch * INCH_TO_MM;
        double reservedLength = calculateReservedLength(
            recommendedTurns[i], tuningPostDiameter, stringDiameterMM);
        reservedLengths.push_back(reservedLength);
    }

    // 计算品柱位置
    const int MAX_FRET = 22;
    vector<double> fretPositions(MAX_FRET + 1);
    for (int i = 0; i <= MAX_FRET; i++) {
        fretPositions[i] = calculateFretPosition(i, scaleLength);
    }

    // 为每个预留长度找到最匹配的品柱区间
    vector<vector<string>> fretIntervals(6);
    vector<vector<string>> fastRefIntervals(6);

    for (size_t s = 0; s < reservedLengths.size(); s++) {
        double target = reservedLengths[s];

        // 存储所有匹配的评分
        vector<tuple<double, int, int, double>> matches;

        for (int i = 0; i <= MAX_FRET; i++) {
            for (int j = i + 1; j <= MAX_FRET; j++) {
                double distance = fretPositions[j] - fretPositions[i];
                double error = distance - target;

                double positionPenalty = calculatePositionPenalty(j);
                double errorPenalty = calculateErrorPenalty(error);
                double score = calculateScore(positionPenalty, errorPenalty);
                matches.push_back(make_tuple(score, i, j, distance));
            }
        }

        // 按综合评分排序
        sort(matches.begin(), matches.end());

        // 存储详细区间信息
        for (size_t i = 0; i < matches.size() && i < 3; i++) {
            double score = get<0>(matches[i]);
            int fretI = get<1>(matches[i]);
            int fretJ = get<2>(matches[i]);
            double distance = get<3>(matches[i]);
            double error = distance - target;

            string intervalStr;
            if (fretI == 0) {
                intervalStr = "弦枕  -第" + (fretJ < 10 ? string(" ") : string("")) + to_string(fretJ) + "品";
            }
            else {
                intervalStr = "第" + (fretI < 10 ? string(" ") : string("")) + to_string(fretI) + "品-第" + (fretJ < 10 ? " " : "") + to_string(fretJ) + "品";
            }

            string detail = intervalStr + " = " + to_string_with_precision(distance, 1) +
                "mm (误差: " + (error >= 0 ? string(" ") : string("")) + to_string_with_precision(error, 1) + "mm)";
            fretIntervals[s].push_back(detail);
        }

        // 存储快速参考表信息
        for (size_t i = 0; i < matches.size(); i++) {
            double score = get<0>(matches[i]);
            int fretI = get<1>(matches[i]);
            int fretJ = get<2>(matches[i]);

            if (score < 1.0) {
                string fastIntervalStr;
                fastIntervalStr = (fretI < 10 ? string(" ") : string("")) + to_string(fretI) + " - " + (fretJ < 10 ? " " : "") + to_string(fretJ);
                fastRefIntervals[s].push_back(fastIntervalStr);
            }
        }
    }

    // 创建三页内容
    vector<string> pages;

    // 第一页：预留长度表格
    stringstream page1;
    page1 << "================================================" << endl;
    page1 << "              计算结果 - 预留长度" << endl;
    page1 << "================================================" << endl;
    page1 << endl;
    page1 << "根据您的参数计算的预留长度:" << endl;
    page1 << "+------+------------+----------+--------------+" << endl;
    page1 << "| 琴弦 | 直径(mm)   | 缠绕圈数 | 预留长度(mm) |" << endl;
    page1 << "+------+------------+----------+--------------+" << endl;

    for (int i = 0; i < 6; i++) {
        double stringDiameterInch = stringGauges[stringGauge][i];
        double stringDiameterMM = stringDiameterInch * INCH_TO_MM;

        page1 << "| " << left << setw(4) << stringNames[i]
            << " | " << fixed << setprecision(3) << setw(10) << stringDiameterMM
            << " | " << setprecision(1) << setw(8) << recommendedTurns[i]
            << " | " << setprecision(1) << setw(12) << reservedLengths[i] << " |" << endl;
    }
    page1 << "+------+------------+----------+--------------+" << endl;
    page1 << endl;
    page1 << "吉他弦长: " << scaleLength << "mm" << endl;
    page1 << "弦钮直径: " << tuningPostDiameter << "mm" << endl;
    page1 << "琴弦规格: " << stringGauge << endl;
    pages.push_back(page1.str());

    // 第二页：详细品位区间
    stringstream page2;
    page2 << "================================================" << endl;
    page2 << "          快速参考品位区间（详细）" << endl;
    page2 << "================================================" << endl;
    page2 << endl;
    page2 << "以下是为每根琴弦推荐的参考品位区间。" << endl;
    page2 << "在换弦时，您可以将琴弦预留长度与这些品位间的距离进行比较。" << endl;
    page2 << endl;

    for (size_t s = 0; s < reservedLengths.size(); s++) {
        page2 << stringNames[s] << " (" << reservedLengths[s] << "mm):" << endl;
        for (const auto& interval : fretIntervals[s]) {
            page2 << " - " << interval << endl;
        }
        page2 << endl;
    }
    pages.push_back(page2.str());

    // 第三页：快速参考表
    stringstream page3;
    page3 << "================================================" << endl;
    page3 << "          快速参考表（简洁版）" << endl;
    page3 << "================================================" << endl;
    page3 << endl;
    page3 << "琴弦       预留长度     推荐品位区间" << endl;
    page3 << "----------------------------------------" << endl;

    for (size_t s = 0; s < reservedLengths.size(); s++) {
        page3 << left << setw(12) << stringNames[s]
            << setw(10) << reservedLengths[s] << "mm   ";

        if (!fastRefIntervals[s].empty()) {
            page3 << fastRefIntervals[s][0];
        }
        page3 << endl;
    }

    page3 << endl;
    page3 << "提示：使用推荐区间时，优先选择靠近弦枕的区间，" << endl;
    page3 << "这样更容易操作和观察。" << endl;
    pages.push_back(page3.str());

    // 分页显示结果
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