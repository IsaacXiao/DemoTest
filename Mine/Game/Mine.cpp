#include "StdAfx.h"
#include "Mine.h"

Mine::Mine():g_nMineBmp(0),m_bShow(FALSE),g_nMineFlag(0),num(0),m_bMine(FALSE),g_ndefaultBmp(0),g_nShowBmp(0),m_bSafe(FALSE),m_bTraveled(FALSE)
{

}

void Mine::ShowRes()
{
	m_bShow = TRUE;
	g_nShowBmp = g_nMineBmp;
}

void Mine::ShowNum()
{
	if (m_bSafe)
	{
		g_nMineBmp = 6;
	}
	else
		g_nMineBmp = 15-num;
}

void Mine::InitMine()
{
	g_nMineBmp = 0;
	m_bShow = FALSE;
	g_nMineFlag = 0;	
	num = 0;
	m_bMine = FALSE;
	m_bSafe = FALSE;
	g_nShowBmp = 0;
	m_bTraveled = FALSE;
}
