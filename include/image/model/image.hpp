#ifndef _IMAGE_MODEL_IMAGE_HPP_
#define _IMAGE_MODEL_IMAGE_HPP_

#include <vector>
#include <tuple>
#include <cstdint>

namespace image
{
    namespace model
    {
        struct image
        {
            uint32_t width;
            uint32_t height;
            std::vector<std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>> pixels;
        };
    }
}

#endif