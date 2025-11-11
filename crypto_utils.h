#pragma once

#include "BigInt.h" // Bắt buộc phải include BigInt vì chúng ta dùng nó

/**
 * ======================================================================
 * CÁC HÀM MẬT MÃ (THEO YÊU CẦU BÀI TẬP)
 * ======================================================================
 */

/**
 * @brief Nhiệm vụ 1 (A & D): Tính (base^exponent) % mod
 * @details Sử dụng thuật toán "Bình phương và Nhân" (Exponentiation by Squaring)
 * để tính toán hiệu quả, tránh bị tràn số.
 */
BigInt modular_exponentiation(BigInt base, BigInt exponent, BigInt mod);

/**
 * @brief Nhiệm vụ 2 (B): Sinh số nguyên tố an toàn p
 * @details Tìm một số nguyên tố p sao cho (p-1)/2 cũng là số nguyên tố (tên là q).
 * Hàm này sẽ bao gồm cả thuật toán kiểm tra nguyên tố Miller-Rabin.
 * @param bit_size Số bit mong muốn của số nguyên tố p (ví dụ: 512).
 */
BigInt generate_safe_prime(int bit_size);

/**
 * @brief Nhiệm vụ 3 (C): Sinh khóa riêng ngẫu nhiên
 * @details Sinh một số nguyên ngẫu nhiên trong khoảng [2, p-2].
 * @param p Số nguyên tố đã được sinh ra.
 */
BigInt generate_private_key(BigInt p);

BigInt generate_random_bigint(int bit_size);