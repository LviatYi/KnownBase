#pragma once
#include <string>
#include <unordered_map>

using namespace std;

enum AtoiStatus_Solution8 {
	start = 0,
	sign = 1,
	number = 2,
	end = 3
};

class Automaton_Solution8 {
	AtoiStatus_Solution8 state = AtoiStatus_Solution8::start;

	unordered_map<AtoiStatus_Solution8, vector<AtoiStatus_Solution8>> table = {
		{
			AtoiStatus_Solution8::start,
			{
				AtoiStatus_Solution8::start, AtoiStatus_Solution8::sign, AtoiStatus_Solution8::number,
				AtoiStatus_Solution8::end
			}
		},
		{
			AtoiStatus_Solution8::sign,
			{
				AtoiStatus_Solution8::end, AtoiStatus_Solution8::end, AtoiStatus_Solution8::number,
				AtoiStatus_Solution8::end
			}
		},
		{
			AtoiStatus_Solution8::number,
			{
				AtoiStatus_Solution8::end, AtoiStatus_Solution8::end, AtoiStatus_Solution8::number,
				AtoiStatus_Solution8::end
			}
		},
		{
			AtoiStatus_Solution8::end,
			{AtoiStatus_Solution8::end, AtoiStatus_Solution8::end, AtoiStatus_Solution8::end, AtoiStatus_Solution8::end}
		}
	};

	AtoiStatus_Solution8 getStatus(char c);
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
