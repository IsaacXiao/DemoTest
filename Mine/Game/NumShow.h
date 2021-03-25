
class NumShow
{
public:
	UINT	m_uNumPos[3];
	NumShow( UINT low, UINT medium, UINT high );
	UINT		operator[](const UINT i)const;
	//注意这样写是重载的前自增和自减
	NumShow&	operator++();
	NumShow&	operator--();					
};
