namespace chord::dsp {

template <typename E>
auto freq_shift(const E& signal, float fs, float fc){
    using T = typename kfr::expression_traits<E>::value_type;
    
    auto phase = kfr::phasor(fc, fs); 

    auto osc = kfr::exp(phase * 2 * kfr::constants<float>::pi);

    return signal * kfr::cast<T>(osc);
}

}  // namespace chord::dsp
