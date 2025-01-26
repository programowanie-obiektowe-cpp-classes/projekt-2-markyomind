#pragma once

#include "Towar.hpp"
#include <fstream>
#include <iostream>
#include <json.hpp> // zewnetrzna biblioteka do zapisu i odczytu w pliku JSON
#include <string>
#include <vector>

using json = nlohmann::json;
using namespace std;

class Magazyn
{
private:
    vector< Towar > towary;

public:
    void dodajTowar(const Towar& towar)
    {
        for (auto& t : towary)
        {
            if (t.getNazwa() == towar.getNazwa())
            {
                t.dodajIlosc(towar.getIlosc());
                return;
            }
        }
        towary.push_back(towar);
    }

    bool sprzedajTowar(string nazwa, int ilosc)
    {
        for (auto& t : towary)
        {
            if (t.getNazwa() == nazwa && t.getIlosc() >= ilosc)
            {
                t.zmniejszIlosc(ilosc);
                return true;
            }
        }
        return false;
    }

    void wyswietlTowary() const
    {
        cout << "\nDostepne towary w magazynie:" << endl;
        for (const auto& t : towary)
        {
            cout << t.getNazwa() << " - " << t.getCena() << " zl (" << t.getIlosc() << " szt.)" << endl;
        }
    }

    // Zapis do pliku JSON
    void zapiszDoJSON(const string& nazwaPliku) const
    {
        json j;
        for (const auto& t : towary)
        {
            j["towary"].push_back({{"nazwa", t.getNazwa()}, {"cena", t.getCena()}, {"ilosc", t.getIlosc()}});
        }

        ofstream plik(nazwaPliku);
        if (plik.is_open())
        {
            plik << j.dump(4); // zapisujemy JSON z wcieciami
            cout << "Magazyn zapisany do pliku: " << nazwaPliku << endl;
        }
        else
        {
            cout << "Nie mozna otworzyc pliku do zapisu!" << endl;
        }
    }

    // Odczyt z pliku JSON
    void wczytajZJSON(const string& nazwaPliku)
    {
        ifstream plik(nazwaPliku);
        if (!plik.is_open())
        {
            cout << "Nie mozna otworzyc pliku do odczytu!" << endl;
            return;
        }

        json j;
        plik >> j;

        towary.clear(); // czyszczenie obecnych danych
        for (const auto& elem : j["towary"])
        {
            towary.push_back(Towar(elem["nazwa"], elem["cena"], elem["ilosc"]));
        }

        cout << "Magazyn wczytany z pliku: " << nazwaPliku << endl;
    }

    Towar* znajdzTowar(string nazwa)
    {
        for (auto& t : towary)
        {
            if (t.getNazwa() == nazwa)
            {
                return &t;
            }
        }
        return nullptr;
    }
};