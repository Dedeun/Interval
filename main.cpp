#include <iostream>
#include "Interval.hpp"

//using namespace dd;

void test1_1 (IntervalSingle const& inter1, IntervalSingle const& inter2)
{
    if (inter1 < inter2) {
        std::cout << inter1 << " < " << inter2 << std::endl;
    } else {
        std::cout << inter1 << " > " << inter2 << std::endl;
    } // endif
    std::cout << inter1 << " inter " << inter2 << " = " << intersection (inter1, inter2);
    IntervalSingle interBis {intersection (inter1, inter2)};
    if (interBis.isEmpty ()) {
        std::cout << " (vide)";
    }
    std::cout << std::endl;
    IntervalSingle inter {inter1};
    if (inter.reunion (inter2)) {
        std::cout << inter1 << " union " << inter2 << " = " << inter << std::endl;
    } else {
        std::cout << inter1 << " union " << inter2 << " = (disjoint)" << std::endl;
    } // endif
}

void test1()
{
    IntervalSingle inter0 {};
    std::cout << "Default Interval  : " << inter0 << std::endl;
    IntervalSingle inter1 {-2,2};
    std::cout << "Interval [-2, 2[  : " << inter1 << std::endl;
    IntervalSingle inter2 {-4,0};
    std::cout << "Interval [-4, 0[  : " << inter2 << std::endl;
    IntervalSingle inter3 {0,4};
    std::cout << "Interval [0, 4[  : " << inter3 << std::endl;
    IntervalSingle inter4 {-4,4};
    std::cout << "Interval [-4, 4[ : " << inter4 << std::endl;
    IntervalSingle inter5 {-1,1};
    std::cout << "Interval [-1, 1[ : " << inter5 << std::endl;
    IntervalSingle inter6 {-4,-2};
    std::cout << "Interval [-4, -2[: " << inter6 << std::endl;
    IntervalSingle inter7 {2,4};
    std::cout << "Interval [2, 4[  : " << inter7 << std::endl;
    IntervalSingle inter8 {-5,-3};
    std::cout << "Interval [-5, -3[: " << inter8 << std::endl;
    IntervalSingle inter9 {3,5};
    std::cout << "Interval [3, 5[  : " << inter9 << std::endl;
    test1_1 (inter1, inter2);
    test1_1 (inter1, inter3);
    test1_1 (inter1, inter4);
    test1_1 (inter1, inter5);
    test1_1 (inter1, inter6);
    test1_1 (inter1, inter7);
    test1_1 (inter1, inter8);
    test1_1 (inter1, inter9);
}

void test2 ()
{
    IntervalMultiple mInter (-5,-3);
    std::cout << mInter << std::endl;
    IntervalSingle inter1 {-2,2};
    std::cout << " union: " << inter1 << " = ";
    mInter.reunion(inter1);
    std::cout << mInter << std::endl;
    IntervalSingle inter2 {-10,-8};
    std::cout << " union: " << inter2 << " = ";
    mInter.reunion(inter2);
    std::cout << mInter << std::endl;
    IntervalSingle inter3 {8,10};
     std::cout << " union: " << inter3 << " = ";
   mInter.reunion(inter3);
    std::cout << mInter << std::endl;
    IntervalSingle inter4 {6,8};
    std::cout << " union: " << inter4 << " = ";
    mInter.reunion(inter4);
    std::cout << mInter << std::endl;
    IntervalSingle inter5 {-4,6};
    std::cout << " union: " << inter5 << " = ";
    mInter.reunion(inter5);
    std::cout << mInter << std::endl;
}

void test3 ()
{
    IntervalMultiple mInter (-5,0);
    IntervalSingle inter1 {1,4};
    mInter.reunion(inter1);
    std::cout << mInter << std::endl;
    IntervalSingle inter3 {-10,10};
    std::cout << " Inter: " << inter3 << " = ";
    mInter.intersection(inter3);
    std::cout << mInter << std::endl;
    IntervalSingle inter2 {-2,2};
    std::cout << " Inter: " << inter2 << " = ";
    mInter.intersection(inter2);
    std::cout << mInter << std::endl;
    IntervalSingle inter4 {-10,0};
    std::cout << " Inter: " << inter4 << " = ";
    mInter.intersection(inter4);
    std::cout << mInter << std::endl;
    IntervalSingle inter5 {0,10};
    std::cout << " Inter: " << inter5 << " = ";
    mInter.intersection(inter5);
    std::cout << mInter << std::endl;
}

int main()
{
    std::cout << "**************************" << std::endl;
    std::cout << "* Test \"Interval Single\" *" << std::endl;
    std::cout << "**************************" << std::endl;
    test1();
    // contract test
    // IntervalSingle inter {5,3};

    std::cout << std::endl;
    std::cout << "************************************" << std::endl;
    std::cout << "* Test \"Interval Multiple: Union \" *" << std::endl;
    std::cout << "************************************" << std::endl;
    test2();

    std::cout << std::endl;
    std::cout << "*******************************************" << std::endl;
    std::cout << "* Test \"Interval Multiple: Intersection \" *" << std::endl;
    std::cout << "*******************************************" << std::endl;
    test3();

    return 0;
}
