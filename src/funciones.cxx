#include "SistemaCuriosity.h"
#include <iostream>
#include <vector>

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
        std::cout << " ayuda <comando>\n\n";
    }
    else{
        if (complemento == "cargar_comandos"){
            std::cout << "Uso correcto:\n";
            std::cout << "  cargar_comandos nombre_archivo\n";
        } else if (complemento == "cargar_elementos"){
            std::cout << "Uso correcto:\n";
            std::cout << "   cargar_elementos nombre_archivo\n";
        } else if (complemento == "agregar_movimiento"){
            std::cout << "Uso correcto:\n";
            std::cout << "   agregar_movimiento tipo_mov magnitud unidad_med\n";
        } else if (complemento == "agregar_analisis"){
            std::cout << "Uso correcto:\n";
            std::cout << "   agregar_analisis tipo_analisis objeto comentario\n";
        } else if (complemento == "agregar_elemento"){
            std::cout << "Uso correcto:\n";
            std::cout << "   agregar_elemento tipo_comp tamaño unidad_med coordX coordY\n";
        } else if (complemento == "guardar"){
            std::cout << "Uso correcto:\n";
            std::cout << "   guardar tipo_archivo nombre_archivo\n";
        } else if (complemento == "simular_comandos"){
            std::cout << "Uso correcto:\n";
            std::cout << "   simular_comandos coordX coordY\n";
        } else if (complemento == "salir"){
            std::cout << "Uso correcto:\n";
            std::cout << "   salir\n";
        }
        else{
            std::cout << "No se reconoce el comando <"<<complemento<<">\n";
            std::cout << "Use \"ayuda\" para ver la lista de comandos.\n";
        }
    }
}
                                                  
bool faltanArgumentos(int argc, std::vector<std::string> argv ){
    std::string arg = argv[0];
    bool flag = true;
    if (arg == "cargar_comandos"){
        if (argc != 2){
            flag = false;
        }
    } else if (arg == "cargar_elementos"){
        if (argc != 2){
            flag = false;
        }
    } else if (arg == "agregar_movimiento"){
        if (argc != 4){
            flag = false;
        }
    } else if (arg == "agregar_analisis"){
        if (argc != 3 && argc != 4){
            flag = false;
        }
    } else if (arg == "agregar_elemento"){
        if (argc != 6){
            flag = false;
        }
    } else if (arg == "guardar"){
        if (argc != 3){
            flag = false;
        }
    } else if (arg == "simular_comandos"){
        if (argc != 3){
            flag = false;
        }
    } else if (arg == "salir"){
        if (argc != 1){
            flag = false;
        }
    } else if (arg == "ayuda"){
        if (argc > 2){
            flag = false;
        }
    }
    return flag;
}
void agregarMovimiento(SistemaCuriosity& curiosity, std::vector<std::string> argv){
    std::string tipoMov = argv[1];
    //Verificar que sea uno de los movimientos aceptados
    if (tipoMov != "avanzar" && tipoMov != "girar"){
        std::cout<<"Formato invalido para el tipo de movimiento: Solo avanzar o girar\n";
        exit(1);
    }
    //Verificar que el casteo de la magnitud sea correcto
    double magnitud;
    try{
        magnitud = std::stod(argv[2]);
    }
    catch (const std::invalid_argument& e){ 
        std::cout << "La magnitud debe ser un numero valido\n";
        exit(1);
    }
    std::string unidad = argv[3];
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

void agregarAnalisis(SistemaCuriosity& curiosity, std::vector<std::string> argv, int argc){
    std::string tipoAna = argv[1];
    //Verificar que sea uno de los movimientos aceptados
    if (tipoAna != "fotografiar" && tipoAna != "composicion" && tipoAna != "perforar"){
        std::cout<<"Formato invalido para el tipo de analisis: Solo fotografiar-composicion-perforar\n";
        exit(1);
    }
    std::string objeto = argv[2];
    //El comando es opcional, si no hay se deja vacio
    std::string comentario = "";
    if (argc == 4){
        comentario = argv[3];
    }
    curiosity.agregarAnalisis(tipoAna, objeto, comentario);
}

void agregarElemento(SistemaCuriosity& curiosity, std::vector<std::string> argv){
    std::string tipoComp = argv[1];
    //Verificar que sea uno de los elementos aceptados
    if (tipoComp != "roca" && tipoComp != "crater" && tipoComp != "monticulo" && tipoComp != "duna"){
        std::cout<<"Formato invalido para el tipo de elemento: Solo roca-crater-monticulo-duna\n";
        exit(1);
    }
    //Verificar que el casteo del tamaño sea correcto
    double tam;
    try {
        tam = std::stod(argv[2]);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "El tamaño debe ser un numero valido\n";
        exit(1);
    }
    std::string unidad = argv[3];
    //Verificar que la unidad sea correcta
    if (unidad != "cm" && unidad != "dm" && unidad != "m" && unidad != "km"){
        std::cout<<"Formato invalido para unidad: Solo cm-dm-m-km\n";
        exit(1);
    }
    //Verificar que el casteo de la coordenada x sea correcto
    double posX;
    try {
        posX = std::stod(argv[4]);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "La coordenada X debe ser un numero valido\n";
        exit(1);
    }
    //Verificar que el casteo de la coordenada y sea correcto
    double posY;
    try {
        posY = std::stod(argv[5]);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "La coordenada Y debe ser un numero valido\n";
        exit(1);
    }
    curiosity.agregarElemento(tipoComp, tam, unidad, posX, posY);
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
    if(comando=="agregar_elemento")  return 5;
    if(comando=="guardar")           return 6;
    if(comando=="simular_comandos")  return 7;
    if (comando=="ayuda")            return -1;
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