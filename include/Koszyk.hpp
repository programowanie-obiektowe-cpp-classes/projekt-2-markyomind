#pragma once

#include "Towar.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Koszyk
{
private:
    vector< pair< Towar, int > > produkty; // Towar i ilosc

public:
    void dodajDoKoszyka(Towar towar, int ilosc) { produkty.push_back(make_pair(towar, ilosc)); }

    double obliczCene() const
    {
        double suma = 0.0;
        for (const auto& para : produkty)
        {
            suma += para.first.getCena() * para.second;
        }
        return suma;
    }

    void wyswietlKoszyk() const
    {
        cout << "\nTwoj koszyk:" << endl;
        for (const auto& para : produkty)
        {
            cout << para.first.getNazwa() << " x" << para.second << " - " << para.first.getCena() * para.second << " zl"
                 << endl;
        }
        cout << "\nRazem: " << obliczCene() << " zl" << endl;
    }

    vector< pair< Towar, int > > getProdukty() const { return produkty; }
};