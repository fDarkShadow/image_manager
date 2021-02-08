#ifndef _IMAGE_STREAM_PNG_STREAM_READER_HPP_
#define _IMAGE_STREAM_PNG_STREAM_READER_HPP_

#include <vector>

namespace image
{
    namespace stream
    {
        namespace png
        {
            template<class T>
            struct stream_reader
            {
                public:
                    stream_reader() = delete;
                    stream_reader(std::vector<T> const& datas) :
                        _end(datas.cend()),
                        _it(datas.cbegin()),
                        _position(0U)
                    {}

                    bool operator++(int)
                    {
                        if(_position == 8U)
                        {
                            flush();
                        }
                        _position++;
                        return (*_it >> (_position - 1U)) & 1;
                    }

                    template<class R>
                    R get_value(std::size_t nb_bits)
                    {
                        if(nb_bits > (sizeof(R) * 8))
                        {
                            throw std::exception() /* TODO : cant read more 32 bits at a time */;
                        }
                        R result = 0;
                        auto range = nb_bits / 8;
                        if(nb_bits % 8 != 0)
                        {
                            range++;
                        }
                        for(auto byte = 0U; byte < range; byte++)
                        {
                            auto b = 0;
                            for(auto i = 0U; i < 8U && (8 * byte + i) < nb_bits; i++)
                            {
                                b |= (operator++(0) << i);
                            }
                            result |= b << (8 * byte);
                        }
                        return result;
                    }

                    void flush()
                    {
                        if(_it == _end)
                        {
                            throw std::exception() /* TODO : correct */;
                        }
                        _it++;
                        _position = 0U;
                    }

                private:
                    typename std::vector<T>::const_iterator _end;
                    typename std::vector<T>::const_iterator _it;
                    uint8_t _position;
            };
        }
    }
}

#endif