// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Juan Nicolás Becerra Rogatinscaia
// Correo: alu0101743011@ull.edu.es
// Fecha: 21/10/2025

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "automata.h"
#include "estado.h"


void Automata::Read(std::ifstream& archivo_entrada) {
  std::string simbolos; // Leo los símbolos
  std::getline(archivo_entrada, simbolos);
  InsertarSimbolos(simbolos);
  archivo_entrada >> numero_estados_; // Leo el número de estados
  archivo_entrada.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Lee la siguiente linea
  std::string estados_iniciales;
  std::getline(archivo_entrada, estados_iniciales);
  UnicoEstadoInicial(estados_iniciales); // Verifico un único estado inicial
  Estado state;
  while(archivo_entrada >> state) {
    estados_.push_back(state);
  }
  
}

void Automata::LeerCadenas(std::ifstream& archivo_entrada) {
  std::string cadena;
  while(std::getline(archivo_entrada, cadena)) {
    std::cout << cadena << " --- ";
    if (ComprobarCadenas(cadena)) std::cout << "Accepted" << std::endl;
    else std::cout << "Rejected" << std::endl;
  }
}
 
bool Automata::ComprobarCadenas(const std::string& cadena) {
  for (char c : cadena) { // Cadena no coincide con alfabeto
    if (alfabeto_.find(c) == alfabeto_.end()) return false; 
  }
  std::vector<Estado> estados_automata = GetEstados();
  return estados_[estado_inicial_].AlgoritmoCadenas(cadena, estados_automata, cadena.size());
}

void Automata::UnicoEstadoInicial(const std::string& estados_iniciales) {
  std::istringstream ss(estados_iniciales);
  ss >> estado_inicial_; // Guardo el estado inicial
  std::string demas;
  if (ss >> demas) { // Error 1: Si hay más de un estado inicial, se lanza un error
    std::cerr << "Error: hay más de un estado inicial." << std::endl;
    exit(1); 
  }
}

void Automata::InsertarSimbolos(const std::string& simbolos) {
  for (char c : simbolos) {
    if (c == '&') { // Error 4: & no puede pertenecer al
      std::cerr << "ERROR:" << std::endl;
      std::cerr << "El carácter & no puede formar parte del alfabeto." << std::endl;
      exit(1);
    }
    if (c != ' ') alfabeto_.insert(c);
  }
}