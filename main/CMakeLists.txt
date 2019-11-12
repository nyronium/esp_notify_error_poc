set(COMPONENT_SRCS
	main.cpp
	application.cpp
	)

set(COMPONENT_ADD_INCLUDEDIRS ".")
#set(COMPONENT_REQUIRES nvs)

register_component()

target_compile_features(${COMPONENT_LIB} PUBLIC cxx_std_20)
target_compile_options(${COMPONENT_LIB} PRIVATE ${PEDANTIC_COMPILE_FLAGS})
target_compile_options(${COMPONENT_LIB} PRIVATE -fdiagnostics-color=always)
