#include "run_dur_flowgraph.hpp"

#include <chrono>
#include <boost/format.hpp>
#include <gnuradio/realtime.h>
#include <gnuradio/blocks/copy.h>


#include <gnuradio/blocks/null_source.h>
#include <gnuradio/blocks/null_sink.h>
#include <gnuradio/blocks/head.h>


namespace po = boost::program_options;

using namespace gr;


run_dur_flowgraph::run_dur_flowgraph(int stages, int pipes, uint64_t samples) :
        d_stages(stages), d_samples(samples), d_pipes(pipes) {

    this->tb = make_top_block("dur_flowgraph");
    create_fork();
}


void
run_dur_flowgraph::create_fork() {

    auto src = sched::timestamp_in::make();
    auto head = blocks::head::make(sizeof(float), d_samples);

    gr::blocks::copy::sptr prev = gr::blocks::copy::make(sizeof(float));
    tb->connect(src, 0, head, 0);
    tb->connect(head, 0, prev, 0);


    for(int stage = 1; stage < d_stages; stage++) {
        gr::blocks::copy::sptr block = gr::blocks::copy::make(sizeof(float));
        tb->connect(prev, 0, block, 0);
        prev = block;
    }

     sink = sched::timestamp_out::make();
    tb->connect(prev, 0, sink, 0);
}

run_dur_flowgraph::~run_dur_flowgraph() {
}


int main(int argc, char **argv) {
    int run;
    int stages;
    int pipes;
    uint64_t samples;
    bool machine_readable = false;
    bool rt_prio = false;

    po::options_description desc("Run DUR Flow Graph");
    desc.add_options()
            ("help,h", "display help")
            ("run,R", po::value<int>(&run)->default_value(1), "Run Number")
            ("pipes,p", po::value<int>(&pipes)->default_value(5), "Number of pipes")
            ("samples,N", po::value<uint64_t>(&samples)->default_value(15000000), "Number of samples")
            ("stages,s", po::value<int>(&stages)->default_value(6), "Number of stages")
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

    run_dur_flowgraph* runner = new run_dur_flowgraph(stages, pipes, samples);

    if (!machine_readable) {
        std::cout << boost::format("run         %1$20d") % run << std::endl;
        std::cout << boost::format("pipes       %1$20d") % pipes << std::endl;
        std::cout << boost::format("stages      %1$20d") % stages << std::endl;
        std::cout << boost::format("samples     %1$20d") % samples << std::endl;
        std::cout << boost::format("rt_prio     %1$20s") % rt_prio << std::endl;

        std::cout << std::endl << gr::dot_graph(runner->tb) << std::endl;
    }



      //  sched::timestamp_out *t;

      //  std::vector<long> results = t->getResults();

       // sink.getResults;
    //    for (auto i = results.begin(); i != results.end(); ++i) {
    //        std::cout << *i << std::endl;
    //    }

        auto start = std::chrono::high_resolution_clock::now();
        runner->tb->run();
        std::vector<long> results = runner->sink->getResults();

    for (auto i = results.begin(); i != results.end(); ++i) {
        std::cout << boost::format(" %1$4d, %2$4d,%3$4d, %4$15d, %5$20.12f") % run % pipes % stages % samples % *i << std::endl;

    }

        auto finish = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / 1e9;



    return 0;
}