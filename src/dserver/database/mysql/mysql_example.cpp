/*
#include "dserver/database/mysql/mysql_conn.h"
#include "dserver/database/mysql/mysql_conn_pool.h"
*/

/*
// MySQL 커넥션풀 테스트
int32_t thread_count = 4;
std::shared_ptr<MySQLConnPool> pool;

pool = std::shared_ptr<MySQLConnPool>(new MySQLConnPool(thread_count));
pool->Init();

std::shared_ptr<MySQLConn> conn = pool->GetMySQLConn();
conn->PrepareQuery("SELECT 19830419");
conn->Execute();

while (conn->Fetch())
{
int32_t a = conn->GetInt();

std::cout << a << std::endl;
}
*/

/*
// MySQL 커넥션 테스트
MysqlConn conn;
conn.Connect();
conn.PrepareQuery("SELECT 19830419");
conn.Execute();

if (conn.Fetch())
{
std::cout << conn.GetInt() << std::endl;
}

conn.Disconnect();
return 0;
*/