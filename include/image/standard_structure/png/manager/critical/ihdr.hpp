#ifndef _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_IHDR_HPP_
#define _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_IHDR_HPP_

#include "image/model/png/chunck.hpp"
#include "image/model/png/content.hpp"

#include "image/type/png.hpp"

#include "image/exception/reader/png/wrong_data_size.hpp"
#include "image/exception/reader/png/wrong_width_dimension.hpp"
#include "image/exception/reader/png/wrong_height_dimension.hpp"
#include "image/exception/reader/png/wrong_bit_depth_for_color_type.hpp"
#include "image/exception/reader/png/wrong_color_type.hpp"

namespace image
{
    namespace standard_structure
    {
        namespace png
        {
            namespace manager
            {
                struct ihdr
                {
                    void operator()(model::png::chunck const& chunck, model::png::content & content) const
                    {
                        if(chunck.datas.size() != 13)
                        {
                            throw exception::reader::wrong_data_size<type::png>("IHDR", chunck.datas.size());
                        }
                        content.width = chunck.datas[0] << 24 | chunck.datas[1] << 16 | chunck.datas[2] << 8 | chunck.datas[3];
                        if(content.width == 0U)
                        {
                            throw exception::reader::wrong_width_dimension<type::png>(content.width);
                        }
                        content.height = chunck.datas[4] << 24 | chunck.datas[5] << 16 | chunck.datas[6] << 8 | chunck.datas[7];
                        if(content.height == 0U)
                        {
                            throw exception::reader::wrong_height_dimension<type::png>(content.height);
                        }
                        content.bit_depth = chunck.datas[8];
                        content.color_type = chunck.datas[9];
                        if(content.color_type == 0)
                        {
                            if(
                                content.bit_depth != 1 &&
                                content.bit_depth != 2 &&
                                content.bit_depth != 4 &&
                                content.bit_depth != 8 &&
                                content.bit_depth != 16
                            )
                            {
                                throw exception::reader::wrong_bit_depth_for_color_type<type::png>(content.color_type, content.bit_depth);
                            }
                        }
                        else if(content.color_type == 2)
                        {
                            if(
                                content.bit_depth != 8 &&
                                content.bit_depth != 16
                            )
                            {
                                throw exception::reader::wrong_bit_depth_for_color_type<type::png>(content.color_type, content.bit_depth);
                            }
                        }
                        else if(content.color_type == 3)
                        {
                            if(
                                content.bit_depth != 1 &&
                                content.bit_depth != 2 &&
                                content.bit_depth != 4 &&
                                content.bit_depth != 8
                            )
                            {
                                throw exception::reader::wrong_bit_depth_for_color_type<type::png>(content.color_type, content.bit_depth);
                            }
                        }
                        else if(content.color_type == 4)
                        {
                            if(
                                content.bit_depth != 8 &&
                                content.bit_depth != 16
                            )
                            {
                                throw exception::reader::wrong_bit_depth_for_color_type<type::png>(content.color_type, content.bit_depth);
                            }
                        }
                        else if(content.color_type == 6)
                        {
                            if(
                                content.bit_depth != 8 &&
                                content.bit_depth != 16
                            )
                            {
                                throw exception::reader::wrong_bit_depth_for_color_type<type::png>(content.color_type, content.bit_depth);
                            }
                        }
                        else
                        {
                            throw exception::reader::wrong_color_type<type::png>(content.color_type);
                        }
                        content.compression_method = chunck.datas[10];
                        content.filter_method = chunck.datas[11];
                        content.interlace_method = chunck.datas[12];
                    }
                };
            }
        }
    }
}

#endif