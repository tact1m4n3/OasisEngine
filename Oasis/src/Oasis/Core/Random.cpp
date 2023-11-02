#include <Oasis/Core/Random.h>

#include <cstdlib>
#include <ctime>

namespace Oasis {

    bool Random::s_Initialized = false;

    float Random::Float()
    {
        if (!s_Initialized)
        {
            srand((uint32_t)time(0));
            s_Initialized = true;
        }

        return (float)rand() / (float)RAND_MAX;
    }

}