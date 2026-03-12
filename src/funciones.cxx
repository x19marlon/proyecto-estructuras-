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

bool faltanArgumentos(int argc, char* argv[]){
    std::string arg = argv[1];
    bool flag = true;
    if (arg == "cargar_comandos"){
        if (argc != 3){
            flag = false;
        }
    } else if (arg == "cargar_elementos"){
        if (argc != 3){
            flag = false;
        }
    } else if (arg == "agregar_movimiento"){
        if (argc != 5){
            flag = false;
        }
    } else if (arg == "agregar_analisis"){
        if (argc != 4 && argc != 5){
            flag = false;
        }
    } else if (arg == "agregar_elemento"){
        if (argc != 7){
            flag = false;
        }
    } else if (arg == "guardar"){
        if (argc != 4){
            flag = false;
        }
    } else if (arg == "simular_comandos"){
        if (argc != 4){
            flag = false;
        }
    } else if (arg == "salir"){
        if (argc != 2){
            flag = false;
        }
    } else if (arg == "ayuda"){
        if (argc > 3){
            flag = false;
        }
    }
    return flag;
}
void agregarMovimiento(SistemaCuriosity& curiosity, char* argv[]){
    std::string tipoMov = argv[2];
    //Verificar que sea uno de los movimientos aceptados
    if (tipoMov != "avanzar" && tipoMov != "girar"){
        std::cout<<"Formato invalido para el tipo de movimiento: Solo avanzar o girar\n";
        exit(1);
    }
    //Verificar que el casteo de la magnitud sea correcto
    double magnitud;
    try{
        magnitud = std::stod(argv[3]);
    }
    catch (const std::invalid_argument& e){
        std::cout << "La magnitud debe ser un numero valido\n";
        exit(1);
    }
    std::string unidad = argv[4];
    //Verificar que unidad este entre las posibles para el tipo de movimiento
    if(tipoMov == "avanzar"){
        if (unidad != "cm" && unidad != "dm" && unidad != "m" && unidad != "km"){
            std::cout<<"Formato invalido para unidad: Solo cm-dm-m-km\n";
            exit(1);
        }
    }
    else if(tipoMov == "girar"){
        if (unidad != "grd" && unidad != "rad"){
            std::cout<<"Formato invalido para unidad: Solo grd-rad\n";
            exit(1);
        }
    }
    curiosity.agregarMovimiento(tipoMov, magnitud, unidad);
}

void agregarAnalisis(SistemaCuriosity& curiosity, char* argv[], int argc){
    std::string tipoAna = argv[2];
    //Verificar que sea uno de los movimientos aceptados
    if (tipoAna != "fotografiar" && tipoAna != "composicion" && tipoAna != "perforar"){
        std::cout<<"Formato invalido para el tipo de analisis: Solo fotografiar-composicion-perforar\n";
        exit(1);
    }
    std::string objeto = argv[3];
    //El comando es opcional, si no hay se deja vacio
    std::string comentario = "";
    if (argc == 5){
        comentario = argv[4];
    }
    curiosity.agregarAnalisis(tipoAna, objeto, comentario);
}

void agregarElemento(SistemaCuriosity& curiosity, char* argv[]){
    std::string tipoComp = argv[2];
    //Verificar que sea uno de los elementos aceptados
    if (tipoComp != "roca" && tipoComp != "crater" && tipoComp != "monticulo" && tipoComp != "duna"){
        std::cout<<"Formato invalido para el tipo de elemento: Solo roca-crater-monticulo-duna\n";
        exit(1);
    }
    //Verificar que el casteo del tamaño sea correcto
    double tam;
    try {
        tam = std::stod(argv[3]);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "El tamaño debe ser un numero valido\n";
        exit(1);
    }
    std::string unidad = argv[4];
    //Verificar que la unidad sea correcta
    if (unidad != "cm" && unidad != "dm" && unidad != "m" && unidad != "km"){
        std::cout<<"Formato invalido para unidad: Solo cm-dm-m-km\n";
        exit(1);
    }
    //Verificar que el casteo de la coordenada x sea correcto
    double posX;
    try {
        posX = std::stod(argv[5]);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "La coordenada X debe ser un numero valido\n";
        exit(1);
    }
    //Verificar que el casteo de la coordenada y sea correcto
    double posY;
    try {
        posY = std::stod(argv[6]);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "La coordenada Y debe ser un numero valido\n";
        exit(1);
    }
    curiosity.agregarElemento(tipoComp, tam, unidad, posX, posY);
}