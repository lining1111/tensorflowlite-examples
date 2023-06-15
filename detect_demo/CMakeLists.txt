#foreach (src_dir src)
#    aux_source_directory(${src_dir} SRC_FILES)
#endforeach (src_dir)
#add_executable(hello_world ${SRC_FILES})
#target_link_libraries(hello_world ${LIBS})

add_executable(detect_demo main.cpp)
target_link_libraries(detect_demo ${LIBS})