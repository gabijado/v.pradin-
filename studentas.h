#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Studentas {
    string var;
    string pav;
    vector<int> paz;
    int egz{};
    double gal_vid{};
    double gal_med{};
};

// Funkcijų deklaracijos
double mediana(vector<int> paz);

template <typename Container>
Container skaitytiIsFailo(const string& failo_pav);

void rodytiRezultatus(vector<Studentas>& studentai);

#endif
