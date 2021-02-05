#ifndef _EXCEPTION_READER_WRONG_PALETTE_DATAS_NB_PNG_HPP_
#define _EXCEPTION_READER_WRONG_PALETTE_DATAS_NB_PNG_HPP_

#include "image/exception/reader/wrong_palette_datas_nb.hpp"
#include "image/type/png.hpp"

#include <string>

namespace image
{
    namespace exception
    {
        namespace reader
        {
            template<>
            struct wrong_palette_datas_nb<type::png> : public std::exception
            {
                public:
                    wrong_palette_datas_nb(std::size_t size) :
                        _msg("Wrong datas number on palette for PNG : " + std::to_string(size) + " is not 3 multiple"),
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