#pragma once

#include <iostream>
#include <string>
using namespace std;

class Towar
{
private:
    string nazwa;
    double cena;
    int    ilosc;

public:
    Towar(string nazwa, double cena, int ilosc) : nazwa(nazwa), cena(cena), ilosc(ilosc) {}

    string getNazwa() const { return nazwa; }
    double getCena() const { return cena; }
    int    getIlosc() const { return ilosc; }

    void zmniejszIlosc(int liczba)
    {
        if (liczba <= ilosc)
        {
            ilosc -= liczba;
        }
    }

    void dodajIlosc(int liczba) { ilosc += liczba; }
};
