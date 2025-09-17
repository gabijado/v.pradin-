#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream> //failų nuskaitymui




using namespace std;
using std::cout;
using std::cin;
using::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::right;

struct Studentas{
  string var;
  string pav;
  vector <int> paz;
  int egz{};
  double gal_vid{};
  double gal_med{};
};

//funkcija medianai apskaiciuoti
double mediana(vector<int>paz){
    sort(paz.begin(),paz.end());
    int n = paz.size();
    if (n == 0) return 0;
    if (n%2==0){
        return (paz[n/2-1]+paz[n/2])/2.0;
    } else{
        return paz[n/2];
    }
}

int main() {
    srand(time(0));
    
    Studentas Pirmas;
    int sum = 0;
    
    cout << "Pasirinkite veiksma: " << endl;
    cout << "1 - Ivesti studentus ranka" << endl;
    cout << "2 - Generuoti atsitiktinius duomenis" << endl;
    cout << "3 - Nuskaityti duomenis is failo" << endl;
    int veiksmas;
    cin >> veiksmas;
    
    if (veiksmas == 1) {
        cout <<"Ivesk studento duomenis"<< endl;
        cout << "Vardas: "; cin>>Pirmas.var;
        cout << "Pavarde: "; cin>>Pirmas.pav;
        
        cout << "Iveskite namu darbu rezultatus (baigti su 0):" << endl;
            int pazymys;
            while (true) {
                cin >> pazymys;
                if (pazymys == 0) break;
                Pirmas.paz.push_back(pazymys);
                sum += pazymys;
            }
            
            cout << "Iveskite egzamino pazymi: ";
            cin >> Pirmas.egz;
            
    } else if (veiksmas == 2) {
            cout << "Iveskite studento duomenis" << endl;
            cout << "Vardas: ";
            cin >> Pirmas.var;
            cout << "Pavarde: ";
            cin >> Pirmas.pav;
            
            int kiek_nd = rand() % 8+3; //tarp 3 ir 10 namu darbu
            cout << "Sugeneruoti namu darbu pazymiai";
            for (int i = 0; i < kiek_nd; i++) {
                int pazymys = rand() % 10 + 1; //pazymis 1-10
                Pirmas.paz.push_back(pazymys);
                sum += pazymys;
                cout << pazymys << " ";
            }
            cout << endl;
            Pirmas.egz = rand() % 10+1; //egzaminas 1-10
            cout << "Sugeneruotas egzamino pazymys: " << Pirmas.egz << endl;
    
    } else if (veiksmas == 3){
        ifstream fin("kursiokai.txt");
        if (!fin) {
            cout << "Nepavyko atidaryti failo" << endl;
            return 0;
        }
        fin >> Pirmas.var >> Pirmas.pav;
        int pazymys;
        for (int i = 0; i < 5; i++) {
            fin >> pazymys;
            Pirmas.paz.push_back(pazymys);
            sum += pazymys;
        }
        fin >> Pirmas.egz;
        fin.close();
    }
            
        
//galutinis pagal vidurki
  if(!Pirmas.paz.empty()){
  Pirmas.gal_vid = double(sum)/Pirmas.paz.size()*0.4 + Pirmas.egz*0.6;
  } else {
      Pirmas.gal_vid = Pirmas.egz; //jei nebuvo pazymiu
  }
//galutinis pagal mediana
double med = mediana(Pirmas.paz);
Pirmas.gal_med = med*0.4+Pirmas.egz*0.6;

//Pasirinkimas, ka rodyti
int pasirinkimas;
cout<<"Pasirinkite galutinio balo skaiciavimo metoda: " << endl;
cout << "1 - Vidurkis" << endl;
cout << "2 - Mediana" << endl;
cout << "3 - Abu" << endl; 
cin >> pasirinkimas;

  cout<<"Studento info: "<< endl;
 if (pasirinkimas == 1){
  cout<<left<<setw(15)<<"Vardas"<<"|"<<setw(20)<<"Pavarde"<<"|"<<setw(18)<<"Galutinis (Vid.)"<<endl; 
  cout << string(50, '-') << endl;
  cout << left << setw(15) << Pirmas.var << "|" << setw(20) << Pirmas.pav << "|"<<setw(18)<<fixed<<setprecision(2)<<Pirmas.gal_vid << endl;
 } else if (pasirinkimas == 2) {
     cout<<left<<setw(15)<<"Vardas"<<"|"<<setw(20)<<"Pavarde"<<"|"<<setw(18)<<"Galutinis (Med.)"<<endl; 
  cout << string(50, '-') << endl;
  cout << left << setw(15) << Pirmas.var << "|" << setw(20) << Pirmas.pav << "|"<<setw(18)<<fixed<<setprecision(2)<<Pirmas.gal_med << endl;
 } else if (pasirinkimas == 3){
     cout<<left<<setw(15)<<"Vardas"<<"|"<<setw(20)<<"Pavarde"<<"|"<<setw(15)<<"Galutinis (Vid.)" << "|" << setw(18) << "Galutinis (Med.)" <<endl; 
  cout << string(70, '-') << endl;
  cout << left << setw(15) << Pirmas.var << "|" << setw(20) << Pirmas.pav << "|"<<setw(18)<<fixed<<setprecision(2)<<Pirmas.gal_vid << "|" << setw(18) << fixed << setprecision(2) << Pirmas.gal_med << endl;
 }
}
