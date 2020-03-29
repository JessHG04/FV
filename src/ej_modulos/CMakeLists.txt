#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/mimodulo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mimodulo2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Juego.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Jugador.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/spritePersonaje.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Guerrera.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Mago.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Proyectil.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Menu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Map.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyxml2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Enemigo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Darkrai.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/AnimationDarkrai.cpp"

)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

