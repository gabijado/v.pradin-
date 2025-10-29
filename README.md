# V0.3 programos testavimo rezultatai

## Testavimo sistema

- Kompiuteris: Dell XPS 13 9380
- CPU: Intel Core i7-8665U (4 branduoliai, 8 gijos, 1.90GHz)
- RAM: 16 GB
- Diskas: SSD
- Operacinė sistema: Windows 11 Pro 64-bit
- Kompiliatorius: g++ (MinGW)

---

## Testavimo failai

Buvo naudojami tie patys duomenų failai, kaip ir v0.2 versijoje:  
`studentai1000.txt`, `studentai10000.txt`, `studentai100000.txt`, `studentai1000000.txt`, `studentai10000000.txt`.

## Išvados

- 'std::vector' veikia greičiau, kai reikia sekti elementus atmintyje ir naudoti atsitiktinę prieigą.  
- 'std::list' lėtesnis dėl žymiai didesnių atminties šuolių.  
- Failų įrašymo laikas nepriklauso nuo konteinerio tipo.  
- Optimizuota versija (v0.3) turi papildomą matavimą: studentų skirstymą ir įrašymą į failus.


## Testo rezultatai (kursiokai.txt)

| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Ra�ymas (s) |
|--------------|----------------:|----------------:|-------------:|
| **vector** | 0.000600 | 0.000031 | 0.001968 |
| **list**   | 0.000589 | 0.000022 | 0.001724 |


## Testo rezultatai (studentai1000.txt)

| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Ra�ymas (s) |
|--------------|----------------:|----------------:|-------------:|
| **vector** | 0.066315 | 0.011824 | 0.024708 |
| **list**   | 0.040474 | 0.002390 | 0.018586 |


## Testo rezultatai (studentai10000.txt)

| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Ra�ymas (s) |
|--------------|----------------:|----------------:|-------------:|
| **vector** | 0.424177 | 0.070519 | 0.148305 |
| **list**   | 0.351350 | 0.022012 | 0.152630 |


## Testo rezultatai (studentai100000.txt)

| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
|--------------|----------------:|----------------:|-------------:|
| **vector** | 4.104167 | 0.856549 | 1.437311 |
| **list**   | 3.621683 | 0.237873 | 1.457648 |


## Testo rezultatai (studentai1000000.txt)

| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
|--------------|----------------:|----------------:|-------------:|
| **vector** | 80.257820 | 13.423128 | 26.278357 |
| **list**   | 28.213363 | 1.655131 | 10.426634 |


## Testo rezultatai (studentai10000000.txt)

| Konteineris | Nuskaitymas (s) | Skirstymas (s) | Rasymas (s) |
|--------------|----------------:|----------------:|-------------:|
| **vector** | 304.348654 | 62.597036 | 99.861151 |
| **list**   | 277.778857 | 26.499658 | 102.786401 |

