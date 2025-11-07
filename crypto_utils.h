#pragma once
#include "BigInt.h"

/**
 * @brief Tính (base^exponent) % mod
 * @task Nhiệm vụ 1 (A & D)
 */
BigInt modular_exponentiation(BigInt base, BigInt exponent, BigInt mod);

/**
 * @brief Sinh số nguyên tố an toàn p (p và (p-1)/2 đều là số nguyên tố)
 * @task Nhiệm vụ 2 (B)
 */
BigInt generate_safe_prime(int bit_size);

/**
 * @brief Sinh khóa riêng ngẫu nhiên trong khoảng [2, p-2]
 * @task Nhiệm vụ 3 (C)
 */
BigInt generate_private_key(BigInt p);