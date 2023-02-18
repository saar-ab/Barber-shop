

#ifndef discount_h
#define discount_h
#include "discount.h"

using namespace std;

int applyDiscount(int total)
{
    int points;
    cout << "Do you have points with us? (press 0 if none) ";
    cin >> points;
    if (points >= 10)
    {
        total = total - (total * 0.1);
    }
    return total;
    
}


#endif /* discount_h */
