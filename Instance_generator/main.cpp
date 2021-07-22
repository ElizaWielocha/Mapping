// AKwB_4.cpp : Ten plik zawiera funkcjê „main”. W nim rozpoczyna siê i koñczy wykonywanie programu.
//

//#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <time.h>
#include <sstream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

vector <int> RestrictionMap;
vector <int> Sums;

int main()
{
    string name;

    cout << "Podaj nazwe pliku do zapisu: ";
    cin >> name;
    string plik = name +".txt";
    int cleavage;
    cout << "Podaj liczbe ciec" << endl;
    cin >> cleavage;

    for(int i = 0; i < (cleavage + 1); i++){
        RestrictionMap.push_back(0);
    }

    cout << "Wprowadz wielkosc fragmentow, ich ilosc powinna wynosic: " << RestrictionMap.size() << endl;
    for(int i = 0; i < RestrictionMap.size(); i++){
        cin >> RestrictionMap[i];

    }

    cout << "Wyswietl mape restrykcyjna" << endl;
    for(int i = 0; i < RestrictionMap.size(); i++){
        cout << RestrictionMap[i] << " ";
    }
    cout << endl;

    for(int i = 0; i < cleavage+1; i++){
        int sum = 0;
        for(int j = i; j < cleavage+1; j++){
            sum += RestrictionMap[j];
            //cout << "Suma to: " << sum << endl;
            Sums.push_back(sum);
            //file << sum << " ";
        }
    }

    sort(Sums.begin(), Sums.end());

    cout << "Sumy to: " << endl;
    for(int i = 0; i < Sums.size(); i++){
        cout << Sums[i] << " ";
    }

    ofstream file;
    file.open(plik, ios::out);
    for(int i = 0; i < Sums.size(); i++){
        file << Sums[i] << " ";
    }
    file.close();
	return 0;
}
