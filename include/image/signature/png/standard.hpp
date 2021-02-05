#ifndef _IMAGE_SIGNATURE_STANDARD_PNG_HPP_
#define _IMAGE_SIGNATURE_STANDARD_PNG_HPP_

#include "image/signature/standard.hpp"
#include "image/type/png.hpp"

namespace image
{
    namespace signature
    {
        template<>
        struct standard<type::png>
        {
            static std::string get_signature()
            {
                std::string sig;
                sig.reserve(8);
                sig.push_back(0x89);
                sig.push_back(0x50);
                sig.push_back(0x4E);
                sig.push_back(0x47);
                sig.push_back(0x0D);
                sig.push_back(0x0A);
                sig.push_back(0x1A);
                sig.push_back(0x0A);
                return sig;
            }
        };
    }
}

#endif