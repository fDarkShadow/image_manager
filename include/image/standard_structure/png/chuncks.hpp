#ifndef _IMAGE_STANDARD_STRUCTURE_PNG_CHUNCKS_HPP_
#define _IMAGE_STANDARD_STRUCTURE_PNG_CHUNCKS_HPP_

#include "image/model/png/standard_chunck.hpp"
#include "image/model/png/chunck.hpp"
#include "image/model/png/content.hpp"

#include "manager/critical/ihdr.hpp"
#include "manager/critical/plte.hpp"
#include "manager/critical/idat.hpp"
#include "manager/critical/iend.hpp"

#include "manager/ancillary/chrm.hpp"
#include "manager/ancillary/gama.hpp"
#include "manager/ancillary/iccp.hpp"
#include "manager/ancillary/sbit.hpp"
#include "manager/ancillary/srgb.hpp"
#include "manager/ancillary/bkgd.hpp"
#include "manager/ancillary/hist.hpp"
#include "manager/ancillary/trns.hpp"
#include "manager/ancillary/phys.hpp"
#include "manager/ancillary/splt.hpp"
#include "manager/ancillary/time.hpp"
#include "manager/ancillary/itxt.hpp"
#include "manager/ancillary/text.hpp"
#include "manager/ancillary/ztxt.hpp"

#include <map>

namespace image
{
    namespace standard_structure
    {
        namespace png
        {
            struct chuncks
            {
                public:
                    static std::map<std::string, model::png::standard_chunck> get()
                    {
                        return {
                            std::make_pair("IHDR", model::png::standard_chunck(true, false, false, manager::ihdr())),
                            std::make_pair("PLTE", model::png::standard_chunck(true, true, false, manager::plte())),
                            std::make_pair("IDAT", model::png::standard_chunck(true, false, true, manager::idat())),
                            std::make_pair("IEND", model::png::standard_chunck(true, false, false, manager::iend())),
                            std::make_pair("cHRM", model::png::standard_chunck(false, true, false, manager::chrm())),
                            std::make_pair("gAMA", model::png::standard_chunck(false, true, false, manager::gama())),
                            std::make_pair("iCCP", model::png::standard_chunck(false, true, false, manager::iccp())),
                            std::make_pair("sBIT", model::png::standard_chunck(false, true, false, manager::sbit())),
                            std::make_pair("sRGB", model::png::standard_chunck(false, true, false, manager::srgb())),
                            std::make_pair("bKGD", model::png::standard_chunck(false, true, false, manager::bkgd())),
                            std::make_pair("hIST", model::png::standard_chunck(false, true, false, manager::hist())),
                            std::make_pair("tRNS", model::png::standard_chunck(false, true, false, manager::trns())),
                            std::make_pair("pHYs", model::png::standard_chunck(false, true, false, manager::phys())),
                            std::make_pair("sPLT", model::png::standard_chunck(false, true, true, manager::splt())),
                            std::make_pair("tIME", model::png::standard_chunck(false, true, false, manager::time())),
                            std::make_pair("iTXt", model::png::standard_chunck(false, true, true, manager::itxt())),
                            std::make_pair("tEXt", model::png::standard_chunck(false, true, true, manager::text())),
                            std::make_pair("zTXt", model::png::standard_chunck(false, true, true, manager::ztxt()))
                        };
                    }
            };
        }
    }
}

#endif