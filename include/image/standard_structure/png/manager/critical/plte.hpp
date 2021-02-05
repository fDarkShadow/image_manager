#ifndef _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_PLTE_HPP_
#define _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_PLTE_HPP_

#include "image/model/png/chunck.hpp"
#include "image/model/png/content.hpp"

#include "image/exception/reader/png/wrong_palette_datas_nb.hpp"

namespace image
{
    namespace standard_structure
    {
        namespace png
        {
            namespace manager
            {
                struct plte
                {
                    void operator()(model::png::chunck const& chunck, model::png::content & content) const
                    {
                        if(chunck.datas.size() % 3 != 0)
                        {
                            throw exception::reader::wrong_palette_datas_nb<type::png>(chunck.datas.size());
                        }
                        content.palette_defined = true;
                    }
                };
            }
        }
    }
}

#endif