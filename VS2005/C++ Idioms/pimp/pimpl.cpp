#include "pimpl.h"
#include <iostream>
#include "impl.h"

pimpl_sample::pimpl_sample():pimpl_(new impl)
{
	pimpl_->s_ = "This is the pimpl idiom";
}

pimpl_sample::~pimpl_sample()
{
	//delete pimpl_;
}

void pimpl_sample::do_something()
{
	//scoped_ptr源码中拷贝构造与赋值运算符声明为私有且无实现
	//boost::scoped_ptr<impl> another(pimpl_);
	//boost::scoped_ptr<impl> another = pimpl_;
	//需要拷贝与赋值的话，需要手动定义与实现在impl里
	//像调用：pimpl_->Copy

	pimpl_->do_something();
}

