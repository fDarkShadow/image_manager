#ifndef _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_CRITICAL_DETAILS_INFLATORS_NO_COMPRESSION_HPP_
#define _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_CRITICAL_DETAILS_INFLATORS_NO_COMPRESSION_HPP_

#include "inflator.hpp"

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
                        struct no_compression;
                        template<>
                        struct inflator<no_compression>
                        {
                        public:
                            template<class T, class R>
                            std::vector<T> inflate(R & reader) const
                            {
                                reader.flush();
                                auto length = reader.template get_value<uint16_t>(16);
                                auto length_comp = reader.template get_value<uint16_t>(16);
                                if((length ^ length_comp) != 0xffff)
                                {
                                    throw std::exception() /* TODO : correct */;
                                }
                                std::vector<T> result;
                                for(auto l = 0; l < length; l++)
                                {
                                    result.push_back(reader.template get_value<T>(8));
                                }
                                return result;
                            }
                        };
                    }
                }
            }
        }
    }
}

#endif