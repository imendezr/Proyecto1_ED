// Implementación de Nodo
template<class T>
struct ListaEnlazada<T>::Nodo {
	T valor;
	Nodo* left;
	Nodo* right;
	Nodo* up;
	Nodo* down;
	Nodo(T valor, Nodo* izquierda = nullptr, Nodo* derecha = nullptr, Nodo* arriba = nullptr, Nodo* abajo = nullptr)
		: valor{ valor }, left{ izquierda }, right{ derecha }, up{ arriba }, down{ abajo } {}
};

template<class T>
void ListaEnlazada<T>::inicializar() { inicio = nullptr; }

// Constructores
// Default
template<class T>
ListaEnlazada<T>::ListaEnlazada() { inicializar(); }

// Copia
template<class T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada& obj) {
	inicializar();
	if (!obj.inicio) {
		return;  // Si la lista original está vacía
	}

	// Copiar fila por fila
	listaptr filaActualOriginal = obj.inicio;
	listaptr filaAnteriorNueva = nullptr;
	while (filaActualOriginal) {
		listaptr nodoActualOriginal = filaActualOriginal;
		listaptr nodoAnteriorNuevo = nullptr;

		while (nodoActualOriginal) {
			listaptr nuevoNodo = new Nodo(nodoActualOriginal->valor);

			// Conexiones izquierda-derecha
			if (nodoAnteriorNuevo) {
				nodoAnteriorNuevo->right = nuevoNodo;
				nuevoNodo->left = nodoAnteriorNuevo;
			}
			else {
				// Es el primer nodo de la fila
				if (!filaAnteriorNueva) {
					// Es la primera fila
					inicio = nuevoNodo;
				}
				else {
					filaAnteriorNueva->down = nuevoNodo;
					nuevoNodo->up = filaAnteriorNueva;
				}
			}

			nodoAnteriorNuevo = nuevoNodo;
			nodoActualOriginal = nodoActualOriginal->right;
		}

		filaAnteriorNueva = inicio;
		while (filaAnteriorNueva->down) {
			filaAnteriorNueva = filaAnteriorNueva->down;
		}

		filaActualOriginal = filaActualOriginal->down;
	}

	// Copiar conteo de filas y columnas
	filas = obj.filas;
	columnas = obj.columnas;
}


// Destructor
template<class T>
ListaEnlazada<T>::~ListaEnlazada() {
	borrarLista();
	filas = 0;
	columnas = 0;
}

// Retorna un apuntador al primer nodo de la lista - modificable
template<class T>
typename ListaEnlazada<T>::listaptr ListaEnlazada<T>::getPrimerNodo() {
	return inicio;
}

// Retorna un apuntador al primer nodo de la lista - para un objeto const
template<class T>
typename ListaEnlazada<T>::const_listaptr ListaEnlazada<T>::getPrimerNodo() const {
	return inicio;
}

// Retorna el número de filas en la lista
template<class T>
int ListaEnlazada<T>::getFilas() const {
	return filas;
}

// Retorna el número de columnas en la lista
template<class T>
int ListaEnlazada<T>::getColumnas() const {
	return columnas;
}

/*// Verifica si un nodo es contiguo a otro en cualquier dirección
template<class T>
bool ListaEnlazada<T>::esAdyacente(listaptr nodo1, listaptr nodo2) {
	if (!nodo1 || !nodo2) return false;

	return (nodo1->right == nodo2 || nodo1->left == nodo2 ||
		nodo1->up == nodo2 || nodo1->down == nodo2);
}

// Encuentra todos los nodos con un mismo valor
template<class T>
std::vector<typename ListaEnlazada<T>::listaptr> ListaEnlazada<T>::buscarCeldasConValor(const T& valorBuscado) {
	std::vector<listaptr> nodosEncontrados;
	listaptr filaActual = inicio;
	while (filaActual) {
		listaptr nodoActual = filaActual;
		while (nodoActual) {
			if (nodoActual->valor == valorBuscado) {
				nodosEncontrados.push_back(nodoActual);
			}
			nodoActual = nodoActual->right;
		}
		filaActual = filaActual->down;
	}
	return nodosEncontrados;
}*/

// Retorna un nodo por posición
template<class T>
typename ListaEnlazada<T>::listaptr ListaEnlazada<T>::obtenerNodo(int fila, int columna) {
	if (fila < 0 || columna < 0 || fila >= ListaEnlazada<T>::filas || columna >= ListaEnlazada<T>::columnas) return nullptr;  // Si la lista está vacía

	typename ListaEnlazada<T>::listaptr nodoActual = ListaEnlazada<T>::inicio;

	// Moverse a la fila correcta
	for (int i = 0; i < fila; i++) {
		nodoActual = nodoActual->down;
		if (!nodoActual) return nullptr;  // Verifica que el nodo actual no sea nullptr
	}

	// Moverse a la columna correcta
	for (int j = 0; j < columna; j++) {
		nodoActual = nodoActual->right;
		if (!nodoActual) return nullptr;  // Verifica que el nodo actual no sea nullptr
	}

	return nodoActual;
}

// Inserta una fila al final de la lista
template<class T>
void ListaEnlazada<T>::insertarFila(const std::vector<T>& valores) {
	if (valores.empty()) return;  // Si el vector de valores está vacío

	listaptr primerDeFilaAnterior = nullptr;
	if (filas > 0) {
		primerDeFilaAnterior = obtenerNodo(filas - 1, 0);
	}

	listaptr finFilaAnterior = nullptr;
	listaptr inicioFilaNueva = nullptr;

	for (const T& val : valores) {
		listaptr nuevoNodo = new Nodo(val);

		if (!inicioFilaNueva) {
			inicioFilaNueva = nuevoNodo;
		}
		else {
			finFilaAnterior->right = nuevoNodo;  // Conecta el nodo derecho del nodo anterior al nuevo nodo
			nuevoNodo->left = finFilaAnterior;   // Conecta el nodo izquierdo del nuevo nodo al nodo anterior
		}

		if (primerDeFilaAnterior) {
			primerDeFilaAnterior->down = nuevoNodo;  // Conecta el nodo de abajo del nodo anterior al nuevo nodo
			nuevoNodo->up = primerDeFilaAnterior;   // Conecta el nodo de arriba del nuevo nodo al nodo anterior

			primerDeFilaAnterior = primerDeFilaAnterior->right;  // Avanza al siguiente nodo de la fila anterior
		}

		finFilaAnterior = nuevoNodo;
	}

	if (!inicio) {
		inicio = inicioFilaNueva;  // Si la lista estaba vacía, establece inicio de la lista en el primer nodo de la fila nueva
	}

	filas++;
	if (valores.size() > columnas) {
		columnas = valores.size();  // Actualiza el número de columnas si es necesario
	}
}

// Inserta una columna al final de la lista
template<class T>
void ListaEnlazada<T>::insertarColumna(const std::vector<T>& valores) {
	if (valores.empty()) return;  // Si el vector está vacío

	listaptr primerDeColumnaAnterior = nullptr;
	if (columnas > 0) {
		primerDeColumnaAnterior = obtenerNodo(0, columnas - 1);
	}

	listaptr finColumnaAnterior = nullptr;
	listaptr inicioColumnaNueva = nullptr;

	for (const T& val : valores) {
		listaptr nuevoNodo = new Nodo(val);

		if (!inicioColumnaNueva) {
			inicioColumnaNueva = nuevoNodo;
		}
		else {
			finColumnaAnterior->down = nuevoNodo;  // Conecta el nodo de abajo del nodo anterior al nuevo nodo
			nuevoNodo->up = finColumnaAnterior;   // Conecta el nodo de arriba del nuevo nodo al nodo anterior
		}

		if (primerDeColumnaAnterior) {
			primerDeColumnaAnterior->right = nuevoNodo;  // Conecta el nodo derecho del nodo anterior al nuevo nodo
			nuevoNodo->left = primerDeColumnaAnterior;   // Conecta el nodo izquierdo del nuevo nodo al nodo anterior

			primerDeColumnaAnterior = primerDeColumnaAnterior->down;  // Avanza al siguiente nodo de la columna anterior
		}

		finColumnaAnterior = nuevoNodo;
	}

	if (!inicio) {
		inicio = inicioColumnaNueva;  // Si la lista estaba vacía, establece inicio de la lista en el primer nodo de la columna nueva
	}

	columnas++;
	if (valores.size() > filas) {
		filas = valores.size();  // Actualiza el número de filas si es necesario
	}
}

// Elimina una fila en la posición dada
template<class T>
void ListaEnlazada<T>::eliminarFila(int posicion) {
	// Si la lista está vacía o si la posición es inválida
	if (!inicio || posicion < 0 || posicion >= filas) return;

	// Moverse a la fila especificada
	listaptr filaActual = inicio;
	for (int i = 0; i < posicion && filaActual; i++) {
		filaActual = filaActual->down;
	}

	// Si no se encuentra la fila
	if (!filaActual) return;

	// Obtener filas adyacentes
	listaptr filaAnterior = filaActual->up;
	listaptr filaSiguiente = filaActual->down;

	// Eliminar todos los nodos en la fila
	listaptr nodoActual = filaActual;
	while (nodoActual) {
		listaptr siguienteNodo = nodoActual->right;

		// Desconectar el nodo actual de sus vecinos
		if (nodoActual->left) nodoActual->left->right = nodoActual->right;
		if (nodoActual->right) nodoActual->right->left = nodoActual->left;
		if (nodoActual->up) nodoActual->up->down = nodoActual->down;
		if (nodoActual->down) nodoActual->down->up = nodoActual->up;

		// Liberar memoria
		delete nodoActual;
		nodoActual = siguienteNodo;
	}

	// Reconectar las filas adyacentes
	if (filaAnterior) filaAnterior->down = filaSiguiente;
	if (filaSiguiente) filaSiguiente->up = filaAnterior;

	// Si se elimina la primera fila, actualizar el inicio
	if (posicion == 0) inicio = filaSiguiente;

	// Actualizar conteo de filas
	filas--;
}

// // Elimina una columna en la posición dada
template<class T>
void ListaEnlazada<T>::eliminarColumna(int posicion) {
	// Si la lista está vacía o si la posición es inválida
	if (!inicio || posicion < 0 || posicion >= columnas) return;

	// Moverse a la columna especificada
	listaptr columnaActual = inicio;
	for (int i = 0; i < posicion && columnaActual; i++) {
		columnaActual = columnaActual->right;
	}

	// Si no se encuentra la columna
	if (!columnaActual) return;

	// Obtener columnas adyacentes
	listaptr columnaAnterior = columnaActual->left;
	listaptr columnaSiguiente = columnaActual->right;

	// Eliminar todos los nodos en la columna
	listaptr nodoActual = columnaActual;
	while (nodoActual) {
		listaptr siguienteNodo = nodoActual->down;

		// Desconectar el nodo actual de sus vecinos
		if (nodoActual->left) nodoActual->left->right = nodoActual->right;
		if (nodoActual->right) nodoActual->right->left = nodoActual->left;
		if (nodoActual->up) nodoActual->up->down = nodoActual->down;
		if (nodoActual->down) nodoActual->down->up = nodoActual->up;

		// Liberar memoria
		delete nodoActual;
		nodoActual = siguienteNodo;
	}

	// Reconectar las columnas adyacentes
	if (columnaAnterior) columnaAnterior->right = columnaSiguiente;
	if (columnaSiguiente) columnaSiguiente->left = columnaAnterior;

	// Si se elimina la primera columna, actualizar el inicio
	if (posicion == 0) inicio = columnaSiguiente;

	// Actualizar conteo de columnas
	columnas--;
}

/*// Imprime el contenido de la lista
template<class T>
void ListaEnlazada<T>::imprimir() {
	listaptr filaActual = inicio;
	while (filaActual) {
		listaptr nodoActual = filaActual;
		while (nodoActual) {
			std::cout << nodoActual->valor << "\t"; // Tabulación entre columnas
			nodoActual = nodoActual->right;
		}
		std::cout << std::endl; // Al final de cada fila
		filaActual = filaActual->down;
	}
}*/

// Borra completamente la lista
template<class T>
void ListaEnlazada<T>::borrarLista() {
	listaptr filaActual = inicio;

	while (filaActual) {
		listaptr nodoActual = filaActual;
		filaActual = filaActual->down;  // Moverse a la siguiente fila antes de borrar nodos

		while (nodoActual) {
			listaptr nodoAEliminar = nodoActual;
			nodoActual = nodoActual->right;  // Moverse al siguiente nodo antes de borrar
			delete nodoAEliminar;
		}
	}

	inicio = nullptr;
}
