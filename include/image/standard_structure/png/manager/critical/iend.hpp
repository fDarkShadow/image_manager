#ifndef _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_IEND_HPP_
#define _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_IEND_HPP_

#include "image/model/png/chunck.hpp"
#include "image/model/png/content.hpp"

#include "image/exception/reader/png/wrong_end_size.hpp"

namespace image
{
    namespace standard_structure
    {
        namespace png
        {
            namespace manager
            {
                struct iend
                {
                    void operator()(model::png::chunck const& chunck, model::png::content & ) const
                    {
                        if(!chunck.datas.empty())
                        {
                            throw exception::reader::wrong_end_size<type::png>(chunck.datas.size());
                        }
                    }
                };
            }
        }
    }
}

#endif