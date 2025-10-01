#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;
using std::cout;
using std::cin;
using::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::right;

struct Studentas {
    string var;
    string pav;
    vector<int> paz;
    int egz{};
    double gal_vid{};
    double gal_med{};
};

// funkcija medianai apskaičiuoti
double mediana(vector<int> paz) {
    if (paz.empty()) return 0.0;
    sort(paz.begin(), paz.end());
    int n = paz.size();
    if (n % 2 == 0) {
        return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;
    }
    else {
        return paz[n / 2];
    }
}

int main() {
    srand(time(0));

    vector<Studentas> studentai;

    int veiksmas;
    cout << "Pasirinkite veiksma: " << endl;
    cout << "1 - Ivesti studentus ranka" << endl;
    cout << "2 - Generuoti atsitiktinius duomenis (su ivestais vardais)" << endl;
    cout << "3 - Nuskaityti duomenis is failo" << endl;
    cout << "4 - Sugeneruoti studentu sarasu failus (1k, 10k, 100k, 1mln, 10mln)" << endl;
    cin >> veiksmas;

    if (veiksmas == 1) {
        int kiek;
        cout << "Kiek studentu norite ivesti? ";
        cin >> kiek;

        for (int k = 0; k < kiek; k++) {
            Studentas s;
            int sum = 0;

            cout << "Ivesk studento duomenis" << endl;
            cout << "Vardas: ";
            cin >> s.var;
            cout << "Pavarde: ";
            cin >> s.pav;

            cout << "Iveskite namu darbu rezultatus (baigti su 0):" << endl;
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

    else if (veiksmas == 2) {
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

            if (!s.paz.empty()) {
                s.gal_vid = double(sum) / s.paz.size() * 0.4 + s.egz * 0.6;
            }
            else {
                s.gal_vid = s.egz;
            }

            s.gal_med = mediana(s.paz) * 0.4 + s.egz * 0.6;

            studentai.push_back(s);
        }
    }

    else if (veiksmas == 3) {
        ifstream fin("kursiokai.txt");
        if (!fin) {
            cout << "Nepavyko atidaryti failo" << endl;
            return 0;
        }

        string header;
        getline(fin, header);

        while (true) {
            Studentas s;
            int sum = 0;
            fin >> s.var >> s.pav;
            if (fin.eof()) break;

            int pazymys;
            for (int i = 0; i < 5; i++) {
                fin >> pazymys;
                s.paz.push_back(pazymys);
                sum += pazymys;
            }
            fin >> s.egz;

            if (!s.paz.empty())
                s.gal_vid = double(sum) / s.paz.size() * 0.4 + s.egz * 0.6;
            else
                s.gal_vid = s.egz;

            s.gal_med = mediana(s.paz) * 0.4 + s.egz * 0.6;

            studentai.push_back(s);
        }
        fin.close();
    }

    else if (veiksmas == 4) {
        vector<int> dydziai = { 1000, 10000, 100000, 1000000, 10000000 };

        for (int d : dydziai) {
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
            cout << "Sugeneruotas failas: " << failo_pavadinimas << endl;
        }
    }

    // jei pasirinkta 1-3, rodome lenteles + išvedame į failus
    if (veiksmas == 1 || veiksmas == 2 || veiksmas == 3) {
        sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            return a.pav < b.pav;
            });

        int pasirinkimas;
        cout << "Pasirinkite galutinio balo skaiciavimo metoda: " << endl;
        cout << "1 - Vidurkis" << endl;
        cout << "2 - Mediana" << endl;
        cout << "3 - Abu" << endl;
        cin >> pasirinkimas;

        cout << "Studento informacija: " << endl;
        if (pasirinkimas == 1) {
            cout << left << setw(15) << "Vardas" << "|" << setw(20) << "Pavarde" << "|" << setw(18) << "Galutinis (Vid.)" << endl;
            cout << string(55, '-') << endl;
            for (auto& s : studentai) {
                cout << left << setw(15) << s.var << "|" << setw(20) << s.pav << "|" << setw(18) << fixed << setprecision(2) << s.gal_vid << endl;
            }
        }
        else if (pasirinkimas == 2) {
            cout << left << setw(15) << "Vardas" << "|" << setw(20) << "Pavarde" << "|" << setw(18) << "Galutinis (Med.)" << endl;
            cout << string(55, '-') << endl;
            for (auto& s : studentai) {
                cout << left << setw(15) << s.var << "|" << setw(20) << s.pav << "|" << setw(18) << fixed << setprecision(2) << s.gal_med << endl;
            }
        }
        else if (pasirinkimas == 3) {
            cout << left << setw(15) << "Vardas" << "|" << setw(20) << "Pavarde" << "|" << setw(15) << "Galutinis (Vid.)" << "|" << setw(18) << "Galutinis (Med.)" << endl;
            cout << string(80, '-') << endl;
            for (auto& s : studentai) {
                cout << left << setw(15) << s.var << "|" << setw(20) << s.pav << "|" << setw(18) << fixed << setprecision(2) << s.gal_vid << "|" << setw(18) << fixed << setprecision(2) << s.gal_med << endl;
            }
        }

        // Suskirstome studentus į dvi grupes pagal galutinį balą (vidurkį)
        vector<Studentas> vargsiukai;
        vector<Studentas> kietiakiai;

        for (auto& s : studentai) {
            if (s.gal_vid < 5.0) {
                vargsiukai.push_back(s);
            }
            else {
                kietiakiai.push_back(s);
            }
        }

        // Įrašome vargsiukus į failą
        ofstream fout_vargsiukai("vargsiukai.txt");
        fout_vargsiukai << left << setw(15) << "Vardas"
            << setw(20) << "Pavarde"
            << setw(18) << "Galutinis (Vid.)" << endl;
        fout_vargsiukai << string(55, '-') << endl;
        for (auto& s : vargsiukai) {
            fout_vargsiukai << left << setw(15) << s.var
                << setw(20) << s.pav
                << fixed << setprecision(2) << s.gal_vid << endl;
        }
        fout_vargsiukai.close();

        // Įrašome kietiakius į failą
        ofstream fout_kietiakiai("kietiakiai.txt");
        fout_kietiakiai << left << setw(15) << "Vardas"
            << setw(20) << "Pavarde"
            << setw(18) << "Galutinis (Vid.)" << endl;
        fout_kietiakiai << string(55, '-') << endl;
        for (auto& s : kietiakiai) {
            fout_kietiakiai << left << setw(15) << s.var
                << setw(20) << s.pav
                << fixed << setprecision(2) << s.gal_vid << endl;
        }
        fout_kietiakiai.close();

        cout << "\nSugeneruoti failai: vargsiukai.txt ir kietiakiai.txt" << endl;
    }

    return 0;
}



//pagrindine.cpp
#include "funkcijos.h"
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

int main() {
    vector<Studentas> studentai;
    int veiksmas;

    cout << "Pasirinkite veiksma:\n";
    cout << "1 - Ivesti studentus\n2 - Generuoti studentus\n3 - Skaityti is failo\n4 - Sugeneruoti sarasu failus\n";
    cin >> veiksmas;

    if (veiksmas == 1) {
        auto start = high_resolution_clock::now();
        ivestiStudentus(studentai);
        auto end = high_resolution_clock::now();
        cout << "\nStudentu ivedimas uztruko: "
            << duration_cast<milliseconds>(end - start).count() << " ms\n";
    }
    else if (veiksmas == 2) {
        auto start = high_resolution_clock::now();
        generuotiStudentus(studentai);
        auto end = high_resolution_clock::now();
        cout << "\nStudentu generavimas uztruko: "
            << duration_cast<milliseconds>(end - start).count() << " ms\n";
    }
    else if (veiksmas == 3) {
        auto start = high_resolution_clock::now();
        skaitytiIsFailo(studentai, "studentai10000.txt");
        auto end = high_resolution_clock::now();
        cout << "\nDuomenu nuskaitymas uztruko: "
            << duration_cast<milliseconds>(end - start).count() << " ms\n";
    }
    else if (veiksmas == 4) {
        auto start = high_resolution_clock::now();
        sugeneruotiFailus();
        auto end = high_resolution_clock::now();
        cout << "\nFailu generavimas uztruko: "
            << duration_cast<milliseconds>(end - start).count() << " ms\n";
    }

    if (veiksmas >= 1 && veiksmas <= 3) {
        cout << "\nIvestu studentu rezultatai:\n";
        rodytiStudentus(studentai);
        rodytiIrIsvestiFailusSuSparta(studentai);
    }

    return 0;
}


//funkcijos.cpp

#include "funkcijos.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

double mediana(vector<int> paz) {
    if (paz.empty()) return 0.0;
    sort(paz.begin(), paz.end());
    int n = paz.size();
    return (n % 2 == 0) ? (paz[n / 2 - 1] + paz[n / 2]) / 2.0 : paz[n / 2];
}

void ivestiStudentus(vector<Studentas>& studentai) {
    int kiek;
    cout << "Kiek studentu norite ivesti? ";
    cin >> kiek;

    for (int k = 0; k < kiek; k++) {
        Studentas s;
        int sum = 0;

        cout << "Vardas: "; cin >> s.var;
        cout << "Pavarde: "; cin >> s.pav;

        cout << "Namu darbu rezultatai (baigti su 0): ";
        int pazymys;
        while (true) {
            cin >> pazymys;
            if (pazymys == 0) break;
            s.paz.push_back(pazymys);
            sum += pazymys;
        }

        cout << "Egzamino pazymys: "; cin >> s.egz;

        s.gal_vid = (!s.paz.empty()) ? double(sum) / s.paz.size() * 0.4 + s.egz * 0.6 : s.egz;
        s.gal_med = mediana(s.paz) * 0.4 + s.egz * 0.6;

        studentai.push_back(s);
    }
}

void generuotiStudentus(vector<Studentas>& studentai) {
    srand(time(0));
    int kiek;
    cout << "Kiek studentu sugeneruoti? ";
    cin >> kiek;

    for (int k = 0; k < kiek; k++) {
        Studentas s;
        int sum = 0;
        cout << "Vardas: "; cin >> s.var;
        cout << "Pavarde: "; cin >> s.pav;

        int kiek_nd = rand() % 8 + 3;
        for (int i = 0; i < kiek_nd; i++) {
            int pazymys = rand() % 10 + 1;
            s.paz.push_back(pazymys);
            sum += pazymys;
        }

        s.egz = rand() % 10 + 1;
        s.gal_vid = (!s.paz.empty()) ? double(sum) / s.paz.size() * 0.4 + s.egz * 0.6 : s.egz;
        s.gal_med = mediana(s.paz) * 0.4 + s.egz * 0.6;

        studentai.push_back(s);
    }
}

void skaitytiIsFailo(vector<Studentas>& studentai, const string& failo_pavadinimas) {
    ifstream fin(failo_pavadinimas);
    if (!fin) { cout << "Nepavyko atidaryti failo: " << failo_pavadinimas << endl; return; }

    string header; getline(fin, header);

    while (!fin.eof()) {
        Studentas s;
        int sum = 0;
        fin >> s.var >> s.pav;
        if (fin.eof()) break;

        int pazymys;
        for (int i = 0; i < 5; i++) {
            fin >> pazymys;
            s.paz.push_back(pazymys);
            sum += pazymys;
        }
        fin >> s.egz;

        s.gal_vid = (!s.paz.empty()) ? double(sum) / s.paz.size() * 0.4 + s.egz * 0.6 : s.egz;
        s.gal_med = mediana(s.paz) * 0.4 + s.egz * 0.6;

        studentai.push_back(s);
    }
    fin.close();
}

void sugeneruotiFailus() {
    srand(time(0));
    vector<int> dydziai = { 1000,10000,100000,1000000,10000000 };

    for (int d : dydziai) {
        string failo_pavadinimas = "studentai" + to_string(d) + ".txt";
        auto start = high_resolution_clock::now();

        ofstream fout(failo_pavadinimas);
        fout << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egz\n";
        for (int i = 1; i <= d; i++) {
            fout << "Vardas" << i << " Pavarde" << i << " ";
            for (int j = 0; j < 5; j++) fout << (rand() % 10 + 1) << " ";
            fout << (rand() % 10 + 1) << "\n";
        }
        fout.close();

        auto end = high_resolution_clock::now();
        cout << "Sugeneruotas failas: " << failo_pavadinimas
            << " (" << duration_cast<milliseconds>(end - start).count() << " ms)\n";
    }
}

void rodytiStudentus(const vector<Studentas>& studentai) {
    cout << left << setw(15) << "Vardas"
        << setw(20) << "Pavarde"
        << setw(20) << "Namu darbai"
        << setw(15) << "Egz"
        << setw(15) << "Galutinis (Vid.)"
        << setw(15) << "Galutinis (Med.)" << endl;
    cout << string(100, '-') << endl;

    for (auto& s : studentai) {
        cout << left << setw(15) << s.var
            << setw(20) << s.pav;

        for (auto& p : s.paz) cout << p << " ";
        cout << setw(15 - s.paz.size() * 2);

        cout << setw(15) << s.egz
            << setw(15) << fixed << setprecision(2) << s.gal_vid
            << setw(15) << fixed << setprecision(2) << s.gal_med << endl;
    }
}

void rodytiIrIsvestiFailusSuSparta(const vector<Studentas>& studentai) {
    auto start_sort = high_resolution_clock::now();
    vector<Studentas> sorted_studentai = studentai;
    sort(sorted_studentai.begin(), sorted_studentai.end(), [](const Studentas& a, const Studentas& b) {
        return a.pav < b.pav;
        });
    auto end_sort = high_resolution_clock::now();
    cout << "Studentu rusiavimas uztruko: "
        << duration_cast<milliseconds>(end_sort - start_sort).count() << " ms\n";

    auto start_group = high_resolution_clock::now();
    vector<Studentas> vargsiukai, kietiakiai;
    for (auto& s : sorted_studentai)
        (s.gal_vid < 5.0) ? vargsiukai.push_back(s) : kietiakiai.push_back(s);
    auto end_group = high_resolution_clock::now();
    cout << "Studentu grupavimas uztruko: "
        << duration_cast<milliseconds>(end_group - start_group).count() << " ms\n";

    auto start_write = high_resolution_clock::now();
    ofstream fout_v("vargsiukai.txt");
    fout_v << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << setw(18) << "Galutinis (Vid.)\n";
    fout_v << string(55, '-') << endl;
    for (auto& s : vargsiukai)
        fout_v << setw(15) << s.var << setw(20) << s.pav << fixed << setprecision(2) << s.gal_vid << endl;
    fout_v.close();

    ofstream fout_k("kietiakiai.txt");
    fout_k << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << setw(18) << "Galutinis (Vid.)\n";
    fout_k << string(55, '-') << endl;
    for (auto& s : kietiakiai)
        fout_k << setw(15) << s.var << setw(20) << s.pav << fixed << setprecision(2) << s.gal_vid << endl;
    fout_k.close();
    auto end_write = high_resolution_clock::now();
    cout << "Irasymas i failus uztruko: "
        << duration_cast<milliseconds>(end_write - start_write).count() << " ms\n";
}



//funkcijos.h
#pragma once
#include "studentas.h"
#include <vector>
#include <string>

double mediana(std::vector<int> paz);

void ivestiStudentus(std::vector<Studentas>& studentai);
void generuotiStudentus(std::vector<Studentas>& studentai);
void skaitytiIsFailo(std::vector<Studentas>& studentai, const std::string& failo_pavadinimas);
void sugeneruotiFailus();
void rodytiStudentus(const std::vector<Studentas>& studentai);
void rodytiIrIsvestiFailusSuSparta(const std::vector<Studentas>& studentai);


//studentas.h
#pragma once
#include <string>
#include <vector>

struct Studentas {
    std::string var;
    std::string pav;
    std::vector<int> paz;
    int egz{};
    double gal_vid{};
    double gal_med{};
};


