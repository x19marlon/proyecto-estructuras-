#include "SistemaCuriosity.h"
#include "funciones.cxx"
#include <iostream>

int main(int argc, char* argv[]){
    if (argc < 2){
        std::cout<<"Ingrese un argumento, utilice el comando ayuda"<<std::endl;
        return 1;
    }
    std::string arg = argv[1];
    if (arg == "ayuda"){
        if (argc >= 3){
            ayuda(argv[2]);
        } else{
            ayuda("");
        }
    }
}