#include <algorithm>
#include <iostream>
#include <string>

void printBackwards(std::string const st) {
    if (st.length() == 0) { return; }
    std::string word = "";
    for (size_t i = 0; i < st.length(); ++i) {
        if (isalpha(st[i])) { word += st[i]; } else { break; }
    }
    int pos = word.length() ? word.length() : 1;
    printBackwards(st.substr(pos));
    if (word.length()) { std::cout << word << " "; }
}

int hj31() {
    std::string sentence;
    std::getline(std::cin, sentence, '\n');
    printBackwards(sentence);
    std::cout << std::endl;
    return 0;
}
