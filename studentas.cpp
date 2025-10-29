#include "studentas.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <list>

using namespace std;

// Funkcija medianai apskaičiuoti
double mediana(vector<int> paz) {
    if (paz.empty()) return 0.0;
    sort(paz.begin(), paz.end());
    int n = paz.size();
    if (n % 2 == 0)
        return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;
    else
        return paz[n / 2];
}

// Template funkcija duomenims skaityti iš failo
template <typename Container>
Container skaitytiIsFailo(const string& failo_pav) {
    Container studentai;
    ifstream fin(failo_pav);
    if (!fin) {
        cout << "Nepavyko atidaryti failo: " << failo_pav << endl;
        return studentai;
    }

    string header;
    getline(fin, header);

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Studentas s;
        ss >> s.var >> s.pav;

        int sum = 0;
        int pazymys;
        for (int i = 0; i < 5; i++) {
            ss >> pazymys;
            s.paz.push_back(pazymys);
            sum += pazymys;
        }

        ss >> s.egz;

        s.gal_vid = double(sum) / s.paz.size() * 0.4 + s.egz * 0.6;
        s.gal_med = mediana(s.paz) * 0.4 + s.egz * 0.6;

        studentai.push_back(s);
    }

    fin.close();
    return studentai;
}

// Explicit instanciacijos
template vector<Studentas> skaitytiIsFailo<vector<Studentas>>(const string&);
template list<Studentas> skaitytiIsFailo<list<Studentas>>(const string&);
