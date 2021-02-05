#ifndef _IMAGE_CHECKER_PNG_ADLER32_HPP_
#define _IMAGE_CHECKER_PNG_ADLER32_HPP_

#include "image/model/png/chunck.hpp"

namespace image
{
    namespace checker
    {
        namespace png
        {
            struct adler32
            {
                public:
                    bool check(model::png::chunck const& chunck, uint32_t checksum)
                    {
                        uint32_t a = 1;
                        uint32_t b = 0;
                        for(uint32_t data : chunck.type)
                        {
                            a = (a + data) % 65521;
                            b = (b + a) % 65521;
                        }
                        for(uint32_t const& data : chunck.datas)
                        {
                            a = (a + data) % 65521;
                            b = (b + a) % 65521;
                        }

                        auto adler32 = (b << 16) | a;

                        return adler32 == checksum;
                    }
            };
        }
    }
}

#endif