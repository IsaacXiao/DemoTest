
class Mine
{
public:
	DWORD			g_nShowBmp;			//应该显示的图
	DWORD			g_nMineBmp;			//初始化游戏后该单元格的预设图
	const DWORD		g_ndefaultBmp ;		//默认显示图
	DWORD			g_nMineFlag;		//鼠标右键做的标记

	BOOL	m_bMine;					//该单元格是否有雷
	BOOL	m_bSafe;					//是否1个雷都没得
	BOOL	m_bTraveled;				//是否被遍历过
	UINT	num;						
	BOOL	m_bShow;					//是否已经被显示

	Mine();
	void ShowRes();
	void ShowNum();
	void InitMine();
	
protected:
private:
};
