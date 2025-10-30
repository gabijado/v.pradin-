#include "funkcijos.h"
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

int main() {
    srand(time(0));
    int veiksmas;
    cout << "Pasirinkite veiksma: " << endl;
    cout << "1 - Ivesti studentus ranka" << endl;
    cout << "2 - Generuoti atsitiktinius duomenis (su ivestais vardais)" << endl;
    cout << "3 - Nuskaityti duomenis is failo" << endl;
    cout << "4 - Sugeneruoti studentu sarasu failus (1k, 10k, 100k, 1mln, 10mln)" << endl;
    cin >> veiksmas;

    if (veiksmas == 1) {
        int n; cout << "Kiek studentu norite ivesti? "; cin >> n;
        vector<Studentas> studentai;
        for (int i = 0; i < n; i++) {
            Studentas s;
            cout << "Vardas: "; cin >> s.var;
            cout << "Pavarde: "; cin >> s.pav;
            int nd; cout << "Kiek namu darbu? "; cin >> nd;
            for (int j = 0; j < nd; j++) {
                int paz; cout << "ND" << j + 1 << ": "; cin >> paz; s.paz.push_back(paz);
            }
            cout << "Egzamino rezultatas: "; cin >> s.egz;
            int sum = 0; for (auto p : s.paz) sum += p;
            s.gal_vid = sum / 5.0 * 0.4 + s.egz * 0.6;
            studentai.push_back(s);
        }
        skirstytiIrRasyti(studentai, "rankiniu");
    }
    else if (veiksmas == 2) {
        int n; cout << "Kiek studentu sugeneruoti? "; cin >> n;
        vector<Studentas> studentai;
        for (int i = 0; i < n; i++) {
            Studentas s; s.var = "Vardas" + to_string(i + 1); s.pav = "Pavarde" + to_string(i + 1);
            for (int j = 0; j < 5; j++) s.paz.push_back(rand() % 10 + 1);
            s.egz = rand() % 10 + 1;
            int sum = 0; for (auto p : s.paz) sum += p;
            s.gal_vid = sum / 5.0 * 0.4 + s.egz * 0.6;
            studentai.push_back(s);
        }
        skirstytiIrRasyti(studentai, "generuoti");
    }
    else if (veiksmas == 3) {
        string failo_pav; cout << "Iveskite failo pavadinima: "; cin >> failo_pav;
        auto studentai = skaitytiIsFailo(failo_pav);
        skirstytiIrRasyti(studentai, "nuskaityti");
    }
    else if (veiksmas == 4) {
        vector<int> dydziai = { 1000,10000,100000,1000000,10000000 };
        for (int k : dydziai) {
            auto start = high_resolution_clock::now();
            generuotiFaila(k);
            auto end = high_resolution_clock::now();
            cout << "Generavimo laikas: " << duration_cast<duration<double>>(end - start).count() << " s\n";
        }
    }
    else cout << "Neteisingas pasirinkimas.\n";

    return 0;
}
