#include "funkcijos.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace std::chrono;

void generuotiFaila(int kiekis) {
    string failo_pav = "studentai_" + to_string(kiekis) + ".txt";
    ofstream fout(failo_pav);
    fout << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egz\n";
    for (int i = 0; i < kiekis; i++) {
        fout << "Vardas" + to_string(i + 1) << " Pavarde" + to_string(i + 1);
        for (int j = 0; j < 5; j++) fout << " " << (rand() % 10 + 1);
        fout << " " << (rand() % 10 + 1) << "\n";
    }
    fout.close();
    cout << "Sugeneruotas failas: " << failo_pav << endl;
}

vector<Studentas> skaitytiIsFailo(const string& failo_pav) {
    vector<Studentas> studentai;
    ifstream fin(failo_pav);
    if (!fin) { cout << "Nepavyko atidaryti failo " << failo_pav << endl; return studentai; }
    string line, var, pav;
    int egz, pazymys;
    getline(fin, line); // praleidžiame header
    while (fin >> var >> pav) {
        Studentas s; s.var = var; s.pav = pav;
        int sum = 0;
        for (int i = 0; i < 5; i++) { fin >> pazymys; s.paz.push_back(pazymys); sum += pazymys; }
        fin >> egz; s.egz = egz;
        s.gal_vid = sum / 5.0 * 0.4 + egz * 0.6;
        studentai.push_back(s);
    }
    fin.close();
    return studentai;
}

void skirstytiIrRasyti(const vector<Studentas>& studentai, const string& failo_pavadinimas) {
    auto start_s = chrono::high_resolution_clock::now();
    vector<Studentas> vargsiukai, kietiakiai;
    for (auto& s : studentai) {
        if (s.gal_vid < 5) vargsiukai.push_back(s);
        else kietiakiai.push_back(s);
    }
    auto end_s = chrono::high_resolution_clock::now();
    double split_time = chrono::duration_cast<chrono::duration<double>>(end_s - start_s).count();

    auto start_w = chrono::high_resolution_clock::now();
    ofstream f1("vargsiukai_" + failo_pavadinimas + ".txt");
    ofstream f2("kietiakiai_" + failo_pavadinimas + ".txt");
    for (auto& s : vargsiukai) f1 << s.var << " " << s.pav << " " << s.gal_vid << "\n";
    for (auto& s : kietiakiai) f2 << s.var << " " << s.pav << " " << s.gal_vid << "\n";
    f1.close(); f2.close();
    auto end_w = chrono::high_resolution_clock::now();
    double write_time = chrono::duration_cast<chrono::duration<double>>(end_w - start_w).count();

    cout << "Skirstymas uztruko: " << split_time << " s, Rasymas: " << write_time << " s\n";
}
