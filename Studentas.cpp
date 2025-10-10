#include "Studentas.h"
#include <algorithm>

double mediana(std::vector<int> paz) {
    if (paz.empty()) return 0.0;
    std::sort(paz.begin(), paz.end());
    int n = paz.size();
    if (n % 2 == 0) {
        return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;
    }
    else {
        return paz[n / 2];
    }
}
