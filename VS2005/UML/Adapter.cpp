#include <string>
#include <iostream>

using namespace std;

class Player
{
public:
	virtual void Attack( ) = 0;
};

class Centor: public Player
{
public:
	virtual void Attack()
	{
		cout << "中场球员进攻" << endl;
	}
};

class Back: public Player
{
public:
	virtual void Attack()
	{
		cout << "后场球员进攻" << endl;
	}
};

class Translator: public Player
{
private:
	Player * m_player;
public:
	Translator( Player * p_centor ):m_player( p_centor ){ }
	virtual void Attack()
	{
		cout << "翻译教练的命令：" << endl;
		m_player->Attack();
	}
};

int main3(int argc, char **argv)
{
	Centor cent;
	Translator trans( &cent );
	trans.Attack();

	Back back;
	trans = Translator( &back );
	trans.Attack();
	
	return 0;
}

