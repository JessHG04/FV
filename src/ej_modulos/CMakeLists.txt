#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Menu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Juego.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Jugador.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/spritePersonaje.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Guerrera.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Mago.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Proyectil.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Map.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyxml2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Enemigo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Darkrai.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/AnimationDarkrai.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lara.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mojon.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cuadradoI.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cuadradoD.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/bala.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/AnimationKinder.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/KinderSorpresa.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Portal.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MenuSeleccionPersonaje.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Interfaz.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Boss.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/PersonajeBoss.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/PersonajeNPC.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/PoderTrueno.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SpriteBoss.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SpriteNPC.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SpriteTrueno.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Trueno.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/NPC.cpp"
    
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

