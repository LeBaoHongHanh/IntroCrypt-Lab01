#pragma once
#include "big_int.h"

/**
 * @brief Tính (base^exponent) % mod
 * @task Nhiệm vụ 1 (A & D)
 */
big_int modular_exponentiation(big_int base, big_int exponent, big_int mod);

/**
 * @brief Sinh số nguyên tố an toàn p (p và (p-1)/2 đều là số nguyên tố)
 * @task Nhiệm vụ 2 (B)
 */
big_int generate_safe_prime(int bit_size);

/**
 * @brief Sinh khóa riêng ngẫu nhiên trong khoảng [2, p-2]
 * @task Nhiệm vụ 3 (C)
 */
big_int generate_private_key(big_int p);