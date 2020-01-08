#ifndef BANDMATDEF
#define BANDMATDEF
//! This class defines a SYMETRIC banded matrix. So we are only interested
//! in banded matrices that have equal upper and lower bandwidth. That is,
//! the value of B is equal to the upper bandwidth plus the lower bandwidth
//! plus 1. e.g for a tridiagonal matrix B = 3.
//! We don't find any use for having seperate upper and lower band matrices.
#include <array>
namespace solvant {
namespace base {
template <typename T, std::size_t N, std::size_t B>
class banded_matrix {
private:
    // First N entries store the lowest sub-band
    // and entires start at B and finish at N
    // ...
    // last N entries store the highest sub-band
    // etc
    std::array<T, N * B> m_data;

public:
    banded_matrix(std::array<T, B>&& diagonal_constants);
    virtual ~banded_matrix(){};

    // move assignment operator
    banded_matrix& operator=(banded_matrix&& other) noexcept {
        if (this != &other) {
            m_data = std::move(other.m_data);
        }
        return *this;
    }

    const T* data() const { return m_data.data(); }

    std::size_t bands() const { return B; }

    T at(const std::size_t i, const std::size_t j) {
        if (i >= N || j >= N || i < 0 || j < 0) {
            throw std::out_of_range("index out of bounds");
        }
        if (std::abs(long(i - j)) > (B >> 1)) {
            return 0;
        }
        return (*this)(i, j);
    }
    void set(const std::size_t i, const std::size_t j, const T val) {
        if (i >= N || j >= N || i < 0 || j < 0) {
            throw std::out_of_range("index out of bounds");
        }
        if (std::abs(long(i - j)) <= (B >> 1)) {
            (*this)(i, j) = val;
        }
    }

    // using band-major form
    T operator[](const std::size_t i) const { return m_data[i]; }

    // standard (i,j) access
    T operator()(const std::size_t i, const std::size_t j) const {
        return m_data[((j - i) + (B >> 1)) * N + j];
    }

    T& operator()(const std::size_t i, const std::size_t j) {
        return m_data[((j - i) + (B >> 1)) * N + j];
    }
};  // namespace base

template <typename T, std::size_t N, std::size_t B>
banded_matrix<T, N, B>::banded_matrix(std::array<T, B>&& diagonal_constants) {
    for (std::size_t j = 0; j < B; ++j) {
        auto c = diagonal_constants[j];
        for (std::size_t i = 0; i < N; ++i) {
            m_data[j * N + i] = c;
        }
    }
}

//! this makes use of the fact that the product of two banded matrices
template <typename T, std::size_t N, std::size_t B1, std::size_t B2>
void matrix_prod(const banded_matrix<T, N, B1>& A,
                 const banded_matrix<T, N, B2>& B,
                 banded_matrix<T, N, 2 * (B1 / 2 + B2 / 2) + 1>& C) {
    
}

}  // namespace base
}  // namespace solvant
#endif
