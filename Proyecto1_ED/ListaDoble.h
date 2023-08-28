// Descripción: Definición de una lista doblemente enlazada

#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include <iostream>
#include <cstddef>

// Lista que se construye a partir de nodos autoreferenciados
// con datos definidos por el usuario
template<class T> class ListaDoble {
private:
	// Declaración de cada nodo de la lista: contiene el valor y un apuntador a un nodo
	// Queda oculto para el usuario
	struct Nodo {
		T valor;
		Nodo* prev;
		Nodo* next;
		// Constructor del Nodo - asigna NULL si se invoca sin el segundo parámetro
		Nodo(T val, Nodo* ant = nullptr, Nodo* sig = nullptr) : valor{ val }, prev{ ant }, next { sig } {}
	};

	// Apuntador al inicio de la lista
	Nodo* inicio;

	void Inicializar() { inicio = nullptr; }

	// Interfaz de la Lista Enlazada Simple
public:

	// Declaración de definición de tipos
	typedef Nodo* listaptr;
	typedef const Nodo* const_listaptr;

	// Constructores
	// Default
	ListaDoble() { Inicializar(); }
	// Copia
	explicit ListaDoble(const ListaDoble& obj) {
		if (obj.inicio == nullptr)
			inicio = nullptr;
		else {
			inicio = new Nodo(obj.inicio->valor);
			listaptr actual = inicio;
			listaptr actualObj = obj.inicio->next;
			while (actualObj != nullptr) {
				actual->next = new Nodo(actualObj->valor); // nodo copiado
				actual->next->prev = actual; // prev del nodo recien copiado
				actual = actual->next;
				actualObj = actualObj->next;
			}
		}
	}

	// Destructor
	~ListaDoble() { BorrarLista(); }

	// Retorna un apuntador al primer nodo de la lista - modificable
	listaptr GetPrimerNodo() { return inicio; }

	// Retorna un apuntador al primer nodo de la lista - para un objeto const
	const_listaptr GetPrimerNodo() const { return inicio; }

	// Inserta un elemento al final de la lista enlazada
	void Insertar(const T& val) {
		listaptr nuevo;

		try {
			nuevo = new Nodo(val);
		}
		catch (std::bad_alloc exception) {
			return;
		}

		if (inicio == nullptr)
			inicio = nuevo;
		else {
			listaptr tmp = inicio;
			while (tmp->next != nullptr) {
				tmp = tmp->next;
			}
			tmp->next = nuevo;
			nuevo->prev = tmp; // asigno prev del nuevo nodo
		}
	}

	// Inserta un elemento al inicio de la lista enlazada
	void InsertarInicio(const T& val) {
		listaptr nuevo;

		try {
			nuevo = new Nodo(val);
		}
		catch (std::bad_alloc exception) {
			return;
		}

		if (inicio == nullptr)
			inicio = nuevo;
		else {
			nuevo->next = inicio;
			inicio->prev = nuevo; // asigno prev del nodo inicio anterior
			inicio = nuevo;
		}
	}

	// Elimina el nodo especificado de la lista enlazada
	void Eliminar(listaptr puntero) {
		// No hay nada que borrar si la lista enlazada está vacía
		// o el puntero es NULL
		if (puntero == nullptr || inicio == nullptr)
			return;

		// Caso #1: El elemento a borrar es el primero de la lista enlazada
		if (inicio == puntero) {
			inicio = inicio->next;
			if (inicio) inicio->prev = nullptr; // = if (inicio != nullptr). Evita desreferenciar un puntero nulo (si inicio->next es nullptr, entonces nullptr->prev daría error)
			delete puntero;
		}
		// Caso #2: El elemento se encuentra en alguna otra posición de la lista
		else {
			listaptr tmp = inicio;
			listaptr tmp2 = tmp->next;
			while (tmp2 != nullptr) {
				if (tmp2 == puntero) {
					tmp->next = tmp2->next;

					if (tmp2->next) { // = if (tmp2->next != nullptr). Si el nodo que se elimina no es el último, se ajusta prev del siguiente.
						tmp2->next->prev = tmp;
					}

					delete tmp2;
					return;
				}
				tmp = tmp2;
				tmp2 = tmp2->next;
			}
		}
	}

	// Elimina un nodo de la lista en la posición especificada
	void EliminarEnPos(std::size_t pos) {
		if (pos <= 0)
			return;

		listaptr tmp = inicio;
		for (std::size_t i = 1; i < pos; ++i) {
			tmp = tmp->next;
			if (tmp == nullptr)
				return;
		}
		Eliminar(tmp);
	}

	// Busca un elemento en la lista y retorna el nodo
	listaptr Buscar(const T& val) {
		listaptr tmp = inicio;
		while (tmp != nullptr) {
			if (tmp->valor == val)
				return tmp;
			tmp = tmp->next;
		}
		return nullptr;  // Si no lo encuentra retorna nullptr
	}

	// Borra completamente la lista
	void BorrarLista() {
		listaptr tmp;
		while (inicio != nullptr) {
			tmp = inicio;
			inicio = inicio->next;
			delete tmp;
		}
	}
};

#endif