#include "Funkcijos.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void ivestiStudentus(vector<Studentas>& studentai) {
    int kiek;
    cout << "Kiek studentu norite ivesti? ";
    cin >> kiek;

    for (int k = 0; k < kiek; k++) {
        Studentas s;
        int sum = 0;

        cout << "Ivesk studento duomenis\n";
        cout << "Vardas: ";
        cin >> s.var;
        cout << "Pavarde: ";
        cin >> s.pav;

        cout << "Iveskite namu darbu rezultatus (baigti su 0):\n";
        int pazymys;
        while (true) {
            cin >> pazymys;
            if (pazymys == 0) break;
            s.paz.push_back(pazymys);
            sum += pazymys;
        }

        cout << "Iveskite egzamino pazymi: ";
        cin >> s.egz;

        if (!s.paz.empty())
            s.gal_vid = double(sum) / s.paz.size() * 0.4 + s.egz * 0.6;
        else
            s.gal_vid = s.egz;

        s.gal_med = mediana(s.paz) * 0.4 + s.egz * 0.6;
        studentai.push_back(s);
    }
}

void generuotiStudentus(vector<Studentas>& studentai) {
    int kiek;
    cout << "Kiek studentu sugeneruoti? ";
    cin >> kiek;

    for (int k = 0; k < kiek; k++) {
        Studentas s;
        int sum = 0;

        cout << "Studento vardas: ";
        cin >> s.var;
        cout << "Studento pavarde: ";
        cin >> s.pav;

        int kiek_nd = rand() % 8 + 3;
        cout << "Sugeneruoti namu darbu pazymiai: ";
        for (int i = 0; i < kiek_nd; i++) {
            int pazymys = rand() % 10 + 1;
            s.paz.push_back(pazymys);
            sum += pazymys;
            cout << pazymys << " ";
        }
        cout << endl;

        s.egz = rand() % 10 + 1;
        cout << "Sugeneruotas egzamino pazymys: " << s.egz << endl;

        if (!s.paz.empty())
            s.gal_vid = double(sum) / s.paz.size() * 0.4 + s.egz * 0.6;
        else
            s.gal_vid = s.egz;

        s.gal_med = mediana(s.paz) * 0.4 + s.egz * 0.6;
        studentai.push_back(s);
    }
}

void nuskaitytiIsFailo(vector<Studentas>& studentai) {
    auto start = high_resolution_clock::now();

    ifstream fin("kursiokai.txt");
    if (!fin) {
        cout << "Nepavyko atidaryti failo" << endl;
        return;
    }

    string header;
    getline(fin, header);

    int nd_kiekis = 0;
    {
        stringstream ss(header);
        string zodis;
        vector<string> stulpeliai;
        while (ss >> zodis) stulpeliai.push_back(zodis);
        nd_kiekis = stulpeliai.size() - 3;
    }

    while (true) {
        Studentas s;
        int sum = 0;
        fin >> s.var >> s.pav;
        if (fin.fail()) break;

        int pazymys;
        for (int i = 0; i < nd_kiekis; i++) {
            fin >> pazymys;
            if (fin.fail()) break;
            s.paz.push_back(pazymys);
            sum += pazymys;
        }

        fin >> s.egz;
        if (fin.fail()) break;

        if (!s.paz.empty())
            s.gal_vid = double(sum) / s.paz.size() * 0.4 + s.egz * 0.6;
        else
            s.gal_vid = s.egz;

        s.gal_med = mediana(s.paz) * 0.4 + s.egz * 0.6;
        studentai.push_back(s);
    }
    fin.close();

    auto end = high_resolution_clock::now();
    cout << "Duomenu nuskaitymas uztruko: "
        << duration_cast<duration<double>>(end - start).count()
        << " s" << endl;
}

void generuotiFailus() {
    vector<int> dydziai = { 1000, 10000, 100000, 1000000, 10000000 };

    for (int d : dydziai) {
        auto start = high_resolution_clock::now();

        string failo_pavadinimas = "studentai" + to_string(d) + ".txt";
        ofstream fout(failo_pavadinimas);

        fout << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egz" << endl;

        for (int i = 1; i <= d; i++) {
            fout << "Vardas" << i << " Pavarde" << i << " ";
            for (int j = 0; j < 5; j++) {
                fout << (rand() % 10 + 1) << " ";
            }
            fout << (rand() % 10 + 1) << "\n";
        }
        fout.close();

        auto end = high_resolution_clock::now();
        cout << "Failo " << failo_pavadinimas
            << " kurimas uztruko: "
            << duration_cast<duration<double>>(end - start).count()
            << " s" << endl;
    }
}

void rodytiRezultatus(vector<Studentas>& studentai) {
    cout << left
        << setw(15) << "Vardas" << "|"
        << setw(20) << "Pavarde" << "|"
        << setw(18) << "Galutinis (Vid.)" << "|"
        << setw(18) << "Galutinis (Med.)" << endl;

    cout << string(15, '-') << "|"
        << string(20, '-') << "|"
        << string(18, '-') << "|"
        << string(18, '-') << endl;

    for (auto& s : studentai) {
        cout << left
            << setw(15) << s.var << "|"
            << setw(20) << s.pav << "|"
            << setw(18) << fixed << setprecision(2) << s.gal_vid << "|"
            << setw(18) << fixed << setprecision(2) << s.gal_med << endl;
    }
}

void issaugotiIRusiuoti(vector<Studentas>& studentai) {
    sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
        return a.pav < b.pav;
        });

    vector<Studentas> vargsiukai, kietiakiai;
    for (auto& s : studentai) {
        if (s.gal_vid < 5.0) vargsiukai.push_back(s);
        else kietiakiai.push_back(s);
    }

    ofstream fout_v("vargsiukai.txt");
    fout_v << left << setw(15) << "Vardas" << "|"
        << setw(20) << "Pavarde" << "|"
        << setw(18) << "Galutinis (Vid.)" << endl;
    fout_v << string(15, '-') << "|"
        << string(20, '-') << "|"
        << string(18, '-') << endl;
    for (auto& s : vargsiukai) {
        fout_v << left << setw(15) << s.var << "|"
            << setw(20) << s.pav << "|"
            << setw(18) << fixed << setprecision(2) << s.gal_vid << endl;
    }
    fout_v.close();

    ofstream fout_k("kietiakiai.txt");
    fout_k << left << setw(15) << "Vardas" << "|"
        << setw(20) << "Pavarde" << "|"
        << setw(18) << "Galutinis (Vid.)" << endl;
    fout_k << string(15, '-') << "|"
        << string(20, '-') << "|"
        << string(18, '-') << endl;
    for (auto& s : kietiakiai) {
        fout_k << left << setw(15) << s.var << "|"
            << setw(20) << s.pav << "|"
            << setw(18) << fixed << setprecision(2) << s.gal_vid << endl;
    }
    fout_k.close();

    cout << "\nSugeneruoti failai: vargsiukai.txt ir kietiakiai.txt\n";
}
