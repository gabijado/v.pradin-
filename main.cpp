#include "funkcijos.h"
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {
    srand(time(0));
    int veiksmas;
    cout << "Pasirinkite veiksma:\n";
    cout << "1 - Ivesti studentus ranka\n";
    cout << "2 - Generuoti atsitiktinius duomenis\n";
    cout << "3 - Nuskaityti duomenis is failo\n";
    cout << "4 - Sugeneruoti testinius failus (1k,10k,100k,1M,10M)\n";
    cout << "5 - Palyginti vector ir list veikimo greiti (su strategijos pasirinkimu)\n";
    cout << "6 - Iseiti\n";
    cin >> veiksmas;
    cin.ignore();

    if (veiksmas == 1) {
        vector<Studentas> studentai;
        int n;
        cout << "Kiek studentu norite ivesti? "; cin >> n; cin.ignore();
        for (int i = 0; i < n; i++) {
            Studentas s;
            cout << "Vardas: "; getline(cin, s.var);
            cout << "Pavarde: "; getline(cin, s.pav);
            int nd; cout << "Kiek namu darbu? "; cin >> nd; cin.ignore();
            for (int j = 0; j < nd; j++) {
                int paz; cout << "ND" << j + 1 << ": "; cin >> paz; cin.ignore();
                s.paz.push_back(paz);
            }
            cout << "Egzamino rezultatas: "; cin >> s.egz; cin.ignore();
            int sum = 0; for (int p : s.paz) sum += p;
            s.gal_vid = double(sum) / s.paz.size() * 0.4 + s.egz * 0.6;
            s.gal_med = mediana(s.paz) * 0.4 + s.egz * 0.6;
            studentai.push_back(s);
        }
        rodytiRezultatus(studentai);
    }
    else if (veiksmas == 2) {
        vector<Studentas> studentai;
        int n; cout << "Kiek studentu sugeneruoti? "; cin >> n; cin.ignore();
        for (int i = 0; i < n; i++) {
            Studentas s; s.var = "Vardas" + to_string(i + 1); s.pav = "Pavarde" + to_string(i + 1);
            for (int j = 0; j < 5; j++) s.paz.push_back(rand() % 10 + 1);
            s.egz = rand() % 10 + 1;
            int sum = 0; for (int p : s.paz) sum += p;
            s.gal_vid = double(sum) / s.paz.size() * 0.4 + s.egz * 0.6;
            s.gal_med = mediana(s.paz) * 0.4 + s.egz * 0.6;
            studentai.push_back(s);
        }
        rodytiRezultatus(studentai);
    }
    else if (veiksmas == 3) {
        string failo_pav;
        cout << "Iveskite failo pavadinima: "; getline(cin, failo_pav);
        ifstream test(failo_pav);
        if (!test) cout << "Nepavyko atidaryti failo: " << failo_pav << endl;
        else {
            auto studentai = skaitytiIsFailo<vector<Studentas>>(failo_pav);
            rodytiRezultatus(studentai);
        }
    }
    else if (veiksmas == 4) {
        vector<int> dydziai = { 1000,10000,100000,1000000,10000000 };
        for (int k : dydziai) generuotiFaila(k);
    }
    else if (veiksmas == 5) {
        string failo_pav;
        cout << "Iveskite testinio failo pavadinima: "; getline(cin, failo_pav);
        ifstream test(failo_pav);
        if (!test) cout << "Nepavyko atidaryti failo: " << failo_pav << endl;
        else {
            int strategija;
            cout << "Pasirinkite strategija:\n";
            cout << "1 - Du nauji konteineriai (kopijuoja i 2 naujus, paliekant originala)\n";
            cout << "2 - Vienas naujas konteineris (perkelia vargsiukus ir istrina is originalo)\n";
            cout << "3 - Optimizuota (partition / splice)\n";
            cin >> strategija;
            cin.ignore();

            // Vector skaitymas ir skirstymas
            auto start_v = high_resolution_clock::now();
            auto studentai_v = skaitytiIsFailo<vector<Studentas>>(failo_pav);
            auto end_v = high_resolution_clock::now();
            double v_read = duration_cast<duration<double>>(end_v - start_v).count();

            double v_split = 0.0, v_write = 0.0;
            if (strategija == 1)
                skirstytiStrategija1<vector<Studentas>>(studentai_v, "vector", v_split, v_write);
            else if (strategija == 2)
                skirstytiStrategija2<vector<Studentas>>(studentai_v, "vector", v_split, v_write);
            else
                skirstytiStrategija3<vector<Studentas>>(studentai_v, "vector", v_split, v_write);

            // List skaitymas ir skirstymas
            auto start_l = high_resolution_clock::now();
            auto studentai_l = skaitytiIsFailo<list<Studentas>>(failo_pav);
            auto end_l = high_resolution_clock::now();
            double l_read = duration_cast<duration<double>>(end_l - start_l).count();

            double l_split = 0.0, l_write = 0.0;
            if (strategija == 1)
                skirstytiStrategija1<list<Studentas>>(studentai_l, "list", l_split, l_write);
            else if (strategija == 2)
                skirstytiStrategija2<list<Studentas>>(studentai_l, "list", l_split, l_write);
            else
                skirstytiStrategija3<list<Studentas>>(studentai_l, "list", l_split, l_write);

            // Ekrano išvedimas
            cout << "\n---------------------------------------------------------------\n";
            cout << "| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |\n";
            cout << "---------------------------------------------------------------\n";
            cout << "| vector      | " << setw(15) << v_read << " | " << setw(14) << v_split << " | " << setw(11) << v_write << " |\n";
            cout << "| list        | " << setw(15) << l_read << " | " << setw(14) << l_split << " | " << setw(11) << l_write << " |\n";
            cout << "---------------------------------------------------------------\n";

            // Automatinis įrašymas į README.md
            irasytiRezultatusReadme(v_read, v_split, v_write, l_read, l_split, l_write, failo_pav);
        }
    }
    else if (veiksmas == 6) {
        cout << "Programa baige darba.\n";
    }
    else
        cout << "Neteisingas pasirinkimas.\n";

    return 0;
}
