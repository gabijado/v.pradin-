#include "studentas.h"
#include <chrono>
#include <list>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;
using namespace std::chrono;

// Skirstymas ir rašymas į failus su laiko matavimu
template <typename Container>
void skirstytiIrRasyti(const Container& studentai, const string& konteinerio_pav,
    double& skirstymo_laikas, double& rasymo_laikas) {
    auto start_s = high_resolution_clock::now();

    Container vargsiukai, kietiakiai;
    for (auto& s : studentai) {
        if (s.gal_vid < 5.0)
            vargsiukai.push_back(s);
        else
            kietiakiai.push_back(s);
    }

    auto end_s = high_resolution_clock::now();
    skirstymo_laikas = duration_cast<duration<double>>(end_s - start_s).count();

    auto start_w = high_resolution_clock::now();

    string failas_vargs = "vargsiukai_" + konteinerio_pav + ".txt";
    string failas_kiet = "kietiakiai_" + konteinerio_pav + ".txt";

    ofstream fout1(failas_vargs), fout2(failas_kiet);
    fout1 << left << setw(15) << "Vardas" << setw(20)
        << "Pavarde" << setw(18) << "Galutinis (Vid.)" << endl;
    fout2 << left << setw(15) << "Vardas" << setw(20)
        << "Pavarde" << setw(18) << "Galutinis (Vid.)" << endl;

    for (auto& s : vargsiukai)
        fout1 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;
    for (auto& s : kietiakiai)
        fout2 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;

    fout1.close();
    fout2.close();

    auto end_w = high_resolution_clock::now();
    rasymo_laikas = duration_cast<duration<double>>(end_w - start_w).count();
}

// Testinių failų generavimas
void generuotiFaila(int kiekis) {
    string failo_pav = "studentai_" + to_string(kiekis) + ".txt";
    ofstream fout(failo_pav);

    fout << left << setw(15) << "Vardas" << setw(15)
        << "Pavarde";
    for (int i = 1; i <= 5; i++)
        fout << setw(8) << ("ND" + to_string(i));
    fout << setw(8) << "Egz" << endl;

    for (int i = 0; i < kiekis; i++) {
        fout << left << setw(15) << ("Vardas" + to_string(i + 1))
            << setw(15) << ("Pavarde" + to_string(i + 1));
        for (int j = 0; j < 5; j++)
            fout << setw(8) << (rand() % 10 + 1);
        fout << setw(8) << (rand() % 10 + 1) << endl;
    }
    fout.close();
    cout << "Sugeneruotas failas: " << failo_pav << endl;
}

// Rezultatų rašymas į README.md
void irasytiRezultatusReadme(double v_read, double v_split, double v_write,
    double l_read, double l_split, double l_write,
    const string& failo_pav) {
    ofstream fout("readme.md", ios::app);

    fout << "\n## Testo rezultatai (" << failo_pav << ")\n\n";
    fout << "| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |\n";
    fout << "|--------------|----------------:|----------------:|-------------:|\n";
    fout << "| **vector** | " << fixed << setprecision(6) << v_read
        << " | " << v_split << " | " << v_write << " |\n";
    fout << "| **list**   | " << l_read
        << " | " << l_split << " | " << l_write << " |\n";
    fout << "\n";
    fout.close();
    cout << "Rezultatai irasyti i readme.md\n";
}

int main() {
    srand(time(0));
    int veiksmas;
    cout << "Pasirinkite veiksma:\n";
    cout << "1 - Ivesti studentus ranka\n";
    cout << "2 - Generuoti atsitiktinius duomenis\n";
    cout << "3 - Nuskaityti duomenis is failo\n";
    cout << "4 - Sugeneruoti testinius failus (1k,10k,100k,1M,10M)\n";
    cout << "5 - Palyginti vector ir list veikimo greiti\n";
    cin >> veiksmas;
    cin.ignore(); // pašalina newline iš stream

    if (veiksmas == 1) {
        vector<Studentas> studentai;
        int n;
        cout << "Kiek studentu norite ivesti? ";
        cin >> n; cin.ignore();
        for (int i = 0; i < n; i++) {
            Studentas s;
            cout << "Vardas: "; getline(cin, s.var);
            cout << "Pavarde: "; getline(cin, s.pav);
            int nd;
            cout << "Kiek namu darbu? "; cin >> nd; cin.ignore();
            for (int j = 0; j < nd; j++) {
                int paz;
                cout << "ND" << j + 1 << ": "; cin >> paz; cin.ignore();
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
        if (!test) {
            cout << "Nepavyko atidaryti failo: " << failo_pav << endl;
        }
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
        if (!test) {
            cout << "Nepavyko atidaryti failo: " << failo_pav << endl;
        }
        else {
            auto start_v = high_resolution_clock::now();
            auto studentai_v = skaitytiIsFailo<vector<Studentas>>(failo_pav);
            auto end_v = high_resolution_clock::now();
            double v_read = duration_cast<duration<double>>(end_v - start_v).count();

            double v_split, v_write;
            skirstytiIrRasyti(studentai_v, "vector", v_split, v_write);

            auto start_l = high_resolution_clock::now();
            auto studentai_l = skaitytiIsFailo<list<Studentas>>(failo_pav);
            auto end_l = high_resolution_clock::now();
            double l_read = duration_cast<duration<double>>(end_l - start_l).count();

            double l_split, l_write;
            skirstytiIrRasyti(studentai_l, "list", l_split, l_write);

            cout << "\n---------------------------------------------------------------\n";
            cout << "| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |\n";
            cout << "---------------------------------------------------------------\n";
            cout << "| vector      | " << setw(15) << v_read << " | " << setw(14) << v_split << " | " << setw(11) << v_write << " |\n";
            cout << "| list        | " << setw(15) << l_read << " | " << setw(14) << l_split << " | " << setw(11) << l_write << " |\n";
            cout << "---------------------------------------------------------------\n";

            irasytiRezultatusReadme(v_read, v_split, v_write, l_read, l_split, l_write, failo_pav);
        }
    }

    else {
        cout << "Neteisingas pasirinkimas.\n";
    }

    return 0;
}
