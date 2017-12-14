//#include "clases.h"
#include "funciones.h"

int main(int argc,char *argv[])
{
  Grafo<> g1;
  
  for(int i=0;i<15;i+=5)
    g1.agregar_vertice(i);
  g1.agregar_arista(3,10,5);
  g1.agregar_arista(10,0,5);
  g1.agregar_arista(15,10,0);
  g1.visualizar();
  g1.generar_dijkstra(10,5).visualizar();
  
  
  return 0;
}
