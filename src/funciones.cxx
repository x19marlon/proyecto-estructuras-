#include "SistemaCuriosity.h"
#include <iostream>

void ayuda(std::string complemento){
    if (complemento == ""){
        std::cout << "\n===== SISTEMA CURIOSITY - AYUDA =====\n\n";
        std::cout << "Comandos disponibles:\n\n";
        std::cout << "  cargar_comandos      -> Cargar comandos desde archivo\n";
        std::cout << "  cargar_elementos     -> Cargar elementos del terreno\n";
        std::cout << "  agregar_movimiento   -> Agregar comando de movimiento\n";
        std::cout << "  agregar_analisis     -> Agregar comando de analisis\n";
        std::cout << "  agregar_elemento     -> Agregar punto de interes\n";
        std::cout << "  guardar              -> Guardar informacion en archivo\n";
        std::cout << "  simular_comandos     -> Simular movimientos del robot\n";
        std::cout << "  salir                -> Terminar el programa\n\n";
        std::cout << "Para ver como usar un comando especifico escriba:\n";
        std::cout << "  ./exe ayuda <comando>\n\n";
    }
    else{
        if (complemento == "cargar_comandos"){
            std::cout << "Uso correcto:\n";
            std::cout << "  ./exe cargar_comandos nombre_archivo\n";
        } else if (complemento == "cargar_elementos"){
            std::cout << "Uso correcto:\n";
            std::cout << "  ./exe cargar_elementos nombre_archivo\n";
        } else if (complemento == "agregar_movimiento"){
            std::cout << "Uso correcto:\n";
            std::cout << "  ./exe agregar_movimiento tipo_mov magnitud unidad_med\n";
        } else if (complemento == "agregar_analisis"){
            std::cout << "Uso correcto:\n";
            std::cout << "  ./exe agregar_analisis tipo_analisis objeto comentario\n";
        } else if (complemento == "agregar_elemento"){
            std::cout << "Uso correcto:\n";
            std::cout << "  ./exe agregar_elemento tipo_comp tamaño unidad_med coordX coordY\n";
        } else if (complemento == "guardar"){
            std::cout << "Uso correcto:\n";
            std::cout << "  ./exe guardar tipo_archivo nombre_archivo\n";
        } else if (complemento == "simular_comandos"){
            std::cout << "Uso correcto:\n";
            std::cout << "  ./exe simular_comandos coordX coordY\n";
        } else if (complemento == "salir"){
            std::cout << "Uso correcto:\n";
            std::cout << "  ./exe salir\n";
        }
        else{
            std::cout << "No se reconoce el comando: "<<complemento<<"\n";
            std::cout << "Use \"./exe ayuda\" para ver la lista de comandos.\n";
        }
    }
}