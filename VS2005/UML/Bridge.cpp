#include <string>
#include <iostream>
#include <boost/shared_ptr.hpp> 

using namespace std;

class Color
{
public:
	virtual void Fill( ) = 0;
};

class Red: public Color
{
public:
	virtual void Fill( ) { cout << "fill red" << endl; }
};

class Green: public Color
{
public:
	virtual void Fill( ) { cout << "fill Green" << endl; }
};

class Shape
{
protected:
	boost::shared_ptr<Color> m_col;
public:
	Shape( boost::shared_ptr<Color> pColor ):m_col( pColor ){ }
	virtual void FillColor( ) = 0;
};

class Rectangle: public Shape
{
public:
	Rectangle( boost::shared_ptr<Color> pColor ):Shape( pColor ){ }
	virtual void FillColor( )
	{
		cout << "Rectangle:" << endl;
		m_col->Fill( );
	}
};

class Triangle: public Shape
{
public:
	Triangle( boost::shared_ptr<Color> pColor ):Shape( pColor ){ }
	virtual void FillColor( )
	{
		cout << "Triangle:" << endl;
		m_col->Fill( );
	}
};

int main4(int argc, char **argv)
{
	boost::shared_ptr<Color> pRed( new Red );
	boost::shared_ptr<Color> pGreen( new Green );

	boost::shared_ptr<Shape> pRectangle( new Rectangle( pRed ) );
	boost::shared_ptr<Shape> pTriangle( new Triangle( pGreen ) );

	pRectangle->FillColor();
	pTriangle->FillColor();

	pRectangle.reset( new Rectangle( pGreen ) );
	pRectangle->FillColor();

	return 0;
}


