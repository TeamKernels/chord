namespace chord::math {

template <typename E>
auto mul_vec_w_offset_conj(E&& input, size_t offset, Status& status, size_t trunc_start, size_t trunc_end) {
    using T = typename kfr::expression_traits<E>::value_type;
    auto length = input.size() - offset - trunc_end - trunc_start;
    
    if (length <= 0) {
        status = Status::INPUT_TOO_SMALL;
        throw std::runtime_error("Input vector is too small");
    }
    
    status = Status::OK;
    return input.slice(trunc_start, length) * kfr::cconj(input.slice(offset + trunc_start, length));
}

}  // namespace chord::math
