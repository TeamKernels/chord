#include <chord/dsp/freq_shift.hpp>
#include <gtest/gtest.h>

TEST(FreqShiftTest, CompileTest) {
    kfr::univector<kfr::complex<float>> input(100, kfr::complex<float>{1.0f, 0.0f});
    auto shifted = chord::dsp::freq_shift(input, 1000.0f, 100.0f);
    
    auto uni_vec_res = kfr::univector<kfr::complex<float>>(shifted);

    EXPECT_EQ(uni_vec_res.size(), input.size());
}
