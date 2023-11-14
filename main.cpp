#include "DiGrafo.h"
#include "Grafo.h"
#include "Jaula.h"

using namespace std;

int MooreBound(int deg, int g)
{
  int d = deg - 1;
  int diam = (g - 1) / 2; //Diametro

  if(deg == 2) //Ciclos
  {
    return g;
  }
  else if(g % 2 == 1) //Jaulas de cuello impar
  {
    return (2 - deg * pow(d,diam)) / (2 - deg);
  }
  else //Jaulas de cuello par
  {
    return 2 * (1 - pow(d,diam)) / (2 - deg);
  }
}

/*
  VISITANTE: NO OLVIDES AJUSTAR LOS PARAMETROS

      C5: (d,g) = (2,5) - Orden 5
      Petersen: (d,g) = (3,5) - Orden 10
      Hoffman-Singleton: (d,g) = (7,5) - Orden 50

  :D
*/

int main(int argc, char const * argv[])
{
  int deg = 7; //grado
  int girth = 5; //cuello
  int MB = MooreBound(deg, girth); //orden

  Jaula<int, 50> G(deg,girth);
  G.construirJaula();
  
  cout << endl << endl;
  G.imprimeMtz();
  cout << endl;
  cout << "|V| = \t\t" << MB << endl;
  cout << "|E| = \t\t" << G.tam << endl; //debe coincidir con grado*orden/2
  cout << "CUELLO =\t" << girth << endl;
  cout << "GRADO = \t[\t"; //debe ser uniforme
  
  for(int i = 0; i < MB; ++i)
  {
    cout << G.grado[i] << " ";
  }

  cout << "]" << endl << endl << endl;

  return 69;
}