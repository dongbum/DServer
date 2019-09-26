CMAKE_MINIMUM_REQUIRED ( VERSION 3.10 )

PROJECT ( "DServer" )

SET ( CMAKE_BUILD_TYPE Debug )
SET ( CMAKE_VERBOSE_MAKEFILE false )

SET ( GAMESERVER_OUTPUT "GameServer" )

# SET ( CMAKE_C_COMPILER "g++" )

ADD_SUBDIRECTORY ( src/dutil )
ADD_SUBDIRECTORY ( src/dnetwork )

SET ( GAMESERVER_SRC_FILES
	src/game_server/main.cpp
	src/game_server/game_user.cpp
	src/game_server/game_server.cpp
	src/game_server/protocol/game_protocol.cpp
	src/game_server/protocol/game_protocol_chatting_req.cpp
	src/game_server/protocol/BR_GS/bridge_protocol.cpp
	)

INCLUDE_DIRECTORIES (
	/usr/include/jsoncpp
	external_library/cpp_redis/includes
	external_library/jemalloc/include
	external_library/jsoncpp/include
	)

LINK_DIRECTORIES (
	src/dutil
	src/dnetwork
	)

LINK_LIBRARIES (
	pthread
	boost_thread
	boost_system
	boost_filesystem
	gcov
	dutil
	dnetwork
	)

ADD_COMPILE_OPTIONS (
	-g
	-pthread
	-std=c++11
	--coverage
	)

ADD_EXECUTABLE ( ${GAMESERVER_OUTPUT} ${GAMESERVER_SRC_FILES} )
