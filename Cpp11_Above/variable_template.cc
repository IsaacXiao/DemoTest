#include <memory>
#include <iostream>
using namespace std;

int main()
{
    auto i_ptr = std::make_unique<int>(4);
    cout << *i_ptr << endl;
}