#ifndef PIMPL_SAMPLE
#define PIMPL_SAMPLE

#include <string>
#include "boost/scoped_ptr.hpp"

using namespace std;

//Ç°ÖÃÉùÃ÷
struct impl;

class pimpl_sample
{
	//impl * pimpl_;
	boost::scoped_ptr<impl> pimpl_;
public:
	pimpl_sample();
	~pimpl_sample();
	void do_something();
};

#endif
