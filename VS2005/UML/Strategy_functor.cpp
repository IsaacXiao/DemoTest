#include <string>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
using namespace std;

namespace
{
#if 0
	struct Discount
	{
		virtual void Price( ) = 0;
	};
	
	struct discA: public Discount
	{
		virtual void Price( ) 
		{ 
			cout << "策略A（0.8折）" << endl;
		}
	};
	
	struct discB: public Discount
	{
		virtual void Price( ) 
		{ 
			cout << "策略B（消费满200，返券100）" << endl;
		}
	};
#endif

	void OrdinaryPolicy( ) 
	{ 
		cout << "原价不打折" << endl;
	}

	void DiscountPolicy( double discount ) 
	{ 
		cout << "策略A:\t" << discount << "折" << endl;
	}

	void RebatePolicy( int reach, int ret ) 
	{ 
		cout << "策略B:\t消费满 " << reach << "返现" << ret << endl;
	}

	//更换优惠策略只需增加新的函数即可，在客户端(main函数)中做切换

	typedef boost::function<void()> FunctorPolicy;
	
	class Store
	{
	private:
		FunctorPolicy accept_cash;
	public:
		Store( FunctorPolicy & fp ): accept_cash( fp ){ }
		//为了兼容带参数的函数对象，需把形参类型做成模板
		template<typename FP>
		void SetPolicy( FP & fp )
		{
			accept_cash = fp;
		}
		void Sale( )
		{
			if ( accept_cash )
			{
				accept_cash();
			}
		}
	};
}

int main_strategy( )
{
	FunctorPolicy ordinaryPolicy(&OrdinaryPolicy);
	Store store( ordinaryPolicy );
	store.Sale( );
	
	store.SetPolicy( boost::bind(&DiscountPolicy, 0.8) );
	store.Sale( );

	store.SetPolicy( boost::bind(&RebatePolicy, 300, 30) );
	store.Sale( );

	return 0;
}

