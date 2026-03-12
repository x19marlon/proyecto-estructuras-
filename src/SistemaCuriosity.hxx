#pragma once
#include "SistemaCuriosity.h"
#include <iostream>
//Constructor
SistemaCuriosity::SistemaCuriosity() : colaComandos(), listaElementos() {

}
//Setters
void SistemaCuriosity::setColaComandos(std::queue<Comando> cola){
    this->colaComandos = cola;
}
void SistemaCuriosity::setListaElementos(std::vector<Elemento> lista){
    this->listaElementos = lista;
}
//Getters
std::queue<Comando> SistemaCuriosity::getColaComandos(){
    return this->colaComandos;
}
std::vector<Elemento> SistemaCuriosity::getListaElementos(){
    return this->listaElementos;
}
//Operaciones para cargar informacion
void SistemaCuriosity::cargarComandos(std::string nombreArchivo){
    std::cout<<"Se esta cargando el archivo\n";
}
void SistemaCuriosity::cargarElementos(std::string nombreArchivo){
    std::cout<<"Se esta cargando el archivo\n";
}
//Operaciones para agregar comandos y elementos
void SistemaCuriosity::agregarMovimiento(std::string tipoMov, double magnitud, std::string unidadMed){
    Comando nuevo(tipoMov, magnitud, unidadMed);
    nuevo.setTipoComando("Movimiento");
    colaComandos.push(nuevo);
    std::cout<<"Movimiento añadido exitosamente a la lista de comandos\n";
}
void SistemaCuriosity::agregarAnalisis(std::string tipoAnalisis, std::string objeto, std::string comentario){
    Comando nuevo(tipoAnalisis, objeto, comentario);
    nuevo.setTipoComando("Analisis");
    colaComandos.push(nuevo);
    std::cout<<"Analisis añadido exitosamente a la lista de comandos\n";
}
void SistemaCuriosity::agregarElemento(std::string tipoElemento, double tam, std::string unidadMed, double x, double y){
    Elemento nuevo(tipoElemento, tam, unidadMed, x, y);
    listaElementos.push_back(nuevo);
    std::cout<<"Elemento añadido exitosamente a la lista de elementos\n";

}
//Guardar la informacion en un archivo
void guardar(std::string tipoArchivo, std::string nombreArchivo){

}
//Simular comandos cargados con cordenadas
void simularComandos(double coordX, double coordY){

}