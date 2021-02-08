#ifndef _IMAGE_COMPRESSOR_PNG_DETAILS_INFLATORS_FIXED_HUFFMAN_HPP_
#define _IMAGE_COMPRESSOR_PNG_DETAILS_INFLATORS_FIXED_HUFFMAN_HPP_

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
                    struct fixed_huffman;
                    template<>
                    struct inflator<fixed_huffman> : inflator<huffman>
                    {
                    public:
                        inflator() :
                            inflator<huffman>()
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
                            auto tree_computer = [this](R &){
                                return std::make_pair(_literal_length_tree, _distance_tree);
                            };
                            return inflator<huffman>::inflate<T>(reader, tree_computer);
                        }

                    private:
                        huffman_tree<uint16_t> _literal_length_tree;
                        huffman_tree<uint16_t> _distance_tree;
                    };
                }
            }
        }
    }
}

#endif