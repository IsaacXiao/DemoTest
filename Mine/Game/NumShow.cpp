
#include "StdAfx.h"
#include "NumShow.h"

#define OFFSET 11

NumShow::NumShow( UINT low, UINT medium, UINT high )
{
	m_uNumPos[0] = OFFSET - high;
	m_uNumPos[1] = OFFSET - medium;
	m_uNumPos[2] = OFFSET - low;
}

UINT NumShow::operator [](const UINT i)const
{
	return m_uNumPos[i];
}

NumShow& NumShow::operator --()
{
	if ( m_uNumPos[2] != 11 )	//低位不为0
	{
		m_uNumPos[2]++;
	} 
	else
	{
		m_uNumPos[2] = 2;		//低位变为9
		m_uNumPos[1]++;
	}
	
	return *this;
}

NumShow& NumShow::operator ++()
{
	if ( m_uNumPos[2] != 2 )	//低位不为9
	{
		m_uNumPos[2]--;
	} 
	else
	{
// 		m_uNumPos[2] = 11;		//低位变为0
// 		m_uNumPos[1]--;
		if ( m_uNumPos[1] != 2 )	//中位不为9
		{
			m_uNumPos[1]--;
			m_uNumPos[2] = 11;
		} 
		else
		{
			m_uNumPos[2] = 11;
			m_uNumPos[1] = 11;		//中位变为0
			m_uNumPos[0]--;
		}
	}

	//时间的3位数显示为999时未作处理，懒得搞了

	return *this;
}