add_executable(app app.cpp "../glad.c")
target_compile_features(app PRIVATE cxx_std_17)

target_link_libraries(app PRIVATE ${ASSIMP_LIBRARIES})
target_link_libraries(app PRIVATE ${LIBS})

target_link_libraries(app PUBLIC game)
target_link_libraries(app PUBLIC engine)
target_link_libraries(app PUBLIC model)
target_link_libraries(app PUBLIC generator)
target_link_libraries(app PUBLIC graphics)
target_link_libraries(app PUBLIC gameplay)
target_link_libraries(app PUBLIC manager)

