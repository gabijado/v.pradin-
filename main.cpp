#include "studentas.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {
    srand(time(0));
    vector<Studentas> studentai;

    int veiksmas;
    cout << "Pasirinkite veiksma: " << endl;
    cout << "1 - Ivesti studentus ranka" << endl;
    cout << "2 - Generuoti atsitiktinius duomenis (su ivestais vardais)" << endl;
    cout << "3 - Nuskaityti duomenis is failo" << endl;
    cout << "4 - Sugeneruoti studentu sarasu failus (1k, 10k, 100k, 1mln, 10mln)" << endl;
    cout << "5 - Palyginti vector ir list veikimo greiti" << endl;
    cin >> veiksmas;

    if (veiksmas == 1) {
        int kiek;
        cout << "Kiek studentu norite ivesti? ";
        cin >> kiek;
        for (int k = 0; k < kiek; k++) {
            Studentas s;
            int sum = 0;
            cout << "Vardas: ";
            cin >> s.var;
            cout << "Pavarde: ";
            cin >> s.pav;
            cout << "Iveskite namu darbu rezultatus (baigti su 0):" << endl;
            int paz;
            while (true) {
                cin >> paz;
                if (paz == 0) break;
                s.paz.push_back(paz);
                sum += paz;
            }
            cout << "Egzamino pazymys: ";
            cin >> s.egz;
            if (!s.paz.empty())
                s.gal_vid = (double)sum / s.paz.size() * 0.4 + s.egz * 0.6;
            else
                s.gal_vid = s.egz;
            s.gal_med = mediana(s.paz) * 0.4 + s.egz * 0.6;
            studentai.push_back(s);
        }
        rodytiRezultatus(studentai);
    }
    else if (veiksmas == 2) {
        int kiek;
        cout << "Kiek studentu sugeneruoti? ";
        cin >> kiek;
        for (int i = 0; i < kiek; i++) {
            Studentas s;
            int sum = 0;
            cout << "Studento vardas: ";
            cin >> s.var;
            cout << "Studento pavarde: ";
            cin >> s.pav;
            int kiek_nd = rand() % 8 + 3;
            for (int j = 0; j < kiek_nd; j++) {
                int paz = rand() % 10 + 1;
                s.paz.push_back(paz);
                sum += paz;
            }
            s.egz = rand() % 10 + 1;
            s.gal_vid = (double)sum / s.paz.size() * 0.4 + s.egz * 0.6;
            s.gal_med = mediana(s.paz) * 0.4 + s.egz * 0.6;
            studentai.push_back(s);
        }
        rodytiRezultatus(studentai);
    }
    else if (veiksmas == 3) {
        // 🔹 ČIA nurodai failo pavadinimą
        string failo_pav = "kursiokai.txt";

        auto start = high_resolution_clock::now();
        studentai = skaitytiIsFailo<vector<Studentas>>(failo_pav);
        auto end = high_resolution_clock::now();

        cout << "Duomenu nuskaitymas uztruko: "
            << duration_cast<duration<double>>(end - start).count() << " s\n";

        if (studentai.empty()) {
            cout << "Failas tuscias arba nerastas.\n";
        }
        else {
            rodytiRezultatus(studentai);
        }
    }
    else if (veiksmas == 4) {
        vector<int> dydziai = { 1000, 10000, 100000, 1000000, 10000000 };
        for (int d : dydziai) {
            auto start = high_resolution_clock::now();
            string failo_pav = "studentai" + to_string(d) + ".txt";
            ofstream fout(failo_pav);
            fout << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egz\n";
            for (int i = 1; i <= d; i++) {
                fout << "Vardas" << i << " Pavarde" << i << " ";
                for (int j = 0; j < 5; j++) fout << rand() % 10 + 1 << " ";
                fout << rand() % 10 + 1 << "\n";
            }
            fout.close();
            auto end = high_resolution_clock::now();
            cout << "Failo " << failo_pav
                << " kurimas uztruko: "
                << duration_cast<duration<double>>(end - start).count() << " s\n";
        }
    }
    else if (veiksmas == 5) {
        cout << "Testuojamas konteineriu veikimo greitis (vector vs list)...\n";

        string failo_pav = "kursiokai.txt"; // 🔹 tas pats failas abiem testams

        auto start_v = high_resolution_clock::now();
        auto studentai_v = skaitytiIsFailo<vector<Studentas>>(failo_pav);
        auto end_v = high_resolution_clock::now();
        double laikas_vector = duration_cast<duration<double>>(end_v - start_v).count();

        auto start_l = high_resolution_clock::now();
        auto studentai_l = skaitytiIsFailo<list<Studentas>>(failo_pav);
        auto end_l = high_resolution_clock::now();
        double laikas_list = duration_cast<duration<double>>(end_l - start_l).count();

        cout << fixed << setprecision(4);
        cout << "\n-------------------------------------------\n";
        cout << "| Konteineris | Nuskaitymo laikas (s) |\n";
        cout << "-------------------------------------------\n";
        cout << "| vector      | " << setw(24) << laikas_vector << " |\n";
        cout << "| list        | " << setw(24) << laikas_list << " |\n";
        cout << "-------------------------------------------\n";
    }

    return 0;
}
