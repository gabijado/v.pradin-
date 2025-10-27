#include "funkcijos.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

// Rodyti rezultatus ir generuoti failus
void rodytiRezultatus(vector<Studentas>& studentai) {
    sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) { return a.pav < b.pav; });

    int pasirinkimas;
    cout << "Pasirinkite galutinio balo skaiciavimo metoda: \n";
    cout << "1 - Vidurkis\n2 - Mediana\n3 - Abu\n";
    cin >> pasirinkimas;

    cout << fixed << setprecision(2);
    if (pasirinkimas == 1) {
        cout << left << setw(15) << "Vardas" << "|" << setw(20)
            << "Pavarde" << "|" << setw(18) << "Galutinis (Vid.)" << endl;
        cout << string(55, '-') << endl;
        for (auto& s : studentai)
            cout << left << setw(15) << s.var << "|" << setw(20)
            << s.pav << "|" << setw(18) << s.gal_vid << endl;
    }
    else if (pasirinkimas == 2) {
        cout << left << setw(15) << "Vardas" << "|" << setw(20)
            << "Pavarde" << "|" << setw(18) << "Galutinis (Med.)" << endl;
        cout << string(55, '-') << endl;
        for (auto& s : studentai)
            cout << left << setw(15) << s.var << "|" << setw(20)
            << s.pav << "|" << setw(18) << s.gal_med << endl;
    }
    else {
        cout << left << setw(15) << "Vardas" << "|" << setw(20)
            << "Pavarde" << "|" << setw(18) << "Galutinis (Vid.)"
            << "|" << setw(18) << "Galutinis (Med.)" << endl;
        cout << string(80, '-') << endl;
        for (auto& s : studentai)
            cout << left << setw(15) << s.var << "|" << setw(20)
            << s.pav << "|" << setw(18) << s.gal_vid
            << "|" << setw(18) << s.gal_med << endl;
    }

    vector<Studentas> vargsiukai, kietiakiai;
    for (auto& s : studentai) {
        if (s.gal_vid < 5.0) vargsiukai.push_back(s);
        else kietiakiai.push_back(s);
    }

    ofstream fout1("vargsiukai.txt"), fout2("kietiakiai.txt");
    fout1 << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << setw(18) << "Galutinis (Vid.)" << endl;
    fout2 << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << setw(18) << "Galutinis (Vid.)" << endl;

    for (auto& s : vargsiukai) fout1 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;
    for (auto& s : kietiakiai) fout2 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;

    cout << "\nSugeneruoti failai: vargsiukai.txt ir kietiakiai.txt\n";
}

// Skirstyti ir rasyti i failus
template <typename Container>
void skirstytiIrRasyti(const Container& studentai, const string& konteinerio_pav, double& skirstymo_laikas, double& rasymo_laikas) {
    auto start_s = high_resolution_clock::now();
    Container vargsiukai, kietiakiai;
    for (auto& s : studentai) {
        if (s.gal_vid < 5.0) vargsiukai.push_back(s);
        else kietiakiai.push_back(s);
    }
    auto end_s = high_resolution_clock::now();
    skirstymo_laikas = duration_cast<duration<double>>(end_s - start_s).count();

    auto start_w = high_resolution_clock::now();
    string failas_vargs = "vargsiukai_" + konteinerio_pav + ".txt";
    string failas_kiet = "kietiakiai_" + konteinerio_pav + ".txt";

    ofstream fout1(failas_vargs), fout2(failas_kiet);
    fout1 << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << setw(18) << "Galutinis (Vid.)" << endl;
    fout2 << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << setw(18) << "Galutinis (Vid.)" << endl;

    for (auto& s : vargsiukai) fout1 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;
    for (auto& s : kietiakiai) fout2 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;

    fout1.close(); fout2.close();
    auto end_w = high_resolution_clock::now();
    rasymo_laikas = duration_cast<duration<double>>(end_w - start_w).count();
}

// Template explicit instanciacija
template void skirstytiIrRasyti<vector<Studentas>>(const vector<Studentas>&, const string&, double&, double&);
template void skirstytiIrRasyti<list<Studentas>>(const list<Studentas>&, const string&, double&, double&);

// Generuoti faila
void generuotiFaila(int kiekis) {
    string failo_pav = "studentai_" + to_string(kiekis) + ".txt";
    ofstream fout(failo_pav);
    fout << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
    for (int i = 1; i <= 5; i++) fout << setw(8) << ("ND" + to_string(i));
    fout << setw(8) << "Egz" << endl;
    for (int i = 0; i < kiekis; i++) {
        fout << left << setw(15) << ("Vardas" + to_string(i + 1)) << setw(15) << ("Pavarde" + to_string(i + 1));
        for (int j = 0; j < 5; j++) fout << setw(8) << (rand() % 10 + 1);
        fout << setw(8) << (rand() % 10 + 1) << endl;
    }
    fout.close();
    cout << "Sugeneruotas failas: " << failo_pav << endl;
}

// Irasyti i readme
void irasytiRezultatusReadme(double v_read, double v_split, double v_write, double l_read, double l_split, double l_write, const string& failo_pav) {
    ofstream fout("readme.md", ios::app);
    fout << "\n## Testo rezultatai (" << failo_pav << ")\n\n";
    fout << "| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |\n";
    fout << "|--------------|----------------:|----------------:|-------------:|\n";
    fout << "| **vector** | " << fixed << setprecision(6) << v_read << " | " << v_split << " | " << v_write << " |\n";
    fout << "| **list**   | " << l_read << " | " << l_split << " | " << l_write << " |\n";
    fout << "\n";
    fout.close();
    cout << "Rezultatai irasyti i readme.md\n";
}
