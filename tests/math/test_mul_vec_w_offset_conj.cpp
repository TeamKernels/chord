#include <chord/math/mul_vec_w_offset_conj.hpp>
#include <gtest/gtest.h>

TEST(MulVecWOffsetConjTest, BasicComputation) {
    kfr::univector<kfr::complex<float>> input = {{1.0f, 0.0f},
                                                 {0.0f, 1.0f},
                                                 {-1.0f, 0.0f},
                                                 {0.0f, -1.0f}};
    chord::Status status;
    // offset=1, trunc_start=0, trunc_end=1
    // length = 4 - 1 - 1 - 0 = 2
    // input1 = input.slice(0, 2) = {1.0f, 0.0f}, {0.0f, 1.0f}
    // input2 = input.slice(1, 2) = {0.0f, 1.0f}, {-1.0f, 0.0f}
    // product[0] = {1, 0} * conj({0, 1}) = -i
    // product[1] = {0, 1} * conj({-1, 0}) = -i


    auto result = chord::math::mul_vec_w_offset_conj(input, 1, status, 0, 1);

    auto uni_vec_res = kfr::univector<kfr::complex<float>>(result);

    EXPECT_EQ(status, chord::Status::OK);
    EXPECT_EQ(uni_vec_res.size(), 2);
    EXPECT_NEAR(uni_vec_res[0].real(), 0.0f, 1e-6);
    EXPECT_NEAR(uni_vec_res[0].imag(), -1.0f, 1e-6);
    EXPECT_NEAR(uni_vec_res[1].real(), 0.0f, 1e-6);
    EXPECT_NEAR(uni_vec_res[1].imag(), -1.0f, 1e-6);
}

TEST(MulVecWOffsetConjTest, ErrorCase) {
    kfr::univector<kfr::complex<float>> input = {{1.0f, 0.0f}};
    chord::Status status;

    kfr::univector<kfr::complex<float>> uni_vec_res;
    try {
        auto result = chord::math::mul_vec_w_offset_conj(input, 1, status, 0, 0);
        uni_vec_res = kfr::univector<kfr::complex<float>>(result);
    } catch (const std::runtime_error& e) {
    }

    EXPECT_EQ(status, chord::Status::INPUT_TOO_SMALL);
    EXPECT_EQ(uni_vec_res.size(), 0);
}
