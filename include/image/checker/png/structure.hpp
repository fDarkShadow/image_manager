#ifndef _IMAGE_CHECKER_PNG_STRUCTURE_HPP_
#define _IMAGE_CHECKER_PNG_STRUCTURE_HPP_

#include "image/model/png/standard_chunck.hpp"

#include <map>
#include <string>
#include <algorithm>

namespace image
{
    namespace checker
    {
        namespace png
        {
            struct structure
            {
                public:
                    structure(std::map<std::string, model::png::standard_chunck>& chuncks_standard) :
                        _chuncks_standard(std::ref(chuncks_standard))
                    {}

                    bool check(model::png::chunck const& chunck)
                    {
                        auto standard = _chuncks_standard.get().find(chunck.type);
                        if(standard == _chuncks_standard.get().end())
                        {
                            return false;
                        }
                        if(chunck.type != "IEND")
                        {
                            if(_chuncks_standard.get().at("IEND").count() != 0U)
                            {
                                return false;
                            }
                        }
                        else
                        {
                            auto all_required = std::any_of(_chuncks_standard.get().begin(), _chuncks_standard.get().end(), [](auto const& standard){return !standard.second.is_optional() && standard.second.count() != 0U;});
                            if(!all_required)
                            {
                                return false;
                            }
                        }

                        if(chunck.type == "IHDR")
                        {
                            auto has_chunk = std::any_of(_chuncks_standard.get().begin(), _chuncks_standard.get().end(), [](auto const& standard){return standard.second.count() != 0U;});
                            if(has_chunk)
                            {
                                return false;
                            }
                        }
                        else if(
                            chunck.type == "PLTE" ||
                            chunck.type == "pHYs" ||
                            chunck.type == "sPLT"
                        )
                        {
                            if(_chuncks_standard.get().at("IDAT").count() != 0U)
                            {
                                return false;
                            }
                        }
                        else if(chunck.type == "gAMA")
                        {
                            if(
                                _chuncks_standard.get().at("PLTE").count() != 0U ||
                                _chuncks_standard.get().at("IDAT").count() != 0U
                            )
                            {
                                return false;
                            }
                        }
                        else if(
                            chunck.type == "cHRM" ||
                            chunck.type == "iCCP" ||
                            chunck.type == "sBIT" ||
                            chunck.type == "sRGB"
                        )
                        {
                            if(
                                _chuncks_standard.get().at("PLTE").count() != 0U ||
                                _chuncks_standard.get().at("IDAT").count() == 0U
                            )
                            {
                                return false;
                            }
                        }
                        else if(
                            chunck.type == "bKGD" ||
                            chunck.type == "hIST" ||
                            chunck.type == "tRNS"
                        )
                        {
                            if(
                                _chuncks_standard.get().at("IDAT").count() != 0U ||
                                _chuncks_standard.get().at("PLTE").count() == 0U
                            )
                            {
                                return false;
                            }
                        }
                        ++standard->second;
                        return true;
                    }

                private:
                    std::reference_wrapper<std::map<std::string, model::png::standard_chunck>> _chuncks_standard;
            };
        }
    }
}

#endif