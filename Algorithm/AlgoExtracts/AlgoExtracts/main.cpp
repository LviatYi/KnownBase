#include <iostream>

#include "AvlTree.h"
#include "SortUtil.h"

int main() {
    std::vector<int> a = {5, 3, 2, 4, 1, 6};

    LviatAlgoExtract::SortUtil::quick_sort(a, 0, a.size());

    return 1;
}
