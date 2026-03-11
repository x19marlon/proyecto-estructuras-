#pragma once
#include "Comando.h"

//Constructores
Comando::Comando(){

}
//Comando de Movimiento
Comando::Comando(std::string tipoMov, double magnitud, std::string unidad){
    this->tipoMovimiento = tipoMov;
    this->magnitud = magnitud;
    this->unidadMovimiento = unidad;
}
//Comando de analisis
Comando::Comando(std::string tipoAnalisis, std::string objeto, std::string comentario){
    this->tipoAnalisis = tipoAnalisis;
    this->objeto = objeto;
    this->comentario = comentario;
}
//Tipo de comando
std::string Comando::getTipoComando(){
    return this->tipoComando;
}
void Comando::setTipoComando(std::string tipo){
    this->tipoComando = tipo;
}
//Getters
std::string Comando::getTipoMovimiento(){
    return this->tipoMovimiento;
}
double Comando::getMagnitud(){
    return this->magnitud;
}
std::string Comando::getUnidadMovimiento(){
    return this->unidadMovimiento;
}
std::string Comando::getTipoAnalisis(){
    return this->tipoAnalisis;
}
std::string Comando::getObjeto(){
    return this->objeto;
}
std::string Comando::getComentario(){
    return this->comentario;
}