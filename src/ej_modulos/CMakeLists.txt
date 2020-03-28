#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
"${CMAKE_CURRENT_SOURCE_DIR}/AnimationDarkrai.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Enemigo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Darkrai.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

