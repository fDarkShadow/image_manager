#ifndef _EXCEPTION_READER_WRONG_CRC_PNG_HPP_
#define _EXCEPTION_READER_WRONG_CRC_PNG_HPP_

#include "image/exception/reader/wrong_crc.hpp"
#include "image/type/png.hpp"

#include "image/model/png/chunck.hpp"

#include <string>

namespace image
{
    namespace exception
    {
        namespace reader
        {
            template<>
            struct wrong_crc<type::png> : public std::exception
            {
                public:
                    wrong_crc(model::png::chunck chunck) :
                        _msg("Wrong CRC for PNG"),
                        _chunck(std::move(chunck))
                    {}

                    const char * what() const noexcept override
                    {
                        return _msg.c_str();
                    }

                    model::png::chunck get_chunk() const { return _chunck; }

                private:
                    std::string _msg;
                    model::png::chunck _chunck;
            };
        }
    }
}

#endif