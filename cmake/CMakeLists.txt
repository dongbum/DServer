CMAKE_MINIMUM_REQUIRED ( VERSION 3.10 )

PROJECT ( "LIBRARY_MAKE_TEST" )

SET ( CMAKE_BUILD_TYPE Debug )
SET ( CMAKE_VERBOSE_MAKEFILE false )

SET ( DUTIL_OUTPUT "dutil" )
SET ( DNETWORK_OUTPUT "dnetwork" )

SET ( DUTIL_SRC_FILES
	../src/dutil/config/config.cpp
	../src/dutil/database/excel/excel_conn.cpp
	../src/dutil/database/excel/excelformat/basicexcel.cpp
	../src/dutil/database/excel/excelformat/excelformat.cpp
	../src/dutil/database/mssql/mssql_conn.cpp
	../src/dutil/database/mssql/mssql_conn_pool.cpp
	../src/dutil/database/mysql/mysql_conn.cpp
	../src/dutil/database/mysql/mysql_conn_pool.cpp
	../src/dutil/database/mysql/mysql_example.cpp
	../src/dutil/database/redis/redis_conn.cpp
	../src/dutil/logging/log_manager.cpp
	../src/dutil/monitor/system_resource_monitor.cpp
	../src/dutil/stdafx.cpp
	)

SET ( DNETWORK_SRC_FILES
	../src/dnetwork/stdafx.cpp
	../src/dnetwork/server.cpp
	../src/dnetwork/basic_connector.cpp
	../src/dnetwork/basic_socket.cpp
	../src/dnetwork/protocol/base_protocol.cpp
	)


SET ( CMAKE_C_COMPILER "g++" )

INCLUDE_DIRECTORIES (
       	/usr/include/jsoncpp
	../external_library/cpp_redis/includes
	)

ADD_LIBRARY ( ${DUTIL_OUTPUT} ${DUTIL_SRC_FILES} )
ADD_LIBRARY ( ${DNETWORK_OUTPUT} ${DNETWORK_SRC_FILES} )
