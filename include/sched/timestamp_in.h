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

#ifndef INCLUDED_SCHED_TIMESTAMP_IN_H
#define INCLUDED_SCHED_TIMESTAMP_IN_H

#include <sched/api.h>
#include <gnuradio/block.h>

namespace gr {
    namespace sched {

        /*!
         * \brief <+description of block+>
         * \ingroup sched
         *
         */
        class SCHED_API timestamp_in : virtual public gr::block {
        public:
            typedef boost::shared_ptr<timestamp_in> sptr;

            /*!
             * \brief Return a shared_ptr to a new instance of sched::timestamp_in.
             *
             * To avoid accidental use of raw pointers, sched::timestamp_in's
             * constructor is in a private implementation
             * class. sched::timestamp_in::make is the public interface for
             * creating new instances.
             */
            static sptr make();
        };

    } // namespace sched
} // namespace gr

#endif /* INCLUDED_SCHED_TIMESTAMP_IN_H */

