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
                                        
                                        
                                        
                                        
                     
                SistemaCuriosity curiosity;
                                                                                                                                       
char* linea;                                                                        
bool doing=true;
do{
    
    std::vector<std::string> palabras;
    palabras.clear();
    linea = new char[300];
    std::cout<<celeste<<usuario<<yellow<<" $";
    std::cin.getline(linea,300);

    //llamar a cadena de palabras

    separarPalabras(palabras,linea);

    if(!palabras.empty() && palabras[0]=="salir")
        doing=false;
    //ayuda
    if (palabras[0] == "ayuda"){
        if (palabras.size() >= 2){
            ayuda(palabras[1]);
        } else{
            ayuda("");
        }
        }
    if (palabras.size() < 2) {
        if (!palabras.empty() && palabras[0]!="ayuda" && palabras[0]!="salir") {
            std::cout<<"Ingrese un argumento válido, utilice el comando ayuda"<<std::endl;
            }  
        }
      

    if(palabras.size()>1){
    int opcion=obtenerComando(palabras[0]);
    double coordX, coordY;

    //llamar a cade
    //coger comando 
    switch (opcion) {
        
        // cargar comandos
        case 1:{
        std::string nombreArchivo = palabras[1];
        curiosity.cargarComandos(nombreArchivo);
        break;}
        //cargar elementos
        case 2:{
        std::string nombreArchivo = palabras[1];
        curiosity.cargarElementos(nombreArchivo);
        break;}
        //agregar_movimiento
        case 3:
        agregarMovimiento(curiosity, palabras);
        break;   
        // agregar analisis
        case 4:
        agregarAnalisis(curiosity, palabras, palabras.size()-1);
        // agregar elemento
        break;
        case 5:
        agregarElemento(curiosity, palabras);
        break;
        //guardar 
        case 6:{
        std::string tipoArchivo = palabras[1];
        std::string nombreArchivo = palabras[2];
        curiosity.guardar(tipoArchivo, nombreArchivo);
        //simular comandos
        break;}
        case 7:
        coordX=obtenerCoordenadas(palabras[1]);
        coordY=obtenerCoordenadas(palabras[2]);
        curiosity.simularComandos(coordX, coordY);
        break;
        case 0:
            std::cout << "No se reconoce el comando< "<<palabras[0]<<">\n";
        break;
    }
    }
    
delete [] linea;
}while(doing);
    return 0;
}
