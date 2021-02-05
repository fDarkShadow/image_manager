#ifndef _IMAGE_MODEL_PNG_CHUNCK_HPP_
#define _IMAGE_MODEL_PNG_CHUNCK_HPP_

#include <string>
#include <vector>

namespace image
{
    namespace model
    {
        namespace png
        {
            struct chunck
            {
                public:
                    using size_type = uint32_t;
                    using type_type = std::string;
                    using data_type = unsigned char;
                    using datas_type = std::vector<data_type>;
                    using crc_type = uint32_t;

                    size_type size;
                    type_type type;
                    datas_type datas;
                    crc_type crc;
            };
        }
    }
}

#endif