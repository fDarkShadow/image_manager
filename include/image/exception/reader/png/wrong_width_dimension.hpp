#ifndef _EXCEPTION_READER_WRONG_WIDTH_DIMENSION_PNG_HPP_
#define _EXCEPTION_READER_WRONG_WIDTH_DIMENSION_PNG_HPP_

#include "image/exception/reader/wrong_width_dimension.hpp"
#include "image/type/png.hpp"

#include <string>

namespace image
{
    namespace exception
    {
        namespace reader
        {
            template<>
            struct wrong_width_dimension<type::png> : public std::exception
            {
                public:
                    wrong_width_dimension(uint32_t dimension) :
                        _msg("Wrong width for PNG : " + std::to_string(dimension) + " pixels"),
                        _dimension(std::move(dimension))
                    {}

                    const char * what() const noexcept override
                    {
                        return _msg.c_str();
                    }

                    uint32_t get_dimension() const { return _dimension; }

                private:
                    std::string _msg;
                    uint32_t _dimension;
            };
        }
    }
}

#endif