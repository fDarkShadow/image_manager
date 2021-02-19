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
                        content.flag_check = flag & 0x1f;
                        content.flag_dict = (flag >> 5) & 1;
                        content.flag_level = (flag >> 6) & 0b11;

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
                    }
                };
            }
        }
    }
}

#endif