#include <string>
#include <iostream>
#include "boost/tuple/tuple.hpp"

boost::tuples::tuple<int,double> get_values()
{  
    return boost::make_tuple(6,12.0);
}
class base 
{
public:  
    virtual ~base() {}; 
    virtual void test() 
    {    
        std::cout << "base::test()\n"; 
    }
};
class derived : public base 
{
public:  
    virtual void test() { std::cout << "derived::test()\n"; }
};

void main()
{
    // test for constructor
    boost::tuple<int,double,std::string>  triple(42,3.14,"My first tuple!");
    boost::tuple<short,int,long> another;
    boost::tuple<int,int,double> another2(10);

    // test for make_tuple , ref and cref function
    int plain=42;
    int& ref=plain;
    const int& cref=ref;

    boost::tuples::tuple<int> plaint(plain);
    plaint = boost::make_tuple(plain);
    plaint = boost::make_tuple(ref);
    plaint = boost::make_tuple(cref);

    boost::tuples::tuple<int&>     reft(ref);
    boost::make_tuple(boost::ref(plain));
    boost::make_tuple(boost::ref(ref));
    boost::make_tuple(boost::ref(cref));

    boost::tuples::tuple<const int&> creft(cref);
    boost::make_tuple(boost::cref(plain));
    boost::make_tuple(boost::cref(ref));
    boost::make_tuple(boost::cref(cref));


    // test for get function
    boost::tuple<int,double,std::string> triple2(42,3.14,"The amazing tuple!"); 
    int i=boost::tuples::get<0>(triple2);  
    double d=triple2.get<1>(); 
    std::string s=boost::get<2>(triple2);   

    // test for function return tuple
    boost::tuples::tuple<int,double> value = get_values();

    // test for copy constructor 
    boost::tuple<int,std::string,derived> tup1(-5,"Tuples"); 
    boost::tuple<unsigned int,std::string,base> tup2; 
    tup2=tup1;  
    tup2.get<2>().test(); 
    std::cout << "Interesting value: "     << tup2.get<0>() << '\n'; 
    const boost::tuple<double,std::string,base> tup3(tup2);  
    //tup3.get<0>()=3.14; // error, because tup3 is const

    boost::tuples::tuple<int,int,double> tuple1(10,30,20.000);
    int head = tuple1.get_head();
    int tailhead = tuple1.get_tail().get_head();
    double tail = tuple1.get_tail().get_tail().get_head();

    // for TR1
    /*boost::tuples::tuple<double, char, int> tuplesize;    
    std::tr1::tuple_size();
    std::tr1::tuple_element();*/
}