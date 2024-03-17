#include <iostream>
#include <SalusEngine.h>

using namespace std;

int main()
{
    SalusEngine *salusEngine = new SalusEngine("shashankp@gmail.com");
    cout << typeid(salusEngine).name() << endl;
    return 0;
}