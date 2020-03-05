#include <iostream>
#include "Campo.hpp"
using namespace std;

/**********************************
 *      stampa del campo
********************************/
void Campo::stampa()
{
    for(int i = 0; i<row; i++)
    {
        for(int j = 0; j<col; j++)
        {
            cout << campo[i][j];
        }
        cout << endl;
    }
}

/**********************************
 *      inizializza campo
********************************/
void Campo::inizializza()
{
    for(int i = 0; i<row; i++)
    {
        for(int j = 0; j<col; j++)
        {
           campo[i][j] = ' ';
        }
    }
}

/**********************************
 *aggiunge i bordi ai lati del campo
********************************/
void Campo::bordi()
{
    for(int i = 0; i<row; i++)
    {
        campo[i][0] = '|';
        campo[i][col-1] = '|';
    }
}

/**********************************
 *         costruttore
********************************/
Campo::Campo()
{
    inizializza();
    bordi();
}

/**********************************
 *  inserisce un carattere 's' nella
 *  riga 'r' e colonna 'c'
********************************/
void Campo::inserisci(char s, int r, int c)
{
	campo[r][c] = s;
}

/**********************************
 *  aggiorna il campo copiando la riga
 *  sopra nella riga sotto
********************************/
void Campo::aggiorna()
{
	for (int i = row - 1; i >= 0; i--)
	{
		for (int j = 0; j < col; j++)
		{
			if (i == 0)
			{
				if (j == 0 || j == col - 1)
				{
					campo[i][j] = '|';
				}
				else
					campo[i][j] = ' ';
			}
			else
				campo[i][j] = campo[i - 1][j];
		}
	}
}
