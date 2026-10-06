#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

int selectKthA(std::vector<int> a, int k)
{
    std::sort(a.begin(), a.end(), std::greater<int>());
    return a[k - 1];
}

int selectKthB(std::vector<int> a, int k)
{
    std::vector<int> top(a.begin(), a.begin() + k);
    std::sort(top.begin(), top.end(), std::greater<int>());

    for (std::size_t i = k; i < a.size(); ++i)
    {
        int x = a[i];
        if (x <= top[k - 1])
            continue;

        int j = k - 1;
        while (j > 0 && top[j - 1] < x)
        {
            top[j] = top[j - 1];
            --j;
        }
        top[j] = x;
    }

    return top[k - 1];
}

int main()
{
    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dist(1, 1000000);

    std::vector<int> sizes = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    std::cout << "N\t\tTime (ms)\n";
    for (int N : sizes)
    {
        std::vector<int> data(N);
        for (int &x : data)
            x = dist(gen);

        int k = N / 2;

        // Algo A
        auto start = std::chrono::high_resolution_clock::now();
        int resultA = selectKthA(data, k);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> elapsedA = end - start;

        // Algo B
        auto startB = std::chrono::high_resolution_clock::now();
        int resultB = selectKthB(data, k);
        auto endB = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> elapsedB = endB - startB;

        std::cout << N << "\t\t"
                  << "Algo A: "
                  << elapsedA.count()
                  << "      (results: "
                  << resultA << ")"
                  << "  Algo B: "
                  << elapsedB.count()
                  << "      (results: "
                  << resultB << ")"
                  << ")\n";
    }

    return 0;
}