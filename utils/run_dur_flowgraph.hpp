#ifndef RUN_DUR_FLOWGRAPH_HPP
#define RUN_DUR_FLOWGRAPH_HPP

#include <gnuradio/top_block.h>
#include "sched/timestamp_in.h"
#include <sched/timestamp_out.h>

#include <iostream>
#include <boost/program_options.hpp>

using namespace gr;

class run_dur_flowgraph {

private:

    int d_stages;

public:
    explicit run_dur_flowgraph(int stages);
        ~run_dur_flowgraph();

    top_block_sptr tb;
    sched::timestamp_out::sptr src;
};


#endif
