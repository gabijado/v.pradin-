#include "funkcijos.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <type_traits>

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
}

// Senoji funkcija palikta kaip yra (naudojama jei reikia)
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

// Strategija 1: kopijuoja į du naujus konteinerius (palieka originalą)
template <typename Container>
void skirstytiStrategija1(const Container& studentai, const string& konteinerio_pav, double& skirstymo_laikas, double& rasymo_laikas) {
    auto start_s = high_resolution_clock::now();
    Container vargsiukai, kietiakiai;
    for (const auto& s : studentai) {
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

    for (const auto& s : vargsiukai) fout1 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;
    for (const auto& s : kietiakiai) fout2 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;

    fout1.close(); fout2.close();
    auto end_w = high_resolution_clock::now();
    rasymo_laikas = duration_cast<duration<double>>(end_w - start_w).count();
}

// Strategija 2: naudojame vieną naują konteinerį (vargsiukai) ir ištriname juos iš pradinio
template <typename Container>
void skirstytiStrategija2(Container& studentai, const string& konteinerio_pav, double& skirstymo_laikas, double& rasymo_laikas) {
    auto start_s = high_resolution_clock::now();

    if constexpr (std::is_same_v<Container, std::vector<Studentas>>) {
        auto it = stable_partition(studentai.begin(), studentai.end(), [](const Studentas& s) { return s.gal_vid < 5.0; });
        std::vector<Studentas> vargsiukai(studentai.begin(), it);
        studentai.erase(studentai.begin(), it);

        auto end_s = high_resolution_clock::now();
        skirstymo_laikas = duration_cast<duration<double>>(end_s - start_s).count();

        auto start_w = high_resolution_clock::now();
        ofstream fout1("vargsiukai_" + konteinerio_pav + ".txt");
        ofstream fout2("kietiakiai_" + konteinerio_pav + ".txt");

        for (auto& s : vargsiukai) fout1 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;
        for (auto& s : studentai) fout2 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;

        fout1.close(); fout2.close();
        auto end_w = high_resolution_clock::now();
        rasymo_laikas = duration_cast<duration<double>>(end_w - start_w).count();
    }
    else if constexpr (std::is_same_v<Container, std::list<Studentas>>) {
        std::list<Studentas> vargsiukai;
        for (auto it = studentai.begin(); it != studentai.end(); ) {
            if (it->gal_vid < 5.0) {
                vargsiukai.push_back(*it);
                it = studentai.erase(it);
            }
            else ++it;
        }

        auto end_s = high_resolution_clock::now();
        skirstymo_laikas = duration_cast<duration<double>>(end_s - start_s).count();

        auto start_w = high_resolution_clock::now();
        ofstream fout1("vargsiukai_" + konteinerio_pav + ".txt");
        ofstream fout2("kietiakiai_" + konteinerio_pav + ".txt");

        for (auto& s : vargsiukai) fout1 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;
        for (auto& s : studentai) fout2 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;

        fout1.close(); fout2.close();
        auto end_w = high_resolution_clock::now();
        rasymo_laikas = duration_cast<duration<double>>(end_w - start_w).count();
    }
}

// Strategija 3: optimizuota (vector -> partition, list -> ciklas + erase)
template <typename Container>
void skirstytiStrategija3(Container& studentai, const string& konteinerio_pav, double& skirstymo_laikas, double& rasymo_laikas) {
    auto start_s = high_resolution_clock::now();

    if constexpr (std::is_same_v<Container, std::vector<Studentas>>) {
        auto it = std::partition(studentai.begin(), studentai.end(), [](const Studentas& s) { return s.gal_vid < 5.0; });
        std::vector<Studentas> vargsiukai(studentai.begin(), it);
        studentai.erase(studentai.begin(), it);

        auto end_s = high_resolution_clock::now();
        skirstymo_laikas = duration_cast<duration<double>>(end_s - start_s).count();

        auto start_w = high_resolution_clock::now();
        ofstream fout1("vargsiukai_" + konteinerio_pav + ".txt");
        ofstream fout2("kietiakiai_" + konteinerio_pav + ".txt");

        for (auto& s : vargsiukai) fout1 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;
        for (auto& s : studentai) fout2 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;

        fout1.close(); fout2.close();
        auto end_w = high_resolution_clock::now();
        rasymo_laikas = duration_cast<duration<double>>(end_w - start_w).count();
    }
    else if constexpr (std::is_same_v<Container, std::list<Studentas>>) {
        std::list<Studentas> vargsiukai;
        for (auto it = studentai.begin(); it != studentai.end(); ) {
            if (it->gal_vid < 5.0) {
                vargsiukai.push_back(*it);
                it = studentai.erase(it);
            }
            else ++it;
        }

        auto end_s = high_resolution_clock::now();
        skirstymo_laikas = duration_cast<duration<double>>(end_s - start_s).count();

        auto start_w = high_resolution_clock::now();
        ofstream fout1("vargsiukai_" + konteinerio_pav + ".txt");
        ofstream fout2("kietiakiai_" + konteinerio_pav + ".txt");

        for (auto& s : vargsiukai) fout1 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;
        for (auto& s : studentai) fout2 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;

        fout1.close(); fout2.close();
        auto end_w = high_resolution_clock::now();
        rasymo_laikas = duration_cast<duration<double>>(end_w - start_w).count();
    }
    else {
        skirstytiStrategija2(studentai, konteinerio_pav, skirstymo_laikas, rasymo_laikas);
    }
}

// Template explicit instantiations
template void skirstytiStrategija1<vector<Studentas>>(const vector<Studentas>&, const string&, double&, double&);
template void skirstytiStrategija1<list<Studentas>>(const list<Studentas>&, const string&, double&, double&);

template void skirstytiStrategija2<vector<Studentas>>(vector<Studentas>&, const string&, double&, double&);
template void skirstytiStrategija2<list<Studentas>>(list<Studentas>&, const string&, double&, double&);

template void skirstytiStrategija3<vector<Studentas>>(vector<Studentas>&, const string&, double&, double&);
template void skirstytiStrategija3<list<Studentas>>(list<Studentas>&, const string&, double&, double&);

// Generuoti failą
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

// Įrašyti į README.md
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
