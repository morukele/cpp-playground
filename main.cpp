#include <iostream>
#include <string>
#include <thread>
#include <mutex>

namespace
{
    template <typename Object>
    class MemoryCell
    {
    public:
        explicit MemoryCell(const Object& initialValue = Object{})
            : storedValue{initialValue}
        {
        }

        const Object& read() const { return storedValue; }
        void write(const Object& x) { storedValue = x; }

    private:
        Object storedValue;
    };

    class Square
    {
    public:
        explicit Square(double s = 0.0) : side{s}
        {
        }

        double getSide() const { return side; }
        double getArea() const { return side * side; }
        double getPerimeter() const { return 4 * side; }

        void print(std::ostream& out = std::cout) const
        {
            std::cout << "(square " << getSide() << ")";
        }

        bool operator<(const Square& rhs) const
        {
            return getSide() < rhs.getSide();
        }

    private:
        double side;
    };

    // Define an output operator for a Square
    std::ostream& operator<<(std::ostream& out, const Square& rhs)
    {
        rhs.print(out);
        return out;
    }

    // template <typename Comparable>
    // const Comparable& findMax(const std::vector<Comparable>& a)
    // {
    //     int maxIndex = 0;
    //
    //     for (int i = 1; i < a.size(); ++i)
    //     {
    //         if (a[maxIndex] < a[i])
    //         {
    //             maxIndex = i;
    //         }
    //     }
    //     return a[maxIndex];
    // }

    // Generic findMax, with a function object, V1
    // Precondition: a.size() > 0.
    // template <typename Object, typename Comparator>
    // const Object& findMax(const std::vector<Object>& arr, Comparator cmp)
    // {
    //     int maxIndex = 0;
    //
    //     for (int i{0}; i < arr.size(); ++i)
    //     {
    //         if (cmp.isLessThan(arr[maxIndex], arr[i]))
    //         {
    //             maxIndex = i;
    //         }
    //     }
    //
    //     return arr[maxIndex];
    // }

    class CaseInsensitiveCompare
    {
    public:
        [[nodiscard]] bool isLessThan(const std::string& lhs, const std::string& rhs) const
        {
            return strcasecmp(lhs.c_str(), rhs.c_str()) < 0;
        }

        bool operator()(const std::string& lhs, const std::string& rhs) const
        {
            return strcasecmp(lhs.c_str(), rhs.c_str()) < 0;
        }
    };

    // Generic findMax, with a function object, V2 (C++ style)
    // Precondition: a.size() > 0.
    template <typename Object, typename Comparator>
    const Object& findMax(const std::vector<Object>& arr, Comparator isLessThan)
    {
        int maxIndex = 0;

        for (int i{0}; i < arr.size(); ++i)
        {
            if (isLessThan(arr[maxIndex], arr[i]))
            {
                maxIndex = i;
            }
        }

        return arr[maxIndex];
    }

    // Generic findMax, using default ordering.
    template <typename Object>
    const Object& findMax(const std::vector<Object>& arr)
    {
        return findMax(arr, std::less<Object>{});
    }
}


int main()
{
    std::vector<std::string> arr = {"ZEBRA", "alligator", "crocodile"};

    std::cout << findMax(arr, CaseInsensitiveCompare{}) << std::endl;
    std::cout << findMax(arr) << std::endl;

    return 0;
}
