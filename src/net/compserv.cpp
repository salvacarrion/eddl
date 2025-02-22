/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 1.0
* copyright (c) 2021, Universitat Politècnica de València (UPV), PRHLT Research Centre
* Date: November 2021
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <thread>

#include <stdexcept>
#include <iostream>
#include "eddl/net/compserv.h"

CompServ::CompServ()= default;

// for local
CompServ::CompServ(int t, const vector<int>& g, const vector<int> &f, int lsb, int mem) {
    type = "local";
    isshared = false;

    threads_arg = t;
    if (t == -1) local_threads = (int)std::thread::hardware_concurrency();  // Avoid eigen dependency
    else local_threads = t;

    for (auto _ : g) this->local_gpus.push_back(_);
    for (auto _ : f) this->local_fpgas.push_back(_);

    if (!local_fpgas.empty()) hw="FPGA";
    else if (!local_gpus.empty()) hw="GPU";
    else hw="CPU";

    this->lsb = lsb;

    if (lsb < 0) {
        throw std::runtime_error("Error creating CS with lsb<0 in CompServ::CompServ");
    }

    mem_level = mem;
    if ((mem < 0) || (mem > 2)) {
        fprintf(stderr,"Error creating CS with incorrect memory saving level param in CompServ::CompServ");
        exit(EXIT_FAILURE);
    }
    else {
        if (mem==0) fprintf(stderr,"CS with full memory setup\n");
        if (mem==1) fprintf(stderr,"CS with mid memory setup\n");
        if (mem==2) fprintf(stderr,"CS with low memory setup\n");
    }
}

CompServ* CompServ::share() {
    CompServ *n = new CompServ(threads_arg,local_gpus,local_fpgas,lsb,mem_level);
    n->isshared = true;
    return n;
}
CompServ* CompServ::clone() {
    CompServ *n = new CompServ(threads_arg,local_gpus,local_fpgas,lsb,mem_level);
    return n;
}


// for Distributed
CompServ::CompServ(const string& filename) {
    std::cerr << "Not implemented error [Computing service with filename]" << std::endl;
}
