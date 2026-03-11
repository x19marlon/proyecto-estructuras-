#pragma once

#include "Elemento.h"
//Constructor vacio
Elemento::Elemento(){

}
//Constructor con parametros
Elemento::Elemento(std::string tipo, double tam, std::string unidad, double x, double y){
    this->tipoElemento = tipo;
    this->tamano = tam; 
    this->unidadMedida = unidad;
    this->posX = x;
    this->posY = y;
}
//Getters
std::string Elemento::getTipoElemento(){
    return this->tipoElemento;
}
double Elemento::getTamano(){
    return this->tamano;
}
std::string Elemento::getUnidadMedida(){
    return this->unidadMedida;
}
double Elemento::getPosX(){
    return this->posX;
}
double Elemento::getPosY(){
    return this->posY;
}