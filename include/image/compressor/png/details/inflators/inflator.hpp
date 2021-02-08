#ifndef _IMAGE_COMPRESSOR_PNG_DETAILS_INFLATORS_INFLATOR_HPP_
#define _IMAGE_COMPRESSOR_PNG_DETAILS_INFLATORS_INFLATOR_HPP_

#include <vector>

namespace image
{
    namespace compressor
    {
        namespace png
        {
            namespace details
            {
                namespace inflators
                {
                    template<class I>
                    struct inflator
                    {
                        template<class T, class R>
                        std::vector<T> inflate(R & reader) const;
                    };
                }
            }
        }
    }
}

#endif