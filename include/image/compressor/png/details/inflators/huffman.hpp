#ifndef _IMAGE_COMPRESSOR_PNG_DETAILS_INFLATORS_HUFFMAN_HPP_
#define _IMAGE_COMPRESSOR_PNG_DETAILS_INFLATORS_HUFFMAN_HPP_

#include "inflator.hpp"

#include "image/compressor/png/details/huffman_tree.hpp"

#include <array>
#include <utility>

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
                    struct huffman;
                    template<>
                    struct inflator<huffman>
                    {
                    protected:
                        inflator() :
                            _length_extra_def({
                                std::make_pair(3, 0),
                                std::make_pair(4, 0),
                                std::make_pair(5, 0),
                                std::make_pair(6, 0),
                                std::make_pair(7, 0),
                                std::make_pair(8, 0),
                                std::make_pair(9, 0),
                                std::make_pair(10, 0),
                                std::make_pair(11, 1),
                                std::make_pair(13, 1),
                                std::make_pair(15, 1),
                                std::make_pair(17, 1),
                                std::make_pair(19, 2),
                                std::make_pair(23, 2),
                                std::make_pair(27, 2),
                                std::make_pair(31, 2),
                                std::make_pair(35, 3),
                                std::make_pair(43, 3),
                                std::make_pair(51, 3),
                                std::make_pair(59, 3),
                                std::make_pair(67, 4),
                                std::make_pair(83, 4),
                                std::make_pair(99, 4),
                                std::make_pair(115, 4),
                                std::make_pair(131, 5),
                                std::make_pair(163, 5),
                                std::make_pair(195, 5),
                                std::make_pair(227, 5),
                                std::make_pair(258, 0)
                            }),
                            _distance_extra_def({
                                std::make_pair(1, 0),
                                std::make_pair(2, 0),
                                std::make_pair(3, 0),
                                std::make_pair(4, 0),
                                std::make_pair(5, 1),
                                std::make_pair(7, 1),
                                std::make_pair(9, 2),
                                std::make_pair(13, 2),
                                std::make_pair(17, 3),
                                std::make_pair(25, 3),
                                std::make_pair(33, 4),
                                std::make_pair(49, 4),
                                std::make_pair(65, 5),
                                std::make_pair(97, 5),
                                std::make_pair(129, 6),
                                std::make_pair(193, 6),
                                std::make_pair(257, 7),
                                std::make_pair(385, 7),
                                std::make_pair(513, 8),
                                std::make_pair(769, 8),
                                std::make_pair(1025, 9),
                                std::make_pair(1537, 9),
                                std::make_pair(2049, 10),
                                std::make_pair(3073, 10),
                                std::make_pair(4097, 11),
                                std::make_pair(6145, 11),
                                std::make_pair(8193, 12),
                                std::make_pair(12289, 12),
                                std::make_pair(16385, 13),
                                std::make_pair(24577, 13)
                            })
                        {}

                        virtual ~inflator() = default;

                        template<class T, class R, class F>
                        std::vector<T> inflate(R & reader, F trees_finder) const
                        {
                            std::vector<T> result;
                            auto trees = trees_finder(reader);
                            while(true)
                            {
                                auto symbol = trees.first.find(reader);
                                if(symbol <= 255)
                                {
                                    result.push_back(symbol);
                                }
                                else if(symbol == 256)
                                {
                                    break;
                                }
                                else if(symbol < 286)
                                {
                                    symbol -= 257;
                                    std::size_t length = reader.template get_value<uint8_t>(_length_extra_def[symbol].second) + _length_extra_def[symbol].first;
                                    auto distance_symbol = trees.second.find(reader);
                                    std::size_t distance = reader.template get_value<uint16_t>(_distance_extra_def[distance_symbol].second) + _distance_extra_def[distance_symbol].first;
                                    for(auto i = 0U; i < length; i++)
                                    {
                                        auto it = result.end();
                                        std::advance(it, -distance);
                                        result.emplace_back(*it);
                                    }
                                }
                                else
                                {
                                    throw std::exception() /* TODO : not known symbol */;
                                }
                            }
                            return result;
                        }

                    private:
                        std::array<std::pair<uint16_t, uint8_t>, 29> _length_extra_def;
                        std::array<std::pair<uint16_t, uint8_t>, 30> _distance_extra_def;
                    };
                }
            }
        }
    }
}

#endif