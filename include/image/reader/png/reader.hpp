#ifndef _IMAGE_READER_READER_PNG_HPP_
#define _IMAGE_READER_READER_PNG_HPP_

#include "image/reader/reader.hpp"
#include "image/type/png.hpp"

#include "image/signature/png/reader.hpp"
#include "image/signature/png/standard.hpp"

#include "image/checker/png/crc.hpp"
#include "image/checker/png/structure.hpp"

#include "image/model/png/chunck.hpp"
#include "chunck_reader.hpp"

#include "image/standard_structure/png/chuncks.hpp"

#include "image/compressor/png/decompressor.hpp"
#include "image/filter/png/filter.hpp"

#include "image/model/png/content.hpp"
#include "image/model/image.hpp"

#include "image/exception/reader/png/wrong_signature.hpp"
#include "image/exception/reader/png/wrong_crc.hpp"
#include "image/exception/reader/png/wrong_structure.hpp"

namespace image
{
    namespace reader
    {
        template<>
        struct reader<type::png>
        {
            using image_type = type::png;

            std::map<std::string, model::png::standard_chunck> _standard_chuncks;
            compressor::png::decompressor _decompressor;
            filter::png::filter _filter;

            reader() :
                _standard_chuncks(standard_structure::png::chuncks::get()),
                _decompressor(),
                _filter()
            {}

            template<class Stream>
            model::image read_image(Stream & stream)
            {
                auto signature_read = signature::reader<image_type>::read_signature(stream);
                auto signature_default = signature::standard<image_type>::get_signature();
                if(signature_read != signature_default)
                {
                    throw exception::reader::wrong_signature<image_type>(signature_read, signature_default);
                }

                model::image image_read;
                {
                    model::png::content content;
                    checker::png::crc crc_checker;
                    checker::png::structure structure_checker(_standard_chuncks);
                    model::png::chunck chunck;
                    do
                    {
                        chunck = chunck_reader::read_chunk(stream);
                        if(!crc_checker.check(chunck))
                        {
                            throw exception::reader::wrong_crc<image_type>(chunck);
                        }
                        if(!structure_checker.check(chunck))
                        {
                            throw exception::reader::wrong_structure<image_type>(chunck);
                        }
                        auto standard_chunck = _standard_chuncks.find(chunck.type);
                        if(standard_chunck != _standard_chuncks.end())
                        {
                            standard_chunck->second(chunck, content);
                        }
                    } while(chunck.type != "IEND" && !stream.eof());

                    auto decompressed_datas = _decompressor.decompress(content.datas);
                    auto filtered_datas = _filter.compute(decompressed_datas, content.width, content.height, content.bytes_per_pixel);

                    image_read.width = content.width;
                    image_read.height = content.height;
                    image_read.pixels.reserve(image_read.width * image_read.height);
                    for(auto i = 0U; i < filtered_datas.size(); i+=4U)
                    {
                        image_read.pixels.emplace_back(std::make_tuple(
                            filtered_datas[i],
                            filtered_datas[i+1],
                            filtered_datas[i+2],
                            filtered_datas[i+3]
                        ));
                    }
                }

                return image_read;
            }
        };
    }
}

#endif