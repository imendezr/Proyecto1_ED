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
	std::vector<std::string> niveles;
	Repeticion repeticion;
	IVista* vista;

	void CargarNivel(int nivel);
	void GuardarJuego();
	bool CargarJuego();
	void mostrarInstrucciones();
	void ManejarEntrada(char entrada);
	void ReiniciarNivel();
	void MostrarRepeticion();
	void AvanzarAlSiguienteNivel();

public:
	JuegoControlador();
	~JuegoControlador();
	void IniciarJuego();
};

#endif
