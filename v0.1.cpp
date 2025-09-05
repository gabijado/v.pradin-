#include <iosstream>
#include <iomanip>
#include <vector>
#include <string>


using namespace std;
using std::cout;
using std::cin;
using::endl;
using std::string;
using std::vektor;
using std::setw;
using std::left;
using std::right;

struct Studentas{
  string var;
  string pav;
  vector <int> paz;
  int egz;
  int gal;
};

int main(){
  int n, laik_paz, sum=0;
  cout << "Sveiki" << endl;
  Studentas Pirmas;
  cout <<"Ivesk studento duomenis"<< endl;
  cout << "Vardas: "; cin>>Pirmas.var;
  cout << "Pavardė: "; cin>>Pirmas.pav;
  cout << "Kiek pažymių turi " << Pirmas.var<< " " << Pirmas.pav<<": "; cin >> n;
  for (int a=0;a<n;a++)
  {
    cout<<a+1<<": "; cin >> laik_paz;
    Pirmas.paz.push_back(laik_paz);
    sum+=laik_paz; //sum+=Pirmas.paz[a];
  }
  cout<<"Iveskite egzamino pažymį: "; cin>>Pirmas.egz;
  Pirmas.gal = double(sum)/double(n)*0.4 + Pirmas.egz*0.6;
  cout<<"Studento info: "<< endl;
  cout << setw(10) << left << Pirmas.var << "|" << setw(15) << right << Pirmas.pav << "|";
  for (auto& a : Pirmas.paz) cout << setw(3)<<a<<"|";
  cout << setw(5) << Pirmas.egz << "|" << setw(10) << Pirmas.gal << endl;
}
