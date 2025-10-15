// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Diseño e implementación de un simulador de autómatas finitos
// Autor: Juan Nicolás Becerra Rogatinscaia
// Correo: alu0101743011@ull.edu.es
// Fecha: 21/10/2025
// Archivo cya-P06.cc: programa cliente.
// Función main del proyecto:
// Usa las clases Alfabeto, Cadena y Lenguaje para:
// Leer datos por un archivo de entrada, realizar las operaciones
// deseadas, y escribir los resultados en un archivo de salida.
// Referencias:
// Map -> https://en.cppreference.com/w/cpp/containerr/map.html
// Multimap -> https://learn.microsoft.com/es-es/cpp/standard-library/multimap-class?view=msvc-170
// Find (Multimap) -> https://cplusplus.com/reference/map/multimap/find/
// Historial de revisiones:
// Main -> https://github.com/jnicolasbr5/Practica-02-Cadenas-y-lenguajes
// 14/10/2025 - Creación (primera versión) del código 
// -> https://github.com/jnicolasbr5/Practica-02-Cadenas-y-lenguajes/tree/dia1
// 15/10/2025 - Segunda versión del código -> 
// https://github.com/jnicolasbr5/Practica-02-Cadenas-y-lenguajes/tree/dia2
// 20/09/2025 - Tercera versión del código -> 
// https://github.com/jnicolasbr5/Practica-02-Cadenas-y-lenguajes/tree/dia3
// ./p02_strings filein.txt fileout.txt codigo_operacion


// DOXYGEN

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "automata.h"
#include "estado.h"

void MostrarError() {
  std::cerr << "Modo de empleo: ./p06_automata_simulator input.fa input.txt" << std::endl;
  std::cerr << "Pruebe 'p06_automata_simulator --help' para más información." << std::endl;
  exit(1);
}

void MostrarAyuda() {
  std::cout << std::endl;
  exit(0);
}

int main(int argc, char* argv[]) {
  if (argc == 2 && std::string(argv[1]) == "--help") MostrarAyuda();
  else if (argc != 3) MostrarError();
  std::ifstream archivo_entrada(argv[1]);
  if (!archivo_entrada.is_open()) MostrarError();
  std::ifstream archivo_entrada_cadenas(argv[2]);
  if (!archivo_entrada_cadenas.is_open()) MostrarError();
  Automata nfa;
  nfa.Read(archivo_entrada);
  nfa.LeerCadenas(archivo_entrada_cadenas);
  return 0;
}