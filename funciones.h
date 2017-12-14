#ifndef __METODOS_GRAFO__
#define __METODOS_GRAFO__

#include <algorithm>
#include "clases.h"

/////// -------------- SOBRECARGA DE OPERADORES ----------////////////
template<class T>
bool operator == (const Vertice<T> & v1,const Vertice<T> & v2)
{
  return v1.data==v2.data;
}

template<class T>
bool operator == (const Arista<T> & a1,const Arista<T> & a2)
{
  return a1.peso==a2.peso && a1.origen=a2.origen && a1.destino==a2.destino;
}

template<class T>
bool operator != (const Arista<T> & a1,const Arista<T> & a2)
{
  return !(a1==a2);
}

template<class T>
bool operator != (const Vertice<T> & v1,const Vertice<T> & v2)
{
  return !(v1==v2);
}

// el criterio para la desigualdad son las etiquetas
template<class T>
bool operator > (const Vertice<T> & v1,const Vertice<T> & v2)
{
  return v1.etiqueta > v2.etiqueta;
}

template<class T>
bool operator < (const Vertice<T> & v1,const Vertice<T> & v2)
{
  return !(v1>v2);
}

////// ------------- METODOS PRIVADOS -------------- ////////////
template<class T>
num Grafo<T>::suma_pesos()
{
  num sumador=0;
  
  for(itA=aristas.begin();itA!=aristas.end();itA++)
    sumador+=(*itA)->peso;
  return sumador+1;
}

template<class T>
void Grafo<T>::etiquetar_vertices()
{
  num etiquetaMaxima=suma_pesos();
  cout<<"etiqueta maxima: "<<etiquetaMaxima<<endl;
  
  for(itV=vertices.begin();itV!=vertices.end();itV++)
    (*itV)->etiqueta=etiquetaMaxima;
}

template<class T>
list<Arista<T>*>  Grafo<T>::buscar_aristas_adyacentes(Vertice<T> *v)
{
  list<Arista<T>*> adyacentes;
  
  for(itA=aristas.begin();itA!=aristas.end();itA++)
    if((*itA)->origen == v){
      adyacentes.push_back(*itA);
    }
  return adyacentes;
}

template<class T>
list<Vertice<T>*> Grafo<T>::buscar_vertices_adyacentes(Vertice<T>* v)
{
  list<Arista<T>*> aristasAdyacentes;
  list<Vertice<T> *> verticesAdyacentes;

  aristasAdyacentes=buscar_aristas_adyacentes(v);
  for(itA=aristasAdyacentes.begin();itA!=aristasAdyacentes.end();itA++)
    verticesAdyacentes.push_back((*itA)->destino);
  return verticesAdyacentes;
}

template <class T>
bool Grafo<T>::consultar_vertice(T v)
{
  itV=find(vertices.begin(),vertices.end(),new Vertice<T>(v));

  if(itV!=vertices.end())
    return true;
  return false;
}

template <class T>
bool Grafo<T>::consultar_arista(T a)
{
  itA=find(aristas.begind(),aristas.end(),new Arista<T>(a));

  if(itA==vertices.end())
    return true;
  return false;
}

template<class T>
Vertice<T>*  Grafo<T>:: buscar_vertice(T dato)
{
  for(itV=vertices.begin();itV!=vertices.end();itV++)
    if((*itV)->data==dato)
      return (*itV);
  return NULL;
}

template<class T>
Arista<T>*  Grafo<T>:: buscar_arista(T peso,T origen,T destino)
{
  for(itA=aristas.begin();itA!=aristas.end();itA++)
    if((*itA)->peso==peso && (*itA)->origen->data==origen && (*itA)->destino->data==destino)
      return *itA;
  return NULL;
}

///////---------------- METODOS PUBLICOS------------///////////
template<class T>
void Grafo<T>::agregar_vertice(T dato)
{
  if(!consultar_vertice(dato)){
    vertices.push_back(new Vertice<T> (dato));
    nVertices++;
  }
}

template <class T>
void Grafo<T>::agregar_arista(T peso ,T origen,T destino)
{
  Vertice<T> *des;
  Vertice<T> *ori;

  if(buscar_vertice(origen)!=*vertices.end() && buscar_vertice(destino)!=*vertices.end()){
    des=buscar_vertice(origen);
    ori=buscar_vertice(destino);
    des->nVerticesAdyacentes++;
    ori->nVerticesAdyacentes++;
  }
  else return;
  cout<<"llegamos otra vez"<<endl;
  aristas.push_back(new Arista<T>(peso,ori,des));
  nAristas++;
}

template<class T>
Grafo<T> Grafo<T>::generar_dijkstra(T o,T d)
{
  Vertice<T> *origen=buscar_vertice(o);
  Vertice<T> *destino=buscar_vertice(d);
  list<Vertice<T>*> copia;
  Vertice<T> *temp=origen;
  list<Arista<T>*> aristasAdyacentes;
  list<Vertice<T>*> verticesAdyacentes;
  num etiquetaActual;
  num etiquetaAdyacente;

  etiquetar_vertices();cout<<"vertices etiquetados"<<endl;
  visualizar();
  copia=vertices;        
  do{
    aristasAdyacentes=buscar_aristas_adyacentes(temp);
    verticesAdyacentes=buscar_vertices_adyacentes(temp);
    etiquetaActual = temp->etiqueta;
    cout<<"la etiqueta actual es: "<<etiquetaActual<<endl;
    for(itA=aristasAdyacentes.begin();itA!=aristasAdyacentes.end();itA++){
      cout<<"segundo for con: "<<(*itA)->peso<<"-"<<(*itA)->origen->data<<"-"<<(*itA)->destino->data<<endl;
      if((*itA)->destino->etiqueta > etiquetaActual+(*itA)->peso){
	cout<<"se cumplio el if con: "<<(*itA)->destino->data<<" y "<<(*itA)->peso+etiquetaActual;
        (*itA)->destino->etiqueta=etiquetaActual+(*itA)->peso;
        (*itA)->destino->anterior=(*itA)->destino->data;
      }
    }
    copia.remove(temp);
    temp=*min_element(verticesAdyacentes.begin(),verticesAdyacentes.end());
    cout<<"nuevo tem p "<<temp->data<<endl;
    cout<<"iterando como huebon"<<endl; 
  }
  while(temp!=destino);

  return *this;
}

template<class T>
void Grafo<T>::visualizar()
{
  for(itV=vertices.begin();itV!=vertices.end();itV++)
    cout<<"["<<(*itV)->data<<","<<(*itV)->etiqueta<<"] ";
  cout<<endl;
  for(itA=aristas.begin();itA!=aristas.end();itA++)
    cout<<"->"<<(*itA)->peso<<","<<(*itA)->origen->data<<","<<(*itA)->destino->data<<" ";
  cout<<endl;
}

#endif
