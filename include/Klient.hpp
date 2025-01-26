#pragma once

#include <iostream>
#include <string>
using namespace std;

class Klient
{
private:
    string nazwa;
    double portfel;

public:
    Klient(string nazwa, double portfel) : nazwa(nazwa), portfel(portfel) {}

    string getNazwa() const { return nazwa; }
    double getPortfel() const { return portfel; }

    bool zaplac(double kwota)
    {
        if (kwota <= portfel)
        {
            portfel -= kwota;
            return true;
        }
        return false;
    }

    void dodajSrodki(double kwota) { portfel += kwota; }
};