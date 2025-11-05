# 吉他换弦计算器

一个用于帮助手工换弦时预留长度与快速参考品位区间的控制台工具。基于简单几何与吉他品位等比律，计算需要在弦钮绕线处预留的长度，并给出与琴颈品柱对应的参考区间，方便无需精确测量时快速上弦。

## 主要功能
- 按弦钮直径、琴弦直径与推荐缠绕圈数计算预留长度（mm）。
- 计算琴颈上各品位位置，比较并给出与预留长度最匹配的品位区间（详细与简洁两种显示）。
- 基于“位置惩罚 + 误差惩罚”给出排序，优先推荐更易操作的靠近弦枕区间。
- 内置常见电吉他 / 民谣吉他的弦规集合（可在源码中扩展）。

## 算法简介

### 预留长度计算
基于几何模型计算在弦钮上缠绕指定圈数所需的琴弦长度：

```cpp

double calculateReservedLength(double n, double D, double d) {
    const double PI = 3.14159265358979323846;
    return (n - 0.5) * PI * (D + d);
}

```

**公式**：`L = (n - 0.5) × π × (弦钮直径 + 琴弦直径)`  
- `n`：目标缠绕圈数
- `D`：弦钮直径
- `d`：琴弦直径
- `-0.5`：锁弦法消耗的等效半圈长度

### 品位位置计算
基于十二平均律计算从弦枕到各品柱的距离：

```cpp

double calculateFretPosition(int fret, double scaleLength) {
    return scaleLength * (1.0 - 1.0 / pow(2.0, fret / 12.0));
}

```

**公式**：`pos(fret) = scaleLength × (1 - 2^(-fret/12))`  
- `fret`：品位数（0 = 弦枕）
- `scaleLength`：吉他有效弦长

### 优化匹配算法
通过多目标优化在品位区间中找到最佳视觉参考：

```cpp

// 代价函数：平衡误差与操作便利性
double calculateScore(double positionPenalty, double errorPenalty,
                    double positionWeight = 0.5, double errorWeight = 0.5) {
    return positionPenalty * positionWeight + errorPenalty * errorWeight;
}

// 遍历所有可能的品位区间组合
for (int i = 0; i <= MAX_FRET; i++) {
    for (int j = i + 1; j <= MAX_FRET; j++) {
        double distance = fretPositions[j] - fretPositions[i];
        double error = distance - targetLength;
        
        double positionPenalty = calculatePositionPenalty(j); // 偏好低品位
        double errorPenalty = calculateErrorPenalty(error);   // 控制精度
        double score = calculateScore(positionPenalty, errorPenalty);
        
        // 记录最优解...
    }
}

```

**算法流程**：
1. 遍历所有品位区间组合 `[i, j]`
2. 计算区间物理长度与目标长度的误差
3. 应用位置惩罚（偏好操作便利的低品位）和误差惩罚（控制匹配精度）
4. 按综合评分排序，输出最优参考区间

该算法确保在**精度**与**操作便利性**间取得最佳平衡，为换弦提供直观可靠的视觉参考。

## 编译与运行（Windows 推荐）
- 依赖：支持 C++11 的编译器，Windows API（源码使用了 Windows.h、system("cls") 等），建议在 Windows 环境下使用 MinGW 或 Visual Studio。
- 示例（使用 g++ / MinGW）:

```
    g++ -std=c++11 -O2 -o ffr.exe *.cpp
    ./ffr.exe
```

- 交互说明：
    - 启动后按 T 显示教程、C 进入计算、Q 或回车退出。
    - 计算界面会提示输入：琴弦长（mm）、弦钮直径（mm）、琴弦规格（例如 010E）。直接回车使用默认值。

## 默认值与内置数据
- 默认弦长：628.65 mm（Les Paul 型示例）
- 默认弦钮直径：4.5 mm
- 默认弦规：010E（内置多种电吉他/民谣吉他规格）
- 推荐缠绕圈数（六根弦示例）：5.0, 4.5, 4.0, 3.0, 2.5, 2.0

## 使用建议与注意事项
- 推荐区间优先选择靠近弦枕的一组品位，便于手工操作与观察。
- 换弦后新弦需反复拉紧并等待 24–48 小时以稳定音高。
- 修剪多余琴弦时请佩戴护目镜并注意安全。

## 可扩展项
- 添加七弦 / 贝斯 / 尤克里里等规格支持（在源码 stringGauges 映射中新增条目）。
- 改进界面以支持 GUI 或跨平台终端清屏兼容。
- 引入更精确的缠绕螺旋模型（如果需要更高精度的缠绕长度估算）。

## 示例输出（简略）
- 预留长度表：列出每根弦的直径（mm）、建议缠绕圈数、计算出的预留长度（mm）。
- 详细参考：列出若干“第 i 品 - 第 j 品 = XX.X mm (误差: ±Y.Y mm)”项。
- 简洁快速参考：每根弦显示最合适的品位区间（例如 “弦枕 - 第2品”）。

## 相关文档
- 本项目附带针对预算有限的电吉他新手的入门指南，详情可移步 [ROCK4BROKE.md](https://github.com/marefaker/Rock4Broke/blob/main/ROCK4BROKE.md)

## 许可证与贡献

- 本项目为开源；欢迎修改弦规、改进算法或添加平台兼容性。请在提交改动时附上简短说明与测试用例。