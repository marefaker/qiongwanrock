#pragma once
#ifndef FAST_FRET_REFERENCE_H
#define FAST_FRET_REFERENCE_H
#include <vector>
#include <string>

using namespace std;

double calculateFretPosition(int fret, double scaleLength);
double calculatePositionPenalty(int j);
double calculateErrorPenalty(double error);
double calculateScore(double positionPenalty, double errorPenalty,
    double positionWeight = 0.5, double errorWeight = 0.5);
string to_string_with_precision(double value, int precision);
double calculateReservedLength(double n, double D, double d);
void tutorial();
void calculate();

#endif