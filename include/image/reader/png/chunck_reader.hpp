#ifndef _IMAGE_READER_CHUNCK_READER_PNG_HPP_
#define _IMAGE_READER_CHUNCK_READER_PNG_HPP_

#include "image/model/png/chunck.hpp"

#include <algorithm>

namespace image
{
    namespace reader
    {
        struct chunck_reader
        {
            template<class Stream>
            static model::png::chunck read_chunk(Stream & stream)
            {
                model::png::chunck chunck;

                {
                    auto mem = reinterpret_cast<char*>(&chunck.size);
                    stream.read(mem, sizeof(model::png::chunck::size_type));
                    std::reverse(mem, mem+sizeof(model::png::chunck::size_type));
                }

                chunck.type.resize(4);
                stream.read(reinterpret_cast<char*>(&chunck.type[0]), chunck.type.size());

                chunck.datas.resize(chunck.size);
                stream.read(reinterpret_cast<char*>(&chunck.datas[0]), chunck.datas.size());

                {
                    auto mem = reinterpret_cast<char*>(&chunck.crc);
                    stream.read(mem, sizeof(model::png::chunck::crc_type));
                    std::reverse(mem, mem+sizeof(model::png::chunck::crc_type));
                }

                return chunck;
            }
        };
    }
}

#endif