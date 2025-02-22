/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 1.0
* copyright (c) 2021, Universitat Politècnica de València (UPV), PRHLT Research Centre
* Date: November 2021
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/

#include <float.h>

#include "eddl/tensor/nn/tensor_nn.h"
#include "eddl/hardware/cpu/nn/cpu_tensor_nn.h"
#include "eddl/profiling.h"

#ifdef cGPU
#include "eddl/hardware/gpu/gpu_tensor.h"
#include "eddl/hardware/gpu/gpu_hw.h"
#include "eddl/hardware/gpu/nn/gpu_tensor_nn.h"
#endif

#ifdef cFPGA
#include "eddl/hardware/fpga/fpga_hw.h"
#include "eddl/hardware/fpga/nn/fpga_nn.h"

extern int next_fpga_tensor_id;
#endif

PROFILING_ENABLE_EXTERN(repeat_nn);
PROFILING_ENABLE_EXTERN(d_repeat_nn);
PROFILING_ENABLE_EXTERN(select);
PROFILING_ENABLE_EXTERN(select_back);
PROFILING_ENABLE_EXTERN(set_select);
PROFILING_ENABLE_EXTERN(set_select_back);

namespace tensorNN {

    // Deprecated. Used in UpSampling2D.
    // Repeats the rows and columns of the data by size[0] and size[1] respectively.
    void repeat_nn(Tensor *A, Tensor *B, vector<int> size) {
        if ((A->device != B->device)) msg("Tensors in different devices", "Tensor::Repeat_NN");
        if (A->ndim != B->ndim) msg("Incompatible dims", "Tensor::Repeat");

        // Check size
        for (int i = 2; i < A->ndim; i++) {
            if (A->shape[i] * size[i - 2] != B->shape[i]) {
                msg("Incompatible dimensions (size)", "Tensor::Repeat_NN");
            }
        }

        PROFILING_HEADER(repeat_nn);

        if (A->isCPU() && B->isCPU()) {
            cpu_repeat_nn(A, B, size);
        }
#ifdef cGPU
        else if (A->isGPU() && B->isGPU()) {
            gpu_repeat_nn(A, B, size);
        }
#endif
#ifdef cFPGA
        else {
            printf("repeat_nn not supported yet on FPGA\n");
            exit(1);
        }
#endif
        PROFILING_FOOTER(repeat_nn);
    }

    void d_repeat_nn(Tensor *D, Tensor *A, vector<int> size) {
        if ((D->device != A->device)) msg("Tensors in different devices", "Tensor::D_Repeat_NN");

        PROFILING_HEADER(d_repeat_nn);

        if (D->isCPU() && A->isCPU()) {
            cpu_d_repeat_nn(D, A, size);
        }
#ifdef cGPU
        else if (D->isGPU() && A->isGPU()) {
            gpu_d_repeat_nn(D, A, size);
        }
#endif
#ifdef cFPGA
        else {
            printf("d_repeat_nn not implemented in FPGA yet\n");
            exit(1);
        }
#endif
        PROFILING_FOOTER(d_repeat_nn);
    }


    void select(Tensor *A, Tensor* B, SelDescriptor *sd){

        PROFILING_HEADER(select);

        if (A->isCPU() && B->isCPU()) {
            cpu_select_nn(A, B, sd);
        }
#ifdef cGPU
        else if (A->isGPU() && B->isGPU())
        {
            gpu_select_nn(A, B, sd);
        }
#endif
#ifdef cFPGA
        else if (A->isFPGA() && B->isFPGA())
        {
            fpga_select_nn(A, B, sd);
        }
#endif
        PROFILING_FOOTER(select);
    }

    void select_back(Tensor *A, Tensor* B, SelDescriptor *sd){

        PROFILING_HEADER(select_back);

        if (A->isCPU() && B->isCPU()) {
            cpu_select_back_nn(A, B, sd);
        }
#ifdef cGPU
        else if (A->isGPU() && B->isGPU())
        {
           gpu_select_back_nn(A, B, sd);
        }
#endif
#ifdef cFPGA
        else if (A->isFPGA() && B->isFPGA())
        {
           fpga_select_back_nn(A, B, sd);
        }
#endif
        PROFILING_FOOTER(select_back);
    }

    void set_select(Tensor *A, Tensor *B, SelDescriptor *sd){

        PROFILING_HEADER(set_select);

        if (A->isCPU() && B->isCPU()) {
            cpu_set_select_nn(A, B, sd);
        }
#ifdef cGPU
        else if (A->isGPU() && B->isGPU())
        {
            gpu_set_select_nn(A, B, sd);
        }
#endif
#ifdef cFPGA
        else if (A->isFPGA() && B->isFPGA())
        {
            fpga_set_select_nn(A, B, sd);
        }
#endif
        PROFILING_FOOTER(set_select);
    }


    void set_select_back(Tensor *A, Tensor* B, SelDescriptor *sd){

        PROFILING_HEADER(set_select_back);

        if (A->isCPU() && B->isCPU()) {
            cpu_set_select_back_nn(A, B, sd);
        }
#ifdef cGPU
        else if (A->isGPU() && B->isGPU())
        {
            gpu_set_select_back_nn(A, B, sd);
        }
#endif
#ifdef cFPGA
        else if (A->isFPGA() && B->isFPGA())
        {
            fpga_set_select_back_nn(A, B, sd);
        }
#endif
        PROFILING_FOOTER(set_select_back);
    }



    void expand(Tensor *A, Tensor* B, ExpandDescriptor *sd){


        if (A->isCPU() && B->isCPU()) {
            cpu_expand_nn(A, B, sd);
        }
#ifdef cGPU
        else if (A->isGPU() && B->isGPU())
        {
            gpu_expand_nn(A, B, sd);
        }
#endif
#ifdef cFPGA
            else if (A->isFPGA() && B->isFPGA())
        {
//            fpga_expand_nn(A, B, sd);
        }
#endif
    }

    void expand_back(Tensor *A, Tensor* B, ExpandDescriptor *sd){


        if (A->isCPU() && B->isCPU()) {
            cpu_expand_back_nn(A, B, sd);
        }
#ifdef cGPU
        else if (A->isGPU() && B->isGPU())
        {
            gpu_expand_back_nn(A, B, sd);
        }
#endif
#ifdef cFPGA
            else if (A->isFPGA() && B->isFPGA())
        {
//           fpga_expand_back_nn(A, B, sd);
        }
#endif
    }

    void repeat_batch(Tensor *A, Tensor* B){


        if (A->isCPU() && B->isCPU()) {
            cpu_repeat_batch(A, B);
        }
#ifdef cGPU
        else if (A->isGPU() && B->isGPU())
        {
            gpu_repeat_batch(A, B);
        }
#endif
#ifdef cFPGA
        else if (A->isFPGA() && B->isFPGA())
        {
        }
#endif
    }

}
