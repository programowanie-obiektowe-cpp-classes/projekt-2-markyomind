#pragma once

#include "Klient.hpp"
#include "Koszyk.hpp"
#include "Magazyn.hpp"
#include "Towar.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// obsluga sklepu
class Sklep
{
private:
    Magazyn          magazyn;
    vector< Klient > staliKlienci;

public:
    void przyjmijTowar(string nazwa, double cena, int ilosc) { magazyn.dodajTowar(Towar(nazwa, cena, ilosc)); }

    void rejestrujStalegoKlienta(string nazwa, double portfel) { staliKlienci.push_back(Klient(nazwa, portfel)); }

    void wyswietlTowary() { magazyn.wyswietlTowary(); }

    void sprzedajDetalicznie(Klient& klient)
    {
        Koszyk koszyk;
        string nazwa;
        int    ilosc;

        while (true)
        {
            cout << "\nPodaj nazwe towaru (lub 'koniec', aby zakonczyc): ";
            cin >> nazwa;
            if (nazwa == "koniec")
                break;

            Towar* towar = magazyn.znajdzTowar(nazwa);
            if (towar)
            {
                cout << "Podaj ilosc: ";
                cin >> ilosc;
                if (towar->getIlosc() >= ilosc)
                {
                    koszyk.dodajDoKoszyka(*towar, ilosc);
                }
                else
                {
                    cout << "Brak wystarczajacej ilosci towaru w magazynie." << endl;
                }
            }
            else
            {
                cout << "Nie znaleziono towaru o nazwie: " << nazwa << endl;
            }
        }

        koszyk.wyswietlKoszyk();
        double suma = koszyk.obliczCene();
        if (klient.zaplac(suma))
        {
            cout << "Platnosc zaakceptowana! Dziekujemy za zakupy." << endl;
            for (const auto& para : koszyk.getProdukty())
            {
                magazyn.sprzedajTowar(para.first.getNazwa(), para.second);
            }
        }
        else
        {
            cout << "Brak wystarczajacych srodkow w portfelu!" << endl;
        }
    }

    void sprzedajHurtowo(Klient& klient)
    {
        Koszyk koszyk;
        string nazwa;
        int    ilosc;

        while (true)
        {
            cout << "\nPodaj nazwê towaru (lub 'koniec', aby zakonczyc): ";
            cin >> nazwa;
            if (nazwa == "koniec")
                break;

            Towar* towar = magazyn.znajdzTowar(nazwa);
            if (towar)
            {
                cout << "Podaj ilosc: ";
                cin >> ilosc;
                if (towar->getIlosc() >= ilosc)
                {
                    koszyk.dodajDoKoszyka(*towar, ilosc);
                }
                else
                {
                    cout << "Brak wystarczajacej ilosci towaru w magazynie." << endl;
                }
            }
            else
            {
                cout << "Nie znaleziono towaru o nazwie: " << nazwa << endl;
            }
        }

        koszyk.wyswietlKoszyk();
        double suma   = koszyk.obliczCene();
        double znizka = suma * 0.1; // 10% znizki na sprzedaz hurtowa
        suma -= znizka;
        cout << "Zastosowano znizke hurtowa: -" << znizka << " zl" << endl;
        cout << "Cena po znizce: " << suma << " zl" << endl;

        if (klient.zaplac(suma))
        {
            cout << "Platnosc zaakceptowana! Dziekujemy za zakupy." << endl;
            for (const auto& para : koszyk.getProdukty())
            {
                magazyn.sprzedajTowar(para.first.getNazwa(), para.second);
            }
        }
        else
        {
            cout << "Brak wystarczajacych srodkow w portfelu!" << endl;
        }
    }

    void wyswietlMenu()
    {
        int wybor;
        do
        {
            cout << "\n=== Sklep ===";
            cout << "\n1. Przyjmij towar do magazynu";
            cout << "\n2. Rejestruj stalego klienta";
            cout << "\n3. Wyswietl towary w magazynie";
            cout << "\n4. Sprzedaz detaliczna";
            cout << "\n5. Sprzedaz hurtowa";
            cout << "\n6. Zapisz magazyn do pliku JSON";
            cout << "\n7. Wczytaj magazyn z pliku JSON";
            cout << "\n0. Wyjdz";
            cout << "\nWybierz opcje: ";
            cin >> wybor;

            switch (wybor)
            {
            case 1: {
                string nazwa;
                double cena;
                int    ilosc;
                cout << "Podaj nazwe towaru: ";
                cin >> nazwa;
                cout << "Podaj cene: ";
                cin >> cena;
                cout << "Podaj ilosc: ";
                cin >> ilosc;
                przyjmijTowar(nazwa, cena, ilosc);
                break;
            }
            case 2: {
                string nazwa;
                double portfel;
                cout << "Podaj nazwe klienta: ";
                cin >> nazwa;
                cout << "Podaj srodki w portfelu: ";
                cin >> portfel;
                rejestrujStalegoKlienta(nazwa, portfel);
                break;
            }
            case 3:
                wyswietlTowary();
                break;
            case 4: {
                string nazwaKlienta;
                double portfel;
                cout << "Podaj nazwe klienta: ";
                cin >> nazwaKlienta;
                cout << "Podaj srodki w portfelu: ";
                cin >> portfel;
                Klient klient(nazwaKlienta, portfel);
                sprzedajDetalicznie(klient);
                break;
            }
            case 5: {
                string nazwaKlienta;
                cout << "Podaj nazwe klienta: ";
                cin >> nazwaKlienta;
                Klient* klient = nullptr;
                for (auto& k : staliKlienci)
                {
                    if (k.getNazwa() == nazwaKlienta)
                    {
                        klient = &k;
                        break;
                    }
                }
                if (klient)
                {
                    sprzedajHurtowo(*klient);
                }
                else
                {
                    cout << "Nie znaleziono klienta o nazwie: " << nazwaKlienta << endl;
                }
                break;
            }
            case 6: {
                string nazwaPliku;
                cout << "Podaj nazwe pliku do zapisu : ";
                cin >> nazwaPliku;
                magazyn.zapiszDoJSON(nazwaPliku);
                break;
            }
            case 7: {
                string nazwaPliku;
                cout << "Podaj nazwe pliku do odczytu : ";
                cin >> nazwaPliku;
                magazyn.wczytajZJSON(nazwaPliku);
                break;
            }
            case 0:
                cout << "Do widzenia!" << endl;
                break;
            default:
                cout << "Nieprawidlowa opcja. Sprobuj ponownie." << endl;
            }
        } while (wybor != 0);
    }
};