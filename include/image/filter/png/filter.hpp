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
            public:
                template<class T>
                std::vector<T> compute(
                    std::vector<T> const& datas,
                    uint32_t width,
                    uint32_t height,
                    float bytes_per_pixel
                ) const
                {
                    auto line_size = std::round(width * bytes_per_pixel);
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
                            if(filter_type == 0U)
                            {
                                filter_datas.emplace_back(filter_x & 0xff);
                            }
                            else if(filter_type == 1U)
                            {
                                auto filtered = filter_sub(filter_datas, line, colomn, line_size, bytes_per_pixel);
                                filter_datas.emplace_back((filter_x + filtered) & 0xff);
                            }
                            else if(filter_type == 2U)
                            {
                                auto filtered = filter_up(filter_datas, line, colomn, line_size, bytes_per_pixel);
                                filter_datas.emplace_back((filter_x + filtered) & 0xff);
                            }
                            else if(filter_type == 3U)
                            {
                                auto filtered = filter_average(filter_datas, line, colomn, line_size, bytes_per_pixel);
                                filter_datas.emplace_back((filter_x + filtered) & 0xff);
                            }
                            else if(filter_type == 4U)
                            {
                                auto filtered = filter_paeth(filter_datas, line, colomn, line_size, bytes_per_pixel);
                                filter_datas.emplace_back((filter_x + filtered) & 0xff);
                            }
                            else
                            {
                                throw std::exception() /* TODO : filter type not known */;
                            }
                        }
                    }
                    return filter_datas;
                }

            private:
                template<class T>
                T filter_sub(std::vector<T> const& filter_datas, uint32_t line, uint32_t colomn, uint32_t line_size, float bytes_per_pixel) const
                {
                    T data = 0;
                    if(colomn >= bytes_per_pixel)
                    {
                        data = filter_datas.at(line * line_size + colomn - bytes_per_pixel);
                    }
                    return data;
                }

                template<class T>
                T filter_up(std::vector<T> const& filter_datas, uint32_t line, uint32_t colomn, uint32_t line_size, float ) const
                {
                    T data = 0;
                    if(line > 0U)
                    {
                        data = filter_datas.at((line - 1) * line_size + colomn);
                    }
                    return data;
                }

                template<class T>
                T filter_average(std::vector<T> const& filter_datas, uint32_t line, uint32_t colomn, uint32_t line_size, float bytes_per_pixel) const
                {
                    auto data_sub = filter_sub(filter_datas, line, colomn, line_size, bytes_per_pixel);
                    auto data_up = filter_up(filter_datas, line, colomn, line_size, bytes_per_pixel);
                    auto data = std::floor((data_sub + data_up) / 2);
                    return data;
                }

                template<class T>
                T filter_paeth(std::vector<T> const& filter_datas, uint32_t line, uint32_t colomn, uint32_t line_size, float bytes_per_pixel) const
                {
                    auto data_sub = filter_sub(filter_datas, line, colomn, line_size, bytes_per_pixel);
                    auto data_up = filter_up(filter_datas, line, colomn, line_size, bytes_per_pixel);
                    T data_mid = 0;
                    if(line > 0U && colomn >= bytes_per_pixel)
                    {
                        data_mid = filter_datas.at((line - 1) * line_size + colomn - bytes_per_pixel);
                    }

                    T data = 0;
                    auto value = data_sub + data_up - data_mid;
                    auto paeth_sub = std::abs(value - data_sub);
                    auto paeth_up = std::abs(value - data_up);
                    auto paeth_mid = std::abs(value - data_mid);
                    if(paeth_sub <= paeth_up && paeth_sub <= paeth_mid)
                    {
                        data = paeth_sub;
                    }
                    else if(paeth_up <= paeth_mid)
                    {
                        data = paeth_up;
                    }
                    else
                    {
                        data = paeth_mid;
                    }

                    return data;
                }
            };
        }
    }
}

#endif