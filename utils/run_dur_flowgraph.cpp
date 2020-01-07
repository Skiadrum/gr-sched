#include "run_dur_flowgraph.hpp"

#include <chrono>
#include <boost/format.hpp>
#include <gnuradio/realtime.h>

namespace po = boost::program_options;

using namespace gr;


run_dur_flowgraph::run_dur_flowgraph(int stages) :
    d_stages(stages) {

    this->tb = make_top_block("dur_flowgraph");

    }

/**
void
run_dur_flowgraph::create_fork() {

    src = sched::timestamp_out::make();

    sched::timestamp_out::sptr prev;

    for(int pipe = 0; pipe < d_pipes; pipe++) {
        prev = sched::timestamp_out::make();
        tb->msg_connect(src, "out", prev, "in");

        for(int stage = 1; stage < d_stages; stage++) {
            sched::timestamp_out::sptr block = sched::timestamp_out::make();
            tb->msg_connect(prev, "out", block, "in");
            prev = block;
        }
    }
}


void
run_dur_flowgraph::create_diamond() {

    src = sched::timestamp_out::make();

    sched::timestamp_out::sptr snk = sched::timestamp_out::make();

    sched::timestamp_out::sptr prev;

    for(int pipe = 0; pipe < d_pipes; pipe++) {
        prev = sched::timestamp_out::make();
        tb->msg_connect(src, "out", prev, "in");

        for(int stage = 1; stage < d_stages; stage++) {
            sched::timestamp_out::sptr block = sched::timestamp_out::make();
            tb->msg_connect(prev, "out", block, "in");
            prev = block;
        }
        tb->msg_connect(prev, "out", snk, "in");
    }
} **/

run_dur_flowgraph::~run_dur_flowgraph () {
}


int main (int argc, char **argv) {
    int run;
    int stages;
    int repetitions;
    bool machine_readable = false;
    bool rt_prio = false;

    po::options_description desc("Run MSG Flow Graph");
    desc.add_options()
        ("help,h", "display help")
        ("run,R", po::value<int>(&run)->default_value(1), "Run Number")
        ("stages,s", po::value<int>(&stages)->default_value(6), "Number of stages")
        ("repetitions,r", po::value<int>(&repetitions)->default_value(100), "Number of repetitions")
        ("machine_readable,m", "Machine-readable Output")
        ("rt_prio,t", "Enable Real-time priority");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    if (vm.count("machine_readable")) {
        machine_readable = true;
    }

    if (vm.count("rt_prio")) {
        rt_prio = true;
    }

    if (rt_prio && gr::enable_realtime_scheduling() != RT_OK) {
        std::cout << "Error: failed to enable real-time scheduling." << std::endl;
    }

    run_dur_flowgraph* runner = new run_dur_flowgraph(stages);

    if(!machine_readable) {
        std::cout << boost::format("run         %1$20d") % run << std::endl;
        std::cout << boost::format("stages      %1$20d") % stages << std::endl;
        std::cout << boost::format("repetitions %1$20d") % repetitions << std::endl;
        std::cout << boost::format("rt_prio     %1$20s") % rt_prio << std::endl;

        // std::cout << std::endl << gr::dot_graph(runner->tb) << std::endl;
    }

    std::string rt = rt_prio ? "rt" : "normal";

    for(int repetition = 0; repetition < repetitions; repetition++) {

        pmt::pmt_t msg = pmt::cons(pmt::intern("done"), pmt::from_long(1));
        runner->src->post(pmt::mp("system"), msg);

        sched::timestamp_out *t;

        std::vector<long> results = t->getResults();

        for (auto i = results.begin(); i != results.end(); ++i) {
            std::cout << *i << std::endl;
        }

        auto start = std::chrono::high_resolution_clock::now();
        runner->tb->run();
        auto finish = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count()/1e9;

        std::cout << boost::format("%2$s, %3$4d, %5$4d,  %6$4d, %9$20.12f") % rt % run % stages % repetition % time << std::endl;

    }

    return 0;
}