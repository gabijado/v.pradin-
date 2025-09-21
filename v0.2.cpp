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

    // jei pasirinkta 1-3, rodome lenteles
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
    }

    return 0;
}
