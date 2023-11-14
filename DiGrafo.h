#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>

using namespace std;
using std::ifstream;
using std::string;
using std::stack;
using std::queue;

static const int INFTY = 1000;

template <typename T, int m>
class DiGrafo
{
  public:
    int orden;        //numero de vertices
    int tam;          //numero de aristas
    T vertices[m];
    double mtz[m][m];

  public:
    DiGrafo()
    {
      orden = 0;
      tam = 0;
      
      for (int i = 0; i < m; ++i)
      {
          vertices[i] = T();

          for (int j = 0; j < m; ++j)
          {
              mtz[i][j] = 0;
          }
      }
    }

    void nuevoVertice(T dato)
    {
      vertices[orden] = dato;
      ++orden;
    }

    int buscar(T v)
    {
      for (int i = 0; i < orden; ++i)
      {
          if (vertices[i] == v)
          {
              return i;
          }
      }
      
      return -1;
    }

    void nuevaFlecha(T u, T v, double w)
    {
      int indiceU, indiceV;

      indiceU = buscar(u);
      indiceV = buscar(v);

      if (indiceU >= 0 && indiceV >= 0)
      {
        mtz[indiceU][indiceV] = w;
        ++tam;
      }
      else
      {
        cout << "Error al agregar arista" << endl;
      }
    }

    void nuevaFlecha(T u, T v)
    {
      nuevaFlecha(u, v, 1);
    }

    void eliminarFlecha(T u, T v)
    {
      int i = buscar(u);
      int j = buscar(v);

      if(i >= 0 && j >= 0)
      {  
        mtz[i][j] = 0;
        --tam;
      }
      else
      {
        cout << endl <<"ERROR: La flecha entre " << u << " y "<< v << " no existe." << endl;
      }
    }

    void imprimeMtz()
    {
      for (int i = 0; i < m; ++i)
      {
        cout << " [\t";

        for (int j = 0; j < m; ++j)
        {
            cout << mtz[i][j] << "  ";
        }
        
        cout << "\t]" << endl;
      }
    }

    void recorerAnchura(T v) //dijkstra sin pesos
    {
      int marcados[m], indiceV = buscar(v), w;
      queue<int> cola;

        
      for (int i = 0; i < m; ++i) //iniciar los vertices como no marcados
      {
        marcados[i] = -1;
      }
      
      if (indiceV < 0)
      {
        cout << " El vertice no existe" << endl;
        return;
      }

      marcados[indiceV] = 0; //El vertice de inicio se marca como visitado
      cola.push(indiceV);

      while (!cola.empty())
      {
        w = cola.front();
        cola.pop();

        cout << " Nodo visitado: " << vertices[w] << endl;
        cout << " d(" << v << "," << vertices[w] << ") = " << marcados[w] << endl;

        //Se encolan y marcan todos sus adyacentes no marcados
        for (int i = 0; i < m; ++i)
        {
          if (mtz[w][i] && marcados[i] < 0)
          {
            marcados[i] = marcados[w] + mtz[w][i];
            cola.push(i);
          }
        }
      }

      for(int i = 0; i < m; ++i)
      {
        if(marcados[i] < 0)
        {
          cout << " No existe una " << v << "-" << vertices[i] << " trayectoria." << endl;
        }
      }
    }

    void recorerProfundidad(T v) //DFS
    {
      int marcados[m], indiceV = buscar(v), w;
      stack<int> pila;

        
      for(int i = 0; i < m; ++i)
      {
        marcados[i] = -1;
      }
      
      if(indiceV < 0)
      {
        cout << " El vertice no existe" << endl;
        return;
      }

      marcados[indiceV] = 0;
      pila.push(indiceV);

      while(!pila.empty())
      {
        w = pila.top();
        pila.pop();
        cout << " Nodo visitado: " << vertices[w] << endl;
        
        for(int i = 0; i < m; ++i)
        {
          if(mtz[w][i] && marcados[i] < 0)
          {
            marcados[i] = mtz[w][i];
            pila.push(i);
          }
        }
      }

      for(int i = 0; i < m; ++i)
      {
        if(marcados[i] < 0)
        {
          cout << " No existe una " << v << "-" << vertices[i] << " trayectoria." << endl;
        }
      }
    }

    void cargarDeArchivoInt(string nombre)
    {
        ifstream archivo; //objeto archivo
        archivo.open(nombre);

        for (int i = 0; i < m; ++i)
        {
            nuevoVertice(i);
            for (int j = 0; j < m; ++j)
            {
              archivo >> mtz[i][j];
            }
        }
    }

    int minimo(int F[], int D[])
    {
        int u;
        int min = INFTY;

        for (int j = 0; j < m; ++j)
        {
            if (F[j] == 0 && D[j] < min)
            {
                min = D[j];
                u = j;
            }
        }
        return u;
    }

    void dijkstra(T vs)
    {
        int F[m]; //seleccionados(1) y no seleccionados(0)
        int D[m]; //distancia al origen
        int U[m]; //predecesor en el camino
        int u;    //vertice arbitrario u

        for (int i = 0; i < m; ++i)
        {
            if (i == vs)
            {
                F[i] = 1; //el origen es seleccionado
            }
            else
            {
                F[i] = 0;
            }

            D[i] = mtz[vs][i]; //Se establecen las distancias

            if (D[i] < INFTY)
            {
                U[i] = vs; //Peso de flecha desde el origen
            }
            else
            {
                U[i] = -1; //No es exvecino del origen
            }
        }

        for (int i = 1; i < m; ++i)
        {
            u = minimo(F, D, INFTY); //Se identifica u con la menor distancia a vs
            F[u] = 1; //Se selecciona

            for (int j = 0; j < m; ++j)
            { //Se actualiza D y U para los elementos en V-F
                if (F[j] == 0 && D[u] + mtz[u][j] < D[j])
                {
                    D[j] = D[u] + mtz[u][j];
                    U[j] = u;
                }
            }
        }

        cout << endl << "Distancias minimas desde v = " << vs << ":" << endl << "\t[\t";

      
        for (int j = 0; j < m; ++j)
        {
            if (D[j] == INFTY)
            {
              cout << "inf" << "\t";
            }
            else
            {
              cout << D[j] << "\t";
            }
        }
        cout << "\t]" << endl << endl << "Predecesores:" << endl << "\t[\t";

        for (int j = 0; j < m; ++j)
        {
            cout << U[j] << "\t";
        }

        cout << "\t]" << endl;
    }  
};