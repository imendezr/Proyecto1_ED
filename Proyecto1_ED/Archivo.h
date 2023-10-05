#pragma once

#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <string>
#include <vector>

class Archivo {
public:
	static std::vector<std::string> LeerArchivo(const std::string& nombreArchivo);
	static bool GuardarArchivo(const std::string& nombreArchivo, const std::vector<std::string>& contenido);
};

#endif
