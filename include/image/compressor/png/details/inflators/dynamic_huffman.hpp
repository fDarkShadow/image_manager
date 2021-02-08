#ifndef _IMAGE_COMPRESSOR_PNG_DETAILS_INFLATORS_DYNAMIC_HUFFMAN_HPP_
#define _IMAGE_COMPRESSOR_PNG_DETAILS_INFLATORS_DYNAMIC_HUFFMAN_HPP_

#include "huffman.hpp"

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
                    struct dynamic_huffman;
                    template<>
                    struct inflator<dynamic_huffman> : inflator<huffman>
                    {
                    public:
                        inflator() :
                            inflator<huffman>(),
                            _code_length_codes_order({16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15})
                        {}

                        template<class T, class R>
                        std::vector<T> inflate(R & reader) const
                        {
                            auto tree_computer = [this](R & reader){
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
                            };
                            return inflator<huffman>::inflate<T>(reader, tree_computer);
                        }

                    private:
                        std::array<std::size_t, 19> _code_length_codes_order;
                    };
                }
            }
        }
    }
}

#endif