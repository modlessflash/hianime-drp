cmake_minimum_required(VERSION 3.11)
project("hianime-drp")

set(LIBS discord-rpc)

add_subdirectory("discord-rpc")

add_executable(hianime-drp main.cpp)
foreach(LIB ${LIBS})
	target_link_libraries(hianime-drp ${LIB})
endforeach()






