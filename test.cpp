#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> a;
    a.push_back(11);
    a.push_back(2);
    a.erase(1);
    cout << a[0];
}