#pragma once

#ifndef JUEGOCONTROLADOR_H
#define JUEGOCONTROLADOR_H

#include "Tablero.h"
#include "Archivo.h"
#include "Repeticion.h"
#include "IVista.h"
#include <string>
#include <vector>

class JuegoControlador {
private:
	Tablero tableroActual;
	int nivelActual;
	bool juegoEnProgreso;
	bool esperandoRespuesta;
	std::vector<std::string> niveles;
	Repeticion repeticion;
	IVista* vista;

	void cargarNivel(int nivel);
	void guardarJuego();
	bool cargarJuego();
	void mostrarInstrucciones();
	void manejarEntrada(char entrada);
	void nivelCompletado();
	void reiniciarNivel();
	void mostrarRepeticion();
	void avanzarAlSiguienteNivel();

public:
	JuegoControlador();
	~JuegoControlador();
	void iniciarJuego();
};

#endif
