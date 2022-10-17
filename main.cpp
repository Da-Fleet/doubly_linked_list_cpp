#include "doubly_linkedlist.cpp"
#include <iostream>

using namespace std;

int main()
{
    vector<int> numsv = {1, 2, 3, 4, 5, 7, 8, 9, 10};
    LinkedList<int> nums(numsv);
    nums.Print();
    return 0;
}