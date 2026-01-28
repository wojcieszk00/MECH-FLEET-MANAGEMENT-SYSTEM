============================================================
PROJEKT: SYSTEM ZARZĄDZANIA FLOTĄ MECHÓW BOJOWYCH
============================================================
Autor:        Wojciech Cimochowski
Język:        C
Data:         Styczeń 2026
============================================================

1. OPIS PROJEKTU
------------------------------------------------------------
Program służy do ewidencji jednostek bojowych (mechów). Pozwala na pełne 
zarządzanie flotą, przechowywanie danych w strukturach dynamicznych 
oraz trwały zapis stanu floty w pliku tekstowym.

Projekt spełnia wszystkie wymagania funkcjonalne i niefunkcjonalne, w tym:
- Wykorzystanie listy jednokierunkowej.
- Pełna alokacja dynamiczna pamięci (brak tablic statycznych dla obiektów).
- Modularność (podział na main.c, baza.c, baza.h).

2. KOMPILACJA I URUCHOMIENIE
------------------------------------------------------------
Aby skompilować projekt, należy użyć kompilatora GCC.
W terminalu w katalogu projektu wpisz:

  gcc main.c baza.c -o mechy.exe

Aby uruchomić program, należy podać nazwę pliku bazy danych jako argument:

  .\mechy.exe baza.txt

(Jeśli plik baza.txt nie istnieje, program poinformuje o tym i utworzy go 
automatycznie przy zapisie danych).

3. ZAIMPLEMENTOWANE FUNKCJE
------------------------------------------------------------
[1] Wyświetlanie listy
    - Prezentuje tabelaryczne zestawienie wszystkich mechów.

[2] Dodawanie mecha
    - Walidacja niepustych pól tekstowych.

[3] Edycja mecha
    - Wyszukiwanie po unikalnym ID (Model).
    - Możliwość zmiany typu, mocy, pilota i statusu (ID pozostaje stałe).

[4] Usuwanie mecha
    - Zabezpieczenie logiczne: Zgodnie z wymaganiami, można usunąć TYLKO 
      jednostki o statusie "Repair" lub "Scrapped".
    - Próba usunięcia aktywnej jednostki (np. "Operational") zostanie zablokowana.

[5] Wyszukiwanie
    - Tekstowe: Po nazwie modelu (dopasowanie prefiksowe, np. "Atl" znajdzie "Atlas").
    - Liczbowe: Po minimalnej mocy reaktora (znajduje mechy silniejsze lub równe X).

[6] Sortowanie
    - Algorytm: Bubble Sort (na liście jednokierunkowej).
    - Opcja 1: Alfabetycznie po Modelu (A-Z).
    - Opcja 2: Po Mocy Reaktora (Malejąco - od najsilniejszego).

[7] Zapis i Odczyt
    - Automatyczny odczyt z pliku przy starcie.
    - Zapis do pliku przy bezpiecznym wyjściu z programu.

4. STRUKTURA PLIKÓW
------------------------------------------------------------
- main.c    : Główna pętla programu, obsługa menu i argumentów wywołania.
- baza.c    : Implementacja funkcji logicznych, obsługi listy i plików.
- baza.h    : Definicja struktury Mech i prototypy funkcji.
- baza.txt  : Przykładowy plik z bazą danych.