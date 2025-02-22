#include <gtest/gtest.h>
#include <random>
#include <string>

#include "eddl/tensor/tensor.h"
#include "eddl/tensor/tensor_reduction.h"
#include "eddl/tensor/nn/tensor_nn.h"
#include "eddl/descriptors/descriptors.h"


using namespace std;


TEST(TensorTestSuite, tensor_math_sort) {
    // Test #1
    Tensor *t1_ref = new Tensor({-0.5792, -0.1372,  0.5962,  1.2097},
                                {4}, DEV_CPU);
    Tensor *t1 = new Tensor({1.2097, -0.1372, -0.5792,  0.5962},
                            {4}, DEV_CPU);

    Tensor *new_t = t1->sort(false, true);
    ASSERT_TRUE(Tensor::equivalent(t1_ref, new_t, 1e-3f, 0.0f, true, true));

    // Test #2
    Tensor *t2_ref = new Tensor({1.2097, 0.5962, -0.1372, -0.5792,},
                                {4}, DEV_CPU);

    new_t = t1->sort(true, true);
    ASSERT_TRUE(Tensor::equivalent(t2_ref, new_t, 1e-3f, 0.0f, true, true));

    delete t1_ref;
    delete t1;
    delete new_t;
    delete t2_ref;

    // Test GPU
#ifdef cGPU
    // Test #1
    Tensor* t1_cpu = Tensor::randu({10000});
    Tensor* t1_gpu = t1_cpu->clone(); t1_gpu->toGPU();
    t1_cpu->sort_(false, true);
    t1_gpu->sort_(false, true); t1_gpu->toCPU();
    ASSERT_TRUE(Tensor::equivalent(t1_cpu, t1_gpu, 1e-3f, 0.0f, true, true));

    // Test #2
    Tensor* t2_cpu = Tensor::randu({10000});
    Tensor* t2_gpu = t2_cpu->clone(); t2_gpu->toGPU();
    t2_cpu->sort_(true, false);
    t2_gpu->sort_(true, false); t2_gpu->toCPU();
    ASSERT_TRUE(Tensor::equivalent(t2_cpu, t2_gpu, 1e-3f, 0.0f, true, true));

    delete t1_cpu;
    delete t1_gpu;
    delete t2_cpu;
    delete t2_gpu;

#endif
}




TEST(TensorTestSuite, tensor_math_argsort) {
    // Test #1
    Tensor *t1_ref = new Tensor({2, 1, 3, 0},{4}, DEV_CPU);
    Tensor *t1 = new Tensor({1.2097, -0.1372, -0.5792,  0.5962},
                            {4}, DEV_CPU);

    Tensor *new_t = t1->argsort(false, true);
    ASSERT_TRUE(Tensor::equivalent(t1_ref, new_t, 1e-3f, 0.0f, true, true));

    // Test #2
    Tensor *t2_ref = new Tensor({0, 3, 1, 2}, {4}, DEV_CPU);

    new_t = t1->argsort(true, false);
    ASSERT_TRUE(Tensor::equivalent(t2_ref, new_t, 1e-3f, 0.0f, true, true));

    delete t1_ref;
    delete t1;
    delete new_t;
    delete t2_ref;


    // Test GPU
#ifdef cGPU
    // Test #1
    Tensor* t1_cpu = Tensor::randn({10000});
    Tensor* t1_gpu = t1_cpu->clone(); t1_gpu->toGPU();
    t1_cpu = t1_cpu->argsort(false, true);
    t1_gpu = t1_gpu->argsort(false, true); t1_gpu->toCPU();
    ASSERT_TRUE(Tensor::equivalent(t1_cpu, t1_gpu, 1e-3f, 0.0f, true, true));

    // Test #2
    Tensor* t2_cpu = Tensor::randn({10000});
    Tensor* t2_gpu = t2_cpu->clone(); t2_gpu->toGPU();
    t2_cpu = t2_cpu->argsort(true, true);
    t2_gpu = t2_gpu->argsort(true, true); t2_gpu->toCPU();
    ASSERT_TRUE(Tensor::equivalent(t2_cpu, t2_gpu, 1e-3f, 0.0f, true, true));

    delete t1_cpu;
    delete t1_gpu;
    delete t2_cpu;
    delete t2_gpu;

    // Note: I don't test the unstable sort here, because similar (or equal) float values could be
    // sorted into different positions
#endif
}

TEST(TensorTestSuite, tensor_squeeze) {
    // Original
    Tensor* t1 = Tensor::empty({1, 2, 3, 1, 4});

    Tensor* t1_all = t1->squeeze();
    ASSERT_TRUE(t1_all->shape == vector<int>({2, 3, 4}));

    Tensor* t1_dim0 = t1->squeeze(0);
    ASSERT_TRUE(t1_dim0->shape == vector<int>({2, 3, 1, 4}));

    Tensor* t1_dim3 = t1->squeeze(3);
    ASSERT_TRUE(t1_dim3->shape == vector<int>({1, 2, 3, 4}));

    // Delete tensors
    delete t1;
    delete t1_all;
    delete t1_dim0;
    delete t1_dim3;
}


TEST(TensorTestSuite, tensor_unsqueeze) {
    // Original
    Tensor* t1 = Tensor::empty({2, 3, 4});

    Tensor* t1_all = t1->unsqueeze();
    ASSERT_TRUE(t1_all->shape == vector<int>({1, 2, 3, 4}));

    Tensor* t1_dim0 = t1->unsqueeze(2);
    ASSERT_TRUE(t1_dim0->shape == vector<int>({2, 3, 1, 4}));

    // Delete tensors
    delete t1;
    delete t1_all;
    delete t1_dim0;
}

TEST(TensorTestSuite, tensor_expand) {
    // Original
    Tensor* t1 = new Tensor( {1, 2, 3}, {3, 1});

    Tensor *t1_ref = new Tensor({
        1.00, 1.00, 1.00,
        2.00, 2.00, 2.00,
        3.00, 3.00, 3.00}, {3, 3}, DEV_CPU);

    Tensor* new_t = t1->expand(3);
    ASSERT_TRUE(Tensor::equivalent(t1_ref, new_t, 1e-3f, 0.0f, true, true));

    delete t1;
    delete t1_ref;
    delete new_t;

    // Test GPU
#ifdef cGPU
    // Test #1
    Tensor* t1_cpu = Tensor::randn({10, 1, 10, 15, 1, 10, 1});
    Tensor* t1_gpu = t1_cpu->clone(); t1_gpu->toGPU();
    t1_cpu = t1_cpu->expand(3);
    t1_gpu = t1_gpu->expand(3); t1_gpu->toCPU();
    ASSERT_TRUE(Tensor::equivalent(t1_cpu, t1_gpu, 1e-3f, 0.0f, true, true));

    delete t1_cpu;
    delete t1_gpu;
#endif
}


TEST(TensorTestSuite, tensor_repeat_timed){
    // Test axis 1
    int times = 25;
    int factor = 128;
    Tensor* t1 = Tensor::ones({1, 3, 128, 128}, DEV_CPU);
    Tensor* t1_res = new Tensor({1*factor, 3, 128, 128}, DEV_CPU);


    // Repeat function n tims
    clock_t begin = clock();
    for(int i=0; i<times; i++){
        Tensor::repeat(t1, factor, 0, t1_res);
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time elapsed: " << elapsed_secs << "s" << std::endl;
    std::cout << "Time elapsed per function: " << elapsed_secs/times << "s" << std::endl;

    // Delete tensors
    delete t1; delete t1_res;
    ASSERT_TRUE(elapsed_secs<1000);  // Dummy test. Just for debugging
}


TEST(TensorTestSuite, tensor_repeat){
    // Test axis 1
    Tensor* t1 = Tensor::range(1, 6)->unsqueeze(0); t1->reshape_({3, 2});
    Tensor *t1_ref = new Tensor({1, 2,
                                      1, 2,
                                      1, 2,
                                      3, 4,
                                      3, 4,
                                      5, 6}, {6, 2}, DEV_CPU);
    Tensor* t1_res = Tensor::repeat(t1, {3, 2, 1}, 0);
    ASSERT_TRUE(Tensor::equivalent(t1_res, t1_ref, 1e-3f, 0.0f, true, true));

    // Test axis 1
    Tensor* t2 = Tensor::range(1, 4)->unsqueeze(0); t2->reshape_({2, 2});
    Tensor *t2_ref = new Tensor({1, 1, 1, 2, 2, 2,
                                      3, 3, 3, 4, 4, 4}, {2, 6}, DEV_CPU);
    Tensor* t2_res = Tensor::repeat(t2, 3, 1);
    ASSERT_TRUE(Tensor::equivalent(t2_res, t2_ref, 1e-3f, 0.0f, true, true));

    delete t1; delete t1_res;
    delete t2; delete t2_res;

    // Test GPU
#ifdef cGPU
    // Test #1
    Tensor* t1_cpu = Tensor::randn({1, 3, 128, 128});
    Tensor* t1_gpu = t1_cpu->clone(); t1_gpu->toGPU();

    Tensor* t1_cpu_res = Tensor::repeat(t1_cpu, 128, 0);
    Tensor* t1_gpu_res = Tensor::repeat(t1_gpu, 128, 0); t1_gpu_res->toCPU();
    ASSERT_TRUE(Tensor::equivalent(t1_cpu_res, t1_gpu_res, 1e-3f, 0.0f, true, true));

    delete t1_cpu; delete t1_cpu_res;
    delete t1_gpu; delete t1_gpu_res;
#endif
}

TEST(TensorTestSuite, tensor_tile){
    Tensor* t1 = new Tensor({1, 2}, {2, 1}, DEV_CPU);
    Tensor* t1_ref = new Tensor({1,1, 2,2, 1,1, 2,2}, {4, 2}, DEV_CPU);

//    t1->print(0);
    Tensor* t1_res = Tensor::tile(t1, {2, 2});
//    t1_res->print(0);
    ASSERT_TRUE(Tensor::equivalent(t1_res, t1_ref, 1e-3f, 0.0f, true, true));

    Tensor* t2 = new Tensor({1,2,3}, {3, 1}, DEV_CPU);
    Tensor* t2_ref = new Tensor({1,1,1, 2,2,2, 3,3,3}, {3, 3}, DEV_CPU);

//    t2->print(0);
    Tensor* t2_res = Tensor::tile(t2, {1, 3});
//    t2_res->print(0);

    ASSERT_TRUE(Tensor::equivalent(t2_res, t2_ref, 1e-3f, 0.0f, true, true));

    // Test GPU
#ifdef cGPU
    // Test #1
    Tensor* t1_cpu = Tensor::randn({1, 3, 1, 1});
    Tensor* t1_gpu = t1_cpu->clone(); t1_gpu->toGPU();

    Tensor* t1_cpu_res = Tensor::tile(t1_cpu, {1, 1, 128, 128});
    Tensor* t1_gpu_res = Tensor::tile(t1_gpu, {1, 1, 128, 128});; t1_gpu_res->toCPU();
    ASSERT_TRUE(Tensor::equivalent(t1_cpu_res, t1_gpu_res, 1e-3f, 0.0f, true, true));

    delete t1_cpu; delete t1_cpu_res;
    delete t1_gpu; delete t1_gpu_res;
#endif
}


TEST(TensorTestSuite, tensor_broadcast){
    Tensor* t1 = new Tensor({1, 2, 3}, {3}, DEV_CPU);
    Tensor* t1_t2_ref = new Tensor({1,1,1,1, 2,2,2,2, 3,3,3,3}, {3, 4}, DEV_CPU);
    Tensor* t2 = Tensor::zeros(t1_t2_ref->shape, DEV_CPU);

//    t1->print(0);
//    t2->print(0);
    Tensor* t1_res = Tensor::broadcast(t1, t2);
//    t1_res->print(0);
    ASSERT_TRUE(Tensor::equivalent(t1_res, t1_t2_ref, 1e-3f, 0.0f, true, true));

    Tensor* t2_res = Tensor::broadcast(t2, t1);  // Should be commutative
//    t1_res->print(0);
    ASSERT_TRUE(Tensor::equivalent(t2_res, t1_t2_ref, 1e-3f, 0.0f, true, true));

    // Test GPU
#ifdef cGPU
    // Test #1
    Tensor* t1_cpu = Tensor::randn({3});
    Tensor* t2_cpu = Tensor::randn({1, 3, 224, 224});
    Tensor* t1_gpu = t1_cpu->clone(); t1_gpu->toGPU();
    Tensor* t2_gpu = t2_cpu->clone(); t2_gpu->toGPU();

    Tensor* t1_cpu_res = Tensor::broadcast(t1_cpu, t2_cpu);
    Tensor* t1_gpu_res = Tensor::broadcast(t1_gpu, t2_gpu); t1_gpu_res->toCPU();
    ASSERT_TRUE(Tensor::equivalent(t1_cpu_res, t1_gpu_res, 1e-3f, 0.0f, true, true));

    delete t1_cpu; delete t1_cpu_res;
    delete t1_gpu; delete t1_gpu_res;
#endif
}

//vector<vector<int>> res = cartesian_product({{0,1}, {0,1}, {0,1}});
