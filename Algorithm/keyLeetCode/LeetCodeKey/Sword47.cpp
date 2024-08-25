#include "Sword47.h"
#include<cmath> 

using std::max;

int Sword47::maxValue(vector<vector<int>>& grid) {
        vector<vector<int>> dp(grid.size(), vector<int>(grid.at(0).size()));

        dp.at(0).at(0) = grid.at(0).at(0);

        for (int j = 1; j < grid.at(0).size(); j++) {
            dp.at(0).at(j) = dp.at(0).at(j - 1) + grid.at(0).at(j);
        }

        for (int i = 1; i < grid.size(); i++) {
            dp.at(i).at(0) = dp.at(i - 1).at(0) + grid.at(i).at(0);
        }


        for (int i = 1; i < grid.size(); i++) {
            for (int j = 1; j < grid.at(0).size(); j++) {
                dp.at(i).at(j) = max(dp.at(i - 1).at(j), dp.at(i).at(j - 1)) + grid.at(i).at(j);
            }
        }

        return dp.at(grid.size() - 1).at(grid.at(0).size() - 1);
}
