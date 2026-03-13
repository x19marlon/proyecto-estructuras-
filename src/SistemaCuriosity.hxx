#pragma once
#include "SistemaCuriosity.h"
#include <iostream>
#include <fstream>
#include <sstream>

// firmas de funciones auxiliares
bool esMovimientoValido(std::string tipo, double magnitud, std::string unidad);
bool esAnalisisValido(std::string tipo, std::string objeto);
bool esElementoValido(std::string tipo, double tam, std::string unidad, double x, double y, std::istringstream& ss);

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

            //ignorar linea si no cumple el formato
            if (!esMovimientoValido(tipo, magnitud, unidad)){
                std::cout << "Linea ignorada por formato invalido: " << linea << "\n";
                continue;
            }

            Comando nuevo(tipo, magnitud, unidad);
            colaComandos.push(nuevo);

            contador++;

            //para comando de analisis
        } else if (tipo == "fotografiar" || tipo == "composicion" || tipo == "perforar") {
            // Un comando de analisis: tipo objeto comentario 
            std::string objeto;
            ss >> objeto;

            //ignorar linea si no cumple el formato
            if (!esAnalisisValido(tipo, objeto)){
                std::cout << "Linea ignorada por formato invalido: " << linea << "\n";
                continue;
            }

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

        } else {
            //si es otro tipo
            std::cout << "Linea ignorada, tipo desconocido: " << linea << "\n";
            continue;
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
        
        if (!esElementoValido(tipo, tam, unidad, x, y, ss)){
            std::cout << "Linea ignorada por formato invalido: " << linea << "\n";
            continue;
        }

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
    
    if (tipoArchivo == "comandos"){

        // Verificar que haya comandos en memoria
        if (colaComandos.empty()){
            std::cout << "La informacion requerida no esta almacenada en memoria.\n";
            return;
        }

        std::ofstream archivo(nombreArchivo);
        if (!archivo.is_open()){
            std::cout << "Error guardando en " << nombreArchivo << ".\n";
            return;
        }

        // Copiar la cola para no destruirla al recorrerla
        std::queue<Comando> copia = colaComandos;
        while (!copia.empty()){
            Comando c = copia.front();
            copia.pop();

            if (c.getTipoComando() == "movimiento"){
                archivo << c.getTipoMovimiento() << " " << c.getMagnitud() << " " << c.getUnidadMovimiento() << "\n";
            } else if (c.getTipoComando() == "analisis"){
                archivo << c.getTipoAnalisis() << " "<< c.getObjeto();
                
                if (c.getComentario() != ""){
                    archivo << ' "' << c.getComentario() << '"';
                }
                archivo << "\n";
            }
        }

        archivo.close();
        std::cout << "La informacion ha sido guardada en " << nombreArchivo << ".\n";

    } else if (tipoArchivo == "elementos"){
        // Verificar que haya elementos en memoria
        if (listaElementos.empty()){
            std::cout << "La informacion requerida no esta almacenada en memoria.\n";
            return;
        }

        std::ofstream archivo(nombreArchivo);
        if (!archivo.is_open()){
            std::cout << "Error guardando en " << nombreArchivo << ".\n";
            return;
        }

        for (int i = 0; i < listaElementos.size(); i++){
            Elemento e = listaElementos[i];
            archivo << e.getTipoElemento() << " "
                    << e.getTamano() << " "
                    << e.getUnidadMedida() << " "
                    << e.getPosX() << " "
                    << e.getPosY() << "\n";
        }

        archivo.close();
        std::cout << "La informacion ha sido guardada en " << nombreArchivo << ".\n";

    } else {
        std::cout << "Tipo de archivo invalido. Use 'comandos' o 'elementos'.\n";
    }
}

//Simular comandos cargados con cordenadas
void SistemaCuriosity::simularComandos(double coordX, double coordY){

}


// Funciones auxiliares
// Validar un comando de movimiento
bool esMovimientoValido(std::string tipo, double magnitud, std::string unidad){
    if (tipo != "avanzar" && tipo != "girar") return false;

    if (tipo == "avanzar"){
        if (unidad != "cm" && unidad != "dm" && unidad != "m" && unidad != "km") return false;
    }
    else if (tipo == "girar"){
        if (unidad != "grd" && unidad != "rad") return false;
    }
    return true;
}

// Validar un comando de analisis
bool esAnalisisValido(std::string tipo, std::string objeto){
    if (tipo != "fotografiar" && tipo != "composicion" && tipo != "perforar") return false;

    if (objeto.empty()) return false;
    return true;
}

//Validar comando de elemento
bool esElementoValido(std::string tipo, double tam, std::string unidad, double x, double y, std::istringstream& ss){
    // Verificar tipo
    if (tipo != "roca" && tipo != "crater" && tipo != "monticulo" && tipo != "duna") return false;
    // Verificar unidad
    if (unidad != "cm" && unidad != "dm" && unidad != "m" && unidad != "km") return false;
    // Verificar que el stream no haya fallado (tam, x, y son numeros validos)
    if (ss.fail()) return false;
    return true;
}