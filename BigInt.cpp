#include "BigInt.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <iomanip>

// === HELPER FUNCTIONS ===

void BigInt::trim()
{
  while (!a.empty() && a.back() == 0)
    a.pop_back();
  if (a.empty())
    sign = 1;
}

// === CONSTRUCTORS ===

BigInt::BigInt() : sign(1) {}

BigInt::BigInt(long long v)
{
  *this = v;
}

BigInt::BigInt(const string &s)
{
  if (s.empty())
  {
    sign = 1;
    return;
  }
  sign = 1;
  int start = 0;
  if (s[0] == '-')
  {
    sign = -1;
    start = 1;
  }
  for (int i = (int)s.size() - 1; i >= start; i -= base_digits)
  {
    int x = 0;
    for (int j = std::max(start, i - base_digits + 1); j <= i; j++)
      x = x * 10 + s[j] - '0';
    a.push_back(x);
  }
  trim();
}

void BigInt::operator=(long long v)
{
  sign = 1;
  if (v < 0)
  {
    sign = -1;
    v = -v;
  }
  a.clear();
  while (v > 0)
  {
    a.push_back(v % base);
    v /= base;
  }
}

// === COMPARISON OPERATORS ===

bool BigInt::operator<(const BigInt &b) const
{
  if (sign != b.sign)
    return sign < b.sign;
  if (a.size() != b.a.size())
    return (a.size() < b.a.size()) ^ (sign < 0);
  for (int i = (int)a.size() - 1; i >= 0; i--)
    if (a[i] != b.a[i])
      return (a[i] < b.a[i]) ^ (sign < 0);
  return false;
}

bool BigInt::operator>(const BigInt &b) const
{
  return b < *this;
}

bool BigInt::operator<=(const BigInt &b) const
{
  return !(b < *this);
}

bool BigInt::operator>=(const BigInt &b) const
{
  return !(*this < b);
}

bool BigInt::operator==(const BigInt &b) const
{
  return sign == b.sign && a == b.a;
}

bool BigInt::operator!=(const BigInt &b) const
{
  return !(*this == b);
}

bool BigInt::isZero() const
{
  return a.empty() || (a.size() == 1 && a[0] == 0);
}

bool BigInt::operator>(long long v) const
{
  return *this > BigInt(v);
}

bool BigInt::operator<(long long v) const
{
  return *this < BigInt(v);
}

bool BigInt::operator==(long long v) const
{
  return *this == BigInt(v);
}

// === ARITHMETIC OPERATORS ===

BigInt BigInt::operator+(const BigInt &b) const
{
  if (sign == b.sign)
  {
    BigInt res = *this;
    int carry = 0;
    for (size_t i = 0; i < std::max(a.size(), b.a.size()) || carry; ++i)
    {
      if (i == res.a.size())
        res.a.push_back(0);
      res.a[i] += carry + (i < b.a.size() ? b.a[i] : 0);
      carry = res.a[i] >= base;
      if (carry)
        res.a[i] -= base;
    }
    return res;
  }
  return *this - (-b);
}

BigInt BigInt::operator-(const BigInt &b) const
{
  if (sign == b.sign)
  {
    if (abs() >= b.abs())
    {
      BigInt res = *this;
      int carry = 0;
      for (size_t i = 0; i < b.a.size() || carry; ++i)
      {
        res.a[i] -= carry + (i < b.a.size() ? b.a[i] : 0);
        carry = res.a[i] < 0;
        if (carry)
          res.a[i] += base;
      }
      res.trim();
      return res;
    }
    return -(b - *this);
  }
  return *this + (-b);
}

BigInt BigInt::operator*(const BigInt &b) const
{
  BigInt res;
  res.a.resize(a.size() + b.a.size());
  for (size_t i = 0; i < a.size(); ++i)
  {
    long long carry = 0;
    for (size_t j = 0; j < b.a.size() || carry; ++j)
    {
      long long cur = res.a[i + j] + (long long)a[i] * (j < b.a.size() ? b.a[j] : 0) + carry;
      res.a[i + j] = (int)(cur % base);
      carry = cur / base;
    }
  }
  res.sign = sign * b.sign;
  res.trim();
  return res;
}

void divmod(const BigInt &a1, const BigInt &b1, BigInt &q, BigInt &r)
{
  // Xử lý trường hợp đặc biệt
  if (b1.isZero())
  {
    throw std::runtime_error("Division by zero");
  }

  BigInt a = a1.abs();
  BigInt b = b1.abs();

  // Nếu a < b thì q = 0, r = a
  if (a < b)
  {
    q = BigInt(0);
    r = a1;
    return;
  }

  // Nếu b = 1 thì q = a, r = 0
  if (b == BigInt(1))
  {
    q = a;
    q.sign = a1.sign * b1.sign;
    r = BigInt(0);
    return;
  }

  // Thuật toán chia tiêu chuẩn
  int norm = BigInt::base / (b.a.back() + 1);
  a = a * norm;
  b = b * norm;

  q.a.clear();
  q.a.resize(a.a.size());
  r = BigInt(0);

  for (int i = (int)a.a.size() - 1; i >= 0; i--)
  {
    r = r * BigInt::base;
    if (r.a.empty())
      r.a.push_back(0);
    r.a[0] = a.a[i];
    r.trim();

    int s1 = (int)r.a.size() <= (int)b.a.size() ? 0 : r.a[b.a.size()];
    int s2 = (int)r.a.size() <= (int)b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
    int d = ((long long)BigInt::base * s1 + s2) / b.a.back();

    BigInt temp = b * d;
    r = r - temp;

    while (r < BigInt(0))
    {
      r = r + b;
      --d;
    }

    q.a[i] = d;
  }

  q.sign = a1.sign * b1.sign;
  r.sign = a1.sign;
  q.trim();
  r.trim();

  // Chia r cho norm để lấy kết quả đúng
  if (norm != 1)
  {
    r = r / norm;
  }
}

BigInt BigInt::operator/(const BigInt &b) const
{
  if (b.isZero())
  {
    throw std::runtime_error("Division by zero");
  }
  BigInt q, r;
  divmod(*this, b, q, r);
  return q;
}

BigInt BigInt::operator%(const BigInt &b) const
{
  if (b.isZero())
  {
    throw std::runtime_error("Modulo by zero");
  }
  BigInt q, r;
  divmod(*this, b, q, r);
  return r;
}

BigInt BigInt::operator/(int v) const
{
  BigInt res = *this;
  res.sign *= (v < 0 ? -1 : 1);
  v = std::abs(v);
  long long carry = 0;
  for (int i = (int)a.size() - 1; i >= 0; --i)
  {
    long long cur = a[i] + carry * (long long)base;
    res.a[i] = (int)(cur / v);
    carry = cur % v;
  }
  res.trim();
  return res;
}

int BigInt::operator%(int v) const
{
  if (v < 0)
    v = -v;
  int m = 0;
  for (int i = (int)a.size() - 1; i >= 0; --i)
    m = (int)((a[i] + m * (long long)base) % v);
  return m * sign;
}

// === I/O OPERATORS ===

std::ostream &operator<<(std::ostream &stream, const BigInt &v)
{
  if (v.sign == -1)
    stream << '-';
  stream << (v.a.empty() ? 0 : v.a.back());
  for (int i = (int)v.a.size() - 2; i >= 0; --i)
    stream << std::setw(BigInt::base_digits) << std::setfill('0') << v.a[i];
  return stream;
}

std::istream &operator>>(std::istream &stream, BigInt &v)
{
  string s;
  stream >> s;
  v = BigInt(s);
  return stream;
}

// === HELPER FUNCTIONS ===

int BigInt::get_num_digits() const
{
  if (a.empty())
    return 1;
  int total = (a.size() - 1) * base_digits;
  int last = a.back();
  int digits = 0;
  while (last > 0)
  {
    digits++;
    last /= 10;
  }
  return total + digits;
}

BigInt BigInt::abs() const
{
  BigInt res = *this;
  res.sign = 1;
  return res;
}

BigInt operator-(const BigInt &a)
{
  BigInt res = a;
  res.sign = -res.sign;
  return res;
}

BigInt BigInt::operator*(int v) const
{
  BigInt res = *this;
  res.sign *= (v < 0 ? -1 : 1);
  v = std::abs(v);
  long long carry = 0;
  for (size_t i = 0; i < a.size() || carry; ++i)
  {
    if (i == res.a.size())
      res.a.push_back(0);
    long long cur = carry + (long long)res.a[i] * v;
    res.a[i] = (int)(cur % base);
    carry = cur / base;
  }
  res.trim();
  return res;
}

BigInt operator+(const BigInt &a, int v)
{
  return a + BigInt(v);
}

BigInt operator*(int v, const BigInt &a)
{
  return a * v;
}