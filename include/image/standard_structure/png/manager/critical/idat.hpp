#ifndef _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_IDAT_HPP_
#define _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_IDAT_HPP_

#include "image/model/png/chunck.hpp"
#include "image/model/png/content.hpp"

#include "image/checker/png/adler32.hpp"

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
                    void operator()(model::png::chunck const& chunck, model::png::content & content) const
                    {
                        if(chunck.datas.size() < 6U)
                        {
                            throw std::exception() /* TODO : not enough infos */;
                        }
                        
                        auto compression = chunck.datas[0];
                        auto compression_method = compression & 0xf;
                        if(compression_method != 8)
                        {
                            throw std::exception() /* TODO : compression method not supported */;
                        }
                        auto compression_info = (compression >> 4) & 0xf;
                        if(compression_info > 7)
                        {
                            throw std::exception() /* TODO : compression info not supported */;
                        }

                        auto flag = chunck.datas[1];
                        auto flag_check = flag & 0x1f;
                        auto flag_dict = (flag >> 5) & 1;
                        auto flag_level = (flag >> 6) & 0b11;

                        auto checksum = compression * 256U + flag;
                        if(checksum % 31 != 0)
                        {
                            throw std::exception() /* TODO : wrong checksum for data */;
                        }

                        content.datas.insert(content.datas.end(), chunck.datas.begin() + 2, chunck.datas.end() - 4);

                        auto adler32 = (
                            chunck.datas[chunck.datas.size() - 4] << 16 &
                            chunck.datas[chunck.datas.size() - 3] << 8 &
                            chunck.datas[chunck.datas.size() - 2] << 4 &
                            chunck.datas[chunck.datas.size() - 1]
                        );
                        if(!checker::png::adler32().check(chunck, adler32))
                        {
                            //throw std::exception() /* TODO : adler32 wrong */;
                        }

                        //auto line_size = content.width * content.bytes_per_pixel;
                        //content.datas.reserve(content.height * line_size);
                        //auto index = 0U;
                        //for(auto line = 0U; line < content.height; line++)
                        //{
                        //    auto filter_type = decompressed_datas.at(index);
                        //    index++;
                        //    for(auto p = 0U; p < line_size; p++)
                        //    {
                        //        auto filter_x = decompressed_datas.at(index);
                        //        index++;
                        //        if(filter_type == 0U) // None
                        //        {
                        //            content.datas.emplace_back(filter_x & 0xff);
                        //        }
                        //        else if(filter_type == 1U) // Sub
                        //        {
                        //            model::png::chunck::data_type d = 0;
                        //            if(p >= content.bytes_per_pixel)
                        //            {
                        //                d = content.datas.at(line * line_size + p - content.bytes_per_pixel);
                        //            }
                        //            content.datas.emplace_back((filter_x + d) & 0xff);
                        //        }
                        //        else if(filter_type == 2U) // Up
                        //        {
                        //            model::png::chunck::data_type d = 0;
                        //            if(line > 0U)
                        //            {
                        //                d = content.datas.at((line - 1) * line_size + p);
                        //            }
                        //            content.datas.emplace_back((filter_x + d) & 0xff);
                        //        }
                        //        else if(filter_type == 3U) // Average
                        //        {
                        //            model::png::chunck::data_type d1 = 0;
                        //            if(p >= content.bytes_per_pixel)
                        //            {
                        //                d1 = content.datas.at(line * line_size + p - content.bytes_per_pixel);
                        //            }
                        //            model::png::chunck::data_type d2 = 0;
                        //            if(line > 0U)
                        //            {
                        //                d2 = content.datas.at((line - 1) * line_size + p);
                        //            }
                        //            model::png::chunck::data_type d = std::floor((d1 + d2) / 2);
                        //            content.datas.emplace_back((filter_x + d) & 0xff);
                        //        }
                        //        else if(filter_type == 4U) // Paeth
                        //        {
                        //            model::png::chunck::data_type d1 = 0;
                        //            if(p >= content.bytes_per_pixel)
                        //            {
                        //                d1 = content.datas.at(line * line_size + p - content.bytes_per_pixel);
                        //            }
                        //            model::png::chunck::data_type d2 = 0;
                        //            if(line > 0U)
                        //            {
                        //                d2 = content.datas.at((line - 1) * line_size + p);
                        //            }
                        //            model::png::chunck::data_type d3 = 0;
                        //            if(line > 0U && p >= content.bytes_per_pixel)
                        //            {
                        //                d3 = content.datas.at((line - 1) * line_size + p - content.bytes_per_pixel);
                        //            }
                        //            model::png::chunck::data_type d = 0;
                        //            auto p = d1 + d2 - d3;
                        //            auto pd1 = std::abs(p - d1);
                        //            auto pd2 = std::abs(p - d2);
                        //            auto pd3 = std::abs(p - d3);
                        //            if(pd1 <= pd2 && pd1 <= pd3)
                        //            {
                        //                d = d1;
                        //            }
                        //            else if(pd2 <= pd3)
                        //            {
                        //                d = d2;
                        //            }
                        //            else
                        //            {
                        //                d = d3;
                        //            }
                        //            content.datas.emplace_back((filter_x + d) & 0xff);
                        //        }
                        //        else
                        //        {
                        //            throw std::exception() /* TODO : filter type not known */;
                        //        }
                        //    }
                        //}
                    }
                };
            }
        }
    }
}

#endif