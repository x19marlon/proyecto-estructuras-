#include "SistemaCuriosity.h"
#include "funciones.cxx"
#include <iostream>

int main(int argc, char* argv[]){
    //En el caso que solo se ingrese el nombre del ejecutable
    if (argc < 2){
        std::cout<<"Ingrese un argumento, utilice el comando ayuda"<<std::endl;
        return 1;
    }
    std::string arg = argv[1];
    //Revisa que se ingrese el numero correcto de argumentos para cada comando
    bool completos = faltanArgumentos(argc, argv);
    SistemaCuriosity curiosity;
    if (!completos){
        std::cout<<"No se cumplen con el numero de argumentos esperados para "<<arg<<std::endl;
        return 1;
    }
    //Comando ayuda simple o con comando
    else if (arg == "ayuda"){
        if (argc >= 3){
            ayuda(argv[2]);
        } else{
            ayuda("");
        }
    }
    else if (arg == "cargar_comandos"){
        std::string nombreArchivo = argv[2];
        curiosity.cargarComandos(nombreArchivo);
    } else if (arg == "cargar_elementos"){
        std::string nombreArchivo = argv[2];
        curiosity.cargarElementos(nombreArchivo);
    } else if (arg == "agregar_movimiento"){
        agregarMovimiento(curiosity, argv);
    } else if (arg == "agregar_analisis"){
        agregarAnalisis(curiosity, argv, argc);
    } else if (arg == "agregar_elemento"){
        agregarElemento(curiosity, argv);
    } else if (arg == "guardar"){
        
    } else if (arg == "simular_comandos"){
        
    } else if (arg == "salir"){
        exit (0);
    } else{
        std::cout << "No se reconoce el comando"<<arg<<"\n";
        return 1;
    }
    return 0;
}