#include <iostream>
using namespace std;

template<typename T, typename CharT>
T AToAny( const CharT* data)
{
	T result = 0;
	if( data == NULL )
		return result;

	CharT* ptr = (CharT*)(&result);
	for( int i = 0; i < sizeof(T) ; ++i)
		ptr[i] = data[i];
	return result;
}

int main( )
{
	int i = 4;
	unsigned char * data = (unsigned char *)&i;

	float FValue_ = AToAny<float>(data); 

	cout << FValue_ << endl;

	return 0;
}
