add_executable(app app.cpp "../glad.c")
target_compile_features(app PRIVATE cxx_std_17)

# target_link_libraries(app PRIVATE ${ASSIMP_LIBRARIES})
target_include_directories(app PUBLIC ${CMAKE_SOURCE_DIR}/lib/irrKlang)

target_link_libraries(app PRIVATE ${ASSIMP_LIBRARIES} ${LIBS})
target_link_libraries(app PUBLIC game engine model generator manager graphics gameplay)
target_link_libraries(app PUBLIC ${ALSA_LIBRARIES})
target_link_libraries(app PUBLIC ${IRRKLANG_LIBRARY})
target_link_libraries(app PRIVATE ${IKPMP3_LIBRARY})

# target_link_libraries(app PRIVATE irrKlang)

# target_link_libraries(app PUBLIC game ${LIBS}) 
# target_link_libraries(app PUBLIC engine)
# target_link_libraries(app PUBLIC model)
# target_link_libraries(app PUBLIC generator)
# target_link_libraries(app PUBLIC manager)
# target_link_libraries(app PUBLIC graphics)
# target_link_libraries(app PUBLIC gameplay)

# target_link_libraries(app PRIVATE ${LIBS})

