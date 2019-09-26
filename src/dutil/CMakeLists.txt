CMAKE_MINIMUM_REQUIRED ( VERSION 3.10 )

PROJECT ( "dutil" )

SET ( CMAKE_BUILD_TYPE Debug )
SET ( CMAKE_VERBOSE_MAKEFILE false )

SET ( DUTIL_OUTPUT "dutil" )

SET ( DUTIL_SRC_FILES
	config/config.cpp
	database/excel/excel_conn.cpp
	database/excel/excelformat/basicexcel.cpp
	database/excel/excelformat/excelformat.cpp
	database/mssql/mssql_conn.cpp
	database/mssql/mssql_conn_pool.cpp
	database/mysql/mysql_conn.cpp
	database/mysql/mysql_conn_pool.cpp
	database/mysql/mysql_example.cpp
	database/redis/redis_conn.cpp
	logging/log_manager.cpp
	monitor/system_resource_monitor.cpp
	stdafx.cpp
	)
	
SET ( CMAKE_C_COMPILER "g++" )

INCLUDE_DIRECTORIES (
       	/usr/include/jsoncpp
	../../external_library/cpp_redis/includes
	)

LINK_LIBRARIES (
	pthread
	gcov
	boost_thread
	boost_system
	boost_filesystem
	)

ADD_COMPILE_OPTIONS (
	-g
	-std=c++11
	--coverage
	)

ADD_LIBRARY ( ${DUTIL_OUTPUT} STATIC ${DUTIL_SRC_FILES} )
