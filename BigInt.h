#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using std::string;
using std::vector;

class BigInt
{
public:
  vector<int> a;
  int sign;

  const static int base = 1000000000; // 10^9
  const static int base_digits = 9;

  // --- HÀM HỖ TRỢ NỘI BỘ ---
  void trim();

  // --- NHÓM 1: HÀM KHỞI TẠO (CONSTRUCTORS) & GÁN CƠ BẢN ---
  BigInt();
  BigInt(long long v);
  BigInt(const string &s);
  void operator=(long long v);

  // --- NHÓM 2: CÁC TOÁN TỬ SO SÁNH ---
  bool operator>(const BigInt &b) const;
  bool operator<(const BigInt &b) const;
  bool operator==(const BigInt &b) const;
  bool operator!=(const BigInt &b) const;
  bool operator>=(const BigInt &b) const;
  bool operator<=(const BigInt &b) const;
  bool isZero() const;
  bool operator>(long long v) const;
  bool operator<(long long v) const;
  bool operator==(long long v) const;

  // --- NHÓM 3: CÁC TOÁN TỬ SỐ HỌC CƠ BẢN (BigInt vs BigInt) ---
  BigInt operator+(const BigInt &b) const;
  BigInt operator-(const BigInt &b) const;
  BigInt operator*(const BigInt &b) const;
  BigInt operator/(const BigInt &b) const;
  BigInt operator%(const BigInt &b) const;

  // --- NHÓM 4: TOÁN TỬ VỚI SỐ NHỎ (TỐI ƯU HÓA) ---
  BigInt operator/(int v) const;
  int operator%(int v) const;
  BigInt operator*(int v) const;

  // --- NHÓM 5: NHẬP/XUẤT (IN/OUT) ---
  friend std::ostream &operator<<(std::ostream &stream, const BigInt &v);
  friend std::istream &operator>>(std::istream &stream, BigInt &v);
  friend void divmod(const BigInt &a, const BigInt &b, BigInt &q, BigInt &r);

  // --- HÀM FRIEND OPERATORS ---
  friend BigInt operator-(const BigInt &a);
  friend BigInt operator+(const BigInt &a, int v);
  friend BigInt operator*(int v, const BigInt &a);

  // --- HÀM HELPER MỚI ---
  int get_num_digits() const;
  BigInt abs() const;
};