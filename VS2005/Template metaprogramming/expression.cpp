#include <iostream> // std::cout
#include <cmath>    // std::sqrt()

// 表达式类型
class DExprLiteral {                    // 文字量
	double a_;
public:
	DExprLiteral(double a) : a_(a) { }
	double operator()(double x) const { return a_; }
};
class DExprIdentity {                   // 自变量
public:
	double operator()(double x) const { return x; }
};
template<class A, class B, class Op>    // 双目操作
class DBinExprOp {
	A a_; B b_;
public:
	DBinExprOp(const A& a, const B& b) : a_(a), b_(b) { }
	double operator()(double x) const { return Op::apply(a_(x), b_(x)); }
};
template<class A, class Op>             // 单目操作
class DUnaryExprOp {
	A a_;
public:
	DUnaryExprOp(const A& a) : a_(a) { }
	double operator()(double x) const { return Op::apply(a_(x)); }
};
// 表达式
template<class A>
class DExpr {
	A a_;
public:
	DExpr() { }
	DExpr(const A& a) : a_(a) { }
	double operator()(double x) const { return a_(x); }
};

// 运算符，模板参数 A、B 为参与运算的表达式类型
// operator /, division
class DApDiv
{ 
public: 
	static double apply(double a, double b) { return a / b; }
};

//该函数返回值为DExpr类型
template<class A, class B> 
DExpr<DBinExprOp<DExpr<A>, DExpr<B>, DApDiv>> 
operator/(const DExpr<A>& a, const DExpr<B>& b) 
{
	typedef DBinExprOp<DExpr<A>, DExpr<B>, DApDiv> ExprT;
	//模板实例化是由外到内，阅读代码也要由外到内！！
	//调用DExpr的括号操作符double operator()(double x) const { return a_(x); }
	//ExprT(ExprT(a, b))
	//也就是DBinExprOp(DBinExprOp(a,b)) 
	//上面这句的内括号先用a,b构造DBinExprOp，外括号再调用double operator()(double x) const { return Op::apply(a_(x), b_(x)); }，这个DBinExprOp的第一个模板参数为DExpr<A>，第二个模板参数为DExpr<B>，第三个模板参数为DApDiv
	//所以最终会调用DApDiv中的apply函数：static double apply(double a, double b) { return a / b; }对a和b作除法
	return DExpr<ExprT>(ExprT(a, b));
}

// operator +, addition
class DApAdd
{ 
public: 
	static double apply(double a, double b) { return a + b; }
};

template<class A, class B> DExpr<DBinExprOp<DExpr<A>, DExpr<B>, DApAdd>> 
operator+(const DExpr<A>& a, const DExpr<B>& b)
{
	typedef DBinExprOp<DExpr<A>, DExpr<B>, DApAdd> ExprT;
	return DExpr<ExprT>(ExprT(a, b));
}

// sqrt(), square rooting
class DApSqrt
{ 
public: 
	static double apply(double a) { return std::sqrt(a); } 
};

template<class A> DExpr<DUnaryExprOp<DExpr<A>, DApSqrt>>
sqrt(const DExpr<A>& a) 
{
	typedef DUnaryExprOp<DExpr<A>, DApSqrt> ExprT;
	return DExpr<ExprT>(ExprT(a));
}

// operator-, negative sign
class DApNeg 
{ 
public: 
	static double apply(double a) { return -a; } 
};
//注意这个-不是相减操作符，它只有1个参数
template<class A> 
DExpr<DUnaryExprOp<DExpr<A>, DApNeg>>
operator-(const DExpr<A>& a)
{
	typedef DUnaryExprOp<DExpr<A>, DApNeg> ExprT;
	return DExpr<ExprT>(ExprT(a));
}

// evaluate()
template<class Expr>
void evaluate(const DExpr<Expr>& expr, double start, double end, double step)
{
	for(double i=start; i<end; i+=step) std::cout << expr(i) << ' ';
}

int main8()
{
	DExpr<DExprIdentity> x;
	evaluate( -x / sqrt( DExpr<DExprLiteral>(1.0) + x ) , 0.0, 10.0, 1.0 );
	std::cin.get(); return 0;
}