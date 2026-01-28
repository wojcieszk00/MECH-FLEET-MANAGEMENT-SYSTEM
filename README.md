# 🤖 Mech Fleet Management System (2026)

> **System zarządzania ewidencją jednostek bojowych.**

---

## 📋 Opis Projektu
Program to konsolowa aplikacja napisana w języku **C**, służąca do zarządzania bazą danych mechów. Umożliwia pełną obsługę floty, wyszukiwanie, sortowanie oraz trwały zapis danych.

Projekt został zrealizowany z naciskiem na:
* **Alokację dynamiczną pamięci** (brak sztywnych limitów tablic).
* Wykorzystanie **listy jednokierunkowej**.
* **Bezpieczeństwo danych** (walidacja wejścia).
* Czystość i podział kodu na moduły.

## 🚀 Funkcjonalności

| Funkcja | Opis |
| :--- | :--- |
| **List** | Wyświetlanie tabelaryczne całej floty wraz z licznikiem jednostek. |
| **Add** | Dodawanie nowych maszyn z walidacją typów danych i zakresów. |
| **Edit** | Edycja parametrów mecha (Moc, Pilot, Status) przy zachowaniu unikalnego ID. |
| **Delete** | Usuwanie jednostek (tylko o statusie `Repair` lub `Scrapped`). |
| **Search** | Wyszukiwanie po nazwie modelu (prefiksowe) oraz po minimalnej mocy. |
| **Sort** | Sortowanie bąbelkowe: Alfabetyczne (A-Z) lub po Mocy (Malejąco). |
| **Save/Load** | Automatyczny odczyt przy starcie i zapis do pliku `.txt` przy wyjściu. |

## 🛠️ Instalacja i Uruchomienie

Projekt nie wymaga zewnętrznych bibliotek. Wystarczy kompilator GCC.

### 1. Kompilacja
W terminalu wpisz:

```bash
gcc main.c baza.c -o mechy.exe
```
### 2. Uruchomienie
Program wymaga podania nazwy pliku bazy danych jako argumentu:

```bash
.\mechy.exe baza.txt
```
(Jeśli plik nie istnieje, program utworzy go automatycznie przy pierwszym zapisie).

### 📂 Struktura Plików
```text
.
├── main.c       # Główna pętla programu i menu
├── baza.c       # Implementacja logiki biznesowej i obsługi listy
├── baza.h       # Nagłówki funkcji i definicja struktury Mech
├── baza.txt     # Przykładowa baza danych
└── README.md    # Dokumentacja projektu
```
### 💾 Struktura Danych
Program opiera się na strukturze dynamicznej (lista jednokierunkowa):

```C
typedef struct Mech {
    char model[101];        // ID (Unikalne)
    char type[50];          // Klasa (Scout, Assault, etc.)
    int reactor_power;      // Moc (0-100)
    char pilot[101];        // Pseudonim pilota
    char status[50];        // Status operacyjny
    struct Mech *next;      // Wskaźnik na kolejny element
} Mech;
```
Autor: Wojciech Cimochowski


Data: Styczeń 2026
