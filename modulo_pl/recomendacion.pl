
% Es necesario incluir librerias para csv y listas.
:- encoding(utf8).
:- use_module(library(csv)).
:- use_module(library(lists)).


% 1. Crear Hechos que sean dinámicos; es decir, poder
% modificarlos en tiempo de ejecución (assert/retract).
% ------------------------------------------------------------
:- dynamic curso/4.
:- dynamic prerrequisito/2.
:- dynamic historial/3.
:- dynamic interes/2.


% 2. Cargar archivos csv, pasarlo a minusculas y guardar 
% los hechos en memoria
% ------------------------------------------------------------
% limpiar_datos/0: Limpiar los datos de los hechos si los 
% csv se cargan varias veces.
limpiar_datos :-
    retractall(curso(_,_,_,_)),
    retractall(prerrequisito(_,_)),
    retractall(historial(_,_,_)),
    retractall(interes(_,_)).

% normalizar/2: Convierte un atomo/valor leido del csv a 
% minusculas.
normalizar(Valor, Normalizado) :-
    downcase_atom(Valor, Normalizado).


% a_numero/2: csv_read_file convierte los datos que son números a numeros
% en vez de textos.
a_numero(Valor, Valor) :-
    number(Valor), !.
a_numero(Valor, Numero) :-
    atom_number(Valor, Numero).

% cargar_cursos(+Ruta): Lee cursos.csv y crea hechos curso/4.
cargar_cursos(Ruta) :-
    csv_read_file(Ruta, [_Encabezado|Filas], [functor(fila), arity(4)]),
    forall(
        member(fila(Codigo, Nombre, Area, CreditosAtom), Filas),
        (   normalizar(Codigo, CodigoNorm),
            a_numero(CreditosAtom, Creditos),
            assertz(curso(CodigoNorm, Nombre, Area, Creditos))
        )
    ).

% cargar_prerrequisitos(+Ruta): Lee prerrequisitos.csv y crea 
% hechos prerrequisito/2.
cargar_prerrequisitos(Ruta) :-
    csv_read_file(Ruta, [_Encabezado|Filas], [functor(fila), arity(2)]),
    forall(
        member(fila(Curso, Prerreq), Filas),
        (   normalizar(Curso, CursoNorm),
            normalizar(Prerreq, PrerreqNorm),
            assertz(prerrequisito(CursoNorm, PrerreqNorm))
        )
    ).


% cargar_historial(+Ruta):Lee historial.csv y crea hechos 
% historial/3.
cargar_historial(Ruta) :-
    csv_read_file(Ruta, [_Encabezado|Filas], [functor(fila), arity(3)]),
    forall(
        member(fila(Estudiante, Curso, NotaAtom), Filas),
        (   normalizar(Estudiante, EstudianteNorm),
            normalizar(Curso, CursoNorm),
            a_numero(NotaAtom, Nota),
            assertz(historial(EstudianteNorm, CursoNorm, Nota))
        )
    ).


% cargar_intereses(+Ruta): Lee intereses.csv y crea hechos 
%interes/2.
cargar_intereses(Ruta) :-
    csv_read_file(Ruta, [_Encabezado|Filas], [functor(fila), arity(2)]),
    forall(
        member(fila(Estudiante, Area), Filas),
        (   normalizar(Estudiante, EstudianteNorm),
            assertz(interes(EstudianteNorm, Area))
        )
    ).



% cargar_todo(+DirBase): Carga los 4 archivos csv desde un 
% directorio base.
cargar_todo(DirBase) :-
    limpiar_datos,
    atomic_list_concat([DirBase, 'cursos.csv'], Cursos),
    atomic_list_concat([DirBase, 'prerrequisitos.csv'], Prerrequisitos),
    atomic_list_concat([DirBase, 'historial.csv'], Historial),
    atomic_list_concat([DirBase, 'intereses.csv'], Intereses),
    cargar_cursos(Cursos),
    cargar_prerrequisitos(Prerrequisitos),
    cargar_historial(Historial),
    cargar_intereses(Intereses).

% cargar_todo/0: Carga los 4 archivos csv desde el directorio data/ (por defecto).
cargar_todo :-
    cargar_todo('../data/').


% 3. Regla: ¿El estudiante aprobó un curso?
% ------------------------------------------------------------

%Aprobado(Estudiante, Curso): Se aprueba si nota >= 11
aprobado(Estudiante, Curso) :-
    historial(Estudiante, Curso, Nota),
    Nota >= 11.


% desaprobado(Estudiante, Curso): Desaprobado si nota < 11
desaprobado(Estudiante, Curso) :-
    historial(Estudiante, Curso, Nota),
    Nota < 11.


% IMPORTANTE: ya_curso(Estudiante, Curso): Verdadero si ya se 
% llevo el curso (aprobado o no), util para no volver a 
% recomendar cursos ya cursados.
ya_curso(Estudiante, Curso) :-
    historial(Estudiante, Curso, _).


% 4. Regla: ¿Puede un estudiante llevar un curso?
% ------------------------------------------------------------

% puede_llevar(Estudiante, Curso): Verdadero si se puede llevar
%  el curso (no lo llevo antes y cumple los prerrequisitos).
puede_llevar(Estudiante, Curso) :-
    curso(Curso, _, _, _),
    \+ ya_curso(Estudiante, Curso),
    forall(prerrequisito(Curso, Prerreq), aprobado(Estudiante, Prerreq)).


% cumple_prerrequisitos_en_cadena(Estudiante, Curso): Valida los 
% prerrequisitos y los prerrequisitos de prerrequisitos por si un
% curso llegara a depender transitivamente de otro.
cumple_prerrequisitos_en_cadena(_Estudiante, Curso) :-
    \+ prerrequisito(Curso, _), !.
cumple_prerrequisitos_en_cadena(Estudiante, Curso) :-
    forall(
        prerrequisito(Curso, Prerreq),
        (   aprobado(Estudiante, Prerreq),
            cumple_prerrequisitos_en_cadena(Estudiante, Prerreq)
        )
    ).


% 5. Regla: ¿Qué cursos recomendar a un estudiante?
% ------------------------------------------------------------

% recomendar_curso(Estudiante, Cursos): Genera una lista de 
% cursos que el estudiante puede llevar (cumple prerrequisitos).
recomendar_curso(Estudiante, Cursos) :-
    findall(Curso, puede_llevar(Estudiante, Curso), CursosSinOrden),
    sort(CursosSinOrden, Cursos).


% 6. Regla: ¿Qué cursos están bloqueados para un estudiante?
% ------------------------------------------------------------

% bloqueado(Estudiante, Curso) - version "unitaria" (verifica un
% curso puntual), usada como base de la version en lista.
bloqueado(Estudiante, Curso) :-
    curso(Curso, _, _, _),
    \+ ya_curso(Estudiante, Curso),
    prerrequisito(Curso, Prerreq),
    \+ aprobado(Estudiante, Prerreq).


% curso_bloqueado(Estudiante, Cursos): Genera una lista de 
% cursos que el estudiante no puede llevar.
curso_bloqueado(Estudiante, Cursos) :-
    findall(Curso, bloqueado(Estudiante, Curso), CursosSinOrden),
    sort(CursosSinOrden, Cursos).


% 7. Regla: ¿Qué recomendar a un estudiante según sus intereses?
% ------------------------------------------------------------

% recomendar_por_interes(Estudiante, Curso): Verdadero si el
% estudiante tiene un interes en el area del curso y no lo llevo
% antes.
recomendar_por_interes(Estudiante, Curso) :-
    interes(Estudiante, Area),
    curso(Curso, _, Area, _),
    \+ ya_curso(Estudiante, Curso).


% recomendaciones_por_interes(Estudiante, Cursos): Genera una lista
% de cursos que el estudiante está interesado y puede llevar.
recomendaciones_por_interes(Estudiante, Cursos) :-
    findall(Curso, recomendar_por_interes(Estudiante, Curso), CursosSinOrden),
    sort(CursosSinOrden, Cursos).


% 8. Reglas adicionales para consultas de demostración en terminal
% ------------------------------------------------------------

cursos_aprobados(Estudiante, Cursos) :-
    findall(Curso, aprobado(Estudiante, Curso), CursosSinOrden),
    sort(CursosSinOrden, Cursos).

cursos_desaprobados(Estudiante, Cursos) :-
    findall(Curso, desaprobado(Estudiante, Curso), CursosSinOrden),
    sort(CursosSinOrden, Cursos).

promedio_estudiante(Estudiante, Promedio) :-
    findall(Nota, historial(Estudiante, _, Nota), Notas),
    Notas \= [],
    sum_list(Notas, Suma),
    length(Notas, Cantidad),
    Promedio is Suma / Cantidad.


% 9. Reporte logico de estudiante
% ------------------------------------------------------------
nombre_curso(Codigo, Nombre) :-
    curso(Codigo, Nombre, _, _), !.
nombre_curso(Codigo, Codigo).

imprimir_lista_cursos([]) :-
    format("  (ninguno)~n").
imprimir_lista_cursos(Cursos) :-
    Cursos \= [],
    forall(
        member(Codigo, Cursos),
        (   nombre_curso(Codigo, Nombre),
            format("  - ~w (~w)~n", [Codigo, Nombre])
        )
    ).

reporte_estudiante(Estudiante) :-
    format("~n=== Reporte logico: ~w ===~n", [Estudiante]),
    cursos_aprobados(Estudiante, Aprobados),
    format("Cursos aprobados:~n"),
    imprimir_lista_cursos(Aprobados),
    cursos_desaprobados(Estudiante, Desaprobados),
    format("Cursos desaprobados:~n"),
    imprimir_lista_cursos(Desaprobados),
    recomendar_curso(Estudiante, Disponibles),
    format("Cursos que puede llevar (cumple prerrequisitos):~n"),
    imprimir_lista_cursos(Disponibles),
    curso_bloqueado(Estudiante, Bloqueados),
    format("Cursos bloqueados (falta algun prerrequisito):~n"),
    imprimir_lista_cursos(Bloqueados),
    recomendaciones_por_interes(Estudiante, PorInteres),
    format("Cursos recomendados segun intereses:~n"),
    imprimir_lista_cursos(PorInteres),
    format("==============================~n").


% 10. PUNTO DE ENTRADA
% ------------------------------------------------------------
% Ejecucion: swipl -g main -t halt recomendacion.pl
% ------------------------------------------------------------

listar_estudiantes(Estudiantes) :-
    findall(Estudiante, historial(Estudiante, _, _), Todos),
    sort(Todos, Estudiantes).

main :-
    cargar_todo,
    listar_estudiantes(Estudiantes),
    forall(member(Estudiante, Estudiantes), reporte_estudiante(Estudiante)).
