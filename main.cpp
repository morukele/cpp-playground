#include <iostream>
#include <string>

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
}


int main()
{
    MemoryCell<int> m1;
    MemoryCell<std::string> m2{"hello"};

    m1.write(37);
    m2.write(m2.read() + "world");
    std::cout << m1.read() << std::endl << m2.read() << std::endl;

    return 0;
}
