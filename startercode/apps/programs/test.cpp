using namespace std;
#include <iostream>

class X
{
public:
    X() = default;
    
    X(X const& other) = default;
    X& operator=(X const& other) = default;
    
    X(X&& other) = default;
    X& operator=(X&& other) = default;
    
    ~X() = default;
};