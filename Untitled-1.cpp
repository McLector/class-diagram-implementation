#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> v1 = {1,2,3,4};

    v1.push_back(6);
    cout<<v1[4];    
    cout<<v1.capacity();



    return 0;
}