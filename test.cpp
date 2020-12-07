#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    Node* pParent = this;
    vector<Node*> pChildren;
    int value;
};
struct action
{
    int x;
    int y;
};
int main()
{
    action a = {1, 2};
    cout << a.x << ' ' << a.y;
}