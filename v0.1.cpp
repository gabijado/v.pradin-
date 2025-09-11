#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>


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
    if (n%2==0){
        return (paz[n/2-1]+paz[n/2])/2.0;
    } else{
        return paz[n/2];
    }
}

int main(){
  Studentas Pirmas;
  cout <<"Ivesk studento duomenis"<< endl;
  cout << "Vardas: "; cin>>Pirmas.var;
  cout << "Pavarde: "; cin>>Pirmas.pav;
  cin.ignore(numeric_limits<streamsize>::max(), '\n'); //isvalau buferi
  
  cout <<"Iveskite namu darbu rezultatus (ENTER tuscia eilute - pabaiga ";
  string eilute;
  int sum = 0;
  while(true){
      getline(cin, eilute);
      if (eilute==" " ) break; //baigiam, jei nieko neirasyta
      int laik_paz = stoi(eilute); //konvertuoja teksta i skaiciu
      Pirmas.paz.push_back(laik_paz);
      sum+= laik_paz;
  }
  cout << "Kiek pazymiu turi " << Pirmas.var<< " " << Pirmas.pav<<": "; cin >> n;
 
  for (int a=0;a<n;a++)
  {
    cout<<a+1<<": "; cin >> laik_paz;
    Pirmas.paz.push_back(laik_paz);
    sum+=laik_paz; //sum+=Pirmas.paz[a];
  }
  cout<<"Iveskite egzamino pazymi: "; cin>>Pirmas.egz;
  
//galutinis pagal vidurki
  Pirmas.gal_vid = double(sum)/double(n)*0.4 + Pirmas.egz*0.6;
//galutinis pagal mediana
double med = mediana(Pirmas.paz);
Pirmas.gal_med = med*0.4+Pirmas.egz*0.6;

//Pasirinkimas, ka rodyti
int pasirinkimas;
cout<<"Pasirinkite galutinio balo skaiciavimo metoda: " << endl;
cout << "1 - Vidurkis" << endl;
cout << "2 - Mediana" << endl;
cout << "3 - Abu" << endl; cin >> pasirinkimas;

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
