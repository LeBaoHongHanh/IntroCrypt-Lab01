#include <iostream>
#include <cstdint>
#include "utils.h"

int main()
{
  // int bit_size = 512;
  // uint64_t p = generate_safe_prime(bit_size);
  // uint64_t g = 2;

  // uint64_t a = generate_private_key(p);
  // uint64_t b = generate_private_key(p);

  // uint64_t A = modular_exponentiation(g, a, p);
  // uint64_t B = modular_exponentiation(g, b, p);

  // uint64_t alice_shared_secret = modular_exponentiation(B, a, p);
  // uint64_t bob_shared_secret = modular_exponentiation(A, b, p);

  // std::cout << "Bí␣mâ ˙t␣chung␣Alice␣nhâ ˙n␣đươ ˙c:␣" << alice_shared_secret << "\n";
  // std::cout << "Bí␣mâ ˙t␣chung␣Bob␣nhâ ˙n␣đươ ˙c:␣" << bob_shared_secret << "\n";
  // std::cout << "Quá␣trình␣tính␣toán␣đúng␣không?␣" << (alice_shared_secret == bob_shared_secret) << "\n";

  std::cout << "hello world" << generate_safe_prime(1);

  return 0;
}