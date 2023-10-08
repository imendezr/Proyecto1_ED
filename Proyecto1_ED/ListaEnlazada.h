#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <iostream>
#include <cstddef>
#include <vector>

template<class T>
class ListaEnlazada {
public:
    struct Nodo;
    typedef Nodo* listaptr;
    typedef const Nodo* const_listaptr;

private:
    Nodo* inicio;
    int filas = 0;
    int columnas = 0;

    void inicializar();

public:
    ListaEnlazada();
    ListaEnlazada(const ListaEnlazada&);
    ~ListaEnlazada();

    listaptr getPrimerNodo();
    const_listaptr getPrimerNodo() const;
    int getFilas() const;
    int getColumnas() const;
    //bool esAdyacente(listaptr, listaptr);
    //std::vector<listaptr> buscarCeldasConValor(const T&);
    listaptr obtenerNodo(int, int);
    const_listaptr obtenerNodo(int, int) const;
    void insertarFila(const std::vector<T>&);
    void insertarColumna(const std::vector<T>&);
    void eliminarFila(int);
    void eliminarColumna(int);
    //void imprimir();
    void borrarLista();
};

#include "ListaEnlazada.hpp"

#endif
