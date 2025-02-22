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

int LLog10::total_layers = 0;


/**
  @brief Computes logarithm with base 10 of a Layer element-wise

  @param l a Layer.
  @param name a name for the operation (predefined as 'log10_TotalLog10Layers')
  @param dev which computing service utilize

  @returns the result of the logarithm with base 10 operation over l

  */
LLog10::LLog10(Layer *l, string name, int dev, int mem) : OperatorLayer(name, dev, mem) {
    if(name.empty()) this->name = "log10_" + to_string(++total_layers);

    input=l->output;
    output = new Tensor(l->output->shape, dev);


    l->addchild(this);
    addparent(l);
}

void LLog10::forward() {
    Tensor::log10(parent[0]->output, output);
}

void LLog10::backward() {
    delta->div_(log(10));
    Tensor::el_div(delta,parent[0]->output, parent[0]->delta, 1);
}

Layer *LLog10::share(int c, int bs, vector<Layer *> p) {
  return clone(c,bs,p,dev);
}

Layer *LLog10::clone(int c, int bs, vector<Layer *> p, int todev) {
  auto *n = new LLog10(p[0],  name, todev, this->mem_level);
  n->orig = this;
  return n;
}
