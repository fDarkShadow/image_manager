#ifndef _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_CRITICAL_DETAILS_INFLATORS_DYNAMIC_HUFFMAN_HPP_
#define _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_CRITICAL_DETAILS_INFLATORS_DYNAMIC_HUFFMAN_HPP_

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
                        struct dynamic_huffman;
                        template<>
                        struct inflator<dynamic_huffman>
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
                                    std::make_pair(24577, 13),
                                }),
                                _code_length_codes_order({16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15})
                            {}

                            template<class T, class R>
                            std::vector<T> inflate(R & reader) const
                            {
                                auto trees = get_trees(reader);
                                std::vector<T> result;
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
                                reader.flush();
                                return result;
                            }

                        private:
                            std::vector<std::pair<uint16_t, uint8_t>> _length_extra_def;
                            std::vector<std::pair<uint16_t, uint8_t>> _distance_extra_def;
                            std::vector<std::size_t> _code_length_codes_order;

                            template<class R>
                            std::pair<huffman_tree<uint16_t>, huffman_tree<uint16_t>> get_trees(R & reader) const
                            {
                                std::size_t hlit = reader.template get_value<uint8_t>(5) + 257;
                                std::size_t hdist = reader.template get_value<uint8_t>(5) + 1;
                                std::size_t hclen = reader.template get_value<uint8_t>(4) + 4;

                                std::vector<std::pair<std::size_t, std::size_t>> code_length_tree_bits_length(19);
                                for(auto i = 0U; i < code_length_tree_bits_length.size(); i++)
                                {
                                    code_length_tree_bits_length[i].first = i;
                                    if(i < hclen)
                                    {
                                        code_length_tree_bits_length[_code_length_codes_order[i]].second = reader.template get_value<uint8_t>(3);
                                    }
                                }
                                auto code_length_tree = details::generate_canonical_huffman_tree(code_length_tree_bits_length);

                                std::vector<std::size_t> length_codes;
                                length_codes.reserve(hlit + hdist);
                                while(length_codes.size() < length_codes.capacity())
                                {
                                    auto symbol = code_length_tree.find(reader);
                                    if(symbol < 16U)
                                    {
                                        length_codes.emplace_back(symbol);
                                    }
                                    else if(symbol == 16U)
                                    {
                                        std::size_t repeat = reader.template get_value<std::size_t>(2) + 3;
                                        auto previous = length_codes.back();
                                        for(auto j = 0U; j < repeat; j++)
                                        {
                                            length_codes.emplace_back(previous);
                                        }
                                    }
                                    else if(symbol == 17U)
                                    {
                                        std::size_t repeat = reader.template get_value<std::size_t>(3) + 3;
                                        for(auto j = 0U; j < repeat; j++)
                                        {
                                            length_codes.emplace_back(0);
                                        }
                                    }
                                    else if(symbol == 18U)
                                    {
                                        std::size_t repeat = reader.template get_value<std::size_t>(7) + 11;
                                        for(auto j = 0U; j < repeat; j++)
                                        {
                                            length_codes.emplace_back(0);
                                        }
                                    }
                                    else
                                    {
                                        throw std::exception() /* TODO : code unknown */;
                                    }
                                }
                                std::vector<std::pair<uint16_t, std::size_t>> literal_length_alphabet;
                                literal_length_alphabet.reserve(286);
                                for(auto i = 0U; i < std::min(hlit, literal_length_alphabet.capacity()); i++)
                                {
                                    literal_length_alphabet.emplace_back(std::make_pair(i, length_codes[i]));
                                }
                                std::vector<std::pair<uint16_t, std::size_t>> distance_alphabet;
                                distance_alphabet.reserve(30);
                                for(auto i = 0U; i < std::min(length_codes.size() - hlit, distance_alphabet.capacity()); i++)
                                {
                                    distance_alphabet.emplace_back(std::make_pair(i, length_codes[i + hlit]));
                                }

                                auto literal_length_tree = details::generate_canonical_huffman_tree(literal_length_alphabet);
                                auto distance_tree = details::generate_canonical_huffman_tree(distance_alphabet);

                                return std::make_pair(literal_length_tree, distance_tree);
                            }
                        };
                    }
                }
            }
        }
    }
}

#endif