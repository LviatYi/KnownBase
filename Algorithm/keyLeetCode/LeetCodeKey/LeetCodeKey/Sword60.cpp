#include "Sword60.h"

vector<double> Sword60::dicesProbability(int n) {
    if (n <= this->dp.size()) {
        return dp.at(n - 1);
    }

    vector<double> n1 = dp.at(0);
    vector<double> nMinus1 = dicesProbability(n - 1);
    vector<double>nCurr;

        for (int j = 0; j < nMinus1.size(); j++) {
            nCurr.push_back(0);
            for (int i = 0; i < 6 && j - i >= 0; i++) {
                nCurr.at(j) += n1.at(i) * nMinus1.at(j - i);
            }
        }

        int nCurrInsertPos = nCurr.size() - 1;
        int nMinus1LastPos = nMinus1.size() - 1;
        for (int i = 1; i < 6; i++) {
            nCurr.push_back(0);
            for (int j = 0; j < 6 - i && j - j >= 0; j++) {
                nCurr.at(nCurrInsertPos + i) += n1.at(i + j) * nMinus1.at(nMinus1LastPos - j);
            }
        }

    dp.push_back(nCurr);

    return dp.at(n - 1);
}
