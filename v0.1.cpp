#include <iostream>
#include <iomanip>
#include <vector>
#include <string>


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
  int egz;
  double gal;
};

int main(){
  int n, laik_paz, sum=0;
  Studentas Pirmas;
  cout <<"Ivesk studento duomenis"<< endl;
  cout << "Vardas: "; cin>>Pirmas.var;
  cout << "Pavarde: "; cin>>Pirmas.pav;
  cout << "Kiek pažymiu turi " << Pirmas.var<< " " << Pirmas.pav<<": "; cin >> n;
  for (int a=0;a<n;a++)
  {
    cout<<a+1<<": "; cin >> laik_paz;
    Pirmas.paz.push_back(laik_paz);
    sum+=laik_paz; //sum+=Pirmas.paz[a];
  }
  cout<<"Iveskite egzamino pažymi: "; cin>>Pirmas.egz;
  Pirmas.gal = double(sum)/double(n)*0.4 + Pirmas.egz*0.6;
  cout<<"Studento info: "<< endl;
  cout<<left<<setw(15)<<"Vardas"<<"|"<<setw(20)<<"Pavarde"<<"|"<<setw(15)<<"Galutinis"<<endl; 
  cout << string(50, '-') << endl;
  cout << left << setw(15) << Pirmas.var << "|" << setw(20) << Pirmas.pav << "|"<<setw(15)<<fixed<<setprecision(2)<<Pirmas.gal << endl;
}
