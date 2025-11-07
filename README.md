# Studentų rezultatų analizė

Ši C++ programa analizuoja studentų rezultatus, apskaičiuoja jų galutinius įvertinimus ir efektyviai paskirsto studentus į grupes pagal pažymius.
Įgyvendintos trys strategijos su vector ir list konteineriais, siekiant įvertinti jų našumą bei atminties naudojimą.
Programa skaito studentų duomenis, apskaičiuoja galutinius įvertinimus ir skirsto juos į dvi grupes:
- **Vargšiukai** (galutinis < 5)
- **Kietiakai** (galutinis ≥ 5)

## Projekto struktūra

- main.cpp — pagrindinis programos failas
- funkcijos.cpp / funkcijos.h — pagalbinės funkcijos (skaitymas, skirstymas, rašymas)
- studentas.cpp / studentas.h — struktūra ir metodai, susiję su studentu
- CMakeLists.txt — CMake konfigūracija
- README.md — dokumentacija


## Naudojimosi instrukcija

1. Paleiskite programą.
2. Pasirinkite vieną iš veiksmų meniu:
   - '1' – įvesti studentus ranka
   - '2' – sugeneruoti atsitiktinius duomenis
   - '3' – nuskaityti studentus iš failo
   - '4' – sugeneruoti testinius failus (1k, 10k, 100k, 1M, 10M)
   - '5' – palyginti 'vector' ir 'list' veikimo greitį pagal pasirinktas strategijas
3. Įveskite strategijos numerį:
   - '1' – du nauji konteineriai (neefektyvu atminties atžvilgiu)
   - '2' – vienas naujas konteineris (vidutiniškai efektyvu)
   - '3' – optimizuota versija (efektyviausia)
4. Programa išveda veikimo laikus į ekraną ir įrašo rezultatus į 'README.md'.


## Strategijų palyginimas 
- Veikia tiek su 'vector', tiek su 'list'.
- Matuoja laikus:
  - Nuskaitymas
  - Skirstymas
  - Rašymas
- Skaičiuoja vidurkius iš 3 bandymų.
- Generuoja testo failus automatiškai.

## 1 strategija. Kuriami du nauji konteineriai.

## studentai1000.txt

---------------------------------------------------------------
| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
---------------------------------------------------------------
| vector      |        0.000767 |       3.28e-05 |    0.001797 |
| list        |       0.0005035 |       1.45e-05 |   0.0013604 |
---------------------------------------------------------------

## studentai10000.txt
---------------------------------------------------------------
| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
---------------------------------------------------------------
| vector      |        0.480753 |      0.0684609 |    0.150706 |
| list        |        0.349113 |      0.0219625 |    0.184013 |
---------------------------------------------------------------


## studentai100000.txt
---------------------------------------------------------------
| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
---------------------------------------------------------------
| vector      |         4.10747 |       0.842942 |     1.40576 |
| list        |         3.67644 |       0.235018 |     1.40043 |
---------------------------------------------------------------

## studentai1000000.txt
---------------------------------------------------------------
| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
---------------------------------------------------------------
| vector      |         39.3368 |        7.86444 |      14.249 |
| list        |         36.5057 |        2.36722 |     14.1373 |
---------------------------------------------------------------

## studentai10000000.txt
---------------------------------------------------------------
| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
---------------------------------------------------------------
| vector      |          580.72 |        152.523 |     290.112 |
| list        |         623.104 |        30.0315 |     179.145 |
---------------------------------------------------------------

## 2 strategija. Trinama iš pradinio konteinerio.

## studentai1000.txt
---------------------------------------------------------------
| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
---------------------------------------------------------------
| vector      |          0.0614 |      0.0061398 |   0.0450945 |
| list        |       0.0817828 |      0.0008234 |    0.110077 |
---------------------------------------------------------------

## studentai10000.txt
---------------------------------------------------------------
| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
---------------------------------------------------------------
| vector      |         0.62878 |      0.0391703 |    0.164434 |
| list        |        0.393671 |      0.0065584 |    0.193968 |
---------------------------------------------------------------

## studentai100000.txt
---------------------------------------------------------------
| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
---------------------------------------------------------------
| vector      |         4.07228 |       0.452439 |     1.43288 |
| list        |         4.10583 |      0.0616153 |     1.54448 |
---------------------------------------------------------------

## studentai1000000.txt
---------------------------------------------------------------
| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
---------------------------------------------------------------
| vector      |         38.8656 |           4.64 |     13.9249 |
| list        |         50.1516 |          1.016 |      29.804 |
---------------------------------------------------------------

## studentai10000000.txt
---------------------------------------------------------------
| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
---------------------------------------------------------------
| vector      |         571.591 |        73.5051 |     237.212 |
| list        |         514.756 |        8.34059 |     278.346 |
---------------------------------------------------------------

## 3 strategija. Optimizuota.

## studentai1000.txt
---------------------------------------------------------------
| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
---------------------------------------------------------------
| vector      |       0.0607299 |      0.0034258 |   0.0965929 |
| list        |       0.0452313 |      0.0019996 |    0.134116 |
---------------------------------------------------------------

## studentai10000.txt
---------------------------------------------------------------
| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
---------------------------------------------------------------
| vector      |        0.435943 |       0.029476 |    0.148646 |
| list        |        0.350219 |      0.0180486 |    0.141476 |
---------------------------------------------------------------

## studentai100000.txt
---------------------------------------------------------------
| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
---------------------------------------------------------------
| vector      |          4.1077 |       0.287161 |     1.38737 |
| list        |         3.58622 |       0.187353 |      1.4049 |
---------------------------------------------------------------

## studentai1000000.txt
---------------------------------------------------------------
| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
---------------------------------------------------------------
| vector      |         39.5125 |        2.97821 |     13.8951 |
| list        |         36.2945 |        1.92007 |     15.3339 |
---------------------------------------------------------------

## studentai10000000.txt
---------------------------------------------------------------
| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
---------------------------------------------------------------
| vector      |         607.863 |        48.2067 |     289.235 |
| list        |         730.284 |        36.8855 |     290.272 |
---------------------------------------------------------------

- **Strategija 1** naudoja daugiau atminties, nes sukuria 2 papildomus konteinerius.
- **Strategija 2** sunaudoja mažiau atminties, bet 'vector' konteineriui trynimai yra lėti.
- **Strategija 3** pasižymi geriausiu laiko ir atminties balansu.

## Išvados

1. list konteineris veikia greičiau skirstant duomenis, bet lėčiau rašant į failą.
2. vector pasižymi geresniu bendru laiko–atminties balansu.
3. 3 strategija (su partition) yra efektyviausia tiek laiko, tiek atminties požiūriu.

## CMake įdiegimas Windows naudojant .msi paketą
1. Atsisiuntimas
   1. Reikia įeiti į oficialų CMake puslapį: https://cmake.org/download/
   2. Pasirinkti Windows x64 Installer (.msi) versiją.
2. Diegimas
   1. Paleisti atsisiųstą .msi failą.
   2. Spausti Next visuose languose.
   3. Svarbu: pasirinkti "Add CMake to the system PATH for all users" arba "for current user".
3. Baigimas
   1. Spauskite Finish, kai diegimas baigtas.
   2. Atidarykite naują PowerShell langą.
   3. Patikrinkite diegimą įvedę: cmake --version

## CMakeLists.txt failas
CMakeLists.txt failas turėtų atrodyti taip:

cmake_minimum_required(VERSION 3.25)

project(Studentu_programa)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(Studentu_programa ${SOURCES})

## Į PowerShell reikia rašyti taip:
cmake CMakeLists.txt
cmake --install .
cmake -- build .
copy src\studentai_*.txt Debug\Studentu_programa
cd Debug\
Studentu_programa.exe
pause
