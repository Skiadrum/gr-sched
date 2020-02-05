#ifndef RUN_DUR_FLOWGRAPH_HPP
#define RUN_DUR_FLOWGRAPH_HPP

#include <gnuradio/top_block.h>
#include "sched/timestamp_in.h"
#include <sched/timestamp_out.h>

#include <gnuradio/blocks/copy.h>


#include <iostream>
#include <boost/program_options.hpp>

using namespace gr;

class run_dur_flowgraph {

private:

    int d_stages;
    int d_pipes;
    uint64_t d_samples;


    void create_fork();

public:
    run_dur_flowgraph(int stages, int pipes, uint64_t samples);

    ~run_dur_flowgraph();

    top_block_sptr tb;
    //sched::timestamp_in::sptr src;
    sched::timestamp_out::sptr sink;
    //std::vector<blocks::copy::sptr> blocks;

};


#endif
