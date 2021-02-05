#ifndef _IMAGE_SIGNATURE_READER_PNG_HPP_
#define _IMAGE_SIGNATURE_READER_PNG_HPP_

#include "image/signature/reader.hpp"
#include "image/type/png.hpp"

namespace image
{
    namespace signature
    {
        template<>
        struct reader<type::png>
        {
            template<class Stream>
            static std::string read_signature(Stream & stream)
            {
                std::string sig(8, 0);
                stream.read(&sig[0], sig.size());
                return sig;
            }
        };
    }
}

#endif