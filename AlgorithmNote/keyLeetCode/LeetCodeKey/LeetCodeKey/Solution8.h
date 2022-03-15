#pragma once
#include <string>
#include <unordered_map>

using namespace std;

enum AtoiStatus {
    start = 0,
    sign = 1,
    number = 2,
    end = 3
};

class Automaton {
    AtoiStatus state = AtoiStatus::start;

    unordered_map<AtoiStatus, vector<AtoiStatus>> table = {
        {AtoiStatus::start, {AtoiStatus::start, AtoiStatus::sign, AtoiStatus::number, AtoiStatus::end}},
        {AtoiStatus::sign, {AtoiStatus::end, AtoiStatus::end, AtoiStatus::number, AtoiStatus::end}},
        {AtoiStatus::number, {AtoiStatus::end, AtoiStatus::end, AtoiStatus::number, AtoiStatus::end}},
        {AtoiStatus::end, {AtoiStatus::end, AtoiStatus::end, AtoiStatus::end, AtoiStatus::end}}
    };

    AtoiStatus getStatus(char c);
public:
    int sign = 1;
    long long ans = 0;

    void get(char c);
};

class Solution8 {
public:
    int myAtoi(string s);
    int myAtoi2(string s);
};
