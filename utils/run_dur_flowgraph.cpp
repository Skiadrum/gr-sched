#include "run_dur_flowgraph.hpp"

#include <chrono>
#include <boost/format.hpp>
#include <gnuradio/realtime.h>
#include <gnuradio/blocks/copy.h>

#include <tuple>

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

    tb->connect(src, 0, head, 0);

    for (int pipe = 0; pipe < d_pipes; pipe++) {
        auto block = blocks::copy::make(sizeof(float));
        tb->connect(head, 0, block, 0);
        blocks.push_back(block);

        for (int stage = 1; stage < d_stages; stage++) {
            block = blocks::copy::make(sizeof(float));
            tb->connect(blocks.back(), 0, block, 0);
            blocks.push_back(block);
        }
        auto sinks = sched::timestamp_out::make();
        tb->connect(blocks.back(), 0, sinks, 0);
        sink.push_back(sinks);
    }


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

    run_dur_flowgraph *runner = new run_dur_flowgraph(stages, pipes, samples);

    if (!machine_readable) {
        std::cout << boost::format("run         %1$20d") % run << std::endl;
        std::cout << boost::format("pipes       %1$20d") % pipes << std::endl;
        std::cout << boost::format("stages      %1$20d") % stages << std::endl;
        std::cout << boost::format("samples     %1$20d") % samples << std::endl;
        std::cout << boost::format("rt_prio     %1$20s") % rt_prio << std::endl;

        //   std::cout << std::endl << gr::dot_graph(runner->tb) << std::endl;
    }



    //  sched::timestamp_out *t;

    //  std::vector<long> results = t->getResults();

    // sink.getResults;
    //    for (auto i = results.begin(); i != results.end(); ++i) {
    //        std::cout << *i << std::endl;
    //    }

    runner->tb->run();
    int j = 0;

    std::vector<long> results;
 //   std::vector<long> start;
    for (auto i = runner->sink.begin(); i != runner->sink.end(); ++i, ++j) {
        results = runner->sink.at(j)->getResults();
        for (int k = 0; k < results.size(); ++k) {
            std::cout << boost::format(" %1$4d, %2$4d,%3$4d, %4$15d, %5$15d, %6$20.12f") % run % pipes % stages %
                         samples % j %
                         results.at(k)
                        // % start.at(k)
                      << std::endl;
        }

    }
    return 0;
}