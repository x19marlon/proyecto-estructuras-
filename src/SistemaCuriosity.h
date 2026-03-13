#pragma once

//Librerias
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

//Archivos de definicion 
#include "Comando.h"
#include "Elemento.h"

class SistemaCuriosity{
private:
    //Maejar FIFO para la lectura de comandos
    std::queue<Comando> colaComandos;
    std::vector<Elemento> listaElementos;

public:
    //Constructor
    SistemaCuriosity();
    //Setters
    void setColaComandos(std::queue<Comando> cola);
    void setListaElementos(std::vector<Elemento> lista);
    //Getters
    std::queue<Comando> getColaComandos();
    std::vector<Elemento> getListaElementos();
    //Operaciones para cargar informacion
    void cargarComandos(std::string nombreArchivo);
    void cargarElementos(std::string nombreArchivo);
    //Operaciones para agregar comandos y elementos
    void agregarMovimiento(std::string tipoMov, double magnitud, std::string unidadMed);
    void agregarAnalisis(std::string tipoAnalisis, std::string objeto, std::string comentario);
    void agregarElemento(std::string tipoElemento, double tam, std::string unidadMed, double x, double y);
    //Guardar la informacion en un archivo
    void guardar(std::string tipoArchivo, std::string nombreArchivo);
    //Simular comandos cargados con cordenadas
    void simularComandos(double coordX, double coordY);
};
#include "SistemaCuriosity.hxx"