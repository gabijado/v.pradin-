#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "studentas.h"
#include <vector>
#include <list>
#include <string>

using namespace std;

// Mediana
double mediana(vector<int> paz);

// Skaityti is failo (template deklaracija)
template <typename Container>
Container skaitytiIsFailo(const string& failo_pav);

// Rodyti rezultatus
void rodytiRezultatus(vector<Studentas>& studentai);

// Skirstyti ir rasyti i failus (sena funkcija palikta)
template <typename Container>
void skirstytiIrRasyti(const Container& studentai, const string& konteinerio_pav,
    double& skirstymo_laikas, double& rasymo_laikas);

// Naujos strategijos (v0.3)
template <typename Container>
void skirstytiStrategija1(const Container& studentai, const string& konteinerio_pav,
    double& skirstymo_laikas, double& rasymo_laikas);
// Strategija2: su vienu nauju konteineriu (perkelti vargsiukus ir istrinti is pradinio)
template <typename Container>
void skirstytiStrategija2(Container& studentai, const string& konteinerio_pav,
    double& skirstymo_laikas, double& rasymo_laikas);
// Strategija3: optimizuota (partition / splice)
template <typename Container>
void skirstytiStrategija3(Container& studentai, const string& konteinerio_pav,
    double& skirstymo_laikas, double& rasymo_laikas);

// Generuoti testini faila
void generuotiFaila(int kiekis);

// Irasyti rezultatus i readme
void irasytiRezultatusReadme(double v_read, double v_split, double v_write,
    double l_read, double l_split, double l_write,
    const string& failo_pav);

#endif
