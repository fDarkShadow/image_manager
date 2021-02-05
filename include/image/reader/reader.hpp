#ifndef _IMAGE_READER_READER_HPP_
#define _IMAGE_READER_READER_HPP_

#include "image/model/image.hpp"

namespace image
{
    namespace reader
    {
        template<class T>
        struct reader
        {
            template<class Stream>
            static model::image read_image(Stream & stream);
        };
    }
}

#endif