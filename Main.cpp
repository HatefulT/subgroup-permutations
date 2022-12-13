#include <iostream>
#include <bitset>
#include <vector>
#include <array>

using namespace std;

const uint32_t MAX_ORDER = 32;
using bitset32 = bitset<MAX_ORDER>;

class Permutation
{
private:
  uint32_t ORDER;
  vector<uint32_t> perm_value;

public:
  enum PRINT_METHOD {
    PRINT_STANDART,
    PRINT_INDEPENDENT, 
    PRINT_INDEX
  };
    

  explicit Permutation(uint32_t p_ORDER, uint32_t perm_index = 0)
    : ORDER(p_ORDER)
  {
    perm_value.reserve(ORDER);

    vector<uint32_t> Y;
    Y.reserve(ORDER);
    uint32_t tmp_uint = perm_index;
    Y[ORDER-1] = 0;
    for(uint32_t i=1; i<ORDER; ++i) {
      Y[ORDER-1-i] = tmp_uint % (i+1);
      tmp_uint /= i+1;
    }

    bitset32 checked;
    for(uint32_t i = 0; i < ORDER; ++i) {
      uint32_t c = 0;
      uint32_t j;
      for(j = 0; j < ORDER; ++j) {
        if(not checked[j] and c == Y[i])
          break;
        if(not checked[j])
          ++c;
      }
      checked[j] = true;
      // perm_value[i] = j;
      perm_value.push_back(j);
    }
  }

  /* We want to use make bijective mapping between permutations and 
   * uints for ex.: (1 2 3 4 5 6 ... n) -> 0 and
   * (n .. 6 5 4 3 2 1) -> n! - 1
   * just to save it more space-efficient.
   */
  uint32_t get_index() const 
  {
    /* Why we can't just do for permutaiton (a1 a2 a3 .. an)
     * a1 * n ^ (ORDER-1) + a2 * n ^ (ORDER-2) + ... + an?
     * Because, for example we can't have permutation (1 1 1)
     * so we have much less permutations than ORDER^ORDER
     *
     * Firstly, we use the fact that when in permutation 
     * (a1 a2 a3 .. an)
     * if a1 == 1: a2, a3 .. an != 1
     */
    bitset32 checked;
    vector<uint32_t> Y;
    Y.reserve(ORDER);
    for(uint32_t i=0; i<ORDER; ++i) {
      uint32_t c = 0;
      for(uint32_t j=0; j<perm_value[i]; ++j)
        if(not checked[j])
          ++c;
      checked[perm_value[i]] = true;
      Y[i] = c;
    }

    /* Now we just make bijective mapping from Y to uints
     * using factorial notation
     */
    uint32_t index = 0;
    uint32_t factorial = 1;
    uint32_t j = 1;
    for(int i = ORDER-2; i >= 0; --i) {
      index += factorial*Y[i];
      ++j;
      factorial *= j;
    }
    return index;
  }

  vector<vector<uint32_t>> to_independent_cycles() const
  {
    vector<vector<uint32_t>> result;
    bitset32 checked;
    for(uint32_t i = 0; i < ORDER; ++i) {
      if(checked[i])
        continue;
      result.push_back({ i });
      checked[i] = true;
      uint32_t j = perm_value[i];
      while(j != i) {
        checked[j] = true;
        result.back().push_back(j);
        j = perm_value[j];
      }
    }
    return result;
  }

  void print(ostream &os,
      PRINT_METHOD print_method = PRINT_INDEPENDENT) const
  {
    if(print_method == PRINT_INDEPENDENT) {
      auto undep_cycles = to_independent_cycles();
      if(undep_cycles.size() == ORDER) {
        os << "id";
        return;
      }
      for(const auto &cycle : undep_cycles) {
        if(cycle.size() == 1)
          continue;
        os << "(";
        for(const auto &elem : cycle)
          os << elem+1;
        os << ")";
      }
    } else if(print_method == PRINT_STANDART) {
      for(auto elem : perm_value) 
        os << elem << " ";
    } else {
      os << get_index();
    }
  }

  friend ostream &operator<<(ostream &os, const Permutation &perm)
  {
    perm.print(os); 
    return os;
  }
};

int main()
{
  uint32_t ORDER = 5;
  for(uint32_t i = 0; i<5*4*3*2; ++i) {
    Permutation x{ORDER, i};
    if(x.get_index() != i) {
      cout << x << endl;
      return 1;
    } 
    cout << "Permutation ";
    x.print(cout, Permutation::PRINT_METHOD::PRINT_INDEX);
    cout << ": ";
    x.print(cout, Permutation::PRINT_METHOD::PRINT_STANDART);
    cout << x << endl;
  }
}
