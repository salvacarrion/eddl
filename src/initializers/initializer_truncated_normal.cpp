/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.3
* copyright (c) 2019, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: October 2019
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "initializer.h"

using namespace std;

/**
 * Initializer that generates tensors with a truncated normal distribution.
 *
 * @param mean float; Mean of the random values to generate.
 * @param stdev float; Standard deviation of the random values to generate.
 * @param seed int; Used to seed the random generator
*/
ITruncateNormal::ITruncateNormal(float mean, float stdev, int seed) : Initializer("truncated_normal") {
    // Todo: Implement
    this->mean = mean;
    this->stdev = stdev;
    this->seed = seed;

}
void ITruncateNormal::apply(Tensor* params)
{
  params->rand_normal(mean,stdev);
  params->trunc_();
}