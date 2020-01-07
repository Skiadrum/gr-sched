/* -*- c++ -*- */
/*
 * Copyright 2019 gr-sched author.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "timestamp_out_impl.h"

#include <chrono>
#include <ctime>

namespace gr {
    namespace sched {

        timestamp_out::sptr
        timestamp_out::make() {
            return gnuradio::get_initial_sptr
                    (new timestamp_out_impl());
        }


        /*
         * The private constructor
         */
        timestamp_out_impl::timestamp_out_impl()
                : gr::sync_block("timestamp_out",
                                 gr::io_signature::make(1, 1, sizeof(1)),
                                 gr::io_signature::make(0, 0, 0)) {
        }

        /*
         * Our virtual destructor.
         */
        timestamp_out_impl::~timestamp_out_impl() {
        }

        std::string vectorToString(std::vector<tag_t> vec) {
            std::string elementText = "[";
            for (tag_t tag : vec) {
                elementText += " " +
                               pmt::symbol_to_string(tag.key) + ": " +
                               std::to_string(pmt::to_long(tag.value)) + "  ";

            }
            elementText += "]";

            return elementText;
        }

        std::vector<long> timestamp_out_impl::getResults() {
            return results;
        }

        int
        timestamp_out_impl::work(int noutput_items,
                                 gr_vector_const_void_star &input_items,
                                 gr_vector_void_star &output_items) {

            auto duration = std::chrono::high_resolution_clock::now().time_since_epoch();
            auto nano = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();

            std::vector<tag_t> tags;
            uint64_t nread = this->nitems_read(0);

            get_tags_in_range(tags,
                              0,
                              nread,
                              nread + noutput_items,
                              pmt::mp("Start_Time"));

            std::ofstream myfile;
            myfile.open ("example.csv");
            myfile << "Duration\n";

            for (tag_t tag : tags) {
                double test = nano - pmt::to_double(tag.value);
                results.push_back(test);
            //    myfile << test << std::endl;

                std::cout << "Duration " << test << std::endl;
            }


            for (auto i = results.begin(); i != results.end(); ++i) {
            //    std::cout << *i << ' ';
                myfile << *i << std::endl;
            }

            myfile.close();

            return noutput_items;
        }


    } /* namespace sched */
} /* namespace gr */