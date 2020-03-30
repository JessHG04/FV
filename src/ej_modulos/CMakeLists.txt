#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/mimodulo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mimodulo2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mojon.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cuadradoD.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cuadradoI.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Enemigo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lara.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/bala.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

