#ifndef _EXCEPTION_READER_WRONG_STRUCTURE_PNG_HPP_
#define _EXCEPTION_READER_WRONG_STRUCTURE_PNG_HPP_

#include "image/exception/reader/wrong_structure.hpp"
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
            struct wrong_structure<type::png> : public std::exception
            {
                public:
                    wrong_structure(model::png::chunck chunck) :
                        _msg("Wrong structure for PNG"),
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