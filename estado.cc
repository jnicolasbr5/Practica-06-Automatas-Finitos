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

#include "estado.h"

void Estado::Read(std::istream& is) {
  is >> numero_identificador_;
  int aceptacion;
  is >> aceptacion;
  aceptacion_ = (aceptacion == 1) ? true : false; 
  is >> numero_transiciones_;
  transiciones_.clear();
  char simbolo;
  int estado_destino;
  for (int i = 0; i < numero_transiciones_; i++) {
    is >> simbolo;
    is >> estado_destino;
    transiciones_.insert({simbolo, estado_destino});
  }
}



std::istream& operator>>(std::istream& is, Estado& est) {
  est.Read(is);
  return is;
}
