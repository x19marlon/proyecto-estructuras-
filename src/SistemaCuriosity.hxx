#pragma once
#include "SistemaCuriosity.h"
//Operaciones para cargar informacion
void cargarComandos(std::string nombreArchivo){

}
void cargarElementos(std::string nombreArchivo){

}
//Operaciones para agregar comandos y elementos
void SistemaCuriosity::agregarMovimiento(std::string tipoMov, double magnitud, std::string unidadMed){
    Comando nuevo(tipoMov, magnitud, unidadMed);
    nuevo.setTipoComando("Movimiento");
    colaComandos.push(nuevo);
}
void SistemaCuriosity::agregarAnalisis(std::string tipoAnalisis, std::string objeto, std::string comentario){
    Comando nuevo(tipoAnalisis, objeto, comentario);
    nuevo.setTipoComando("Analisis");
    colaComandos.push(nuevo);
}
void SistemaCuriosity::agregarElemento(std::string tipoElemento, double tam, std::string unidadMed, double x, double y){
    Elemento nuevo(tipoElemento, tam, unidadMed, x, y);
    listaElementos.push_back(nuevo);
}
//Guardar la informacion en un archivo
void guardar(std::string tipoArchivo, std::string nombreArchivo){

}
//Simular comandos cargados con cordenadas
void simularComandos(double coordX, double coordY){

}