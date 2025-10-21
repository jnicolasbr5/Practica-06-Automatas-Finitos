// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Juan Nicolás Becerra Rogatinscaia
// Correo: alu0101743011@ull.edu.es
// Fecha: 21/10/2025

#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <fstream>
#include <set>
#include <string>
#include <vector>

#include "estado.h"

/**
 * @brief Representa un autómata finito.
 * 
 * Contiene el alfabeto de los símbolos con los que se puede transitar, el nº de estados,
 * el estado inicial, un vector que contiene todos los objetos Estado del Automata y
 * un set con los números identificativos de cada estado.
 * 
 * Estructura de datos principal:
 * - std::vector<Estado> - almacena los objetos Estado del autómata.
 * - std::set<int> - almacena los nº identificativos de cada estado.
 */
class Automata {
  public:
  // Constructor por defecto
  Automata() = default; 

  // Leer automata
  void Read(std::ifstream& archivo_entrada);
  void LeerCadenas(std::ifstream& archivo_entrada, bool trace);

  // Cadena reconocida o no por el autómata
  bool ComprobarCadenas(const std::string& cadena, bool trace);
  
  private:
    std::set<char> alfabeto_;
    int numero_estados_;
    int estado_inicial_;
    std::vector<Estado> estados_;
    std::set<int> identificadores_estados_;

    // Get
    std::vector<Estado> GetEstados() const {return estados_;}

    // Push
    void InsertarSimbolos(const std::string& simbolos);

    // Comprobación de errores
    void UnicoEstadoInicial(const std::string& estados_iniciales);
    void LineaPorEstado(int numero_lineas, int numero_estados) const;
};

#endif 