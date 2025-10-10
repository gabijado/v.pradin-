#include "Funkcijos.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    vector<Studentas> studentai;

    int veiksmas;
    cout << "Pasirinkite veiksma:\n";
    cout << "1 - Ivesti studentus ranka\n";
    cout << "2 - Generuoti atsitiktinius duomenis (su ivestais vardais)\n";
    cout << "3 - Nuskaityti duomenis is failo\n";
    cout << "4 - Sugeneruoti studentu sarasu failus (1k, 10k, 100k, 1mln, 10mln)\n";
    cin >> veiksmas;

    if (veiksmas == 1) ivestiStudentus(studentai);
    else if (veiksmas == 2) generuotiStudentus(studentai);
    else if (veiksmas == 3) nuskaitytiIsFailo(studentai);
    else if (veiksmas == 4) generuotiFailus();

    if (veiksmas == 1 || veiksmas == 2 || veiksmas == 3) {
        rodytiRezultatus(studentai);
        issaugotiIRusiuoti(studentai);
    }

    return 0;
}
