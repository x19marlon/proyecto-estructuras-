# Documento de Diseño — Sistema Curiosity
## Entrega 1: Componente 1 —

---

## 1. Procedimiento Principal

**Nombre:** main (bucle interactivo del sistema)

**Descripción:** Punto de entrada del sistema. Muestra el banner de bienvenida, inicializa el objeto `SistemaCuriosity` y entra en un bucle que lee comandos del usuario línea por línea hasta que se ingrese `salir`.

**Entradas:**
- Línea de texto ingresada por el usuario desde la consola (máximo 300 caracteres)

**Salidas:**
- Prompt del sistema con formato: `usuario $`
- Resultado de cada comando ejecutado impreso en consola

**Condiciones (precondiciones):**
- El sistema operativo debe proveer la variable de entorno `USER`
- El buffer de entrada no debe superar los 300 caracteres por línea

**Condiciones (postcondiciones):**
- Por cada línea ingresada se identifica el comando y se ejecuta la operación correspondiente
- Si el comando no es reconocido, se informa al usuario
- El bucle termina únicamente cuando el usuario ingresa `salir`

**Condiciones de error:**
- Si se ingresa una línea vacía o un comando sin argumentos (distinto de `ayuda` y `salir`), se muestra un mensaje indicando que se use `ayuda`
- Si el número de argumentos no corresponde al comando, se informa el uso correcto

---

## 2. Operaciones Auxiliares (Comandos)

---

### 2.1 `cargar_comandos`

**Nombre:** `SistemaCuriosity::cargarComandos`

**Descripción:** Carga en memoria los comandos de desplazamiento y análisis desde un archivo de texto. Sobreescribe cualquier información previa en la cola de comandos.

**Entradas:**
| Parámetro | Tipo | Descripción |
|---|---|---|
| `nombreArchivo` | `string` | Ruta o nombre del archivo de texto a leer |

**Salidas (consola):**
| Caso | Mensaje |
|---|---|
| Archivo no encontrado | `<nombreArchivo> no se encuentra o no puede leerse.` |
| Archivo vacío o sin comandos válidos | `<nombreArchivo> no contiene comandos.` |
| Línea con formato inválido | `Linea ignorada por formato invalido: <linea>` |
| Línea con tipo desconocido | `Linea ignorada, tipo desconocido: <linea>` |
| Éxito | `n comandos cargados correctamente desde <nombreArchivo>.` |

**Precondiciones:**
- El archivo debe estar accesible en el sistema de archivos
- Cada línea del archivo debe seguir el formato: `tipo_movimiento magnitud unidad` o `tipo_analisis objeto ['comentario']`

**Postcondiciones:**
- La cola de comandos (`colaComandos`) queda con exactamente los comandos válidos leídos del archivo
- Si existían comandos previos en memoria, son eliminados antes de cargar

**Estructura de datos utilizada:** `std::queue<Comando>` (FIFO)

---

### 2.2 `cargar_elementos`

**Nombre:** `SistemaCuriosity::cargarElementos`

**Descripción:** Carga en memoria los puntos de interés del terreno marciano desde un archivo de texto. Sobreescribe cualquier información previa en la lista de elementos.

**Entradas:**
| Parámetro | Tipo | Descripción |
|---|---|---|
| `nombreArchivo` | `string` | Ruta o nombre del archivo de texto a leer |

**Salidas (consola):**
| Caso | Mensaje |
|---|---|
| Archivo no encontrado | `<nombreArchivo> no se encuentra o no puede leerse.` |
| Archivo vacío o sin elementos válidos | `<nombreArchivo> no contiene elementos.` |
| Línea con formato inválido | `Linea ignorada por formato invalido: <linea>` |
| Éxito | `n elementos cargados correctamente desde <nombreArchivo>.` |

**Precondiciones:**
- El archivo debe estar accesible en el sistema de archivos
- Cada línea debe seguir el formato: `tipo_elemento tamaño unidad_medida coordX coordY`

**Postcondiciones:**
- La lista de elementos (`listaElementos`) queda con exactamente los elementos válidos leídos del archivo
- Si existían elementos previos en memoria, son eliminados antes de cargar

**Estructura de datos utilizada:** `std::vector<Elemento>`

---

### 2.3 `agregar_movimiento`

**Nombre:** `agregarMovimiento` (funciones.cxx) → `SistemaCuriosity::agregarMovimiento`

**Descripción:** Valida y agrega un comando de movimiento al final de la cola de comandos.

**Entradas:**
| Parámetro | Tipo | Valores válidos |
|---|---|---|
| `tipoMov` | `string` | `avanzar`, `girar` |
| `magnitud` | `double` | Cualquier número real |
| `unidadMed` | `string` | `cm`, `dm`, `m`, `km` (avanzar) / `grd`, `rad` (girar) |

**Salidas (consola):**
| Caso | Mensaje |
|---|---|
| Tipo inválido | `Formato invalido para el tipo de movimiento: Solo avanzar o girar` |
| Magnitud no numérica | `La magnitud debe ser un numero valido` |
| Unidad inválida para avanzar | `Formato invalido para unidad: Solo cm-dm-m-km` |
| Unidad inválida para girar | `Formato invalido para unidad: Solo grd-rad` |
| Éxito | `El comando de movimiento ha sido agregado exitosamente.` |

**Precondiciones:**
- Los tres parámetros deben estar presentes
- `magnitud` debe ser convertible a `double`

**Postcondiciones:**
- Si todos los datos son válidos, el comando queda al final de `colaComandos` con `tipoComando = "movimiento"`
- Si algún dato es inválido, la cola no se modifica y el programa termina con código 1

---

### 2.4 `agregar_analisis`

**Nombre:** `agregarAnalisis` (funciones.cxx) → `SistemaCuriosity::agregarAnalisis`

**Descripción:** Valida y agrega un comando de análisis al final de la cola de comandos.

**Entradas:**
| Parámetro | Tipo | Valores válidos |
|---|---|---|
| `tipoAna` | `string` | `fotografiar`, `composicion`, `perforar` |
| `objeto` | `string` | Cualquier cadena no vacía |
| `comentario` | `string` | Opcional. Cadena entre comillas simples |

**Salidas (consola):**
| Caso | Mensaje |
|---|---|
| Tipo inválido | `Formato invalido para el tipo de analisis: Solo fotografiar-composicion-perforar` |
| Éxito | `El comando de analisis ha sido agregado exitosamente.` |

**Precondiciones:**
- `tipoAna` y `objeto` son obligatorios
- `comentario` es opcional; si se omite, se almacena como cadena vacía

**Postcondiciones:**
- Si los datos son válidos, el comando queda al final de `colaComandos` con `tipoComando = "analisis"`
- Si el tipo es inválido, la cola no se modifica y el programa termina con código 1

---

### 2.5 `agregar_elemento`

**Nombre:** `agregarElemento` (funciones.cxx) → `SistemaCuriosity::agregarElemento`

**Descripción:** Valida y agrega un punto de interés al final de la lista de elementos.

**Entradas:**
| Parámetro | Tipo | Valores válidos |
|---|---|---|
| `tipoComp` | `string` | `roca`, `crater`, `monticulo`, `duna` |
| `tam` | `double` | Cualquier número real positivo |
| `unidad` | `string` | `cm`, `dm`, `m`, `km` |
| `posX` | `double` | Cualquier número real |
| `posY` | `double` | Cualquier número real |

**Salidas (consola):**
| Caso | Mensaje |
|---|---|
| Tipo inválido | `Formato invalido para el tipo de elemento: Solo roca-crater-monticulo-duna` |
| Tamaño no numérico | `El tamaño debe ser un numero valido` |
| Unidad inválida | `Formato invalido para unidad: Solo cm-dm-m-km` |
| Coordenada X no numérica | `La coordenada X debe ser un numero valido` |
| Coordenada Y no numérica | `La coordenada Y debe ser un numero valido` |
| Éxito | `El elemento ha sido agregado exitosamente.` |

**Precondiciones:**
- Los cinco parámetros deben estar presentes
- `tam`, `posX` y `posY` deben ser convertibles a `double`

**Postcondiciones:**
- Si todos los datos son válidos, el elemento queda al final de `listaElementos`
- Si algún dato es inválido, la lista no se modifica y el programa termina con código 1

---

### 2.6 `guardar`

**Nombre:** `SistemaCuriosity::guardar`

**Descripción:** Guarda en un archivo de texto la información actualmente almacenada en memoria, ya sean comandos o elementos, en el mismo formato en que serían leídos por `cargar_comandos` o `cargar_elementos`.

**Entradas:**
| Parámetro | Tipo | Valores válidos |
|---|---|---|
| `tipoArchivo` | `string` | `comandos`, `elementos` |
| `nombreArchivo` | `string` | Nombre o ruta del archivo destino |

**Salidas (consola):**
| Caso | Mensaje |
|---|---|
| Sin información en memoria | `La informacion requerida no esta almacenada en memoria.` |
| Error al abrir/crear archivo | `Error guardando en <nombreArchivo>.` |
| Tipo de archivo inválido | `Tipo de archivo invalido. Use 'comandos' o 'elementos'.` |
| Éxito | `La informacion ha sido guardada en <nombreArchivo>.` |

**Precondiciones:**
- Debe haber información cargada en memoria previamente (mediante `cargar_comandos`, `cargar_elementos` o los comandos `agregar_*`)
- El sistema debe tener permisos de escritura en la ruta indicada

**Postcondiciones:**
- El archivo queda creado o sobreescrito con la información en memoria
- La información en memoria no se modifica
- Para comandos: cada línea sigue el formato `tipo magnitud unidad` o `tipo objeto "comentario"`
- Para elementos: cada línea sigue el formato `tipo tamaño unidad x y`

---

### 2.7 `simular_comandos`

**Nombre:** `SistemaCuriosity::simularComandos`

**Descripción:** Simula la ejecución de los comandos de movimiento almacenados en memoria a partir de una posición inicial dada, calculando la posición final del robot mediante trigonometría. Los comandos de análisis son ignorados.

**Entradas:**
| Parámetro | Tipo | Descripción |
|---|---|---|
| `coordX` | `double` | Posición inicial del robot en el eje X (en metros) |
| `coordY` | `double` | Posición inicial del robot en el eje Y (en metros) |

**Salidas (consola):**
| Caso | Mensaje |
|---|---|
| Sin comandos en memoria | `La informacion requerida no esta almacenada en memoria.` |
| Éxito | `La simulacion de los comandos, a partir de la posicion (coordX,coordY), deja al robot en la nueva posicion (nuevoX,nuevoY).` |

**Precondiciones:**
- Debe haber al menos un comando de movimiento cargado en memoria
- `coordX` y `coordY` deben ser números reales válidos
- El robot se asume orientado inicialmente hacia la derecha del eje X (ángulo = 0 radianes)

**Postcondiciones:**
- Se imprime la posición final calculada
- La cola de comandos en memoria **no se modifica** (se trabaja sobre una copia)
- Los ángulos positivos producen giro en sentido antihorario; los negativos en sentido horario

**Lógica de cálculo:**
- Todas las distancias se convierten a metros antes de operar
- Todos los ángulos se convierten a radianes antes de operar
- Para `avanzar`: `x += distancia * cos(angulo)` y `y += distancia * sin(angulo)`
- Para `girar`: `angulo += giro`

---
## 3. Funciones Auxiliares

Estas funciones son de uso interno, definidas en `SistemaCuriosity.hxx`, y no forman parte de la interfaz del TAD.

| Función | Entradas | Salida | Descripción |
|---|---|---|---|
| `esMovimientoValido` | tipo: string, magnitud: double, unidad: string | bool | Verifica que el tipo sea `avanzar` o `girar` y que la unidad corresponda al tipo |
| `esAnalisisValido` | tipo: string, objeto: string | bool | Verifica que el tipo sea `fotografiar`, `composicion` o `perforar` y que el objeto no esté vacío |
| `esElementoValido` | tipo: string, tam: double, unidad: string, x: double, y: double, ss: istringstream& | bool | Verifica tipo, unidad y que el stream no haya fallado al leer los valores numéricos |
| `convertirAMetros` | magnitud: double, unidad: string | double | Convierte una distancia a metros según su unidad (`cm`, `dm`, `m`, `km`) |
| `convertirARadianes` | magnitud: double, unidad: string | double | Convierte un ángulo a radianes desde grados (`grd`) o radianes (`rad`) |
