#include <iostream> // std::cout

// A CRTP base class for Vecs with a size and indexing:
template <typename E>
class VecExpr 
{
public:
	double operator[](int i) const { return static_cast<E const&>(*this)[i]; }
	operator E const&() const { return static_cast<const E&>(*this); } // 向下类型转换
};

// The actual Vec class:
//注意这种手法：父类的模板参数为子类的名字，实现编译器多态
class Vec : public VecExpr<Vec>
{
	double _data[1000];
public:
	double&  operator[](int i) { return _data[i]; }
	double operator[](int i) const { return _data[i]; }
	template <typename E>
	Vec const& operator=(VecExpr<E> const& vec)
	{
		E const& v = vec;
		for (int i = 0; i<1000; ++i) _data[i] = v[i];
		return *this;
	}
	// Constructors
	Vec() { }
	Vec(double v) { for(int i=0; i<1000; ++i) _data[i] = v; }
};

template <typename E1, typename E2>
//注意这种手法：父类的模板参数为子类的名字
class VecDifference : public VecExpr<VecDifference<E1, E2> >
{
	E1 const& _u; E2 const& _v;
public:
	VecDifference(VecExpr<E1> const& u, VecExpr<E2> const& v) : _u(u), _v(v) { }
	double operator[](int i) const { return _u[i] - _v[i]; }
};

template <typename E>
class VecScaled : public VecExpr<VecScaled<E>>
{
	double _alpha; 
	E const& _v;
public:
	VecScaled(double alpha, VecExpr<E> const& v) : _alpha(alpha), _v(v) { }
	double operator[](int i) const { return _alpha * _v[i]; }
};

// Now we can overload operators:
template <typename E1, typename E2> 
VecDifference<E1, E2> const
operator-(VecExpr<E1> const& u, VecExpr<E2> const& v)
{
	return VecDifference<E1, E2>(u, v);
}

template <typename E>
VecScaled<E> const
operator*(double alpha, VecExpr<E> const& v)
{
	return VecScaled<E>(alpha, v);
}

int main9()
{
	Vec u(3), v(1);
	double alpha=9; 
	Vec y;
	y = alpha*(u - v);
	std::cout << y[999] << '\n';

	std::cin.get();
	return 0;
}