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
#include <iostream>

#include "eddl/layers/operators/layer_operators.h"


using namespace std;

int LLog::total_layers = 0;

/**
  @brief Computes natural logarithm of a Layer element-wise

  @param l a Layer.
  @param name a name for the operation (predefined as 'log_TotalLogLayers')
  @param dev which computing service utilize

  @returns the result of the logarithm operation over l

  */
LLog::LLog(Layer *l, string name, int dev, int mem) : OperatorLayer(name, dev, mem) {
    if(name.empty()) this->name = "log_" + to_string(++total_layers);

    input=l->output;
    output = new Tensor(l->output->shape, dev);


    l->addchild(this);
    addparent(l);
}

void LLog::forward() {
    Tensor::log(parent[0]->output, output);
}

void LLog::backward() {
  Tensor::el_div(delta, parent[0]->output, parent[0]->delta, 1);
}

Layer *LLog::share(int c, int bs, vector<Layer *> p) {
  return clone(c,bs,p,dev);
}

Layer *LLog::clone(int c, int bs, vector<Layer *> p, int todev) {
  auto *n = new LLog(p[0],  name, todev, this->mem_level);
  n->orig = this;
  return n;
}
