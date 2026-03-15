#include "SistemaCuriosity.h"
#include "funciones.cxx"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>



const std::string green("\033[38;2;0;255;0m");const std::string yellow("\033[38;2;255;255;0m");
const std::string celeste("\033[38;2;0;255;255m");
const std::string black("\033[38;2;0;0;0m");
const std::string reset("\033[0m");
char* usuario= getenv("USER");

void separarPalabras(std::vector<std::string>  &palabras, char * linea);
int obtenerComando(std::string comando);
double obtenerCoordenadas(std::string cord);

int main(int argc, char* argv[]){

std::cout<<" ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄"<<std::endl;                                                
std::cout<<green<<"      ░██████  ░██     ░██ ░█████████  ░██████  ░██████     ░██████   ░██████░██████████░██     ░██"<<std::endl; 
std::cout<<"     ░██   ░██ ░██     ░██ ░██     ░██   ░██   ░██   ░██   ░██   ░██    ░██      ░██     ░██   ░██"<<std::endl; 
std::cout<<"    ░██        ░██     ░██ ░██     ░██   ░██  ░██     ░██ ░██           ░██      ░██      ░██ ░██"<<std::endl; 
std::cout<<"    ░██        ░██     ░██ ░█████████    ░██  ░██     ░██  ░████████    ░██      ░██       ░████"<<std::endl; 
std::cout<<"    ░██        ░██     ░██ ░██   ░██     ░██  ░██     ░██         ░██   ░██      ░██        ░██"<<std::endl; 
std::cout<<"     ░██   ░██  ░██   ░██  ░██    ░██    ░██   ░██   ░██   ░██   ░██    ░██      ░██        ░██"<<std::endl;     
std::cout<<"      ░██████    ░██████   ░██     ░██ ░██████  ░██████     ░██████   ░██████    ░██        ░██ "<<reset<<std::endl;

std::cout<<" ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄"<<std::endl;                                                
                                        
                                        
                                        
                                        
                     
                                                                                                                                                       
char* linea;                                                                        
bool doing=true;
do{
    
    SistemaCuriosity curiosity;
    std::vector<std::string> palabras;
    palabras.clear();
    linea = new char[300];
    std::cout<<celeste<<usuario<<yellow<<" $:";
    std::cin.getline(linea,300);

    //llamar a cadena de palabras

    separarPalabras(palabras,linea);
    if(palabras.size()>1){
    int opcion=obtenerComando(palabras[0]);
    std::string nombreArchivo = palabras[2];
    double coordX, coordY;

    //llamar a cade
    //coger comando 
    switch (opcion) {
        
        // cargar comandos
        case 1:
        curiosity.cargarComandos(nombreArchivo);
        break;
        //cargar elementos
        case 2:
        curiosity.cargarElementos(nombreArchivo);
        break;
        //agregar_movimiento
        case 3:
        agregarMovimiento(curiosity, argv);
        break;   
        // agregar analisis
        case 4:
        agregarAnalisis(curiosity, argv, argc);
        // agregar elemento
        break;
        case 5:
        agregarElemento(curiosity, argv);
        break;
        //guardar 
        case 6:{
        std::string tipoArchivo = argv[1];
        std::string nombreArchivo = argv[2];
        curiosity.guardar(tipoArchivo, nombreArchivo);
        //simular comandos
        break;}
        case 7:
        coordX=obtenerCoordenadas(palabras[1]);
        coordY=obtenerCoordenadas(palabras[2]);
        curiosity.simularComandos(coordX, coordY);
        break;
    }
    }
    else  std::cout<<"Ingrese un argumento, utilice el comando ayuda"<<std::endl;
    //ayuda
    if (palabras[0] == "ayuda"){
        if (palabras.size() >= 2){
            ayuda(palabras[1]);
        } else{
            ayuda("");
        }
    }

    //salir
     if (palabras[0] == "salir"){
       doing =false;
    }
}while(doing);

                                                                                                
    
    
    return 0;
}

void separarPalabras(std::vector<std::string>  &palabras, char * linea){
    
    std::stringstream ss(linea);
    std::string palabra;

    while (ss >> palabra) {
        palabras.push_back(palabra);
    }
}

int obtenerComando(std::string comando){

   
    //     std::cout << "No se reconoce el comando"<<arg<<"\n";
    //     return 1;
    if(comando=="cargar_comandos")   return 1;
    if(comando=="cargar_elementos")  return 2;
    if(comando=="agregar_movimiento")return 3;
    if(comando=="agregar_analisis")  return 4;
    if(comando=="agregar_elementos") return 5;
    if(comando=="guardar")           return 6;
    if(comando=="simular_comandos")  return 7;

    return 0;
}

double obtenerCoordenadas(std::string cord){
    double coordenada;
    try { //string to double, usar try y catch para evitar errores por el tipo de dato
           coordenada=std::stod(cord);
        } catch (const std::invalid_argument& e) {
            std::cout<<"Las coordenadas deben ser numeros validos.\n";
        }
    return coordenada;
}