#ifndef _IMAGE_FILTER_PNG_FILTER_HPP_
#define _IMAGE_FILTER_PNG_FILTER_HPP_

#include <vector>
#include <cmath>

namespace image
{
    namespace filter
    {
        namespace png
        {
            struct filter
            {
                //template<class T>
                //T filter_a(T value)
                //{
                //    T t = 0;
                //    if(p >= bytes_per_pixel)
                //    {
                //        d = filter_datas.at(line * line_size + p - bytes_per_pixel);
                //    }
                //}
                
                template<class T>
                std::vector<T> compute(
                    std::vector<T> const& datas,
                    uint32_t width,
                    uint32_t height,
                    uint8_t bytes_per_pixel
                ) const
                {
                    auto line_size = width * bytes_per_pixel;
                    std::vector<T> filter_datas;
                    filter_datas.reserve(height * line_size);
                    auto index = 0U;
                    for(auto line = 0U; line < height; line++)
                    {
                        auto filter_type = datas.at(index);
                        index++;
                        for(auto colomn = 0U; colomn < line_size; colomn++)
                        {
                            auto filter_x = datas.at(index);
                            index++;
                            if(filter_type == 0U) // None
                            {
                                filter_datas.emplace_back(filter_x & 0xff);
                            }
                            else if(filter_type == 1U) // Sub
                            {
                                T d = 0;
                                if(colomn >= bytes_per_pixel)
                                {
                                    d = filter_datas.at(line * line_size + colomn - bytes_per_pixel);
                                }
                                filter_datas.emplace_back((filter_x + d) & 0xff);
                            }
                            else if(filter_type == 2U) // Up
                            {
                                T d = 0;
                                if(line > 0U)
                                {
                                    d = filter_datas.at((line - 1) * line_size + colomn);
                                }
                                filter_datas.emplace_back((filter_x + d) & 0xff);
                            }
                            else if(filter_type == 3U) // Average
                            {
                                T d1 = 0;
                                if(colomn >= bytes_per_pixel)
                                {
                                    d1 = filter_datas.at(line * line_size + colomn - bytes_per_pixel);
                                }
                                T d2 = 0;
                                if(line > 0U)
                                {
                                    d2 = filter_datas.at((line - 1) * line_size + colomn);
                                }
                                T d = std::floor((d1 + d2) / 2);
                                filter_datas.emplace_back((filter_x + d) & 0xff);
                            }
                            else if(filter_type == 4U) // Paeth
                            {
                                T d1 = 0;
                                if(colomn >= bytes_per_pixel)
                                {
                                    d1 = filter_datas.at(line * line_size + colomn - bytes_per_pixel);
                                }
                                T d2 = 0;
                                if(line > 0U)
                                {
                                    d2 = filter_datas.at((line - 1) * line_size + colomn);
                                }
                                T d3 = 0;
                                if(line > 0U && colomn >= bytes_per_pixel)
                                {
                                    d3 = filter_datas.at((line - 1) * line_size + colomn - bytes_per_pixel);
                                }
                                T d = 0;
                                auto p = d1 + d2 - d3;
                                auto pd1 = std::abs(p - d1);
                                auto pd2 = std::abs(p - d2);
                                auto pd3 = std::abs(p - d3);
                                if(pd1 <= pd2 && pd1 <= pd3)
                                {
                                    d = d1;
                                }
                                else if(pd2 <= pd3)
                                {
                                    d = d2;
                                }
                                else
                                {
                                    d = d3;
                                }
                                filter_datas.emplace_back((filter_x + d) & 0xff);
                            }
                            else
                            {
                                throw std::exception() /* TODO : filter type not known */;
                            }
                        }
                    }
                    return filter_datas;
                }
            };
        }
    }
}

#endif