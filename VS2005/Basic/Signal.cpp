#include <iostream>
using namespace std;

typedef std::string STRING;
typedef short SHORT;

struct EPPackage
{
	int	PackageId;
};

template<typename T>
struct DefaultPtrType
{
	typedef T* PtrT;
};

class ILogger
{

};

template<typename T, typename LogT>
class ITransfer
{

};

template<typename T,typename LogT,typename TransferT>
class ISignal
{
protected:
	TransferT		comm_;
	LogT			log_;
	long			failure_at_;	
};

typedef DefaultPtrType<EPPackage>::PtrT EPPackagePtrT;

typedef ILogger	LogT;
typedef DefaultPtrType<LogT>::PtrT	LogPtrT;

typedef ITransfer< EPPackagePtrT, LogPtrT >	TransferT;
typedef DefaultPtrType<TransferT>::PtrT	TransferPtrT;

typedef ISignal< EPPackagePtrT, LogPtrT, TransferPtrT> SignalT;

template<typename WinSocketT>
class SendUdpHelper
{
public:
	SendUdpHelper( WinSocketT win_socket ) : win_socket_( win_socket ){}
private:
	WinSocketT win_socket_;
};

template<typename SendHelperT, typename ThreadTraitsT>
class SendUdpPackage
{
private:
	SendHelperT helper_;
public:
	SendUdpPackage( SendHelperT helper ) : helper_( helper ){}
};

template<typename PointTraitsT>
class UdpPackageHelper
{
	typedef typename PointTraitsT::DataType DataType;
public:
	UdpPackageHelper( SHORT sn ) : sn_( sn ), package_id_( 0 ), point_max_( 198 )	
	{					
	}
private:
	SHORT sn_;
	int   point_max_;
	SHORT package_id_;
};

struct FPointTraits{
	typedef float DataType;
	//点ID，点值，时间，状态
};

struct APointTraits{
	typedef long DataType;
	//点ID，点值，时间，状态
};

template<typename SendT>
class UdpSendService
{
private:
	typedef UdpPackageHelper<FPointTraits> FPointHelperT;
	typedef UdpPackageHelper<APointTraits> APointHelperT;
	//typedef Functor<PUCHAR, LOKI_TYPELIST_1( SHORT& )> ActionT;
	//std::vector<ActionT> actions_;
	FPointHelperT fpoints_;
	APointHelperT apoints_;
	std::size_t	index_;
	SendT send_;
public:
	UdpSendService( SHORT sn, SendT send ) : fpoints_( sn ), apoints_( sn ), send_( send ) 
	{
		/*actions_.push_back( ActionT( &fpoints_, &FPointHelperT::GenPackage ) );
		actions_.push_back( ActionT( &apoints_, &APointHelperT::GenPackage ) );*/
	}
};

struct SingleThreadTraits{};

class UdpSignal : public SignalT
{
private:
	typedef SendUdpHelper<TransferPtrT>								SendHelperT;
	///single_thread
	typedef SendUdpPackage<SendHelperT*, SingleThreadTraits>		SendT;	
	typedef UdpSendService<SendT*>									SendServiceT;

	SendHelperT		send_helper_;
	SendT			send_;
	SendServiceT	send_service_;
public:
	UdpSignal() : send_helper_( comm_ ), send_( &send_helper_), send_service_( 64, &send_ ) 
	{		
	}
};

int main( )
{
	UdpSignal * m_pUdpSignal = new UdpSignal();
	
	return 0;
}
