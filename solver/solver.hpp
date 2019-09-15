
#include "base/matrix.hpp"
namespace solvant {
namespace solver {
template <typename T, std::size_t R, std::size_t C>
class Solver {
public:
    virtual void solve() = 0;
};
}  // namespace solver
}  // namespace solvant
