#pragma once

//Librerias
#include <string>
//Implementacion

class Comando{
private:
    //Comando de movimiento o analisis
    std::string tipoComando;
    //Comando de movimiento
    std::string tipoMovimiento; //avanzar, girar
    double magnitud;
    std::string unidadMovimiento; //cm, dm, m, km, grd, rad
    //Comando de analisis
    std::string tipoAnalisis; //fotografiar, composicion, perforar
    std::string objeto;
    std::string comentario;
public:
    //Constructores
    Comando();
    //Comando de Movimiento
    Comando(std::string tipoMov, double magnitud, std::string unidad);
    //Comando de analisis
    Comando(std::string tipoAnalisis, std::string objeto, std::string comentario);
    //Tipo de comando
    std::string getTipoComando();
    //Getters
    std::string getTipoMovimiento();
    double getMagnitud();
    std::string getUnidadMovimiento();
    std::string getTipoAnalisis();
    std::string getObjeto();
    std::string getComentario();
};
#include "Comando.hxx"