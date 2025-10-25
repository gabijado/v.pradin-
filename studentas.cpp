#include "studentas.h"

// Funkcija medianai apskaičiuoti
double mediana(vector<int> paz) {
    if (paz.empty()) return 0.0;
    sort(paz.begin(), paz.end());
    int n = paz.size();
    if (n % 2 == 0) return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;
    else return paz[n / 2];
}

// Funkcija duomenims skaityti iš failo (šablonas)
template <typename Container>
Container skaitytiIsFailo(const string& failo_pav) {
    Container studentai;
    ifstream fin(failo_pav);
    if (!fin) {
        cout << "Nepavyko atidaryti failo: " << failo_pav << endl;
        return studentai;
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
    return studentai;
}

// Funkcija rezultatų rodymui ir failų generavimui
void rodytiRezultatus(vector<Studentas>& studentai) {
    sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
        return a.pav < b.pav;
        });

    int pasirinkimas;
    cout << "Pasirinkite galutinio balo skaiciavimo metoda: " << endl;
    cout << "1 - Vidurkis" << endl;
    cout << "2 - Mediana" << endl;
    cout << "3 - Abu" << endl;
    cin >> pasirinkimas;

    cout << fixed << setprecision(2);

    if (pasirinkimas == 1) {
        cout << left << setw(15) << "Vardas" << "|" << setw(20) << "Pavarde" << "|"
            << setw(18) << "Galutinis (Vid.)" << endl;
        cout << string(55, '-') << endl;
        for (auto& s : studentai)
            cout << left << setw(15) << s.var << "|" << setw(20) << s.pav << "|"
            << setw(18) << s.gal_vid << endl;
    }
    else if (pasirinkimas == 2) {
        cout << left << setw(15) << "Vardas" << "|" << setw(20) << "Pavarde" << "|"
            << setw(18) << "Galutinis (Med.)" << endl;
        cout << string(55, '-') << endl;
        for (auto& s : studentai)
            cout << left << setw(15) << s.var << "|" << setw(20) << s.pav << "|"
            << setw(18) << s.gal_med << endl;
    }
    else {
        cout << left << setw(15) << "Vardas" << "|" << setw(20) << "Pavarde" << "|"
            << setw(18) << "Galutinis (Vid.)" << "|" << setw(18) << "Galutinis (Med.)" << endl;
        cout << string(80, '-') << endl;
        for (auto& s : studentai)
            cout << left << setw(15) << s.var << "|" << setw(20) << s.pav << "|"
            << setw(18) << s.gal_vid << "|" << setw(18) << s.gal_med << endl;
    }

    // Skirstymas į grupes
    vector<Studentas> vargsiukai, kietiakiai;
    for (auto& s : studentai) {
        if (s.gal_vid < 5.0)
            vargsiukai.push_back(s);
        else
            kietiakiai.push_back(s);
    }

    ofstream fout1("vargsiukai.txt"), fout2("kietiakiai.txt");
    fout1 << left << setw(15) << "Vardas" << setw(20) << "Pavarde"
        << setw(18) << "Galutinis (Vid.)" << endl;
    fout2 << left << setw(15) << "Vardas" << setw(20) << "Pavarde"
        << setw(18) << "Galutinis (Vid.)" << endl;

    for (auto& s : vargsiukai)
        fout1 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;
    for (auto& s : kietiakiai)
        fout2 << left << setw(15) << s.var << setw(20) << s.pav << s.gal_vid << endl;

    cout << "\nSugeneruoti failai: vargsiukai.txt ir kietiakiai.txt\n";
}

// Kadangi template funkcijos turi būti matomos kompiliacijos metu:
template vector<Studentas> skaitytiIsFailo<vector<Studentas>>(const string&);
template list<Studentas> skaitytiIsFailo<list<Studentas>>(const string&);
