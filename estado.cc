// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Juan Nicolás Becerra Rogatinscaia
// Correo: alu0101743011@ull.edu.es
// Fecha: 21/10/2025

#include <sstream>
#include <string>
#include <vector>

#include "estado.h"

void Estado::Read(std::istream& is) {
  is >> numero_identificador_;
  int aceptacion;
  is >> aceptacion;
  aceptacion_ = (aceptacion == 1); 
  is >> numero_transiciones_;
  char simbolo;
  int estado_destino;
  transiciones_.clear();
  for (int i = 0; i < numero_transiciones_; i++) {
    is >> simbolo;
    is >> estado_destino;
    transiciones_.insert({simbolo, estado_destino});
  }
}

bool Estado::AlgoritmoCadenas(const std::string& cadena, std::vector<Estado>& vec, int size, int i) {
  if (aceptacion_ && size == i) return true; // Si está en estado de aceptación y ha leído todos los símbolos
  auto par = transiciones_.equal_range(cadena[i]);
  for (auto iterador = par.first; iterador != par.second; iterador++) {
    return vec[iterador->second].AlgoritmoCadenas(cadena, vec, size, i + 1); 
  }
  return false;
}

std::istream& operator>>(std::istream& is, Estado& est) {
  est.Read(is);
  return is;
}
