#ifndef __CLASE_GRAFO__
#define __CLASE_GRAFO__

#include <iostream>
#include <list>

using namespace std;

typedef long int num;

template <class T>
struct Vertice{
  T data;
  num etiqueta;
  num nVerticesAdyacentes;
  T anterior;
  
  Vertice(T d):data(d){}
};

template <class T>
struct Arista
{
  T peso;
  Vertice<T> *origen;
  Vertice<T> *destino;
  bool direccion; // 1 si es dirigido , 0 si no lo es

Arista(T p,Vertice<T> *o,Vertice<T> *d):peso(p),origen(o),destino(d),direccion(false){}
Arista(T p):peso(p),origen(NULL),destino(NULL),direccion(false){}
  
};

template<class T= int>
class Grafo
{
  typename list<Arista <T>*>::iterator itA;
  typename list<Vertice <T>*>::iterator itV;
  list<Vertice<T> *> vertices;
  list<Arista<T>*> aristas;
  bool dirigido ; /// 1 para grafo dirigido, 0 para grafo no dirigido
  num nVertices;
  num nAristas;
  num suma_pesos();
  void etiquetar_vertices();
  bool consultar_vertice(T );
  bool consultar_arista(T);
  Vertice<T>*  buscar_vertice(T );
  Arista<T>*  buscar_arista(T,T,T); 
  list<Arista<T>*>  buscar_aristas_adyacentes(Vertice<T> *);
  list<Vertice<T>*>  buscar_vertices_adyacentes(Vertice<T> *);
 public:
  
  Grafo(bool tipo):dirigido(tipo),nVertices(0),nAristas(0){}
  Grafo():dirigido(false),nVertices(0),nAristas(0){}
  void agregar_vertice(T );
  void agregar_arista(T,T,T );
  void visualizar();

  Grafo<T> generar_prim();
  Grafo<T> generar_kruskall();
  Grafo<T> generar_dijkstra(T,T );

  
  
};

#endif
