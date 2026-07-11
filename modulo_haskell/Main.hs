type Registro = (String, String, Int)

separar_texto :: Char -> String -> [String]
separar_texto _ [] = [""]

separar_texto s (x:xs)
    | x == s = "" : separar_texto s xs
    | otherwise =
        let primeraParte : resto = separar_texto s xs
        in (x : primeraParte) : resto



convertir :: String -> Registro
convertir linea =
    case separar_texto ',' linea of
        [nombreEstudiante, curso, notaTexto] ->  (nombreEstudiante, curso, read notaTexto)
        _ -> ("", "", 0)


procesarHistorial :: String -> [Registro]
procesarHistorial contenido =
    map convertir (drop 1 (lines contenido))

obtenerHistorial :: String -> [Registro] -> [Registro]
obtenerHistorial nombre registros =
    filter (\(estudiante, _, _) -> estudiante == nombre) registros

calcularPromedio :: [Registro] -> Double
calcularPromedio [] = 0

calcularPromedio registros =
    fromIntegral (sum (map (\(_, _, nota) -> nota) registros))
    / fromIntegral (length registros)

obtenerAprobados :: [Registro] -> [Registro]
obtenerAprobados registros =
    filter (\(_, _, nota) -> nota >= 11) registros

obtenerDesaprobados :: [Registro] -> [Registro]
obtenerDesaprobados registros =
    filter (\(_, _, nota) -> nota < 11) registros

clasificarRendimiento :: Double -> String
clasificarRendimiento promedio
    | promedio >= 16 = "Alto"
    | promedio >= 13 = "Medio"
    | otherwise = "Bajo"

generarRecomendacion :: Double -> String
generarRecomendacion promedio
    | promedio >= 16 =
        "El estudiante tiene un muy buen rendimiento y si quiere puede llevar cursos de mayor dificultad."
    | promedio >= 13 =
        "El estudiante tiene un rendimiento medio y eso está bien pero se le recomienda mejorar un poco sus hábitos de estudio y si puede llevar un  curso avanzado."
    | otherwise =
        "El estudiante tiene un rendimiento bajo y se le recomienda reforzar los cursos base antes de llevar cursos avanzados."

obtenerCodigos :: [Registro] -> [String]
obtenerCodigos registros =
    map (\(_, curso, _) -> curso) registros

unirCursos :: [String] -> String
unirCursos [] = "Ninguno"
unirCursos [curso] = curso
unirCursos (curso:resto) =  curso ++ ", " ++ unirCursos resto

redondear :: Double -> Double
redondear numero = fromIntegral (round (numero * 100)) / 100

mostrarResumen :: String -> [Registro] -> IO ()
mostrarResumen nombre registros = do
    let historial = obtenerHistorial nombre registros

    if null historial
        then putStrLn "No se encontro historial para ese estudiante."
        else do
            let promedio = calcularPromedio historial
                aprobados = obtenerAprobados historial
                desaprobados = obtenerDesaprobados historial

            putStrLn ("----RESUMEN DEL ESTUDIANTE-----")
            putStrLn ("Estudiante: " ++ nombre)
            putStrLn ("Promedio: " ++ show (redondear promedio))
            putStrLn ("Cursos aprobados: " ++ unirCursos (obtenerCodigos aprobados))
            putStrLn ("Cursos desaprobados: " ++ unirCursos (obtenerCodigos desaprobados))
            putStrLn ("Cantidad de cursos aprobados: " ++ show (length aprobados))
            putStrLn ("Cantidad de cursos desaprobados: " ++ show (length desaprobados))
            putStrLn ("Rendimiento: " ++ clasificarRendimiento promedio)
            putStrLn ("Recomendacion: " ++ generarRecomendacion promedio)

main :: IO ()
main = do
    contenido <- readFile "data/historial.csv"

    let registros = procesarHistorial contenido

    putStrLn "Ingrese el nombre del estudiante:"
    nombre <- getLine

    mostrarResumen nombre registros
