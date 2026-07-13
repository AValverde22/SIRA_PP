# Sistema SIRA (Sistema de Información y Registro Académico)

Este proyecto implementa el Sistema SIRA, una aplicación de gestión académica desarrollada como parte de un proyecto de programación multiparadigma. El sistema gestiona información relacionada con estudiantes, cursos, prerrequisitos, historiales de notas e intereses de los alumnos.

El proyecto está dividido en distintos módulos, cada uno implementado utilizando un paradigma de programación diferente. Todos los módulos interactúan o comparten información utilizando archivos CSV ubicados en la carpeta `data/`.

## Estructura del Proyecto

El proyecto está organizado en los siguientes directorios principales:

- **`data/`**: Contiene los archivos CSV (`cursos.csv`, `historial.csv`, `intereses.csv`, `prerrequisitos.csv`) que funcionan como la "base de datos" compartida entre los diferentes módulos.
- **`modulo_cpp/`** (Paradigma Imperativo / Orientado a Objetos): Módulo escrito en C++ encargado principalmente de la interacción con el usuario, registro de notas, reportes generales y la inicialización/guardado de los datos en los archivos CSV.
- **`modulo_haskell/`** (Paradigma Funcional): Módulo escrito en Haskell, utilizado para procesar datos, realizar cálculos y filtros sobre la información académica utilizando un enfoque puramente funcional.
- **`modulo_pl/`** (Paradigma Lógico): Módulo escrito en Prolog que permite realizar consultas e inferencias lógicas (por ejemplo, determinar si un estudiante cumple los prerrequisitos para matricularse en un curso o inferir recomendaciones de cursos basadas en intereses).

## Módulos y Ejecución

Cada módulo tiene sus propias instrucciones de compilación y ejecución. Puedes encontrar los detalles dentro de cada directorio:

* [Módulo C++ (modulo_cpp)](modulo_cpp/README.md)
* [Módulo Haskell (modulo_hsakell)](modulo_haskell/README.md)
* [Módulo Prolog (modulo_pl)](modulo_pl/README.md)

## Flujo de Trabajo General

1. El sistema puede iniciar ejecutando el **Módulo C++**, el cual cargará datos iniciales y generará los archivos CSV en la carpeta `data/` si no existen.
2. Desde el módulo de C++ se pueden agregar nuevas notas y guardar los cambios.
3. Los módulos de **Haskell** y **Prolog** pueden entonces leer los archivos CSV actualizados para realizar análisis funcionales y responder consultas lógicas, respectivamente.
