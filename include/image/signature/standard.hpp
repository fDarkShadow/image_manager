#ifndef _IMAGE_SIGNATURE_STANDARD_HPP_
#define _IMAGE_SIGNATURE_STANDARD_HPP_

#include <string>

namespace image
{
    namespace signature
    {
        template<class T>
        struct standard
        {
            static std::string get_signature();
        };
    }
}

#endif