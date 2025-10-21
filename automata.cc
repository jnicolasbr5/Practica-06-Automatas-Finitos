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
#include <set>
#include <sstream>
#include <string>

#include "automata.h"
#include "estado.h"

/**
 * @brief Lee y carga la definición del autómata desde un archivo de entrada
 * 
 * @param archivo_entrada Archivo .fa que contiene los datos del autómata
 */
void Automata::Read(std::ifstream& archivo_entrada) {
  std::string simbolos; // Leo los símbolos
  std::getline(archivo_entrada, simbolos);
  InsertarSimbolos(simbolos);
  archivo_entrada >> numero_estados_; // Leo el número de estados
  archivo_entrada.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Paso a la siguiente linea
  std::string estados_iniciales;
  std::getline(archivo_entrada, estados_iniciales);
  UnicoEstadoInicial(estados_iniciales); // Verifico un único estado inicial, error 1
  Estado state;
  while(archivo_entrada >> state) { // Leo los estados
    state.ComprobarSimbolosTransiciones(alfabeto_); // Comprobar error 3
    estados_.push_back(state);
    identificadores_estados_.insert(state.GetNumeroIdentificador());
  }
  LineaPorEstado(estados_.size(), numero_estados_); // Comprueba error 2
}

/**
 * @brief Lee las cadenas y muestra si son reconocidas o no por el autómata
 * 
 * @param archivo_entrada Archivo .txt que contiene las cadenas
 */
void Automata::LeerCadenas(std::ifstream& archivo_entrada, bool trace) {
  std::string cadena;
  while(std::getline(archivo_entrada, cadena)) {
    std::cout << std::endl;
    std::cout << cadena << " --- " << std::endl;
    if (ComprobarCadenas(cadena, trace)) std::cout << cadena << " - Accepted" << std::endl;
    else std::cout << cadena << " - Rejected" << std::endl;
  }
}

/**
 * @brief Devuelve si la cadena es reconocida o no por el autómata.
 *        Primero verifica que los símbolos forman parte del alfabeto y
 *        posteriormente llama al algoritmo
 * 
 * @param cadena Cadena que analiza el autómata.
 * @return true La cadena es reconocida por el autómata.
 * @return false La cadena no es reconocida por el autómata. 
 */
bool Automata::ComprobarCadenas(const std::string& cadena, bool trace) {
  for (char c : cadena) { // Cadena no coincide con alfabeto
    if (alfabeto_.find(c) == alfabeto_.end()) return false; 
  }
  return estados_[estado_inicial_].AlgoritmoCadenas(cadena, estados_, identificadores_estados_, cadena.size(), trace);
}

/**
 * @brief Comprueba que haya un único estado inicial.
 *        Si hay más de un estado inicial, lanza un error.
 *        Se corresponde con el error 1)
 * 
 * @param estados_iniciales Línea que contiene estados iniciales
 */
void Automata::UnicoEstadoInicial(const std::string& estados_iniciales) {
  std::istringstream ss(estados_iniciales);
  ss >> estado_inicial_; // Leo el estado inicial
  std::string demas;
  if (ss >> demas) { // Error 1: Si hay más de un estado inicial, se lanza un error
    std::cerr << "ERROR:" << std::endl;
    std::cerr << "Hay más de un estado inicial." << std::endl;
    exit(1); 
  }
}

/**
 * @brief Verifica que hay una línea en el fichero por cada estado del autómata.
 *        Se corresponde con el error 2)
 * 
 * @param num_lineas Número de líneas de información de los estados
 * @param num_estados Número de estados del autómata
 */
void Automata::LineaPorEstado(int num_lineas, int num_estados) const {
  if (num_lineas != num_estados) {
    std::cerr << "ERROR:" << std::endl;
    std::cerr << "El número de líneas (" << num_lineas << ") no corresponde "
              << "con el número de estados (" << num_estados << ")." << std::endl;
    std::cerr << "Cada estado debe tener información, aunque no tenga transiciones salientes." << std::endl;
    exit(2);
  }
}

/**
 * @brief Inserta los símbolos en el set<char> alfabeto.
 *        Comprueba que no esté la cadena vacía.
 *        También comprueba el error 4)
 * 
 * @param simbolos Línea que contiene los símbolos
 */
void Automata::InsertarSimbolos(const std::string& simbolos) {
  for (char c : simbolos) {
    if (c == '&') { // Error 4: '&' no puede pertenecer al alfabeto
      std::cerr << "ERROR:" << std::endl;
      std::cerr << "El carácter & no puede formar parte del alfabeto." << std::endl;
      exit(4);
    }
    if (c != ' ') alfabeto_.insert(c);
  }
}