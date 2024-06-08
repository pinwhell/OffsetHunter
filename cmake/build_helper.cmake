if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    add_compile_definitions(VBXI_BITS32)
	set (BUILDING_ARCH x86)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_compile_definitions(VBXI_BITS64)
	set (BUILDING_ARCH x64)
endif()

set (BIN_OUTPUT "${CMAKE_SOURCE_DIR}/bin/${BUILDING_ARCH}/${CMAKE_BUILD_TYPE}")