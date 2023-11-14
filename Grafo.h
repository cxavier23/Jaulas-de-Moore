#pragma once

#include "DiGrafo.h"

template <typename T, int m> //optimizado para T = int
class Grafo : public DiGrafo<T,m> //grafo no dirigido
{
  typedef DiGrafo<T,m> DG;

  public:
    int grado[m]; //cardinalidad de las vecindades de cada vertice (vecindad = num de ady)

    Grafo() : DG::DiGrafo()
    {
      for(int i = 0; i < m; ++i)
      {
        grado[i] = 0;
      }
    }

    void nuevaArista(int u, int v)
    {
      DG::mtz[u][v] = 1;
      DG::mtz[v][u] = 1;

      ++grado[u]; //aumenta el grado de los vertices en la arista
      ++grado[v];

      ++DG::tam;
    }

    
    void eliminarArista(int u, int v) 
    {
      DG::mtz[u][v] = 0;
      DG::mtz[v][u] = 0;

      --grado[u];
      --grado[v];

      --DG::tam;
    }
};