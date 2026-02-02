//
// Created by Oghenemarho Orukele on 23/01/2026.
//

#include <fstream>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>


struct Record
{
    int id;
    std::string name;

    explicit Record(const int id, std::string name) : id{id}, name{std::move(name)} {}
};

void necessary_heap_allocations()
{
    // pointer deletes itself as it goes out of scope.
    auto customer = std::make_unique<Record>(0, "James");
    auto other = std::make_unique<Record>(1, "Someone");
}

void read_from_a_file(char* name)
{
    const std::ifstream input{name}; // RAII - Resource Acquisition Is Initialisation
    if (!input.is_open())
    {
        std::cout << "Unable to open file" << std::endl;
    }
    else
    {
    }
}

int* some_c_function()
{
    int res = 10 * 10;

    return &res;
}

struct FreeDeleter
{
    // An operator that takes anytype of pointer and frees it.
    // It is expected to return nothing.
    void operator()(void* x) const { free(x); }
};

int main()
{

    std::pair<double, int> myPair{1.23, 5};
    std::cout << myPair.first << " " << myPair.second << std::endl;

    std::vector<int> myVector{11, 22};
    myVector.push_back(33);
    myVector.push_back(44);

    auto data = std::unique_ptr<int, FreeDeleter>(some_c_function());
}
