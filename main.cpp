#include "Algoritmos.hpp"


#include <list>
#include <utility>
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    string archivo = "TEST.txt";
    cin >> archivo;
    ifstream entrada;

    //true: local, false: todo el path, para QT
    if(false)
    {
        entrada.open(archivo);
    }
    else
    {
        entrada.open("/home/ayra/Documents/AEDIII/EjerciciosLabo/BuscarK3/"+archivo);
    }
    if(!entrada.is_open())
    {
        cout << "Archivo cerrado" << endl;
        return 1;
    }

    string swap = "PLACEHOLDER";
    //Busco la cantidad de nodos.
    getline(entrada, swap);

    int size = stoi(swap);

    list<pair<int,int> > aristas;

    while( getline(entrada,swap,' ') )
    {
        pair<int,int> par;
        par.first = stoi(swap);
        getline(entrada,swap);
        par.second = stoi(swap);

        aristas.push_back(par);
    }

    bool res = HayK3(size,aristas,1);
    cout << res << endl;
    res = HayK3(size,aristas,2);
    cout << res << endl;
    res = HayK3(size,aristas,3);
    cout << res << endl;

    return 0;
}
