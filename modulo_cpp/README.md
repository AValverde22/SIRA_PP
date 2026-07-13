# Módulo C++ - Sistema SIRA

Este módulo en C++ (estilo imperativo) se encarga de gestionar de forma interactiva el registro y consulta de las notas del historial de los estudiantes, así como de guardar dicha información en archivos CSV para que otros módulos (como el de Haskell o Prolog) puedan utilizarla.

## Requisitos Previos

- Compilador de C++ compatible con el estándar C++14 (por ejemplo, GCC, Clang, o MSVC).
- **CMake** (versión 3.10 o superior recomendada).
- Sistema operativo compatible con comandos básicos del sistema (Windows).

## Instrucciones de Ejecución

Existen dos formas principales de compilar y ejecutar este módulo:

### Opción 1: Usando CMake 

1. Abre tu terminal o línea de comandos.
2. Navega hasta la carpeta del módulo C++:
   ```bash
   cd ruta/a/SIRA_PP/modulo_cpp
   ```
3. Crea un directorio de compilación y entra en él:
   ```bash
   mkdir build
   cd build
   ```
4. Configura el proyecto con CMake:
   ```bash
   cmake ..
   ```
5. Compila el proyecto:
   ```bash
   cmake --build .
   ```
6. Ejecuta el archivo resultante:
   - En Windows: `Debug\modulo_cpp.exe` o `modulo_cpp.exe` (dependiendo del generador).
   - En Linux/Mac: `./modulo_cpp`

### Opción 2: Usando la IDE (CLion, Visual Studio, etc.)(Recomendado)

1. Abre el archivo `CMakeLists.txt` ubicado en la carpeta `modulo_cpp` usando tu IDE preferido.
2. Espera a que la IDE cargue e indexe los archivos del proyecto.
3. Compila el proyecto usando el botón de "Build" o compilar proporcionado por la IDE.
4. Ejecuta el programa utilizando el botón de "Run" o "Play".

## Funcionamiento

Al ejecutar el programa, se cargarán datos de ejemplo de Cursos, Prerrequisitos, Historial e Intereses, y se guardarán automáticamente en archivos CSV en la carpeta `data/` del proyecto.
Luego, se mostrará un menú interactivo con las siguientes opciones:

1. **Registrar nueva nota en historial:** Permite añadir temporalmente en memoria la nota de un curso para un estudiante.
2. **Consultar historial de un estudiante:** Permite visualizar los cursos, las notas, y el estado de aprobación de un estudiante ingresando su ID.
3. **Ver Reporte General del estudiante:** Muestra un resumen del desempeño de un estudiante, incluyendo el promedio, cursos aprobados/desaprobados, y las notas más alta y más baja obtenidas.
4. **Guardar cambios en archivos CSV:** Exporta las modificaciones realizadas en memoria (como nuevas notas) a los archivos CSV.
5. **Salir:** Finaliza la ejecución del programa.
