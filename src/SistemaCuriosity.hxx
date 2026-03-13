#pragma once
#include "SistemaCuriosity.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
    std::ifstream archivo(nombreArchivo);

    //Archivo no encontrado
    if (!archivo.is_open()){
        std::cout<< nombreArchivo << "no se encuentra o no puede leerse.\n";
    }

    //Limpiar cola
    while(!colaComandos.empty()) { colaComandos.pop() ;}

    int contador = 0;

    std::string linea;

    while(std::getline(archivo, linea)){
        //Linea vacia
        if(linea.empty()) continue;
        
        //lectura sobre la linea
        std::istringstream ss(linea);
        std::string tipo;
        ss >> tipo;
        
        // comando es de movmiento
        if(tipo == "avanzar" || tipo == "girar"){
            // Un comando de movimiento: tipo magnitud unidad
            double magnitud;
            std::string unidad;

            ss >> magnitud >> unidad;

            Comando nuevo(tipo, magnitud, unidad);
            colaComandos.push(nuevo);

            contador++;

            //para comando de analisis
        } else if (tipo == "fotografiar" || tipo == "composicion" || tipo == "performar") {
            // Un comando de analisis: tipo objeto comentario 
            std::string objeto;
            ss >> objeto;

            // Buscar comentario entre comillas "______"
            std::string comentario = "";
            std::string resto;

            std::getline(ss, resto); // leer el resto de la linea
            size_t inicio = resto.find('"');
            size_t fin = resto.find('"');

            // si se encontraron las dos comillas
            if (inicio != std::string::npos && inicio != fin) {
                //el comentario es el contenido entre las dos
                comentario = resto.substr(inicio + 1, fin - inicio - 1);
            }

            Comando nuevo(tipo, objeto, comentario);
            colaComandos.push(nuevo);

            contador++;
        }
    }

    archivo.close();

    //Archivo vacio
    if(contador == 0) {
        std::cout<< nombreArchivo << " no contiene comandos.\n";
        return;
    }

    std::cout << contador << " comandos cargados correctamente desde " << nombreArchivo << ".\n";

}

void SistemaCuriosity::cargarElementos(std::string nombreArchivo){
    std::ifstream archivo(nombreArchivo);
    
    //Archivo no encontrado
    if (!archivo.is_open()){
        std::cout << nombreArchivo << " no se encuentra o no puede leerse.\n";
        return;
    }
    
    //Limpiar lista
    listaElementos.clear();
    
    int contador = 0;

    std::string linea;
    
    while (std::getline(archivo, linea)){
        //Linea vacia
        if (linea.empty()) continue;
        
        std::istringstream ss(linea);
        std::string tipo, unidad;
        double tam, x, y;
        
        ss >> tipo >> tam >> unidad >> x >> y;
        
        Elemento nuevo(tipo, tam, unidad, x, y);
        listaElementos.push_back(nuevo);
        contador++;
    }
    
    archivo.close();
    
    //Archivo vacio
    if (contador == 0){
        std::cout << nombreArchivo << " no contiene elementos.\n";
        return;
    }
    
    std::cout << contador << " elementos cargados correctamente desde " << nombreArchivo << ".\n";
}

//Operaciones para agregar comandos y elementos
void SistemaCuriosity::agregarMovimiento(std::string tipoMov, double magnitud, std::string unidadMed){
    Comando nuevo(tipoMov, magnitud, unidadMed);
    colaComandos.push(nuevo);
    std::cout<<"El comando de movimiento ha sido agregado exitosamente.\n";
}

void SistemaCuriosity::agregarAnalisis(std::string tipoAnalisis, std::string objeto, std::string comentario){
    Comando nuevo(tipoAnalisis, objeto, comentario);
    colaComandos.push(nuevo);
    std::cout<<"El comando de analisis ha sido agregado exitosamente.\n";
}

void SistemaCuriosity::agregarElemento(std::string tipoElemento, double tam, std::string unidadMed, double x, double y){
    Elemento nuevo(tipoElemento, tam, unidadMed, x, y);
    listaElementos.push_back(nuevo);
    std::cout<<"El elemento ha sido agregado extiosamente.\n";

}

//Guardar la informacion en un archivo
void SistemaCuriosity::guardar(std::string tipoArchivo, std::string nombreArchivo){

}

//Simular comandos cargados con cordenadas
void SistemaCuriosity::simularComandos(double coordX, double coordY){

}