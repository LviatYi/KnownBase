#include "Solution28.h"
#include<iostream>
/// <summary>
/// 求取 next 数组。
/// next[i] 指 字符串 str 中前 i 个字符的最长公共真前后缀的长度。
/// </summary>
/// <param name="str"></param>
/// <param name="length">str 长度</param>
/// <param name="next">next 数组，要求长度不小于 length</param>
/// <returns></returns>
void getNext(const char* str, int length, int* next) {
    if (length <= 0) {
        return;
    }
    next[0] = 0;
    for (int i = 1, j = 0; i < length; ) {
        if (j > 0 && str[i] != str[j]) {
            j = next[j - 1];
        }
        else if (str[i] == str[j]) {
            next[i] = j + 1;
            i++, j++;
        }
        else {
            next[i++] = 0;
        }
    }
    return;
}

int Solution28::strStr(std::string haystack, std::string needle) {
    if (needle.size() <= 0) {
        return 0;
    }

    int* next;
    next = (int*)malloc(sizeof(int) * needle.size());
    getNext(needle.c_str(), needle.size(), next);
    int pos = -1;

    for (int i = 0; i < needle.length(); i++) {
        std::cout << next[i] << std::endl;
    }

    for (int i = 0, j = 0; i < haystack.size(); i++) {
        if (haystack[i] == needle[j]) {
            j++;
        }
        else if (j > 0) {
            i--;
            j = next[j - 1];
        }

        if (j == needle.size()) {
            pos = i - needle.size() + 1;
            break;
        }
    }

    free(next);
    return pos;
}