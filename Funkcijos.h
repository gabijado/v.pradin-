#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "studentas.h"
#include <vector>
#include <string>

void generuotiFaila(int kiekis);
std::vector<Studentas> skaitytiIsFailo(const std::string& failo_pav);
void skirstytiIrRasyti(const std::vector<Studentas>& studentai, const std::string& failo_pavadinimas);

#endif
