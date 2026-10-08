#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    const double GROWTH_RATE = 0.1;
    const double DT = 0.001;
    const double P_START = 100.0;
    const double POP_LIMIT = 1e10;
    const long long PRINT_EVERY = 10000; // steps between printed rows

    double P = P_START; // Current population state
    long long step = 0;
    double t = 0.0;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(10) << "t"
              << std::setw(20) << "simulated"
              << std::setw(20) << "exact" << "\n";

    while (P < POP_LIMIT)
    {
        if (step % PRINT_EVERY == 0)
        {
            double exact = P_START * std::exp(GROWTH_RATE * t); // exact solution at this step
            std::cout << std::setw(10) << t
                      << std::setw(20) << P
                      << std::setw(20) << exact << "\n";
        }

        P += GROWTH_RATE * P * DT; // Euler step
        ++step;
        t = step * DT; // avoid accumulating rounding error
    }

    double theory = std::log(POP_LIMIT / P_START) / GROWTH_RATE;
    std::cout << "\nReached limit at t = " << t
              << " (theory: " << theory << ")\n";

    return 0;
}