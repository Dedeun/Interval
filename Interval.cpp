#include "Interval.hpp"
#include <cassert>
#include <algorithm>

//using namespace dd;

IntervalSingle::IntervalSingle(int limMin, int limMax) :
            m_min{limMin}, m_max{limMax}
{
    assert ((m_min <= m_max)&&"Inversion of the limit");
};

bool IntervalSingle::intersection (IntervalSingle const& inter)
{
    if (belong(inter.m_min)) {
        m_min = inter.m_min;
        if (belong(inter.m_max)) {
            m_max = inter.m_max;
        } // end if
        return true;
    } else if (belong(inter.m_max)) {
        m_max = inter.m_max;
        return true;
    } else if ((m_min >= inter.m_max) || (inter.m_min >= m_max)) {
        m_min = 0;
        m_max = 0;
        return (false);
    } //end if
    return (true);
}

bool IntervalSingle::reunion (IntervalSingle const& inter)
{
    if ((m_min > inter.m_max) || (inter.m_min > m_max)) {
        return false;
    } else {
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

IntervalSingle intersection (IntervalSingle const& inter1, IntervalSingle const& inter2)
{
    IntervalSingle inter{inter1};
    inter.intersection (inter2);
    return (inter);
}


IntervalMultiple::IntervalMultiple (int limMin, int limMax)
{
    m_inter.clear();
    IntervalSingle inter{limMin, limMax};
    m_inter.push_back(inter);
}
void IntervalMultiple::intersection (IntervalSingle const& inter)
{
    // pour chaque interval du multi interval, faire l'intersection avec le nouveau interval

    for (size_t i =0; i < m_inter.size(); i++) {
        m_inter[i].intersection (inter);
    } //end for
    // reduire le multi interval.

    std::vector<IntervalSingle>::iterator it;
    auto f = std::bind(&IntervalMultiple::isEmpty, this, std::placeholders::_1);
    it = std::remove_if (m_inter.begin(), m_inter.end(), f);
    m_inter.resize( std::distance(m_inter.begin(),it) );

    if (m_inter.size() == 0) {
        IntervalSingle tmp{0,0};
        reunion (tmp);
    } // end if

}

void IntervalMultiple::reunion (IntervalSingle const& inter)
{
    // pour chaque interval du multi interval, faire la reunion avec le nouveau interval
    bool unionDone {false};
    for (size_t i =0; i < m_inter.size(); i++) {
        unionDone |= m_inter[i].reunion (inter);
    } //end for
    std::vector<IntervalSingle>::iterator it;
    if (unionDone) {
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
    // Si pas de reunion, on l'ajoute à la fin, et on fait une mise par ordre croissant.
        m_inter.push_back(inter);
        std::sort(m_inter.begin(), m_inter.end());
    }
}

bool IntervalMultiple::isEmpty (IntervalSingle const& inter) const
{
    return inter.isEmpty();
}
