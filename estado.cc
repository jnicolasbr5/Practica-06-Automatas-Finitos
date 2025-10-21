// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Juan Nicolás Becerra Rogatinscaia
// Correo: alu0101743011@ull.edu.es
// Fecha: 21/10/2025

#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "estado.h"

/**
 * @brief Lee los datos desde un flujo de entrada los datos del Estado
 * 
 * @param is Flujo de entrada desde el que se leen los datos
 */
void Estado::Read(std::istream& is) {
  is >> numero_identificador_;
  int aceptacion;
  is >> aceptacion;
  aceptacion_ = (aceptacion == 1); 
  is >> numero_transiciones_;
  transiciones_.clear(); // Reinicializa las transiciones de cada estado
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

/**
 * @brief Algoritmo recursivo que comprueba si una cadena es reconocida por el autómata.
 *        Tiene 2 casos base, uno si la cadena es leída y está en un estado de aceptación (true)
 *        El otro caso base por si la cadena es leída y no está en un estado de aceptación (false)
 *        Junto a los casos base agregué que las transiciones finales puedan ser vacías. 
 *        Posteriormente hay 2 casos recursivos, primero se comprueban las transiciones por
 *        cadenas vacías y después por símbolos del alfabeto.
 *      
 * @param cadena Cadena que reconoce o no el autómata
 * @param vec Vector que almacena los objetos Estado del autómata
 * @param identificadores Vector que almacena los nº identificadores de cada estado
 * @param size Tamaño de la cadena
 * @param i Número de transiciones
 * @return true La cadena no es reconocida por el autómata
 * @return false La cadena no es reconocida por el autómata
 */
bool Estado::AlgoritmoCadenas(const std::string& cadena, std::vector<Estado>& vec, 
                              const std::set<int>& identificadores, int size, bool trace, int i) {
  // Casos base
  if (size == i) {
    if (aceptacion_) return true; // Estado de aceptación
    
    // Comprueba que pueda haber una última transición vacía para llegar al estado de aceptación
    auto par_epsilon = transiciones_.equal_range('&');
    for (auto iterador = par_epsilon.first; iterador != par_epsilon.second; ++iterador) {
      ComprobarSimbolosEstados(identificadores, iterador->second);
      if (vec[iterador->second].AlgoritmoCadenas(cadena, vec, identificadores, size, trace, i))
        return true;
    }
    return false; // No es un estado de aceptación
  }
  std::set<int> conjunto;  

  // Modificacion
  if (trace) {
    std::cout << "\nEstado actual: " << numero_identificador_ << std::endl;
    std::cout << "Símbolo: " << cadena[i] << std::endl;
    std::cout << "Posibles direcciones: " << std::endl;
    for (auto it : transiciones_) {
      std::cout << "(" << it.first << ", " << it.second << ")" << std::endl;
      if (it.first == cadena[i]) conjunto.insert(it.second);
    }
    std::cout << "Conjunto de estados: {";
    for (auto c : conjunto) {
      std::cout <<  c  << ", ";
    }
    std::cout << "}" << std::endl;
  }

  // Transiciones por epsilon, caso recursivo
  auto par_epsilon = transiciones_.equal_range('&');
  for (auto iterador = par_epsilon.first; iterador != par_epsilon.second; iterador++) {
    ComprobarSimbolosEstados(identificadores, iterador->second); // Comprobar error 5
    if (vec[iterador->second].AlgoritmoCadenas(cadena, vec, identificadores, size, trace, i)) {
      return true;
    } 
  }

  // Transiciones por símbolos, caso recursivo
  auto par = transiciones_.equal_range(cadena[i]);
  for (auto iterador = par.first; iterador != par.second; iterador++) {
    ComprobarSimbolosEstados(identificadores, iterador->second); // Comprobar error 5
    if (vec[iterador->second].AlgoritmoCadenas(cadena, vec, identificadores, size, trace, i + 1)) {
      return true; // Cadena reconocida
    } 
  }
  return false; // Cadena no reconocida 
}

/**
 * @brief Comprueba que los símbolos de las transiciones existen en el alfabeto.
 *        Se corresponde con el error 3).
 * 
 * @param alfabeto Set almacena los símbolos del alfabeto
 */
void Estado::ComprobarSimbolosTransiciones(const std::set<char>& alfabeto) const {
  for (const auto& par : transiciones_) { // Itero cada par
    if (par.first != '&') { // La cadena vacía no puede estar en el alfabeto
      if (alfabeto.find(par.first) == alfabeto.end()) { // Si el símbolo no está en el alfabeto, error
        std::cerr << "ERROR:" << std::endl;
        std::cerr << "El símbolo " << par.first << " no forma parte del alfabeto." << std::endl;
        exit(3);
      }
    }
  }
}

/**
 * @brief Comprueba si el estado al que se quiere transitar es parte del autómata. 
 *        Si no lo es, muestra el error y sale del programa.
 *        Se corresponde con el error 5)
 *  
 * @param identificadores Set que almacena los estados del autómata
 * @param estado Estado al que se quiere transitar.
 */
void Estado::ComprobarSimbolosEstados(const std::set<int>& identificadores, int estado) const { // Error 5
  if (identificadores.find(estado) == identificadores.end()) {
    std::cerr << "ERROR: " << std::endl; // Si no existe el estado, muestra error
    std::cerr << "El estado '" << estado << "' al que se quiere transitar no es parte del autómata." << std::endl;
    exit(5);
  }
}

/**
 * @brief Sobrecarga del operador de extracción para leer un objeto Estado por el flujo de entrada
 *        Usa internamente el método Read.
 * 
 * @param is Flujo de entrada 
 * @param est Objeto estado donde se almacenan los datos
 * @return std::istream& Devuelve el flujo de entrada
 */
std::istream& operator>>(std::istream& is, Estado& est) {
  est.Read(is);
  return is;
}