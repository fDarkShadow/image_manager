#ifndef _EXCEPTION_READER_WRONG_DATA_SIZE_PNG_HPP_
#define _EXCEPTION_READER_WRONG_DATA_SIZE_PNG_HPP_

#include "image/exception/reader/wrong_data_size.hpp"
#include "image/type/png.hpp"

#include <string>

namespace image
{
    namespace exception
    {
        namespace reader
        {
            template<>
            struct wrong_data_size<type::png> : public std::exception
            {
                public:
                    wrong_data_size(std::string field, std::size_t size) :
                        _msg("Wrong nb of data for field " + field + " (" + std::to_string(size) + " bytes)"),
                        _field(std::move(field)),
                        _size(std::move(size))
                    {}

                    const char * what() const noexcept override
                    {
                        return _msg.c_str();
                    }

                    std::string get_field() const { return _field; }
                    std::size_t get_size() const { return _size; }

                private:
                    std::string _msg;
                    std::string _field;
                    std::size_t _size;
            };
        }
    }
}

#endif