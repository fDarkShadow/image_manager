#ifndef _IMAGE_CHECKER_PNG_CRC_HPP_
#define _IMAGE_CHECKER_PNG_CRC_HPP_

#include "image/model/png/chunck.hpp"
#include <array>

namespace image
{
    namespace checker
    {
        namespace png
        {
            struct crc
            {
                public:
                    crc()
                    {
                        for(uint32_t i = 0U; i < 256U; i++)
                        {
                            auto crc = i;
                            for(uint32_t j = 0U; j < 8U; j++)
                            {
                                if(crc & 1)
                                {
                                    crc = 0xedb88320L ^ (crc >> 1);
                                }
                                else
                                {
                                    crc = crc >> 1;
                                }
                            }
                            _crc_table[i] = crc;
                        }
                    }

                    bool check(model::png::chunck const& chunck)
                    {
                        uint32_t crc = 0xffffffff;
                        for(uint32_t data : chunck.type)
                        {
                            crc = _crc_table.at((crc ^ data) & 0xff) ^ (crc >> 8);
                        }
                        for(uint32_t const& data : chunck.datas)
                        {
                            crc = _crc_table.at((crc ^ data) & 0xff) ^ (crc >> 8);
                        }

                        crc ^= 0xffffffff;

                        return crc == chunck.crc;
                    }

                private:
                    std::array<uint32_t, 256> _crc_table;
            };
        }
    }
}

#endif