#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <conio.h>
#include <sstream>
#include <math.h>
using namespace std;

clock_t start, stop;
double czas;
vector<int> A;             // multizbior A
int liczba_fragmentow;     // liczba elementow mapy
int maxind;                // liczba ciec
int pierwszy_elem;         // wartosc pierwszego elementu mapy

void wyswietl_A(vector<int>&A)     // wyswietlanie vectora A zawierajacego multizbior A
{
    cout << "Multizbior A: ";
    for(int i = 0; i < A.size(); i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;
}

void wyswietl_M(int *M)  // wyswietlanie mapy
{
    cout << "Mapa M: ";
    for(int j = 0; j < liczba_fragmentow; j++)
    {
        cout << M[j] << " ";
    }
    cout << endl;
}

void wczytaj(string instancja, vector<int>&A)   // wczytywanie multizbioru A
{
    fstream file;
    string f = instancja + ".txt";             // nazwa pliku

    file.open(f,ios::in);
    if(file.good() == false)
    {
       cout << "Brak pliku do odczytu." << endl;
    }

    int i = 0;                // zmienna do wczytywania elementow

    if (file.good()== true)
	{
		while (!file.eof())
		{
			file >> i;              // wczytuj po jednym elemencie
			A.push_back(i);         // dodawaj do vectora A
		}
	}
    cout << "Wczytano plik" << endl;

    sort(A.begin(), A.end());      // sortowanie multizbioru przy okazji
}

bool liczba_elementow(vector<int>&A)        // sprawdzenie czy liczba ciec zgadza sie z liczba elementow
{
    cout << "Czy wprowadzono prawidlowe dane?" << endl;
    int k;
    for(k = 0; k < A.size(); k++)
    {
        if( ((k*(k-1))/2) == A.size())
        {
            cout << "TAK :)" << endl;
            liczba_fragmentow = k-1;
            maxind = liczba_fragmentow - 1;
            return true;
        }

    }
    cout << "NIE :(" << endl;
    return false;

}


void pierwszy_element()         // znalezienie pierwszego elementu mapy
{
    int max1 = A[0];
    for(int i = 0; i < A.size(); i++)
    {
        if(A[i]>max1)
        {
            max1 = A[i];
        }
    }

    int max2 = A[0];                      // drugi najwiekszy element

	if (max2 == max1)                        // jesli max1 i max2 bylyby na 0-wym miejscu A to
	{
		max2 = A[1];                         // ustawiam max2 na nastepny element
		for (int j = 2; j < A.size(); j++)
		{
			if (A[j] > max2)
				max2 = A[j];
		}
	}
	else                                      // jesli max1 i max2 to nie to samo miejsce to
	{
		for (int j = 1; j < A.size(); j++)    // przechodze po elementach A od elementu o indeksie 1
		{
			if (A[j] != max1)
				if (A[j] > max2)
					max2 = A[j];
		}

	}

    pierwszy_elem = max1 - max2;  // pierwszym elementem map y= roznica miedzy dwoma najwiekszymi elementami A

}


void szukaj(int *M, int ind, int *jest)   // funkcja szukajaca rekurencyjnie reszty elementow mapy
{
    int element;
    bool suma_jest = false;

    int *zuzyte = new int[A.size()];
	for (int i = 0; i < A.size(); i++)
		zuzyte[i] = 0;

    for (int i = 0; i < liczba_fragmentow; i++)
	{
		for (int j = 0; j < A.size(); j++)
		{
			if (A[j] == M[i])
			{
				if (zuzyte[j] == 0)
				{
					zuzyte[j] = 1;
					break;
				}
			}
		}
	}

   if (ind == maxind)
   {
		bool rozwiazanie = true;
		vector < int > pomocna;



        int it;

		for (int i = 0; i < liczba_fragmentow; i++)
		{
			it = M[i];
			pomocna.push_back(it);
			for (int j = i + 1; j < liczba_fragmentow; j++)
			{
				int suma = it + M[j];
				it += M[j];
				pomocna.push_back(suma);
			}
		}


		sort(pomocna.begin(), pomocna.end());
		sort(A.begin(), A.end());


		if (pomocna.size() != A.size())
			rozwiazanie = false;
		else if (pomocna.size() == A.size())
        {
			for (int k = 0; k < pomocna.size(); k++)
			{
				if (pomocna[k] != A[k])
				{
					rozwiazanie = false;
					break;
				}
			}
        }


		if (rozwiazanie)
		{
			wyswietl_M(M);
			*jest = 1;
		}
		else
		{
			int zla_liczba = M[ind];
			for (int i = 0; i < A.size(); i++)
			{
				if (zla_liczba == A[i])
				{
					M[ind] = 0;
					zuzyte[i] = 0;
					break;
				}
			}
		}

	}
	else for (int a = 0; a < A.size(); a++)
	{
		bool warto = true;

		if (zuzyte[a] == 0)
		{
			element = A[a];
			M[ind + 1] = element;

            int sklad;

			for (int i = 0; i < liczba_fragmentow - 1; i++)
			{
				sklad = M[i];
				for (int j = i + 1; j < liczba_fragmentow; j++)
				{
					int suma = sklad + M[j];
					sklad += M[j];
					suma_jest = false;

					if (suma == 0)
						suma_jest = true;
					else
                    {
						for(int k = 0; k < A.size(); k++)
						{
							if (suma == A[k])
								suma_jest = true;
						}
                    }
					if (!suma_jest)
					{
						warto = false;
						M[ind + 1] = 0;
						break;
					}
					else
						warto = true;
				}
				if (!suma_jest)
					break;
			}
			if (warto)
            {
                szukaj(M,ind+1,jest);
            }
		}
		if (*jest == 1)
			break;
	}

}


int main()
{
    string instancja;
    int jest = 0;

    cout<<"Podaj nazwe pliku do odczytu: ";
    cin >> instancja;
    wczytaj(instancja,A);
    wyswietl_A(A);

    cout << endl;
    if(liczba_elementow(A) == true)
    {
        cout << endl;
        pierwszy_element();


        int *M = new int[liczba_fragmentow];
        for (int m = 0; m < liczba_fragmentow; m++)
            M[m] = 0;
        M[0] = pierwszy_elem;

        cout << endl;
        start = clock();
        szukaj(M,0, &jest);
        stop = clock();

        czas = (double)(stop - start)/(double)(CLOCKS_PER_SEC);
        // czas wykonania algorytmu to roznica miedzy czasem konca a rozpoczecia dzialania
        cout << "Czas wykonywania algorytmu: " << czas << endl;
    }
    else
        exit(0);

    return 0;
}
