#ifndef _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_SPLT_HPP_
#define _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_SPLT_HPP_

#include "image/model/png/chunck.hpp"
#include "image/model/png/content.hpp"

namespace image
{
    namespace standard_structure
    {
        namespace png
        {
            namespace manager
            {
                struct splt
                {
                    void operator()(model::png::chunck const& , model::png::content & ) const
                    {

                    }
                };
            }
        }
    }
}

#endif