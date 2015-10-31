#include "Interval.hpp"
#include <cassert>
#include <algorithm>

//using namespace dd;
// *******************************************************************************
// * class IntervalSingle
// *******************************************************************************
// Constructor (with contract verification)
IntervalSingle::IntervalSingle(int limMin, int limMax) :
            m_min{limMin}, m_max{limMax}
{
    assert ((m_min <= m_max)&&"Inversion of the limit");
};

// Intersection of 2 intervals
bool IntervalSingle::intersection (IntervalSingle const& inter)
{
    // 4 cases to be evaluated
    // Case 1: Inter insides *this
    // Case 2: Inter on right of *this
    // case 3: Inter on left of *this
    // Case 4: Inter and *this have no common point
    // case 5: Inter is bigger than *this
    if (belong(inter.m_min)) {
        m_min = inter.m_min;
        if (belong(inter.m_max)) {
            // it is case 1
            m_max = inter.m_max;
        } // end if
        // it is case 2
        return true;
    } else if (belong(inter.m_max)) {
        // it is case 3
        m_max = inter.m_max;
        return true;
    } else if ((m_min >= inter.m_max) || (inter.m_min >= m_max)) {
        // it is case 4
        m_min = 0;
        m_max = 0;
        return (false);
    } //end if
    // it is case 5: no change
    return (true);
}

bool IntervalSingle::reunion (IntervalSingle const& inter)
{
    // 2 cases to be evaluated
    // Case 1: there is no common points between the two interval ==> the result is not one interval!
    // Case 2: There is common point between the two intervals ==> the result is one interval.
    if ((m_min > inter.m_max) || (inter.m_min > m_max)) {
        // It is case 1
        return false;
    } else {
        // it is case 2
        if (m_min > inter.m_min) {
            m_min = inter.m_min;
        } // end if
        if (inter.m_max > m_max) {
            m_max = inter.m_max;
        } // end if
        return true;
    } //end if
}

bool IntervalSingle::belong (int const val)
{
    return ((m_min <= val) && (val < m_max));
}

bool IntervalSingle::operator== (IntervalSingle const& inter) const
{
    return ((m_min == inter.m_min) && (m_max == inter.m_max));
}

bool IntervalSingle::operator< (IntervalSingle const& inter) const
{
    return (m_min < inter.m_min);
}

bool IntervalSingle::isEmpty() const
{
    return (m_min == m_max);
}


// *******************************************************************************
// * Free function: Is it a good idea ?
// *******************************************************************************
IntervalSingle intersection (IntervalSingle const& inter1, IntervalSingle const& inter2)
{
    IntervalSingle inter{inter1};
    inter.intersection (inter2);
    return (inter);
}

// *******************************************************************************
// * class IntervalMultiple
// *******************************************************************************
// Constructor (with contract verification)
IntervalMultiple::IntervalMultiple (int limMin, int limMax)
{
    m_inter.clear();
    IntervalSingle inter{limMin, limMax};
    m_inter.push_back(inter);
}

void IntervalMultiple::intersection (IntervalSingle const& inter)
{
    // For each element of the vectors, realize the intersection with the new interval.
    std::transform(m_inter.begin(), m_inter.end(), m_inter.begin(), [&inter](IntervalSingle interSingle){
        interSingle.intersection (inter);
        return (interSingle);
    });

    // reduce the interval multiple (remove the empty interval)
//    std::vector<IntervalSingle>::iterator it;
//    auto f = std::bind(&IntervalMultiple::isEmpty, this, std::placeholders::_1);
//    it = std::remove_if (m_inter.begin(), m_inter.end(), f);
    auto it = std::remove_if(m_inter.begin(), m_inter.end(), [](IntervalSingle interSingle){
        return (interSingle.isEmpty ());
    });
    m_inter.resize(std::distance(m_inter.begin(),it) );

    // if the multiple interval is empty, add a null interval (refer definition of multiple interval)
    if (m_inter.size() == 0) {
        reunion (IntervalSingle {0,0});
    } // end if

}

void IntervalMultiple::reunion (IntervalSingle const& inter)
{
    // For each interval of the multiple interval, do the reunion with the interval
    bool unionDone {false};
    std::transform(m_inter.begin(), m_inter.end(), m_inter.begin(), [&inter, &unionDone](IntervalSingle interSingle){
        unionDone |= interSingle.reunion (inter);
        return (interSingle);
    });
    // If one or more union have been done
    std::vector<IntervalSingle>::iterator it;
    if (unionDone) {
        // reduce the multiple interval (loop until there is no more intersection between interval)
        do {
            unionDone = false;
            for (size_t i =0; i < m_inter.size()-1; i++) {
                if (m_inter[i].reunion (m_inter[i+1])) {
                    m_inter[i+1] = m_inter[i];
                    unionDone |= true;
                }// end if
            } //end for
            it = std::unique (m_inter.begin(), m_inter.end());
            m_inter.resize( std::distance(m_inter.begin(),it) );
        } while (unionDone);
    } else {
    // if no union have been done
    // add the new interval to the multiple interval
        m_inter.push_back(inter);
        std::sort(m_inter.begin(), m_inter.end());
    }
}
