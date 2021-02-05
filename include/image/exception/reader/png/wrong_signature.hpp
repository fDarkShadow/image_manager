#ifndef _EXCEPTION_READER_WRONG_SIGNATURE_PNG_HPP_
#define _EXCEPTION_READER_WRONG_SIGNATURE_PNG_HPP_

#include "image/exception/reader/wrong_signature.hpp"
#include "image/type/png.hpp"

#include <string>

namespace image
{
    namespace exception
    {
        namespace reader
        {
            template<>
            struct wrong_signature<type::png> : public std::exception
            {
                public:
                    wrong_signature(std::string signature_read, std::string signature_default) :
                        _msg("Wrong signature for PNG"),
                        _signature_read(std::move(signature_read)),
                        _signature_default(std::move(signature_default))
                    {}

                    const char * what() const noexcept override
                    {
                        return _msg.c_str();
                    }

                    std::string get_signature_read() const { return _signature_read; }
                    std::string get_signature_default() const { return _signature_default; }

                private:
                    std::string _msg;
                    std::string _signature_read;
                    std::string _signature_default;
            };
        }
    }
}

#endif