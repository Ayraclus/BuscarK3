#ifndef BUSQUEDASK3
#define BUSQUEDASK3

#include <list>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool HayK3(unsigned int vertices, list<pair<int, int> >& aristas, int metodo);

bool HayK3Matriz(unsigned int vertices, const list<pair<int, int> >& aristas);
bool HayK3Lista(unsigned int vertices, const list<pair<int, int> >& aristas);
bool HayK3ListaIncidencia(unsigned int vertices, const list<pair<int,int> >& aristas);

/// vertices: Cantidad de vertices del grafo
/// aristas: lista de aristas del grafo
/// metodo: 1 para Matiz de adyacencia, 2 para Lista de Adyacencia, 3 para Lista de Incidencia
bool HayK3(unsigned int vertices, list<pair<int,int> >& aristas, int metodo)
{
    bool res;

    switch(metodo)
    {
    case 1:
        res = HayK3Matriz(vertices,aristas);
        break;
    case 2:
        res = HayK3Lista(vertices,aristas);
        break;
    default:
        res = HayK3ListaIncidencia(vertices,aristas);
        break;
    }

    return res;
}


bool HayK3Matriz(unsigned int vertices, const list< pair<int,int> >& aristas)
{
    //Transformo el input en una matriz de adyacencia
    bool matrizAdyacencia[vertices][vertices];
    for(int x = 0; x < vertices; x++)
    {
        for(int y = 0; y < vertices; y++)
        {
            matrizAdyacencia[x][y] = false;
        }
    }

    list<pair<int,int> >::const_iterator it = aristas.begin();

    while(it != aristas.end())
    {
        matrizAdyacencia[it->first][it->second] = true;
        it++;
    }

    //Para cada nodo A, en todos los nodos B conectados a A, si alguno de los nodos C conectados
    //a los nodos B, estan conectados a A.
    for( int A = 0; A < vertices; A++)
    {
        for( int B = 0; B < vertices; B++)
        {
            if( matrizAdyacencia[A][B] )
            {
                for( int C = 0; C < vertices; C++)
                {
                    if( matrizAdyacencia[B][C] && matrizAdyacencia[A][C] )
                        return true;
                }
            }
        }
    }

    return false;
}

bool HayK3Lista(unsigned int vertices, const list<pair<int,int>>& aristas)
{
    //transformo el input en una lista de adyacencia

    vector<list<int> > adyacencia;
    for(int i = 0; i < vertices; i++)
    {
        adyacencia.push_back(list<int>());
    }

    list<pair<int,int> >::const_iterator it = aristas.begin();

    while(it != aristas.end())
    {
        adyacencia[it->first].emplace_back(it->second);
        adyacencia[it->second].emplace_back(it->first);

        it++;
    }


    //Para todos los nodos A:
    //Armo un "Arreglo de adyacencia" para A.
    //Tomo todos los nodos C conectados a los nodos B adyacentes a A y los almaceno en una lista.

    for(int A = 0; A < vertices; A++)
    {
        list<int> TodosLosC;
        int TodosLosB [vertices];
        for( int i = 0; i < vertices; i++)
        {
            TodosLosB[i] = false;
        }
        list<int>::iterator itB = adyacencia[A].begin();
        while(itB != adyacencia[A].end())
        {
            TodosLosB[*itB] = true;

            list<int>::iterator itC = adyacencia[*itB].begin();
            while(itC != adyacencia[*itB].end())
            {
                TodosLosC.emplace_back(*itC);
                itC++;
            }

            itB++;
        }

        //Busco si hay algun adyacente a A en la lista.
        list<int>::iterator ItC = TodosLosC.begin();
        while(ItC != TodosLosC.end())
        {
            if(TodosLosB[*ItC])
            {
                return true;
            }
            ItC++;
        }
    }

    return false;

}

bool HayK3ListaIncidencia(unsigned int vertices, const list<pair<int,int> >& aristas)
{
    //Duplico todas las aristas, para tener A-B y B-A.
    //Armo la matriz de adyacencia

    bool matrizAdyacencia[vertices][vertices];
    for(int x = 0; x < vertices; x++)
    {
        for(int y = 0; y < vertices; y++)
        {
            matrizAdyacencia[x][y] = false;
        }
    }
    vector<pair<int,int>> Incidencias;

    list<pair<int,int> >::const_iterator it = aristas.begin();
    while(it != aristas.end())
    {
        Incidencias.emplace_back( pair<int,int>(it->first,it->second ) );
        Incidencias.emplace_back( pair<int,int>(it->second,it->first ) );

        matrizAdyacencia[it->first][it->second] = true;
        matrizAdyacencia[it->second][it->first] = true;

        it++;
    }

    //Ordeno la lista.

    sort(Incidencias.begin(),Incidencias.end());
    //Para cada una de las tuplas (A,B), reviso todas las tuplas (B,C)
        //Me ubico en la primera tupla.
        //Luego, para cada C, reviso en la matriz si está conectado a A.

    for(int AB = 0; AB < Incidencias.size(); AB++)
    {
        int B = Incidencias[AB].second;
        int BC = 0;
        while(BC < Incidencias.size() && Incidencias[BC].first != B)
        {
            BC++;
        }

        while(BC < Incidencias.size() && Incidencias[BC].first == B)
        {
            if(matrizAdyacencia[Incidencias[BC].second][Incidencias[AB].first])
            {
                return true;
            }
            BC++;
        }
    }

    return false;

}


#endif //BUSQUEDASK3
