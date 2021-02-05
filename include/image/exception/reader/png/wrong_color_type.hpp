#ifndef _EXCEPTION_READER_WRONG_COLOR_TYPE_PNG_HPP_
#define _EXCEPTION_READER_WRONG_COLOR_TYPE_PNG_HPP_

#include "image/exception/reader/wrong_color_type.hpp"
#include "image/type/png.hpp"

#include <string>

namespace image
{
    namespace exception
    {
        namespace reader
        {
            template<>
            struct wrong_color_type<type::png> : public std::exception
            {
                public:
                    wrong_color_type(uint8_t color_type) :
                        _msg("Wrong color type for PNG : " + std::to_string(color_type)),
                        _color_type(std::move(color_type))
                    {}

                    const char * what() const noexcept override
                    {
                        return _msg.c_str();
                    }

                    uint8_t get_color_type() const { return _color_type; }

                private:
                    std::string _msg;
                    uint8_t _color_type;
            };
        }
    }
}

#endif