#ifndef _IMAGE_MODEL_PNG_STANDARD_CHUNCK_HPP_
#define _IMAGE_MODEL_PNG_STANDARD_CHUNCK_HPP_

#include "image/model/png/content.hpp"
#include "image/model/png/chunck.hpp"

#include <functional>

namespace image
{
    namespace model
    {
        namespace png
        {
            struct standard_chunck
            {
                public:
                    standard_chunck() = delete;
                    standard_chunck(
                        bool is_critical,
                        bool is_optional,
                        bool can_be_multiple,
                        std::function<void(model::png::chunck const&, model::png::content &)>&& functor
                    ) :
                        _is_critical(is_critical),
                        _is_optional(is_optional),
                        _can_be_multiple(can_be_multiple),
                        _functor(std::move(functor)),
                        _count(0U)
                    {}

                    void operator++()
                    {
                        _count++;
                    }

                    unsigned int count() const { return _count; }
                    bool is_critical() const { return _is_critical; }
                    bool is_optional() const { return _is_optional; }
                    bool can_be_multiple() const { return _can_be_multiple; }

                    void operator()(model::png::chunck const& chunck, model::png::content & content)
                    {
                        _functor(chunck, content);
                    }

                private:
                    bool _is_critical;
                    bool _is_optional;
                    bool _can_be_multiple;
                    std::function<void(model::png::chunck const&, model::png::content &)> _functor;
                    unsigned int _count;
            };
        }
    }
}

#endif