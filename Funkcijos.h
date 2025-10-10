#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "Studentas.h"
#include <vector>

void ivestiStudentus(std::vector<Studentas>& studentai);
void generuotiStudentus(std::vector<Studentas>& studentai);
void nuskaitytiIsFailo(std::vector<Studentas>& studentai);
void generuotiFailus();
void rodytiRezultatus(std::vector<Studentas>& studentai);
void issaugotiIRusiuoti(std::vector<Studentas>& studentai);

#endif
