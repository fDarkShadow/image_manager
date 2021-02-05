#ifndef _EXCEPTION_READER_WRONG_END_SIZE_PNG_HPP_
#define _EXCEPTION_READER_WRONG_END_SIZE_PNG_HPP_

#include "image/exception/reader/wrong_end_size.hpp"
#include "image/type/png.hpp"

#include <string>

namespace image
{
    namespace exception
    {
        namespace reader
        {
            template<>
            struct wrong_end_size<type::png> : public std::exception
            {
                public:
                    wrong_end_size(std::size_t size) :
                        _msg("End field not empty (" + std::to_string(size) + " bytes)"),
                        _size(std::move(size))
                    {}

                    const char * what() const noexcept override
                    {
                        return _msg.c_str();
                    }

                    std::size_t get_size() const { return _size; }

                private:
                    std::string _msg;
                    std::size_t _size;
            };
        }
    }
}

#endif