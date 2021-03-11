#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <iostream>
using namespace std;

class io_service:private boost::noncopyable
{};

size_t g_count = 0;

template <typename SERVER_PROXY>
class db_connection:private boost::noncopyable
{
private:
	io_service & m_io;
public:
	db_connection( io_service & r_io_ ):m_io( r_io_ )
	{ 
		++g_count;
	}
	~db_connection() 
	{ 
		--g_count; 
	}
	////拷贝构造函数
	//db_connection( db_connection<SERVER_PROXY> const & )
	//{
	//	++g_count;
	//}
	static size_t howmany( ){ return g_count; }
};


//要实现计数，asio_tcp_service该从db_connection继承而来吗
class asio_tcp_service
{
public:
	typedef db_connection <asio_tcp_service> DB_CONNECTION;
	typedef boost::shared_ptr< DB_CONNECTION > DB_CONNECTION_PTR;
	DB_CONNECTION_PTR get_dbPtr( )const
	{ return m_db_newConnection; }

	void handle_accept_cmd( )
	{
		if ( g_count > 5 )
		{
			cout << "overflow" << endl;
			return;
		}
		m_db_newConnection.reset(new DB_CONNECTION( io_service_ ));
		handle_accept_cmd( );
	}
private:
	DB_CONNECTION_PTR m_db_newConnection;
	io_service io_service_;
};

int main( )
{
	asio_tcp_service io;
	io.handle_accept_cmd( );
	cout << io.get_dbPtr()->howmany() << endl;
}