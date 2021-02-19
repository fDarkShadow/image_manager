#ifndef _IMAGE_MODEL_PNG_CONTENT_HPP_
#define _IMAGE_MODEL_PNG_CONTENT_HPP_

#include <vector>

namespace image
{
    namespace model
    {
        namespace png
        {
            struct content
            {
                content() :
                    width(0),
                    height(0),
                    bit_depth(0),
                    color_type(0),
                    compression_method(0),
                    filter_method(0),
                    interlace_method(0),
                    bytes_per_pixel(5./32.), /* TODO : correct */
                    palette_defined(false),
                    flag_check(0),
                    flag_dict(false),
                    flag_level(0)
                {}

                uint32_t width;
                uint32_t height;
                uint8_t bit_depth;
                uint8_t color_type;
                uint8_t compression_method;
                uint8_t filter_method;
                uint8_t interlace_method;
                float bytes_per_pixel;
                bool palette_defined;
                uint8_t flag_check;
                bool flag_dict;
                uint8_t flag_level;
                std::vector<uint8_t> datas;
            };
        }
    }
}

#endif