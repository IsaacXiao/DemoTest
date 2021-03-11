#include <string>
#include <iostream>

using namespace std;

class GamePlayer
{
public:
	virtual void KillMonster( ) = 0;
};

class NormalPlayer: public GamePlayer
{
public:
	virtual void KillMonster( ){ cout << "普通玩家手动打怪" << endl; }
};

class ProxyPlayer: public GamePlayer
{
public:
	virtual void KillMonster( )
	{ 
		normal_.KillMonster();
		cout << "代练玩家作弊打Boss" << endl; 
		normal_.KillMonster();
	}
private:
	NormalPlayer normal_;
};

int main2(int argc, char **argv)
{
	GamePlayer * p = new ProxyPlayer;
	p->KillMonster();
	delete p; 

	return 0;
}

