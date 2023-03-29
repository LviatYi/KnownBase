#include "Solution2469.h"

std::vector<double> Solution2469::convertTemperature(double celsius) {
    std::vector<double> ret;

    ret.push_back(celsius + 273.15);
    ret.push_back(celsius * 1.8 + 32.0);

    return ret;
}
