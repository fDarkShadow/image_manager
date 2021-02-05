#ifndef _IMAGE_SIGNATURE_READER_HPP_
#define _IMAGE_SIGNATURE_READER_HPP_

#include <string>

namespace image
{
    namespace signature
    {
        template<class T>
        struct reader
        {
            template<class Stream>
            static std::string read_signature(Stream & stream);
        };
    }
}

#endif