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
#include "timestamp_in_impl.h"

#include <chrono>
#include <ctime>

namespace gr {
    namespace sched {

        timestamp_in::sptr
        timestamp_in::make() {
            return gnuradio::get_initial_sptr
                    (new timestamp_in_impl());
        }


        /*
         * The private constructor
         */
        timestamp_in_impl::timestamp_in_impl()
                : gr::block("timestamp_in",
                            gr::io_signature::make(0, 0, 0),
                            gr::io_signature::make(1, 1, sizeof(1))) {
        }

        /*
         * Our virtual destructor.
         */
        timestamp_in_impl::~timestamp_in_impl() {
        }

        void
        timestamp_in_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required) {
            /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
        }

        int
        timestamp_in_impl::general_work(int noutput_items,
                                        gr_vector_int &ninput_items,
                                        gr_vector_const_void_star &input_items,
                                        gr_vector_void_star &output_items) {

            auto duration = std::chrono::high_resolution_clock::now().time_since_epoch();
            auto nano = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();

           // std::cout << "Start computation at " << nano << std::endl;

            add_item_tag(0,
                         nitems_written(0),
                         pmt::mp("Start_Time"),
                         pmt::from_long(nano));

            return noutput_items;

        }

    } /* namespace sched */
} /* namespace gr */

