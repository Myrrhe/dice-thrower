#include "IntDistr.hpp"
#include <algorithm>

std::stack<RandManager::IdRand> IntDistr::idRand;

IntDistr::IntDistr() :
values({})
{
    //ctor
}

IntDistr::~IntDistr()
{
    //dtor
}

IntDistr::IntDistr(const IntDistr& other) :
values(other.values)
{
    //copy ctor
}

IntDistr::IntDistr(const std::vector<std::pair<long int, double> >& newValues) :
values(newValues)
{

}

IntDistr::IntDistr(const std::vector<std::pair<IntDistr, double> >& newIntDistr) :
values({})
{
    for (long unsigned int i = 0; i < newIntDistr.size(); i++)
    {
        for (long unsigned int j = 0; j < newIntDistr[i].first.size(); j++)
        {
            long int currV = newIntDistr[i].first[j].first;
            std::vector<std::pair<long int, double> >::iterator it = std::find_if(values.begin(), values.end(), [=](std::pair<long int, double> x)
                                                                                                                   { return x.first == currV; });
            if (it == values.end())
            {
                values.push_back({currV, 0.0});
                it = std::prev(values.end());
            }
            it->second += newIntDistr[i].second*newIntDistr[i].first[j].second;
        }
    }
}

IntDistr::IntDistr(long int c) :
values({{c, 1.0}})
{

}

IntDistr& IntDistr::operator=(const IntDistr& rhs)
{
    if (this == &rhs)
    {
        return *this; // handle self assignment
    }
    values = rhs.values;
    //assignment operator
    return *this;
}

std::size_t IntDistr::size() const
{
    return values.size();
}

std::pair<long int, double>& IntDistr::operator[](std::size_t i)
{
   return values[i];
}

const std::pair<long int, double>& IntDistr::operator[](std::size_t i) const
{
    return values[i];
}

IntDistr IntDistr::operator+() const
{
    return *this;
}

IntDistr IntDistr::operator-() const
{
    IntDistr res = *this;
    long unsigned int nbVal = res.values.size();
    for (long unsigned int i = 0; i < nbVal; i++)
    {
        res.values[i].first = -res.values[i].first;
    }
    return res;
}

IntDistr& IntDistr::operator++()
{
    long unsigned int nbVal = values.size();
    for (long unsigned int i = 0; i < nbVal; i++)
    {
        values[i].first++;
    }
    return *this;
}

IntDistr& IntDistr::operator--()
{
    long unsigned int nbVal = values.size();
    for (long unsigned int i = 0; i < nbVal; i++)
    {
        values[i].first--;
    }
    return *this;
}

IntDistr IntDistr::operator++(int) const
{
    IntDistr res = *this;
    return res++;
}

IntDistr IntDistr::operator--(int) const
{
    IntDistr res = *this;
    return res--;
}

IntDistr& IntDistr::operator+=(const IntDistr& right)
{
    long unsigned int nbValLeft = values.size();
    long unsigned int nbValRight = right.values.size();
    std::vector<std::pair<long int, double> > v = {};
    for (long unsigned int i = 0; i < nbValLeft; i++)
    {
        for (long unsigned int j = 0; j < nbValRight; j++)
        {
            long int currV = values[i].first + right.values[j].first;
            std::vector<std::pair<long int, double> >::iterator it = std::find_if(v.begin(), v.end(), [=](std::pair<long int, double> x)
                                                                                                         { return x.first == currV; });
            if (it == v.end())
            {
                v.push_back({currV, 0.0});
                it = std::prev(v.end());
            }
            it->second += values[i].second*right.values[j].second;
        }
    }
    values = v;
    return *this;
}

IntDistr IntDistr::operator+(const IntDistr& right) const
{
    IntDistr res = *this;
    return res += right;
}

IntDistr& IntDistr::operator-=(const IntDistr& right)
{
    long unsigned int nbValLeft = values.size();
    long unsigned int nbValRight = right.values.size();
    std::vector<std::pair<long int, double> > v = {};
    for (long unsigned int i = 0; i < nbValLeft; i++)
    {
        for (long unsigned int j = 0; j < nbValRight; j++)
        {
            long int currV = values[i].first - right.values[j].first;
            std::vector<std::pair<long int, double> >::iterator it = std::find_if(v.begin(), v.end(), [=](std::pair<long int, double> x)
                                                                                                    { return x.first == currV; });
            if (it == v.end())
            {
                v.push_back({currV, 0.0});
                it = std::prev(v.end());
            }
            it->second += values[i].second*right.values[j].second;
        }
    }
    values = v;
    return *this;
}

IntDistr IntDistr::operator-(const IntDistr& right) const
{
    IntDistr res = *this;
    return res -= right;
}

IntDistr& IntDistr::operator*=(const IntDistr& right)
{
    long unsigned int nbValLeft = values.size();
    long unsigned int nbValRight = right.values.size();
    std::vector<std::pair<long int, double> > v = {};
    for (long unsigned int i = 0; i < nbValLeft; i++)
    {
        for (long unsigned int j = 0; j < nbValRight; j++)
        {
            long int currV = values[i].first * right.values[j].first;
            std::vector<std::pair<long int, double> >::iterator it = std::find_if(v.begin(), v.end(), [=](std::pair<long int, double> x)
                                                                                                    { return x.first == currV; });
            if (it == v.end())
            {
                v.push_back({currV, 0.0});
                it = std::prev(v.end());
            }
            it->second += values[i].second*right.values[j].second;
        }
    }
    values = v;
    return *this;
}

IntDistr IntDistr::operator*(const IntDistr& right) const
{
    IntDistr res = *this;
    return res *= right;
}

IntDistr IntDistr::operator==(const IntDistr& right) const
{
    IntDistr res(std::vector<std::pair<long int, double> >{{0, 0.0}, {1, 0.0}});
    long unsigned int nbValLeft = values.size();
    long unsigned int nbValRight = right.values.size();
    for (long unsigned int i = 0; i < nbValLeft; i++)
    {
        for (long unsigned int j = 0; j < nbValRight; j++)
        {
            res.values[values[i].first == right.values[j].first].second += values[i].second*right.values[j].second;
        }
    }
    if (res.values[0].second <= 0.0)
    {
        res.values.erase(res.values.begin());
    }
    else if (res.values[1].second <= 0.0)
    {
        res.values.erase(std::next(res.values.begin()));
    }
    return res;
}

IntDistr IntDistr::operator!=(const IntDistr& right) const
{
    IntDistr res(std::vector<std::pair<long int, double> >{{0, 0.0}, {1, 0.0}});
    long unsigned int nbValLeft = values.size();
    long unsigned int nbValRight = right.values.size();
    for (long unsigned int i = 0; i < nbValLeft; i++)
    {
        for (long unsigned int j = 0; j < nbValRight; j++)
        {
            res.values[values[i].first != right.values[j].first].second += values[i].second*right.values[j].second;
        }
    }
    if (res.values[0].second <= 0.0)
    {
        res.values.erase(res.values.begin());
    }
    else if (res.values[1].second <= 0.0)
    {
        res.values.erase(std::next(res.values.begin()));
    }
    return res;
}

IntDistr IntDistr::operator>(const IntDistr& right) const
{
    IntDistr res(std::vector<std::pair<long int, double> >{{0, 0.0}, {1, 0.0}});
    long unsigned int nbValLeft = values.size();
    long unsigned int nbValRight = right.values.size();
    for (long unsigned int i = 0; i < nbValLeft; i++)
    {
        for (long unsigned int j = 0; j < nbValRight; j++)
        {
            res.values[values[i].first > right.values[j].first].second += values[i].second*right.values[j].second;
        }
    }
    if (res.values[0].second <= 0.0)
    {
        res.values.erase(res.values.begin());
    }
    else if (res.values[1].second <= 0.0)
    {
        res.values.erase(std::next(res.values.begin()));
    }
    return res;
}

IntDistr IntDistr::operator<(const IntDistr& right) const
{
    IntDistr res(std::vector<std::pair<long int, double> >{{0, 0.0}, {1, 0.0}});
    long unsigned int nbValLeft = values.size();
    long unsigned int nbValRight = right.values.size();
    for (long unsigned int i = 0; i < nbValLeft; i++)
    {
        for (long unsigned int j = 0; j < nbValRight; j++)
        {
            res.values[values[i].first < right.values[j].first].second += values[i].second*right.values[j].second;
        }
    }
    if (res.values[0].second <= 0.0)
    {
        res.values.erase(res.values.begin());
    }
    else if (res.values[1].second <= 0.0)
    {
        res.values.erase(std::next(res.values.begin()));
    }
    return res;
}

IntDistr IntDistr::operator>=(const IntDistr& right) const
{
    IntDistr res(std::vector<std::pair<long int, double> >{{0, 0.0}, {1, 0.0}});
    long unsigned int nbValLeft = values.size();
    long unsigned int nbValRight = right.values.size();
    for (long unsigned int i = 0; i < nbValLeft; i++)
    {
        for (long unsigned int j = 0; j < nbValRight; j++)
        {
            res.values[values[i].first >= right.values[j].first].second += values[i].second*right.values[j].second;
        }
    }
    if (res.values[0].second <= 0.0)
    {
        res.values.erase(res.values.begin());
    }
    else if (res.values[1].second <= 0.0)
    {
        res.values.erase(std::next(res.values.begin()));
    }
    return res;
}

IntDistr IntDistr::operator<=(const IntDistr& right) const
{
    IntDistr res(std::vector<std::pair<long int, double> >{{0, 0.0}, {1, 0.0}});
    long unsigned int nbValLeft = values.size();
    long unsigned int nbValRight = right.values.size();
    for (long unsigned int i = 0; i < nbValLeft; i++)
    {
        for (long unsigned int j = 0; j < nbValRight; j++)
        {
            res.values[values[i].first <= right.values[j].first].second += values[i].second*right.values[j].second;
        }
    }
    if (res.values[0].second <= 0.0)
    {
        res.values.erase(res.values.begin());
    }
    else if (res.values[1].second <= 0.0)
    {
        res.values.erase(std::next(res.values.begin()));
    }
    return res;
}

IntDistr IntDistr::repeat(long unsigned int n) const
{
    IntDistr res = 1;
    for (long unsigned int i = 0; i < n; i++)
    {
        res *= *this;
    }
    return res;
}

IntDistr IntDistr::repeat(const IntDistr& n) const
{
    long unsigned int nbValRight = n.values.size();
    std::vector<std::pair<IntDistr, double> > v = {};
    for (long unsigned int i = 0; i < nbValRight; i++)
    {
        v.emplace_back(repeat(static_cast<long unsigned int>(n[i].first)), n[i].second);
    }
    return IntDistr(v);
}

double IntDistr::getMean() const
{
    double res = 0.0;
    for (long unsigned int i = 0; i < values.size(); i++)
    {
        res += values[i].first*values[i].second;
    }
    return res;
}

long int IntDistr::operator()() const
{
    double sum = 0.0;
    double r = RandManager::genRand(idRand.top());
    long unsigned int i = 0;
    do
    {
        sum += values[i].second;
    } while (r > sum && i < values.size() - 1);
    return values[i].first;
}

void IntDistr::pushIdRand(RandManager::IdRand newIdRand)
{
    idRand.push(newIdRand);
}

void IntDistr::popIdRand()
{
    idRand.pop();
}

std::ostream& operator<<(std::ostream& os, const IntDistr& right)
{
    std::cout.precision(2);
    for (long unsigned int i = 0; i < right.size(); i++)
    {
        os << "(" << right[i].first << ", " << std::fixed << 100.0*right[i].second << ")";
        if (i < right.size() - 1)
        {
            std::cout << ", ";
        }
    }
    return os;
}
