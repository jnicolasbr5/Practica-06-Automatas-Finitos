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
// Referencias:
// Map -> https://en.cppreference.com/w/cpp/containerr/map.html
// Multimap -> https://learn.microsoft.com/es-es/cpp/standard-library/multimap-class?view=msvc-170
// Find (Multimap) -> https://cplusplus.com/reference/map/multimap/find/
// Historial de revisiones:
// 14/10/2025 - Creación (primera versión) del código
// 15/10/2025 - Segunda versión del código -> 
// https://github.com/jnicolasbr5/Practica-06-Automatas-Finitos/tree/dia2
// 16/10/2025 - Tercera versión del código -> 
// https://github.com/jnicolasbr5/Practica-06-Automatas-Finitos/tree/dia3
// 17/10/2025 - Cuarta versión del código -> 
// https://github.com/jnicolasbr5/Practica-06-Automatas-Finitos/tree/dia4
// Ejecución: ./p06_automata_simulator entrada2.fa entrada.txt

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "automata.h"
#include "estado.h"

/**
 * @brief Muestra error por número de argumentos o archivos
 */
void MostrarError(int i = 0) {
  if (i) std::cerr << "ERROR: Archivos" << std::endl;
  else std::cerr << "ERROR: Argumentos" << std::endl;
  std::cerr << "Modo de empleo: ./p06_automata_simulator input.fa input.txt" << std::endl;
  std::cerr << "Pruebe 'p06_automata_simulator --help' para más información." << std::endl;
  exit(1);
}

/**
 * @brief Muestra la ayuda y modo de uso del simulador de autómatas.
 *
 */
void MostrarAyuda() {
  std::cout << "  ---Diseño e implementación de un simulador de autómatas finitos---" << std::endl;
  std::cout << "Modo de uso: ./p06_automata_simulator <input.fa> <input.txt>" << std::endl;
  std::cout << "  <input.fa>   Archivo con la definición del autómata." << std::endl;
  std::cout << "  <input.txt>  Archivo con las cadenas de entrada." << std::endl;
  exit(0);
}
 

/**
 * @brief Función principal que ejecuta el simulador de autómatas.
 * 
 * Recibe como argumentos un archivo .fa con la definición del autómata y
 * otro .txt con las cadenas de entrada.
 * 
 * 1.- Comprueba los argumentos de entrada y muestra ayuda o error si son incorrectos.
 * 2.- Abre los archivos de entrada, y si no puede muestra un error.
 * 3.- Crea un objeto Automata y lo lee desde el archivo .fa
 * 4.- Lee las cadenas de entrada y las procesa.
 * 
 * @param argc Número de argumentos, debe ser 3
 * @param argv Array de cadenas con los argumentos del programa
 * @return Devuelve 0 si la ejecución es correcta 
 */
int main(int argc, char* argv[]) {
  if (argc == 2 && std::string(argv[1]) == "--help") MostrarAyuda();
  else if (argc != 3) MostrarError();
  std::ifstream archivo_entrada(argv[1]);
  if (!archivo_entrada.is_open()) MostrarError(1);
  std::ifstream archivo_entrada_cadenas(argv[2]);
  if (!archivo_entrada_cadenas.is_open()) MostrarError(1);
  Automata nfa;
  nfa.Read(archivo_entrada);
  nfa.LeerCadenas(archivo_entrada_cadenas);
  return 0;
}