#include "Solution735.h"

std::vector<int> Solution735::asteroidCollision(std::vector<int>& asteroids) {
    std::vector<int> ret = {};

    for (int asteroid : asteroids) {
        if (asteroid < 0) {
            while (!ret.empty() && *(ret.end() - 1) > 0 && *(ret.end() - 1) < -asteroid) {
                ret.pop_back();
            }
            if (!ret.empty()) {
                if (*(ret.end() - 1) == -asteroid) {
                    ret.pop_back();
                    continue;
                }
                if (*(ret.end() - 1) > -asteroid) {
                    continue;
                }
            }
        }

        ret.push_back(asteroid);
    }
    return ret;
}
