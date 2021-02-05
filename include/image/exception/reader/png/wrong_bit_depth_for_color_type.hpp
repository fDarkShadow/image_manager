#ifndef _EXCEPTION_READER_WRONG_BIT_DEPTH_FOR_COLOR_TYPE_PNG_HPP_
#define _EXCEPTION_READER_WRONG_BIT_DEPTH_FOR_COLOR_TYPE_PNG_HPP_

#include "image/exception/reader/wrong_bit_depth_for_color_type.hpp"
#include "image/type/png.hpp"

#include <string>

namespace image
{
    namespace exception
    {
        namespace reader
        {
            template<>
            struct wrong_bit_depth_for_color_type<type::png> : public std::exception
            {
                public:
                    wrong_bit_depth_for_color_type(uint8_t color_type, uint8_t bit_depth) :
                        _msg("Wrong bit depth for PNG : " + std::to_string(bit_depth) + " bit depth with " + std::to_string(color_type) + " color type"),
                        _color_type(std::move(color_type)),
                        _bit_depth(std::move(bit_depth))
                    {}

                    const char * what() const noexcept override
                    {
                        return _msg.c_str();
                    }

                    uint8_t get_color_type() const { return _color_type; }
                    uint8_t get_bit_depth() const { return _bit_depth; }

                private:
                    std::string _msg;
                    uint8_t _color_type;
                    uint8_t _bit_depth;
            };
        }
    }
}

#endif