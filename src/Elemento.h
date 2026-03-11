#pragma once

//Librerias
#include <string>
//Implementacion

class Elemento{
private:
    std::string tipoElemento; //roca, crater, monticulo, duna
    double tamano;
    std::string unidadMedida;
    double posX;
    double posY;

public:
    //Constructores
    Elemento();
    Elemento(std::string tipo, double tam, std::string unidad, double x, double y);
    //Getters
    std::string getTipoElemento();
    double getTamano();
    std::string getUnidadMedida();
    double getPosX();
    double getPosY();
};
#include "Elemento.hxx"