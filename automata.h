// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Juan Nicolás Becerra Rogatinscaia
// Correo: alu0101743011@ull.edu.es
// Fecha: 21/10/2025
// Descripción Clase Alfabeto:
// Representa un alfabeto que contiene símbolos.
// Verifica si una cadena está formada por los símbolos del alfabeto
// Estructura de datos principal:
// - std::set<char> - almacena símbolos de manera ordenada
// Historial de modificaciones:
// Bug fix 1 - Corregida la llamada de funciones en sobrecargas.
// Bug fix 2 - Añado IsEmpty() para vaciar el alfabeto al añadir uno nuevo.
// Bug fix 3 - ComprobarAlfabetoCadena() verifica que los símbolos de las
//             cadenas existen en el alfabeto

#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <fstream>
#include <set>
#include <string>
#include <vector>

#include "estado.h"

class Automata {
  public:
  Automata() = default; // Constructor por defecto

  // Leer automata
  void Read(std::ifstream& archivo_entrada);
  void LeerCadenas(std::ifstream& archivo_entrada);
  bool ComprobarCadenas(const std::string& cadena);

  private:
    std::set<char> alfabeto_;
    int numero_estados_;
    int estado_inicial_;
    std::vector<Estado> estados_;

    // Get/Set
    std::vector<Estado> GetEstados() const {return estados_;}

    // Push
    void InsertarSimbolos(const std::string& simbolos);

    // Comprobar si hay error
    void UnicoEstadoInicial(const std::string& estados_iniciales);
};

#endif 