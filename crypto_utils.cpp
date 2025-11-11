#include "crypto_utils.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <sstream>

// ========================================================================
// HÀM 1: MODULAR EXPONENTIATION (Bình phương và nhân)
// ========================================================================
BigInt modular_exponentiation(BigInt base, BigInt exponent, BigInt mod)
{
  BigInt result = 1;
  base = base % mod;

  while (exponent > 0)
  {
    // Nếu exponent là số lẻ
    if (exponent % 2 == 1)
    {
      result = (result * base) % mod;
    }
    // Bình phương base
    base = (base * base) % mod;
    // Chia đôi exponent
    exponent = exponent / 2;
  }
  return result;
}

// ========================================================================
// HÀM HỖ TRỢ: SINH SỐ NGẪU NHIÊN N BIT (VERSION AN TOÀN)
// ========================================================================
BigInt generate_random_bigint(int bit_size)
{
  if (bit_size <= 0)
  {
    std::cerr << "[ERROR] bit_size phai > 0" << std::endl;
    return BigInt(0);
  }

  // Tính số chữ số thập phân cần thiết
  // 2^bit_size có khoảng bit_size * log10(2) chữ số
  int num_digits = (int)(bit_size * 0.30103) + 2;

  std::string s = "";

  // Chữ số đầu không được là 0
  s += char('1' + rand() % 9);

  // Sinh các chữ số còn lại
  for (int i = 1; i < num_digits; i++)
  {
    s += char('0' + rand() % 10);
  }

  BigInt result(s);

  // Đảm bảo số là lẻ (để có thể là số nguyên tố)
  if (result % 2 == 0)
  {
    result = result + 1;
  }

  return result;
}

// ========================================================================
// HÀM HỖ TRỢ: KIỂM TRA SỐ NGUYÊN TỐ VỚI TRIAL DIVISION
// ========================================================================
bool is_divisible_by_small_primes(const BigInt &n)
{
  // Danh sách 100 số nguyên tố đầu tiên
  int small_primes[] = {
      2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
      73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
      157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233,
      239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317,
      331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419,
      421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503,
      509, 521, 523, 541};

  for (int p : small_primes)
  {
    if (n == BigInt(p))
      return false; // Chính nó là số nguyên tố
    if (n % p == 0)
      return true; // Chia hết -> không phải số nguyên tố
  }
  return false;
}

// ========================================================================
// HÀM HỖ TRỢ: MILLER-RABIN PRIMALITY TEST
// ========================================================================
bool miller_rabin_test(const BigInt &n, int iterations)
{
  // Xử lý các trường hợp đặc biệt
  if (n == 2 || n == 3)
    return true;
  if (n < 2 || n % 2 == 0)
    return false;

  // Viết n-1 = 2^r * d với d lẻ
  BigInt d = n - 1;
  int r = 0;
  while (d % 2 == 0)
  {
    d = d / 2;
    r++;
  }

  // Danh sách các base nhỏ để test
  int small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  int num_small = 12;

  // Test với các số nguyên tố nhỏ
  for (int i = 0; i < std::min(num_small, iterations); i++)
  {
    BigInt a = BigInt(small_primes[i]);
    if (a >= n - 1)
      break;

    BigInt x = modular_exponentiation(a, d, n);

    if (x == 1 || x == n - 1)
      continue;

    bool composite = true;
    for (int j = 0; j < r - 1; j++)
    {
      x = modular_exponentiation(x, BigInt(2), n);
      if (x == n - 1)
      {
        composite = false;
        break;
      }
    }

    if (composite)
      return false;
  }

  return true;
}

// ========================================================================
// HÀM 2: SINH SỐ NGUYÊN TỐ AN TOÀN (SAFE PRIME) - VERSION ĐƠN GIẢN HÓA
// ========================================================================
BigInt generate_safe_prime(int bit_size)
{
  std::cout << "   [INFO] Bat dau tim safe prime voi " << bit_size << " bit..." << std::endl;

  if (bit_size < 8)
  {
    std::cerr << "   [ERROR] bit_size qua nho! Phai >= 8" << std::endl;
    return BigInt(0);
  }

  int attempts = 0;
  int max_attempts = 50000;

  while (attempts < max_attempts)
  {
    attempts++;

    // BƯỚC 1: Sinh số ngẫu nhiên q có (bit_size - 1) bits
    BigInt q = generate_random_bigint(bit_size - 1);

    // BƯỚC 2: Kiểm tra q có chia hết cho số nguyên tố nhỏ không
    if (is_divisible_by_small_primes(q))
    {
      continue;
    }

    // BƯỚC 3: Test q có phải số nguyên tố không (Miller-Rabin với ít vòng)
    if (!miller_rabin_test(q, 5))
    {
      continue;
    }

    // BƯỚC 4: Tính p = 2*q + 1
    BigInt p = q * 2 + 1;

    // BƯỚC 5: Kiểm tra p có chia hết cho số nguyên tố nhỏ không
    if (is_divisible_by_small_primes(p))
    {
      continue;
    }

    // BƯỚC 6: Test p có phải số nguyên tố không
    if (miller_rabin_test(p, 5))
    {
      std::cout << "   [SUCCESS] Tim thay sau " << attempts << " lan thu!" << std::endl;
      std::cout << "   [INFO] q = " << q << std::endl;
      return p;
    }

    // In tiến trình
    if (attempts % 500 == 0)
    {
      std::cout << "   [INFO] Da thu " << attempts << " lan..." << std::endl;
    }
  }

  // Không tìm được
  std::cerr << "   [ERROR] Khong tim thay safe prime sau " << max_attempts << " lan thu!" << std::endl;
  return BigInt(0);
}

// ========================================================================
// HÀM 3: SINH KHÓA RIÊNG (PRIVATE KEY)
// ========================================================================
BigInt generate_private_key(BigInt p)
{
  // Sinh số ngẫu nhiên trong khoảng [2, p-2]
  int num_digits = p.get_num_digits();

  // Tạo một số ngẫu nhiên nhỏ hơn p
  std::string s = "";
  s += char('1' + rand() % 9);

  for (int i = 1; i < num_digits - 2; i++)
  {
    s += char('0' + rand() % 10);
  }

  BigInt key(s);

  // Đảm bảo key trong khoảng [2, p-2]
  BigInt range = p - 3;
  key = key % range;
  key = key + 2;

  return key;
}