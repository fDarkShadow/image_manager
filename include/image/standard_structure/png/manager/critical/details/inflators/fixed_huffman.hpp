#ifndef _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_CRITICAL_DETAILS_INFLATORS_FIXED_HUFFMAN_HPP_
#define _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_CRITICAL_DETAILS_INFLATORS_FIXED_HUFFMAN_HPP_

#include "inflator.hpp"

#include "image/standard_structure/png/manager/critical/details/huffman_tree.hpp"

#include <utility>

namespace image
{
    namespace standard_structure
    {
        namespace png
        {
            namespace manager
            {
                namespace details
                {
                    namespace inflators
                    {
                        struct fixed_huffman;
                        template<>
                        struct inflator<fixed_huffman>
                        {
                        public:
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
                                    std::make_pair(131, 3),
                                    std::make_pair(163, 3),
                                    std::make_pair(195, 3),
                                    std::make_pair(227, 3),
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
                            {
                                std::vector<std::pair<uint16_t, std::size_t>> literal_length_alphabet(288);
                                for(auto i = 0U; i < literal_length_alphabet.size(); i++)
                                {
                                    auto length = 0;
                                    auto key = 0;
                                    if(i < 286)
                                    {
                                        key = i;
                                    }
                                    if(i < 144)
                                    {
                                        length = 8;
                                    }
                                    else if(i < 256)
                                    {
                                        length = 9;
                                    }
                                    else if(i < 280)
                                    {
                                        length = 7;
                                    }
                                    else
                                    {
                                        length = 8;
                                    }
                                    literal_length_alphabet[i] = std::make_pair(key, length);
                                }

                                std::vector<std::pair<uint16_t, std::size_t>> distance_alphabet(30);
                                for(auto i = 0U; i < distance_alphabet.size(); i++)
                                {
                                    distance_alphabet[i] = std::make_pair(i, 5);
                                }
                                _literal_length_tree = std::move(details::generate_canonical_huffman_tree(literal_length_alphabet));
                                _distance_tree = std::move(details::generate_canonical_huffman_tree(distance_alphabet));
                            }
                            
                            template<class T, class R>
                            std::vector<T> inflate(R & reader) const
                            {
                                std::vector<T> result;
                                while(true)
                                {
                                    auto symbol = _literal_length_tree.find(reader);
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
                                        uint8_t length = reader.template get_value<uint8_t>(_length_extra_def[symbol].second) + _length_extra_def[symbol].first;
                                        auto distance_symbol = _distance_tree.find(reader);
                                        uint16_t distance = reader.template get_value<uint16_t>(_distance_extra_def[distance_symbol].second) + _distance_extra_def[distance_symbol].first;
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
                                reader.flush();
                                return result;
                            }

                        private:
                            huffman_tree<uint16_t> _literal_length_tree;
                            huffman_tree<uint16_t> _distance_tree;
                            std::vector<std::pair<uint16_t, uint8_t>> _length_extra_def;
                            std::vector<std::pair<uint16_t, uint8_t>> _distance_extra_def;
                        };
                    }
                }
            }
        }
    }
}

#endif