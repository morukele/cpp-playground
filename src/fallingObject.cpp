#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    // ---- Parameters (never change) ----
    const double g = 9.81;             // gravity (m/s^2)
    const double c = 0.5;              // drag per unit mass (1/s)
    const double DT = 0.001;           // time step (s)
    const double T_END = 20.0;         // simulation lenght (s)
    const double PRINT_INTERVAL = 1.0; // time between printed rows (s)

    const long long nSteps = std::llround(T_END / DT);
    const long long printEvery = std::llround(PRINT_INTERVAL / DT);

    // ---- State (evolves) ----
    // Standard Euler: y is updated with the OLD v
    double vE = 0.0, yE = 0.0;
    // Semi-implicit Euler: y is updated with the NEW v
    double vS = 0.0, yS = 0.0;

    std::cout << "Terminal velocity (theory): " << g / c << "m/s\n\n";

    std::cout << std::fixed << std::setprecision(4);
    std::cout << std::setw(8) << "t"
              << std::setw(12) << "v_euler"
              << std::setw(12) << "v_exact"
              << std::setw(14) << "y_euler"
              << std::setw(14) << "y_semi"
              << std::setw(14) << "y_exact" << "\n";

    for (long long step{0}; step <= nSteps; ++step)
    {
        double t = step * DT; // computed from the counter to avoid drift

        // Print selectively
        if (step % printEvery == 0)
        {
            double decay = 1.0 - std::exp(-c * t);
            double vExact = (g / c) * decay;
            double yExact = (g / c) * t - (g / (c * c)) * decay;

            std::cout << std::setw(8) << t
                      << std::setw(12) << vE
                      << std::setw(12) << vExact
                      << std::setw(14) << yE
                      << std::setw(14) << yS
                      << std::setw(14) << yExact << "\n";
        }

        // Standard Euler: update y first, using the old v
        yE += vE * DT;
        vE += (g - c * vE) * DT;

        // Semi-implicit Euler: update v first, then y with the new v
        vS += (g - c * vS) * DT;
        yS += vS * DT;
    }

    return 0;
}