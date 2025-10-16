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
#include <set>
#include <vector>

#include "estado.h"

void Estado::Read(std::istream& is) {
  is >> numero_identificador_;
  int aceptacion;
  is >> aceptacion;
  aceptacion_ = (aceptacion == 1); 
  is >> numero_transiciones_;
  transiciones_.clear(); // Inicializa las transiciones de cada estado
  if (numero_transiciones_ != 0) { // Si el estado tiene transiciones
    char simbolo;
    int estado_destino; 
    for (int i = 0; i < numero_transiciones_; i++) {
      is >> simbolo;
      is >> estado_destino;
      transiciones_.insert({simbolo, estado_destino});
    }
  }
}

bool Estado::AlgoritmoCadenas(const std::string& cadena, std::vector<Estado>& vec, 
                              const std::set<int> identificadores, int size, int i) {
  if (aceptacion_ && size == i) return true; // Si está en estado de aceptación y ha leído todos los símbolos
  auto par = transiciones_.equal_range(cadena[i]);
  for (auto iterador = par.first; iterador != par.second; iterador++) {
    ComprobarSimbolosEstados(identificadores, iterador->second); // Comprobar error 5
    if (vec[iterador->second].AlgoritmoCadenas(cadena, vec, identificadores, size, i + 1)) {
      return true;
    } 
  }
  return false;
}

void Estado::ComprobarSimbolosTransiciones(const std::set<char>& alfabeto) const { // Error 3
  for (const auto& par : transiciones_) { // Itero cada par
    if (alfabeto.find(par.first) == alfabeto.end()) { // Si no está en el alfabeto, error
      std::cerr << "ERROR:" << std::endl;
      std::cerr << "El símbolo " << par.first << " no forma parte del alfabeto." << std::endl;
      exit(1);
    }
  }
}

void Estado::ComprobarSimbolosEstados(const std::set<int>& identificadores, int ident) const { // Error 5
  if (identificadores.find(ident) == identificadores.end()) {
    std::cerr << "ERROR: " << std::endl; // Si no existe el estado, da error
    std::cerr << "El estado '" << ident << "' al que se quiere transitar no es parte del autómata." << std::endl;
    exit(1);
  }
}

std::istream& operator>>(std::istream& is, Estado& est) {
  est.Read(is);
  return is;
}
