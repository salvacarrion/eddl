// This file is part of EDDLL an European Distributed Deep Learning Library.
// Developed within the DeepHealth project.
// Boosting AI in Europe.
//
// The MIT License (MIT)
//
// Copyright (c) 2019
//           Roberto Paredes Palacios, <rparedes@dsic.upv.es>
//           Jon Ander Gómez, <jon@dsic.upv.es>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "eddl.h"


using namespace std;

extern ostream &operator<<(ostream &os, const vector<int> shape);

EDDL eddl;

////////////////////////////////////////////////////////
///// EDDL is a wrapper class to ease and define the API
////////////////////////////////////////////////////////

tensor EDDL::T(const initializer_list<int> &shape) {
    vector<int> s(shape.begin(), shape.end());
    return T(s);
}

tensor EDDL::T(const vector<int> shape) {
    return new LTensor(shape, DEV_CPU);
}

tensor EDDL::T(string fname) {
    return new LTensor(fname);
}


void EDDL::div(tensor t, float v) {
    t->input->div(v);
}

// ---- Operator Layers ----
layer EDDL::Abs(layer l) {
    return new LAbs(l, "abs" + to_string(1 + LAbs::total_layers), DEV_CPU);
}

layer EDDL::Diff(layer l1, layer l2) {
    return new LDiff(l1, l2, "diff" + to_string(1 + LDiff::total_layers), DEV_CPU);
}

layer EDDL::Diff(layer l1, float k) {
    return new LDiff(l1, k, "diff" + to_string(1 + LDiff::total_layers), DEV_CPU);
}

layer EDDL::Div(layer l1, layer l2) {
    return new LDiv(l1, l2, "div" + to_string(1 + LDiv::total_layers), DEV_CPU);
}

layer EDDL::Div(layer l1, float k) {
    return new LDiv(l1, k, "div" + to_string(1 + LDiv::total_layers), DEV_CPU);
}

layer EDDL::Exp(layer l) {
    return new LExp(l, "exp" + to_string(1 + LExp::total_layers), DEV_CPU);
}

layer EDDL::Log(layer l) {
    return new LLog(l, "log" + to_string(1 + LLog::total_layers), DEV_CPU);
}

layer EDDL::Mean(layer l) {
    return new LMean(l, "mean" + to_string(1 + LMean::total_layers), DEV_CPU);
}

layer EDDL::Mult(layer l1, layer l2) {
    return new LMult(l1, l2, "mult" + to_string(1 + LMult::total_layers), DEV_CPU);
}

layer EDDL::Mult(layer l1, float k) {
    return new LMult(l1, k, "mult" + to_string(1 + LMult::total_layers), DEV_CPU);
}

layer EDDL::Pow(layer l1, layer l2) {
    return new LPow(l1, l2, "pow" + to_string(1 + LPow::total_layers), DEV_CPU);
}

layer EDDL::Pow(layer l1, float k) {
    return new LPow(l1, k, "pow" + to_string(1 + LPow::total_layers), DEV_CPU);
}

layer EDDL::Sqrt(layer l) {
    return new LSqrt(l, "sqrt" + to_string(1 + LSqrt::total_layers), DEV_CPU);
}

layer EDDL::Sum(layer l1, layer l2) {
    return new LSum(l1, l2, "sum" + to_string(1 + LSum::total_layers), DEV_CPU);
}

layer EDDL::Sum(layer l1, float k) {
    return new LSum(l1, k, "sum" + to_string(1 + LSum::total_layers), DEV_CPU);
}

layer EDDL::Var(layer l) {
    return new LVar(l, "var" + to_string(1 + LVar::total_layers), DEV_CPU);
}

//////////////////////////////////////////////////////


layer EDDL::Activation(layer parent, string activation) {
    return EDDL::Activation(parent, activation, "activation" + to_string(1 + LActivation::total_layers));
}

layer EDDL::Activation(layer parent, string activation, string name) {
    return new LActivation(parent, activation, name, DEV_CPU);
}
//////////////////////////////////////////////////////

layer EDDL::BatchNormalization(layer parent, float momentum, float epsilon, bool affine){
    return EDDL::BatchNormalization(parent, momentum, epsilon, affine, "batchnorm" + to_string(1 + LBatchNorm::total_layers));
}

layer EDDL::BatchNormalization(layer parent, float momentum, float epsilon, bool affine, string name){
    return new LBatchNorm(parent, momentum, epsilon, affine, name, DEV_CPU);
}

//////////////////////////////////////////////////////

layer EDDL::Conv(layer parent, const initializer_list<int> &ks) {
    return new LConv(parent, ks, {1, 1}, "same", "conv" + to_string(1 + LConv::total_layers), DEV_CPU);
}

layer EDDL::Conv(layer parent, const initializer_list<int> &ks, const initializer_list<int> &st) {
    return new LConv(parent, ks, st, "same", "conv" + to_string(1 + LConv::total_layers), DEV_CPU);
}

layer EDDL::Conv(layer parent, const initializer_list<int> &ks, const initializer_list<int> &st, string p) {
    return new LConv(parent, ks, st, p, "conv" + to_string(1 + LConv::total_layers), DEV_CPU);
}

layer EDDL::Conv(layer parent, const initializer_list<int> &ks, string p) {
    return new LConv(parent, ks, {1, 1}, p, "conv" + to_string(1 + LConv::total_layers), DEV_CPU);
}

layer EDDL::Conv(layer parent, int filters, const initializer_list<int> &kernel_size,
                 const initializer_list<int> &strides, string padding, int groups, const initializer_list<int> &dilation_rate,
                 bool use_bias) {
    return EDDL::Conv(parent, filters, kernel_size, strides, padding, groups, dilation_rate, use_bias, "conv" + to_string(1 + LConv::total_layers));
}
layer EDDL::Conv(layer parent, int filters, const initializer_list<int> &kernel_size,
                 const initializer_list<int> &strides, string padding, int groups, const initializer_list<int> &dilation_rate,
                 bool use_bias, string name) {
    return new LConv(parent, filters, kernel_size, strides, padding, groups, dilation_rate, use_bias, name, DEV_CPU);
}
//////////////////////////////////////////////////////


layer EDDL::ConvT(layer parent, int filters, const initializer_list<int> &kernel_size,
                  const initializer_list<int> &output_padding, string padding, const initializer_list<int> &dilation_rate,
                  const initializer_list<int> &strides, bool use_bias){
    return EDDL::ConvT(parent, filters, kernel_size, output_padding, padding, dilation_rate, strides, use_bias, "convT" + to_string(1 + LConvT::total_layers));
}
layer EDDL::ConvT(layer parent, int filters, const initializer_list<int> &kernel_size,
                  const initializer_list<int> &output_padding, string padding, const initializer_list<int> &dilation_rate,
                  const initializer_list<int> &strides, bool use_bias, string name){
    return new LConvT(parent, filters, kernel_size, output_padding, padding, dilation_rate, strides, use_bias, name, DEV_CPU);
}
/////////////////////////////////////////////////////////


layer EDDL::Dense(layer parent, int ndim, bool use_bias) {
    return EDDL::Dense(parent, ndim, use_bias, "dense" + to_string(1 + LDense::total_layers));
}

layer EDDL::Dense(layer parent, int ndim, bool use_bias, string name){
    return new LDense(parent, ndim, use_bias, name, DEV_CPU);
}
//////////////////////////////////////////////////////


layer EDDL::Dropout(layer parent, float rate) {
    return EDDL::Dropout(parent, rate, "drop" + to_string(1 + LDropout::total_layers));
}

layer EDDL::Dropout(layer parent, float rate, string name) {
    return new LDropout(parent, rate, name, DEV_CPU);
}

//////////////////////////////////////////////////////
layer EDDL::Embedding(int input_dim, int output_dim){
    return EDDL::Embedding(input_dim, output_dim, "embedding" + to_string(1 + LEmbedding::total_layers));
}
layer EDDL::Embedding(int input_dim, int output_dim, string name){
    return new LEmbedding(input_dim, output_dim, name, DEV_CPU);
}

//////////////////////////////////////////////////////
layer EDDL::GaussianNoise(layer parent, float stdev){
    return EDDL::GaussianNoise(parent, stdev, "gaussiannoise" + to_string(1 + LGaussianNoise::total_layers));
}
layer EDDL::GaussianNoise(layer parent, float stdev, string name){
    return new LGaussianNoise(parent, stdev, name, DEV_CPU);
}

//////////////////////////////////////////////////////

layer EDDL::Input(tensor t) {
    return new LInput(t->input, "input" + to_string(1 + LInput::total_layers), DEV_CPU);
}

layer EDDL::Input(const initializer_list<int> &shape) {
    return EDDL::Input(shape, "input" + to_string(1 + LInput::total_layers));
}

layer EDDL::Input(const initializer_list<int> &shape, string name) {
    return new LInput(new Tensor(shape), name, DEV_CPU);
}

//////////////////////////////////////////////////////

layer EDDL::UpSampling(layer parent, const initializer_list<int> &size, string interpolation){
    return EDDL::UpSampling(parent, size, interpolation, "UpSampling" + to_string(1 + LUpSampling::total_layers));
}

layer EDDL::UpSampling(layer parent, const initializer_list<int> &size, string interpolation, string name){
    return new LUpSampling(parent, size, interpolation, name, DEV_CPU);
}

//////////////////////////////////////////////////////
layer EDDL::AveragePool(layer parent, const initializer_list<int> &pool_size) {
    return EDDL::AveragePool(parent, pool_size, pool_size);
}

layer EDDL::AveragePool(layer parent, const initializer_list<int> &pool_size, const initializer_list<int> &strides, string padding){
    //TODO: Fix LMaxPool
    return EDDL::AveragePool(parent, pool_size, strides, padding, "avgpool" + to_string(1 + LAveragePool::total_layers));
}

layer EDDL::AveragePool(layer parent, const initializer_list<int> &pool_size, const initializer_list<int> &strides, string padding, string name){
    //TODO: Implement
    return new LAveragePool(parent, pool_size, strides, padding, name, DEV_CPU);
}

//////////////////////////////////////////////////////
layer EDDL::GlobalMaxPool(layer parent){
    //TODO: Fix LMaxPool
    return EDDL::GlobalMaxPool(parent, "globalmaxpool" + to_string(1 + LGlobalMaxPool::total_layers));
}

layer EDDL::GlobalMaxPool(layer parent, string name){
    //TODO: Implement
    //return new LGlobalMaxPool(parent, PoolDescriptor({1,1}, {1,1}), name, DEV_CPU);
    return nullptr;
}

//////////////////////////////////////////////////////
layer EDDL::GlobalAveragePool(layer parent){
    //TODO: Fix LMaxPool
    return EDDL::GlobalAveragePool(parent, "globalavgpool" + to_string(1 + LGlobalAveragePool::total_layers));
}

layer EDDL::GlobalAveragePool(layer parent, string name){
    //TODO: Implement
    //return new LGlobalAveragePool(parent,  PoolDescriptor({1,1}, {1,1}, "none"), name, DEV_CPU);
    return nullptr;
}


//////////////////////////////////////////////////////
layer EDDL::MaxPool(layer parent, const initializer_list<int> &pool_size) {
    return EDDL::MaxPool(parent, pool_size, pool_size);
}

layer EDDL::MaxPool(layer parent, const initializer_list<int> &pool_size, const initializer_list<int> &strides, string padding){
    return EDDL::MaxPool(parent, pool_size, strides, padding, "mpool" + to_string(1 + LMaxPool::total_layers));
}

layer EDDL::MaxPool(layer parent, const initializer_list<int> &pool_size, const initializer_list<int> &strides, string padding, string name){
    return new LMaxPool(parent, pool_size, strides, padding, name, DEV_CPU);

}

//////////////////////////////////////////////////////
layer EDDL::RNN(layer parent, int units, int num_layers, bool use_bias, float dropout, bool bidirectional){
    //TODO: Fix name
    return EDDL::RNN(parent, units, num_layers, use_bias, dropout, bidirectional, "rnn" + to_string(1 + LRNN::total_layers));
}

layer EDDL::RNN(layer parent, int units, int num_layers, bool use_bias, float dropout, bool bidirectional, string name){
    return new LRNN(parent, units, num_layers, use_bias, dropout, bidirectional, name, DEV_CPU);
}

//////////////////////////////////////////////////////
layer EDDL::LSTM(layer parent, int units, int num_layers, bool use_bias, float dropout, bool bidirectional){
    //TODO: Fix name
    return EDDL::LSTM(parent, units, num_layers, use_bias, dropout, bidirectional, "lstm" + to_string(1 + LLSTM::total_layers));
}

layer EDDL::LSTM(layer parent, int units, int num_layers, bool use_bias, float dropout, bool bidirectional, string name){
    return new LLSTM(parent, units, num_layers, use_bias, dropout, bidirectional, name, DEV_CPU);
}
//////////////////////////////////////////////////////
layer EDDL::Reshape(layer parent, const initializer_list<int> &shape) {
    return EDDL::Reshape(parent, shape, "reshape" + to_string(1 + LReshape::total_layers));
}

layer EDDL::Reshape(layer parent, const initializer_list<int> &shape, string name) {
    return new LReshape(parent, shape, name, DEV_CPU);
}
/////////////////////////////////////////////////////////

layer EDDL::Transpose(layer parent, const initializer_list<int> &dims){
    return EDDL::Transpose(parent, dims, "transpose" + to_string(1 + LTranspose::total_layers));
}
layer EDDL::Transpose(layer parent, const initializer_list<int> &dims, string name){
    return new LTranspose(parent, dims, name, DEV_CPU);
}
/////////////////////////////////////////////////////////


loss EDDL::LossFunc(string type){
    if(type == "mse" || type == "mean_squared_error"){
        return new LMeanSquaredError();
    } else if(type == "cross_entropy"){
        return new LCrossEntropy();
    } else if (type == "soft_cross_entropy"){
        return new LSoftCrossEntropy();
    }
    return nullptr;
}
/////////////////////////////////////////////////////////


metric EDDL::MetricFunc(string type){
    if(type == "mse" || type == "mean_squared_error"){
        return new MMeanSquaredError();
    } else if(type == "categorical_accuracy" || type == "accuracy"){
        return new MCategoricalAccuracy();
    }
    return nullptr;
}
/////////////////////////////////////////////////////////


layer EDDL::Add(const initializer_list<layer> &layers) {
    return EDDL::Add(layers, "add" + to_string(1 + LAdd::total_layers));
}

layer EDDL::Add(const initializer_list<layer> &layers, string name) {
    return new LAdd(vlayer(layers.begin(), layers.end()), name, DEV_CPU);
}

////////////////////////////////////////////////////////

layer EDDL::Average(const initializer_list<layer> &layers){
    // TODO: Fix LCAT
    return EDDL::Average(layers, "average" + to_string(1 + LAverage::total_layers));
}

layer EDDL::Average(const initializer_list<layer> &layers, string name){
    //TODO: Implement
    return new LAverage(layers, name, DEV_CPU);
}

/////////////////////////////////////////////////////////

layer EDDL::Subtract(const initializer_list<layer> &layers) {
    // TODO: Fix LAadd
    return EDDL::Subtract(layers, "substract" + to_string(1 + LSubtract::total_layers));
}

layer EDDL::Subtract(const initializer_list<layer> &layers, string name) {
    return new LSubtract(layers, name, DEV_CPU);
}

////////////////////////////////////////////////////////

layer EDDL::Concat(const initializer_list<layer> &layers) {
    return EDDL::Concat(layers, "concat" + to_string(1 + LConcat::total_layers));
}

layer EDDL::Concat(const initializer_list<layer> &layers, string name) {
    return new LConcat(vlayer(layers.begin(), layers.end()), name, DEV_CPU);
}

////////////////////////////////////////////////////////

layer EDDL::MatMul(const initializer_list<layer> &layers){
    // TODO: Fix LCAT
    return EDDL::MatMul(layers, "matmul" + to_string(1 + LMatMul::total_layers));
}

layer EDDL::MatMul(const initializer_list<layer> &layers, string name){
    return new LMatMul(layers, name, DEV_CPU);
}

////////////////////////////////////////////////////////

layer EDDL::Maximum(const initializer_list<layer> &layers){
    // TODO: Fix LCAT
    return EDDL::Maximum(layers, "maximum" + to_string(1 + LMaximum::total_layers));
}

layer EDDL::Maximum(const initializer_list<layer> &layers, string name){
    return new LMaximum(layers, name, DEV_CPU);
}

////////////////////////////////////////////////////////

layer EDDL::Minimum(const initializer_list<layer> &layers){
    // TODO: Fix LCAT
    return EDDL::Minimum(layers, "minimum" + to_string(1 + LMinimum::total_layers));
}

layer EDDL::Minimum(const initializer_list<layer> &layers, string name){
    return new LMinimum(layers, name, DEV_CPU);
}


////////////////////////////////////////////////////////

optimizer EDDL::Adadelta(float lr, float rho, float epsilon, float weight_decay){
    //Todo: Implement
    return new adadelta(lr, rho, epsilon, weight_decay);
}
optimizer EDDL::Adam(float lr, float beta_1, float beta_2, float epsilon, float weight_decay, bool amsgrad){
    //Todo: Implement
    return new adam(lr, beta_1, beta_2, epsilon, weight_decay, amsgrad);
}
optimizer EDDL::Adagrad(float lr, float epsilon, float weight_decay){
    //Todo: Implement
    return new adagrad(lr, epsilon, weight_decay);
}
optimizer EDDL::Adamax(float lr, float beta_1, float beta_2, float epsilon, float weight_decay){
    //Todo: Implement
    return new adamax(lr, beta_1, beta_2, epsilon, weight_decay);
}
optimizer EDDL::Nadam(float lr, float beta_1, float beta_2, float epsilon, float schedule_decay){
    //Todo: Implement
    return new nadam(lr, beta_1, beta_2, epsilon, schedule_decay);
}
optimizer EDDL::RMSprop(float lr, float rho, float epsilon, float weight_decay){
    //Todo: Implement
    return new rmsprop(lr, rho, epsilon, weight_decay);
}


optimizer EDDL::SGD(float lr, float momentum, float weight_decay, bool nesterov){
    return new sgd(lr, momentum, weight_decay, nesterov);
}


void EDDL::change(optimizer optim, const initializer_list<float> &params) {
    // TODO: Check this function
    optim->change(params);
}

////////////////////////////////////////////////////////

initializer EDDL::Constant(float value){
    //Todo: Implement
    return new IConstant(value);
}

initializer EDDL::Identity(float gain){
    //Todo: Implement
    return new IIdentity(gain);
}
initializer EDDL::GlorotNormal(float seed) {
    //Todo: Implement
    return new IGlorotNormal(seed);
}
initializer EDDL::GlorotUniform(float seed){
    //Todo: Implement
    return new IGlorotUniform(seed);
}
initializer EDDL::RandomNormal(float mean, float stdev, int seed){
    //Todo: Implement
    return new IRandomNormal(mean, stdev, seed);
}
initializer EDDL::RandomUniform(float minval, float maxval, int seed){
    //Todo: Implement
    return new IRandomUniform(minval, maxval, seed);
}
initializer EDDL::Orthogonal(float gain, int seed){
    //Todo: Implement
    return new IOrthogonal(gain, seed);
}


/////////////////////////////////////////////////////////
model EDDL::Model(vlayer in, vlayer out) {
    return new Net(in, out);
}

///////////
compserv EDDL::CS_CPU(int th) {
    return new CompServ(th, {}, {});
}

compserv EDDL::CS_GPU(const initializer_list<int> &g) {
    return new CompServ(0, g, {});
}

compserv EDDL::CS_FGPA(const initializer_list<int> &f) {
    return new CompServ(0, {}, f);
}


////////////

void EDDL::summary(model m) {
    m->info();
}

void EDDL::plot(model m, string fname) {
    m->plot(fname);
}

void EDDL::build(model net, optimizer o, const initializer_list<Loss *> &c, const initializer_list<Metric *> &m) {
    EDDL::build(net, o, c, m, new CompServ(std::thread::hardware_concurrency(), {}, {}));
}

void EDDL::build(model net, optimizer o, const initializer_list<Loss *> &c, const initializer_list<Metric *> &m, CompServ *cs) {
    net->build(o, c, m, cs);
}

void EDDL::fit(model net, const initializer_list<LTensor *> &in, const initializer_list<LTensor *> &out, int batch, int epochs) {
    vltensor ltin = vltensor(in.begin(), in.end());
    vltensor ltout = vltensor(out.begin(), out.end());

    vtensor tin;
    for (int i = 0; i < ltin.size(); i++)
        tin.push_back(ltin[i]->input);

    vtensor tout;
    for (int i = 0; i < ltout.size(); i++)
        tout.push_back(ltout[i]->input);


    net->fit(tin, tout, batch, epochs);
}

void EDDL::fit(model m, const initializer_list<LTensor *> &in, const initializer_list<LTensor *> &out, int batch, int epochs, const initializer_list<Callback *> &cbs){
    // TODO: Implement
}

void EDDL::evaluate(model net, const initializer_list<LTensor *> &in, const initializer_list<LTensor *> &out) {
    vltensor ltin = vltensor(in.begin(), in.end());
    vltensor ltout = vltensor(out.begin(), out.end());

    vtensor tin;
    for (int i = 0; i < ltin.size(); i++)
        tin.push_back(ltin[i]->input);

    vtensor tout;
    for (int i = 0; i < ltout.size(); i++)
        tout.push_back(ltout[i]->input);


    net->evaluate(tin, tout);
}


void EDDL::set_trainable(layer l){
    //Todo: Implement

}


layer EDDL::get_layer(model m, string layer_name){
    //Todo: Implement
    return nullptr;
}


model EDDL::load_model(string fname){
    //Todo: Implement
    return nullptr;
}

void EDDL::save_model(model m, string fname){
    //Todo: Implement
}


void EDDL::set_trainable(model m){
    //Todo: Implement
}

model EDDL::zoo_models(string model_name){
    //Todo: Implement
    return nullptr;
}

////

bool exist(string name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    }
    return false;
}

void EDDL::download_mnist() {
    string cmd;
    string trX = "trX.bin";
    string trY = "trY.bin";
    string tsX = "tsX.bin";
    string tsY = "tsY.bin";

    if ((!exist(trX)) || (!exist(trY)) || (!exist(tsX)) || (!exist(tsY))) {
        cmd = "wget https://www.dropbox.com/s/khrb3th2z6owd9t/trX.bin";
        int status = system(cmd.c_str());
        if (status < 0) {
            msg("wget must be installed", "eddl.download_mnist");
            exit(1);
        }

        cmd = "wget https://www.dropbox.com/s/m82hmmrg46kcugp/trY.bin";
        status = system(cmd.c_str());
        if (status < 0) {
            msg("wget must be installed", "eddl.download_mnist");
            exit(1);
        }
        cmd = "wget https://www.dropbox.com/s/7psutd4m4wna2d5/tsX.bin";
        status = system(cmd.c_str());
        if (status < 0) {
            msg("wget must be installed", "eddl.download_mnist");
            exit(1);
        }
        cmd = "wget https://www.dropbox.com/s/q0tnbjvaenb4tjs/tsY.bin";
        status = system(cmd.c_str());
        if (status < 0) {
            msg("wget must be installed", "eddl.download_mnist");
            exit(1);
        }

    }
}

void EDDL::download_cifar10() {
    // TODO: Implement
}

void EDDL::download_cifar100() {
    // TODO: Implement
}










//////