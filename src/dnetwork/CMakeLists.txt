CMAKE_MINIMUM_REQUIRED ( VERSION 3.10 )

PROJECT ( "dnetwork" )

SET ( CMAKE_BUILD_TYPE Debug )
SET ( CMAKE_VERBOSE_MAKEFILE false )

SET ( DNETWORK_OUTPUT "dnetwork" )

SET ( DNETWORK_SRC_FILES
	stdafx.cpp
	server.cpp
	basic_connector.cpp
	basic_socket.cpp
	protocol/base_protocol.cpp
	)

SET ( CMAKE_C_COMPILER "g++" )

INCLUDE_DIRECTORIES (
       	/usr/include/jsoncpp
	../../external_library/cpp_redis/includes
	)

ADD_COMPILE_OPTIONS (
	-g
	-pthread
	-std=c++11
	--coverage
	)

ADD_LIBRARY ( ${DNETWORK_OUTPUT} ${DNETWORK_SRC_FILES} )
