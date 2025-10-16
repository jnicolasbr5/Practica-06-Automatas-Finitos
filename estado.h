// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Juan Nicolás Becerra Rogatinscaia
// Correo: alu0101743011@ull.edu.es
// Fecha: 21/10/2025

#ifndef ESTADO_H
#define ESTADO_H

#include <iostream>
#include <map>
#include <set>
#include <vector>


/**
 * @brief Representa un estado de un autómata finito.
 * 
 * Cada estado tiene un número que lo identifica, puede ser un estado de aceptación,
 * contiene el número de transiciones y la estructura de datos de las transiciones.
 * 
 * Estructura de datos principal:
 * - std::multimap<char, int> - almacena las transiciones de cada estado {símbolo, estado}
 */
class Estado {
  public:
  // Constructor por defecto
  Estado() = default; 

  // Algoritmo recursivo
  bool AlgoritmoCadenas(const std::string& cadena, std::vector<Estado>& vec, 
                        const std::set<int>& identificadores, int size, int i = 0);

  // Detección de errores
  void ComprobarSimbolosTransiciones(const std::set<char>& alfabeto) const;
  void ComprobarSimbolosEstados(const std::set<int>& identificadores_estados, int identificador) const;

  // Get
  int GetNumeroIdentificador() const {return numero_identificador_;}

  // Lectura
  void Read(std::istream& is);

  private:
    int numero_identificador_;  
    bool aceptacion_; 
    int numero_transiciones_;
    std::multimap<char, int> transiciones_;
};

std::istream& operator>>(std::istream& is, Estado& est);

#endif