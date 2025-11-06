#include "funkcijos.h"
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <numeric> // pridėta dėl vidurkių skaičiavimo
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

            // Saugo 3 kartų laikus
            vector<double> v_read_times, v_split_times, v_write_times;
            vector<double> l_read_times, l_split_times, l_write_times;

            for (int kartas = 1; kartas <= 3; kartas++) {
                cout << "\nTesto kartas: " << kartas << endl;

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

                // Saugo laikus
                v_read_times.push_back(v_read);
                v_split_times.push_back(v_split);
                v_write_times.push_back(v_write);
                l_read_times.push_back(l_read);
                l_split_times.push_back(l_split);
                l_write_times.push_back(l_write);
            }

            // Vidurkių skaičiavimas
            auto avg = [](const vector<double>& v) {
                return accumulate(v.begin(), v.end(), 0.0) / v.size();
                };

            double v_read_avg = avg(v_read_times);
            double v_split_avg = avg(v_split_times);
            double v_write_avg = avg(v_write_times);
            double l_read_avg = avg(l_read_times);
            double l_split_avg = avg(l_split_times);
            double l_write_avg = avg(l_write_times);

            // Išvedimas į ekraną
            cout << "\n---------------------------------------------------------------\n";
            cout << "| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |\n";
            cout << "---------------------------------------------------------------\n";
            cout << "| vector (vid.) | " << setw(13) << v_read_avg << " | " << setw(14) << v_split_avg << " | " << setw(11) << v_write_avg << " |\n";
            cout << "| list (vid.)   | " << setw(13) << l_read_avg << " | " << setw(14) << l_split_avg << " | " << setw(11) << l_write_avg << " |\n";
            cout << "---------------------------------------------------------------\n";

            // Įrašymas į README.md
            irasytiRezultatusReadme(v_read_avg, v_split_avg, v_write_avg, l_read_avg, l_split_avg, l_write_avg, failo_pav);
        }
    }
    else if (veiksmas == 6) {
        cout << "Programa baige darba.\n";
    }
    else
        cout << "Neteisingas pasirinkimas.\n";

    return 0;
}
