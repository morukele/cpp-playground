#include <iostream>
#include <vector>
#include <ostream>
#include <format>
#include <functional>
#include "include/matrix.h"

using namespace std;

class IntCell
{
public:
    explicit IntCell(int initialValue = 0)
    {
        storedValue = new int{initialValue};
    }
    ~IntCell() { delete storedValue; }
    IntCell(const IntCell &rhs)
    {
        storedValue = new int{*rhs.storedValue};
    }
    IntCell(IntCell &&rhs) : storedValue{rhs.storedValue}
    {
        rhs.storedValue = nullptr;
    }
    IntCell &operator=(const IntCell &rhs)
    {
        if (this != &rhs)
        {
            *storedValue = *rhs.storedValue;
        }
        return *this;
    }
    IntCell &operator=(IntCell &&rhs)
    {
        std::swap(storedValue, rhs.storedValue);
        return *this;
    }

    int read() const { return *storedValue; }
    void write(int x)
    {
        *storedValue = x;
    }

private:
    int *storedValue;
};

/**
 * Return the maximum item in array a.
 * Assume a.size() > 0.
 * Comparable objects must provide operator< and operator=
 */
template <typename Comparable>
const Comparable &findMax(const std::vector<Comparable> &a)
{
    int maxIndex = 0;
    for (int i = 1; i < a.size(); ++i)
    {
        if (a[maxIndex] < a[i])
        {
            maxIndex = i;
        }
    }
    return a[maxIndex];
}

/**
 * A class for simulating memory cell.
 */
template <typename Object>
class MemoryCell
{
public:
    explicit MemoryCell(const Object &initialValue = Object{}) : storedValue{initialValue} {}
    const Object &read() const { return storedValue; }
    void write(const Object &x) { storedValue = x; }

private:
    Object storedValue;
};

class Square
{
public:
    explicit Square(double s = 0.0) : side{s} {}
    double getSide() const { return side; }
    double getArea() const { return side * side; }
    double getPerimeter() const { return 4 * side; }
    void print(ostream &out = cout) const { out << "(square " << getSide() << ")"; }
    bool operator<(const Square &rhs) const { return getSide() < rhs.getSide(); }

private:
    double side;
};

ostream &operator<<(ostream &out, const Square &rhs)
{
    rhs.print(out);
    return out;
}

/**
 * Generic findMax, with a function object, Version #1
 * Precondition: a.size() > 0
 */
template <typename Object, typename Comparator>
const Object &findMax(const vector<Object> &arr, Comparator cmp)
{
    int maxIndex = 0;
    for (int i = 1; i < arr.size(); ++i)
        if (cmp.isLessThan(arr[maxIndex], arr[i]))
            maxIndex = i;

    return arr[maxIndex];
};

class CaseInsensitiveCompare
{
public:
    bool isLessThan(const string &lhs, const string &rhs) const
    {
        return strcasecmp(lhs.c_str(), rhs.c_str()) < 0;
    }
};

/**
 * Generic findMax, using default ordering.
 */
template <typename Object>
const Object &findMaw(const vector<Object> &arr)
{
    return findMaw(arr, less<Object>{});
}

int main()
{
    vector<Square> v = {Square{3.0}, Square{2.0}, Square{2.5}};
    matrix<int> mat{1, 1};

    cout
        << "Largest square: " << findMax(v) << endl;

    vector<string> arr = {"ZEBRA", "alligator", "crocodile"};
    cout << findMax(arr, CaseInsensitiveCompare{}) << endl;
    cout << findMax(arr) << endl;

    cout << mat[1][1] << endl;

    return 0;
}