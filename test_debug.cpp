#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BigInt.h"
#include "crypto_utils.h"

int main()
{
  srand(time(NULL));

  std::cout << "=== TEST 1: BigInt Basic Operations ===" << std::endl;
  try
  {
    BigInt a = BigInt(123);
    BigInt b = BigInt(456);
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a * b = " << (a * b) << std::endl;
    std::cout << "b - a = " << (b - a) << std::endl;
    std::cout << "b / a = " << (b / a) << std::endl;
    std::cout << "b % a = " << (b % a) << std::endl;
    std::cout << "TEST 1: PASS" << std::endl
              << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cerr << "TEST 1 FAILED: " << e.what() << std::endl;
    return 1;
  }

  std::cout << "=== TEST 2: Modular Exponentiation ===" << std::endl;
  try
  {
    BigInt base = BigInt(2);
    BigInt exp = BigInt(10);
    BigInt mod = BigInt(1000);
    BigInt result = modular_exponentiation(base, exp, mod);
    std::cout << "2^10 mod 1000 = " << result << std::endl;
    std::cout << "Ket qua mong doi: 24" << std::endl;
    if (result == BigInt(24))
    {
      std::cout << "TEST 2: PASS" << std::endl
                << std::endl;
    }
    else
    {
      std::cout << "TEST 2: FAIL - Ket qua sai!" << std::endl;
      return 1;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "TEST 2 FAILED: " << e.what() << std::endl;
    return 1;
  }

  std::cout << "=== TEST 3: Generate Random BigInt ===" << std::endl;
  try
  {
    std::cout << "Sinh so ngau nhien 32 bit..." << std::endl;
    BigInt random = generate_random_bigint(32);
    std::cout << "Random 32-bit number: " << random << std::endl;
    std::cout << "TEST 3: PASS" << std::endl
              << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cerr << "TEST 3 FAILED: " << e.what() << std::endl;
    return 1;
  }

  std::cout << "=== TEST 4: Generate Safe Prime (64 bit) ===" << std::endl;
  try
  {
    std::cout << "Sinh safe prime 64 bit (khoang 10-30 giay)..." << std::endl;
    BigInt p = generate_safe_prime(64);
    if (p == 0)
    {
      std::cout << "TEST 4: FAIL - Khong tim thay safe prime" << std::endl;
      return 1;
    }
    std::cout << "Safe prime: " << p << std::endl;
    std::cout << "TEST 4: PASS" << std::endl
              << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cerr << "TEST 4 FAILED: " << e.what() << std::endl;
    return 1;
  }

  std::cout << "=== TEST 5: Full Diffie-Hellman (64 bit) ===" << std::endl;
  try
  {
    std::cout << "Sinh safe prime 64 bit..." << std::endl;
    BigInt p = generate_safe_prime(64);
    if (p == 0)
    {
      std::cerr << "Khong the sinh safe prime!" << std::endl;
      return 1;
    }

    BigInt g = BigInt(2);
    std::cout << "p = " << p << std::endl;
    std::cout << "g = " << g << std::endl;

    BigInt a = generate_private_key(p);
    BigInt b = generate_private_key(p);
    std::cout << "Private key a: " << a << std::endl;
    std::cout << "Private key b: " << b << std::endl;

    BigInt A = modular_exponentiation(g, a, p);
    BigInt B = modular_exponentiation(g, b, p);
    std::cout << "Public key A: " << A << std::endl;
    std::cout << "Public key B: " << B << std::endl;

    BigInt s1 = modular_exponentiation(B, a, p);
    BigInt s2 = modular_exponentiation(A, b, p);
    std::cout << "Alice's secret: " << s1 << std::endl;
    std::cout << "Bob's secret:   " << s2 << std::endl;

    if (s1 == s2)
    {
      std::cout << "TEST 5: PASS - Shared secrets match!" << std::endl;
    }
    else
    {
      std::cout << "TEST 5: FAIL - Shared secrets don't match!" << std::endl;
      return 1;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "TEST 5 FAILED: " << e.what() << std::endl;
    return 1;
  }

  std::cout << std::endl;
  std::cout << "========================================" << std::endl;
  std::cout << "  TAT CA CAC TEST DIEU THANH CONG!" << std::endl;
  std::cout << "========================================" << std::endl;

  return 0;
}