#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

class Str
{
public:
    char *str;
    Str(const char value[])
    {
        cout<<"Constructor..."<<endl;
        str = NULL;
        int len = strlen(value);
        str = (char *)malloc(len + 1);
        memset(str,0,len + 1);
        strcpy(str,value);
    }
    Str(const Str &s)
    {
        cout<<"Copy Constructor..."<<endl;
        str = NULL;
        int len = strlen(s.str);
        str = (char *)malloc(len + 1);
        memset(str,0,len + 1);
        strcpy(str,s.str);
    }
    /* Str(Str &&s)
    {
        cout<<"Move Constructor..."<<endl;
        str = NULL;
        str = s.str;
        s.str = NULL;
    } */
    ~Str()
    {
        cout<<"Destructor"<<endl;
        if(str != NULL)
        {
            free(str);
            str = NULL;
        }
    }
};

int main()
{
    // int && ir1 = 42;
    // int && ir2 = ir1;    //错误，无法将右值绑定到左值！注意ir1写到等号右边是左值！

    constexpr char value[] = "I love zx";
    Str s(value);
    vector<Str> vs;
    vs.push_back(move(s));//move doesn't move!!
    //vs.push_back(s);
    cout<<vs[0].str<<endl;
    if(s.str != NULL)
        cout<<s.str<<endl;
    return 0;
}