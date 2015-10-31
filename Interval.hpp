#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <ostream>
#include <vector>
#include <algorithm>
///  \file   Interval.hpp
///  \brief  This file is a short mathematical library which manage the interval.
///          The interval format is [min, max[ (with "min" and "max" integer)
///  \author Dedeun
///  \date   21 october 2015
///  \version Beta 1.4

//namespace dd {

    ///  \class IntervalSingle
    ///  \brief This class is a single interval, with the 2 operations (intersection and reunion),
    ///         2 operations ( == and <) and one function (isEmpty())
    ///         The interval can be displayed also
    class IntervalSingle final {
    public:
        /// \fn    IntervalSingle ();
        /// \brief Constructor (with 2 limits, min and max)
        /// \param limit min (default value is 0)
        /// \param limit max (default value is 0)
        /// \invariant min <= max
        IntervalSingle (int limMin=0, int limMax=0);

        /// \fn     intersection ()
        /// \brief  realize the intersection between two intervals
        /// \param  reference to a second interval
        /// \return Return true if the intersection is not empty
        bool intersection (IntervalSingle const& inter);

        /// \fn     reunion ()
        /// \brief  realize the reunion between two intervals
        /// \param  reference to a second interval
        /// \return Return true if the intersection of the two interval is not empty
        bool reunion (IntervalSingle const& inter);

        /// \fn     belong ()
        /// \brief  test if a value is inside the interval
        /// \param  value to be tested
        /// \return Return true if the value is inside the interval
        bool belong (int const val);

        /// \fn     operator ==
        /// \brief  test if the two interval are equal
        /// \param  reference to a second interval
        /// \return Return true if the two intervals are equal
        bool operator== (IntervalSingle const& inter) const;

        /// \fn     operator <
        /// \brief  compare two intervals
        /// \param  reference to a second interval
        /// \return Return true if the second interval is greater
        bool operator< (IntervalSingle const& inter) const;

        /// \fn     isEmpty ()
        /// \brief  test if the interval is empty
        /// \return Return true if the interval is empty
        bool isEmpty () const;

        /// \fn    operator <<
        /// \brief Output on flux
        /// \param reference to the output flux
        /// \param reference of the single interval
        /// \return reference to the output flux
        friend std::ostream& operator<< (std::ostream& flux, IntervalSingle const& inter)
        {
            flux << "[" << inter.m_min << "," << inter.m_max << "[";
            return flux;
        };
    protected:
    private:
        /// \var   m_min
        /// \brief member variable: minimum limit
        int m_min;
        /// \var   m_max
        /// \brief member variable: maximum limit
        int m_max;
    };

    /// \fn     intersection ()
    /// \brief  free function which compute intersection
    /// \param  reference to the interval 1
    /// \param  reference of the interval 2
    /// \return interval, intersection of the two intervals
    IntervalSingle intersection (IntervalSingle const& inter1, IntervalSingle const& inter2);

    ///  \class IntervalMultiple
    ///  \brief This class is a multiple interval, with the 2 operations (intersection and reunion).
    ///         (the reunion of two single intervals may request a multiple interval)
    ///         The interval can be displayed also
    class IntervalMultiple final {
    public:
        /// \fn    IntervalMultiple ();
        /// \brief Constructor (with 2 limits, min and max)
        /// \param limit min (default value is 0)
        /// \param limit max (default value is 0)
        /// \invariant min <= max
        IntervalMultiple (int limMin=0, int limMax=0);

        /// \fn     intersection ()
        /// \brief  realize the intersection with a single intervals
        /// \param  reference to the single interval
        void intersection (IntervalSingle const& inter);

        /// \fn     reunion ()
        /// \brief  realize the reunion with a single intervals
        /// \param  reference to the single interval
        void reunion (IntervalSingle const& inter);

        /// \fn    operator <<
        /// \brief Output on flux
        /// \param reference to the output flux
        /// \param reference of the multiple interval
        /// \return reference to the output flux
        friend std::ostream& operator<< (std::ostream& flux, IntervalMultiple const& mulInter)
        {
            for (auto inter : mulInter.m_inter) {
               flux << inter << ",";
            } // end for
            return flux;
        };
    protected:
    private:
        /// \var   m_interval
        /// \brief member variable: vector of single interval
        std::vector<IntervalSingle> m_inter;
    };

//};

#endif // INTERVAL_HPP
