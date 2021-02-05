#ifndef _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_CRITICAL_DETAILS_INFLATORS_INFLATOR_HPP_
#define _IMAGE_STANDARD_STRUCTURE_PNG_MANAGER_CRITICAL_DETAILS_INFLATORS_INFLATOR_HPP_

#include <vector>

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
                        template<class I>
                        struct inflator
                        {
                            template<class T, class R>
                            std::vector<T> inflate(R & reader) const;
                        };
                    }
                }
            }
        }
    }
}

#endif