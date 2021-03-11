// 类型过滤，meta_filter 使用时只用一个参数，设置四个模板参数是因为，模板通例的参数列表
// 必须能够包含特例参数列表，后面三个参数设置默认值为 void 或标签模板
template<typename T> 
class dummy_template_1 {};

template<typename T0, typename T1> 
class dummy_template_2 {};

template
<typename T0, 
typename T1 = void,
template<typename> 
class tmp_1 = dummy_template_1,
template<typename, typename> 
class tmp_2 = dummy_template_2>
class meta_filter
{ // 通例，不改变类型
public:
	typedef T0 ret_type;
};

//偏特化的meta_filter
// 匹配任何带有一个类型参数模板的实例，将模板实例替换为代表实例
template<template<typename> class tmp_1, typename T>
class meta_filter<tmp_1<T>, void, dummy_template_1, dummy_template_2>
{
public:
	typedef tmp_1<int> ret_type;
};

// 匹配任何带有两个类型参数模板的实例，将模板实例替换为代表实例
template<template<typename, typename> class tmp_2, typename T0, typename T1>
class meta_filter<tmp_2<T0, T1>, void, dummy_template_1, dummy_template_2> 
{
public:
	typedef tmp_2<int, int> ret_type;
};