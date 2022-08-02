#include "Solution8.h"

int Solution8::myAtoi(string s) {
	// 直接解
	long long ans = 0;
	bool flag = false;

	// 擦除前段非数字字符
	s.erase(0, s.find_first_not_of(" "));

	if (s[0] == '-') {
		flag = true;
		s.erase(s.begin());
	}
	else if (s[0] == '+') {
		s.erase(s.begin());
	}

	int i = 0;
	while (i < s.length() && s[i] <= '9' && s[i] >= '0') {
		ans = ans < (LLONG_MAX - s[i]) / 10 ? ans * 10 + s[i] - '0' : LLONG_MAX;
		i++;
	}

	if (ans > INT_MAX) {
		return flag ? INT_MIN : INT_MAX;
	}
	else {
		return flag ? int(-ans) : int(ans);
	}
}

int Solution8::myAtoi2(string s) {
	// 自动机

	Automaton_Solution8 automaton;
	for (char c : s)
		automaton.get(c);
	return automaton.sign * automaton.ans;
}

AtoiStatus_Solution8 Automaton_Solution8::getStatus(char c) {
	if (isspace(c)) return AtoiStatus_Solution8::start;
	if (c == '+' or c == '-') return AtoiStatus_Solution8::sign;
	if (isdigit(c)) return AtoiStatus_Solution8::number;
	return AtoiStatus_Solution8::end;
}

void Automaton_Solution8::get(char c) {
	state = table[state][getStatus(c)];
	if (state == AtoiStatus_Solution8::number) {
		ans = ans * 10 + c - '0';
		ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);
	}
	else if (state == AtoiStatus_Solution8::sign)
		sign = c == '+' ? 1 : -1;

}
