#ifndef _IMAGE_COMPRESSOR_PNG_DECOMPRESSOR_HPP_
#define _IMAGE_COMPRESSOR_PNG_DECOMPRESSOR_HPP_

#include "image/stream/png/stream_reader.hpp"

#include "details/inflators/no_compression.hpp"
#include "details/inflators/fixed_huffman.hpp"
#include "details/inflators/dynamic_huffman.hpp"

namespace image
{
    namespace compressor
    {
        namespace png
        {
            struct decompressor
            {
            public:
                template<class T>
                std::vector<T> decompress(std::vector<T> const& datas)
                {
                    stream::png::stream_reader<T> reader(datas);
                    std::vector<T> decompressed_datas;
                    auto end_reached = false;
                    while(!end_reached)
                    {
                        end_reached = reader++;
                        auto type = reader.template get_value<uint8_t>(2);
                        if(type == 0)
                        {
                            auto d = _no_compression_inflator.template inflate<T>(reader);
                            decompressed_datas.insert(decompressed_datas.end(), d.begin(), d.end());
                        }
                        else if(type == 1)
                        {
                            auto d = _fixed_huffman_inflator.template inflate<T>(reader);
                            decompressed_datas.insert(decompressed_datas.end(), d.begin(), d.end());
                        }
                        else if(type == 2)
                        {
                            auto d = _dynamic_huffman_inflator.template inflate<T>(reader);
                            decompressed_datas.insert(decompressed_datas.end(), d.begin(), d.end());
                        }
                        else
                        {
                            throw std::exception() /* TODO : type not valid */;
                        }
                    }
                    return decompressed_datas;
                }
                
            private:
                details::inflators::inflator<details::inflators::no_compression> _no_compression_inflator;
                details::inflators::inflator<details::inflators::fixed_huffman> _fixed_huffman_inflator;
                details::inflators::inflator<details::inflators::dynamic_huffman> _dynamic_huffman_inflator;
            };
        }
    }
}

#endif