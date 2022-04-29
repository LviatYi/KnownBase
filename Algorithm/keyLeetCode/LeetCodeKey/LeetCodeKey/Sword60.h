#pragma once
#include<vector>

using std::vector;

class Sword60 {
private:
    vector<vector<double>> dp{ { 1.0 / 6, 1.0 / 6, 1.0 / 6, 1.0 / 6, 1.0 / 6, 1.0 / 6 } };
public:
    vector<double> dicesProbability(int n);
};

