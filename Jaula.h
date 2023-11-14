#pragma once

#include <cmath>
#include <queue>
#include <vector>
#include "Grafo.h"

using namespace std;
using std::queue;


template <typename T, int MB> //solo funciona con T = int
class Jaula : public Grafo<T, MB>
{
  typedef Grafo<T,MB> G;
  typedef DiGrafo<T,MB> DG;

  private:
    int deg; //grado regular
    int g; //cuello - long del ciclo mas corto
    int diam; //diametro - max dist entre vertices
    vector<int> hojas; //del arbol generador

  public:
    Jaula(int grad, int cuello) : G::Grafo()
    {
      deg = grad;
      g = cuello;
      diam = (g - 1) / 2;

      for(int i = 0; i < MB; ++i)
      {
        DG::nuevoVertice(i);
      }
    }

  private:
    void spanningTree() //arbol generador de la jaula con BFS
    {
      queue<int> cola; 
      int d = ((g + 1) % 2) + 1; //impar->d=1, par->d=2
      int u = d - 1;
      int aux = u;

      for(int v = 0; v < d; ++v) //arbol par tiene dos raices
      {
        for(int i = aux; i < deg; ++i)
        {
          ++u;
          cola.push(u);
          G::nuevaArista(v,u);
        }
      }

      while(DG::tam < MB - 1) //un arbol de orden n tiene tamanio n-1
      {
        int v = cola.front();
        cola.pop();

        for(int i = 1; i < deg; ++i) //los vertices ya tienen un vecino (padre)
        {
          ++u;
          cola.push(u);
          G::nuevaArista(v,u);
        }
      }
    }

    void hojasSpanningTree() //identifica y almacena las hojas
    {
      //hay d(d-1)^(k-1) vertices en el nivel k
      int h = MB - 1;

      while(G::grado[h] == 1)
      {
        hojas.insert(hojas.begin(), h);
        --h;
      }
    }

    void closeCage() //conecta las hojas
    {
      int d = deg - 1;
      int numHojas = hojas.size();
      int numRamas = numHojas / d; //familias de hojas
      int j = d, h1, h2;

      for(int k = 1; k < numRamas; ++k)
      {
        for(int i = (k-1)*d; i < k*d; ++i)
        {
          j = i + d;
          h1 = hojas.at(i);

          while(j < numHojas)
          {
            h2 = hojas.at(j);
            G::nuevaArista(h1, h2);
            j += d;
          }
        }
      }
    }

  public:
    void construirJaula() //construye jaula de Moore
    {
      spanningTree();
      hojasSpanningTree();
      closeCage();
    }
};