#pragma once

#include <random>

namespace Oasis {

    class Random
    {
    private:
        static bool s_Initialized;
    public:
        static float Float();
    };

}
