#ifndef _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_CRITICAL_DETAILS_HUFFMAN_TREE_HPP_
#define _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_CRITICAL_DETAILS_HUFFMAN_TREE_HPP_

#include <memory>

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
                    template<class T>
                    std::vector<bool> decompose(T value, std::size_t length)
                    {
                        if(length > (sizeof(T) * 8))
                        {
                            throw std::exception() /* TODO : too much to read */;
                        }
                        std::vector<bool> result;
                        result.reserve(length);
                        for(auto i = 0U; i < length; i++)
                        {
                            result.emplace_back((value >> (length - i - 1)) & 1);
                        }
                        return result;
                    }

                    template<class T>
                    struct huffman_tree
                    {
                        public:
                            huffman_tree() = default;
                            huffman_tree(std::vector<std::pair<T, std::vector<bool>>>&& codewords)
                            {
                                for(auto const& codeword : codewords)
                                {
                                    insert(codeword.first, codeword.second);
                                }
                            }

                            void insert(T value, std::vector<bool> codeword)
                            {
                                auto current = &_root;
                                for(auto bit = codeword.begin(); bit < codeword.end(); bit++)
                                {
                                    if(*bit)
                                    {
                                        if(!current->right())
                                        {
                                            if(bit != std::prev(codeword.end()))
                                            {
                                                current->set_right(std::make_shared<node>());
                                            }
                                            else
                                            {
                                                current->set_right(std::make_shared<node>(value));
                                            }
                                        }
                                        else if(*current->right().get())
                                        {
                                            throw std::exception() /* TODO : leaf is already defined */;
                                        }
                                        current = current->right().get();
                                    }
                                    else
                                    {
                                        if(!current->left())
                                        {
                                            if(bit != std::prev(codeword.end()))
                                            {
                                                current->set_left(std::make_shared<node>());
                                            }
                                            else
                                            {
                                                current->set_left(std::make_shared<node>(value));
                                            }
                                        }
                                        else if(*current->left().get())
                                        {
                                            throw std::exception() /* TODO : leaf is already defined */;
                                        }
                                        current = current->left().get();
                                    }
                                }
                            }

                            template<class I>
                            T find(I& i) const
                            {
                                auto current_node = &_root;
                                while(!*current_node)
                                {
                                    if(i++)
                                    {
                                        if(!current_node->right())
                                        {
                                            throw std::exception() /* TODO : not find */;
                                        }
                                        current_node = current_node->right().get();
                                    }
                                    else
                                    {
                                        if(!current_node->left())
                                        {
                                            throw std::exception() /* TODO : not find */;
                                        }
                                        current_node = current_node->left().get();
                                    }
                                }
                                return current_node->value();
                            }

                        private:
                            struct node
                            {
                                public:
                                    node() :
                                        _value(0),
                                        _value_defined(false)
                                    {}
                                    node(T value) :
                                        _value(value),
                                        _value_defined(true)
                                    {}

                                    void set_right(std::shared_ptr<node>&& n)
                                    {
                                        _right = std::move(n);
                                    }
                                    void set_left(std::shared_ptr<node>&& n)
                                    {
                                        _left = std::move(n);
                                    }

                                    std::shared_ptr<node> const& right() const
                                    {
                                        return _right;
                                    }
                                    std::shared_ptr<node> const& left() const
                                    {
                                        return _left;
                                    }

                                    operator bool() const
                                    {
                                        return _value_defined;
                                    }

                                    T value() const
                                    {
                                        return _value;
                                    }

                                private:
                                    T _value;
                                    bool _value_defined;
                                    std::shared_ptr<node> _left;
                                    std::shared_ptr<node> _right;
                            };

                            node _root;
                    };

                    template<class T>
                    huffman_tree<T> generate_canonical_huffman_tree(std::vector<std::pair<T, std::size_t>>& alphabet)
                    {
                        std::vector<std::pair<T, std::vector<bool>>> codewords;

                        auto max_bits_nb = std::max_element(alphabet.begin(), alphabet.end(), [](auto const& b1, auto const& b2) {return b1.second < b2.second; })->second;

                        std::vector<std::size_t> bits_lengths_count;
                        bits_lengths_count.reserve(max_bits_nb + 1);
                        for(auto y = 0U; y <= max_bits_nb; y++)
                        {
                            bits_lengths_count.emplace_back(
                                std::count_if(
                                    alphabet.begin(),
                                    alphabet.end(),
                                    [&y](auto const& x) { return x.second == y && y != 0U; }
                            ));
                        }

                        std::vector<std::size_t> next_code{0,0};
                        next_code.reserve(max_bits_nb + 2);
                        for(auto bits = 1U; bits < max_bits_nb; bits++)
                        {
                            next_code.emplace_back((next_code[bits] + bits_lengths_count[bits]) << 1);
                        }

                        for(auto const& letter : alphabet)
                        {
                            if(letter.second != 0)
                            {
                                codewords.emplace_back(std::make_pair(
                                    letter.first,
                                    decompose(next_code[letter.second], letter.second)
                                ));
                                next_code[letter.second]++;
                            }
                        }

                        return huffman_tree<T>(std::move(codewords));
                    }
                }
            }
        }
    }
}

#endif