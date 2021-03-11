#include <iostream>  
#include <bitset>  
#include <algorithm>
#include <vector>
using namespace std;

#pragma warning(disable : 4786)

typedef std::string STRING;

template<typename T>
struct DefaultPtrType
{
	typedef T* PtrT;
};

template<typename T, typename CompositeT>
class CreatorTemplate
{
protected:
	STRING path_;
	CompositeT		compos_;
public:
	typedef T ValueT;
	CreatorTemplate( const STRING& path ) : path_( path )
	{
		cout << "CreatorTemplate( const STRING& path )" << endl;
	}
	T Load(){
		return &compos_;
	}
};

template<typename T, typename CompositeT>
class LoadFromLibrary : public CreatorTemplate<T, CompositeT>
{
public:
	LoadFromLibrary( const STRING& path ) : CreatorTemplate<T, CompositeT>( path )
	{
		cout << "LoadFromLibrary( const STRING& path )" << path.c_str() << endl;
	}
	T Load( const STRING& name )
	{
		//检查配置文件，创建对象
		return &compos_;
	}
};

class ISignal
{
public:
	ISignal( ){ /*cout << "ISignal( )" << endl;*/ }
};

class ITransfer
{
public:
	ITransfer( ){ }
};

class SignalComposite : public ISignal
{
public:
	SignalComposite( ){ cout << "SignalComposite( )"<< endl; }
};

/************************************************************************/
/*模板第一个参数是父类(接口类)的指针，第二个参数是该类本身
typedef LoadFromLibrary<ISignal*, SignalComposite>	SignalLoaderT;*/
/************************************************************************/
typedef DefaultPtrType<ISignal>::PtrT	SignalPtrT;
typedef LoadFromLibrary<SignalPtrT, SignalComposite>	SignalLoaderT;

typedef DefaultPtrType<ITransfer>::PtrT	TransferPtrT;
typedef LoadFromLibrary<TransferPtrT, int>			TransferLoaderT;

template<typename SigCreatorT>
class Assembly
{
	typedef typename SigCreatorT::ValueT SigT;
	struct InnerHelper
	{
		SigT Sig;
	};
	public:
		struct InnerHelper ptrs_;
};

template<typename LoadT,typename ComLoadT>
struct RelationHelper
{
	int operator()( const STRING& name, LoadT& loader, ComLoadT com_loader )
	{
		int count = 0;
		typename LoadT::ValueT pto = loader.Load( name );
		
 		return count;		
	}
};

enum FRAMWORK_PART{ PROTOCOL = 0, TRANSFER, BROADCAST, SIGNAL, LOGGER, PT_TABLE, PTO_TRANSFER, BRD_TRANSFER, SIG_TRANSFER };

int GetRelationModuleCount(  FRAMWORK_PART part, const char* name, FRAMWORK_PART relation_part )
{
	SignalLoaderT sig_loader_( "E:\\BackUp\\Visual Studio 2005\\Projects\\InterDtxy\\Debug\\signal" );
	TransferLoaderT com_loader_( "E:\\BackUp\\Visual Studio 2005\\Projects\\InterDtxy\\Debug\\transfer" );
	return RelationHelper<SignalLoaderT,TransferLoaderT>()( name, sig_loader_, com_loader_ );
}

int main()
{
// 	cout << "构造Facade_c..." << endl;
// 	cout << "构造AssemblyT..." << endl;
// 	SignalLoaderT sig_loader_( "D:\\代码\\WorkSpace\\InterDtxy\\debug\\signal" );
// 	
// 	Assembly<SignalLoaderT> assembly_;
// 	//把sig_creator的地址保存到Assembly类中的ISignal指针Sig中*/
// 	assembly_.ptrs_.Sig = sig_loader_.Load();

	GetRelationModuleCount( SIGNAL, "udp_signal", SIG_TRANSFER );
	
	return 0;
}
