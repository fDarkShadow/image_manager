#ifndef _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_IDAT_HPP_
#define _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_IDAT_HPP_

#include "image/model/png/chunck.hpp"
#include "image/model/png/content.hpp"

#include "details/inflators/no_compression.hpp"
#include "details/inflators/fixed_huffman.hpp"
#include "details/inflators/dynamic_huffman.hpp"

#include "image/checker/png/adler32.hpp"

#include "details/stream_reader.hpp"
#include "details/huffman_tree.hpp"

namespace image
{
    namespace standard_structure
    {
        namespace png
        {
            namespace manager
            {
                struct idat
                {
                    details::inflators::inflator<details::inflators::no_compression> _no_compression_inflator;
                    details::inflators::inflator<details::inflators::fixed_huffman> _fixed_huffman_inflator;
                    details::inflators::inflator<details::inflators::dynamic_huffman> _dynamic_huffman_inflator;

                    void operator()(model::png::chunck const& chunck, model::png::content & content) const
                    {
                        details::stream_reader<model::png::chunck::data_type> reader(chunck.datas);

                        auto compression_method = reader.get_value<uint8_t>(4);
                        if(compression_method != 8U)
                        {
                            throw std::exception() /* TODO : compression method not supported */;
                        }
                        auto compression_info = reader.get_value<uint8_t>(4);
                        if(compression_info > 7U)
                        {
                            throw std::exception() /* TODO : compression info not supported */;
                        }

                        auto flag_check = reader.get_value<uint8_t>(5);
                        auto flag_dict = reader++;
                        auto flag_level = reader.get_value<uint8_t>(2);

                        auto checksum = (0 | compression_method | compression_info << 4) * 256U + (0 | flag_check | flag_dict << 5 | flag_level << 6);
                        if(checksum % 31 != 0)
                        {
                            throw std::exception() /* TODO : wrong checksum for data */;
                        }

                        auto end_reached = false;
                        std::vector<model::png::chunck::data_type> datas_inflated;
                        while(!end_reached)
                        {
                            end_reached = reader++;
                            auto type = reader.get_value<uint8_t>(2);
                            if(type == 0)
                            {
                                auto d = _no_compression_inflator.template inflate<model::png::chunck::data_type>(reader);
                                content.datas.insert(content.datas.end(), d.begin(), d.end());
                            }
                            else if(type == 1)
                            {
                                auto d = _fixed_huffman_inflator.template inflate<model::png::chunck::data_type>(reader);
                                content.datas.insert(content.datas.end(), d.begin(), d.end());
                            }
                            else if(type == 2)
                            {
                                auto d = _dynamic_huffman_inflator.template inflate<model::png::chunck::data_type>(reader);
                                content.datas.insert(content.datas.end(), d.begin(), d.end());
                            }
                            else
                            {
                                throw std::exception() /* TODO : type not valid */;
                            }
                        }

                        auto adler32 = reader.get_value<uint32_t>(32); // TODO : error
                        if(!checker::png::adler32().check(chunck, adler32))
                        {
                            //throw std::exception() /* TODO : adler32 wrong */;
                        }
                    }
                };
            }
        }
    }
}

#endif