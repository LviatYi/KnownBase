#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>

int hj19() {
    std::map<std::string, int> record;
    std::queue<std::string> q;
    std::string path;
    int line;
    while (std::cin >> path >> line) {
        auto pos = path.find_last_of('\\');
        std::string filename;
        if (pos == std::string::npos) {
            filename = path.substr(path.size() > 16
                                       ? path.size() - 16
                                       : 0);
        } else {
            filename = path.substr(path.size() - pos - 1 > 16
                                       ? path.size() - 16
                                       : pos + 1);
        }

        auto filename_with_line = filename + " " + std::to_string(line);

        if (record.find(filename_with_line) == record.end()) {
            q.push(filename_with_line);
            if (q.size() > 8) {
                q.pop();
            }
            record.insert({filename_with_line, 1});
        } else {
            record[filename_with_line] = record[filename_with_line] + 1;
        }
    }

    while (!q.empty()) {
        auto r = q.front();
        std::cout << r << " " << record[r] << std::endl;
        q.pop();
    }

    return 0;
}
