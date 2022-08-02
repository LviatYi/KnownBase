#pragma once
#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

enum AtoiStatus_Sword67 {
	start = 0,
	sign = 1,
	number = 2,
	end = 3
};

class Automaton_Sword67 {
	AtoiStatus_Sword67 state = AtoiStatus_Sword67::start;

	unordered_map<AtoiStatus_Sword67, vector<AtoiStatus_Sword67>> table = {
		{
			AtoiStatus_Sword67::start,
			{AtoiStatus_Sword67::start, AtoiStatus_Sword67::sign, AtoiStatus_Sword67::number, AtoiStatus_Sword67::end}
		},
		{
			AtoiStatus_Sword67::sign,
			{AtoiStatus_Sword67::end, AtoiStatus_Sword67::end, AtoiStatus_Sword67::number, AtoiStatus_Sword67::end}
		},
		{
			AtoiStatus_Sword67::number,
			{AtoiStatus_Sword67::end, AtoiStatus_Sword67::end, AtoiStatus_Sword67::number, AtoiStatus_Sword67::end}
		},
		{
			AtoiStatus_Sword67::end,
			{AtoiStatus_Sword67::end, AtoiStatus_Sword67::end, AtoiStatus_Sword67::end, AtoiStatus_Sword67::end}
		}
	};

	AtoiStatus_Sword67 getStatus(char c);
public:
	int sign = 1;
	long long ans = 0;

	void get(char c);
};

class Sword67 {
public:
	int strToInt(string str);
	int strToInt2(string str);
};
