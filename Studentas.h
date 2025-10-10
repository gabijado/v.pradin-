#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <vector>
#include <string>

struct Studentas {
    std::string var;
    std::string pav;
    std::vector<int> paz;
    int egz{};
    double gal_vid{};
    double gal_med{};
};

double mediana(std::vector<int> paz);

#endif
