## Requisitos

- [SWI-Prolog](https://www.swi-prolog.org/download/stable) instalado.
  No requiere librerías externas: usa `library(csv)`, incluida por defecto.

## Estructura de carpetas usadas

```
sira_pp/
├── data/
│   ├── cursos.csv
│   ├── prerrequisitos.csv
│   ├── historial.csv
│   └── intereses.csv
└── modulo_pl/
    ├── recomendacion.pl
    └── README_prolog.md
```

El predicado `cargar_todo/0` busca los CSV en `../data/`, **relativo a la
carpeta desde donde se ejecuta `swipl`**. Por eso siempre debes abrir la
terminal dentro de `modulo_pl/` antes de correr el programa.

## Cómo ejecutar
### Opción A: modo automático (recomendado para las capturas del informe)

Desde la carpeta `modulo_pl/`:
```bash
swipl -g main -t halt recomendacion.pl
```


### Opción B: modo interactivo (para probar consultas puntuales)

Desde la carpeta `modulo_pl/`:
```bash
swipl recomendacion.pl
```
Dentro de la consola de Prolog (`?-`), primero carga los datos una vez:
```prolog
?- cargar_todo.
```

Y luego ejecuta las consultas que necesites, por ejemplo:
```prolog
?- aprobado(estudiante1, cs101).
?- puede_llevar(estudiante2, bd101).
?- recomendar_curso(estudiante1, Cursos).
?- curso_bloqueado(estudiante2, Cursos).
?- recomendar_por_interes(estudiante2, Curso).
?- reporte_estudiante(estudiante1).
```
Para salir: `halt.`


## Notas importantes

- Los códigos de curso y de estudiante se normalizan automáticamente a
  minúsculas al cargarlos (ej. `CS101` del CSV se guarda como `cs101`),
  para que las consultas coincidan con los ejemplos del enunciado del
  proyecto.
- Si editas los CSV a mano, verifica que **no quede ninguna línea en
  blanco** al final ni en medio del archivo.
- Si cambias la ubicación de la carpeta `data/`, ajusta la ruta en
  `cargar_todo/0`.

