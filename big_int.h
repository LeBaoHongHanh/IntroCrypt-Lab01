#pragma once

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class big_int
{
private:
  // Dùng vector để lưu các "chữ số"
  // Mỗi phần tử vector sẽ lưu 1 số có 9 chữ số (base 1 tỷ)
  vector<int> a;

  // Dấu của số: 1 là dương, -1 là âm
  int sign;

  // Các hằng số cơ bản
  const static int base = 1000000000; // 10^9
  const static int base_digits = 9;

  // --- HÀM HỖ TRỢ NỘI BỘ ---

  // Xóa các số 0 vô nghĩa ở đầu vector (ví dụ: 000123 -> 123)
  void trim();

public:
  // --- NHÓM 1: HÀM KHỞI TẠO (CONSTRUCTORS) & GÁN CƠ BẢN ---
  // Yêu cầu: Cần để tạo biến big_int

  big_int();                   // Hàm khởi tạo mặc định (tạo số 0)
  big_int(long long v);        // Khởi tạo từ số long long (ví dụ: g = 2)
  big_int(const string &s);    // Khởi tạo từ một chuỗi (hữu ích cho debug)
  void operator=(long long v); // Gán một số long long cho big_int (ví dụ: result = 1)

  // --- NHÓM 2: CÁC TOÁN TỬ SO SÁNH ---
  // Yêu cầu: Cần cho logic vòng lặp và kiểm tra điều kiện

  // So sánh (a > b)
  bool operator>(const big_int &b) const;
  // So sánh (a < b)
  bool operator<(const big_int &b) const;
  // So sánh (a == b) - [Dùng để kiểm tra alice_secret == bob_secret]
  bool operator==(const big_int &b) const;
  // So sánh (a != b)
  bool operator!=(const big_int &b) const;
  // So sánh (a >= b)
  bool operator>=(const big_int &b) const;
  // So sánh (a <= b)
  bool operator<=(const big_int &b) const;

  // Kiểm tra số có bằng 0 không? - [Rất quan trọng cho modular_exponentiation]
  bool isZero() const;

  // So sánh với số nhỏ (ví dụ: while (exponent > 0))
  bool operator>(long long v) const;

  // --- NHÓM 3: CÁC TOÁN TỬ SỐ HỌC CƠ BẢN (big_int vs big_int) ---
  // Yêu cầu: Đây là "trái tim" của thư viện

  // Phép cộng (a + b)
  big_int operator+(const big_int &b) const;
  // Phép trừ (a - b) - [Dùng để tính p-1 và p-2]
  big_int operator-(const big_int &b) const;
  // Phép nhân (a * b) - [Rất quan trọng cho modular_exponentiation]
  big_int operator*(const big_int &b) const;
  // Phép chia (a / b) - [Dùng để tính (p-1)/2]
  big_int operator/(const big_int &b) const;
  // Phép chia lấy dư (a % b) - [Rất quan trọng cho modular_exponentiation]
  big_int operator%(const big_int &b) const;

  // --- NHÓM 4: TOÁN TỬ VỚI SỐ NHỎ (TỐI ƯU HÓA) ---
  // Yêu cầu: Giúp code trong hàm modular_exponentiation sạch hơn

  // Chia cho số int (ví dụ: exponent / 2)
  big_int operator/(int v) const;
  // Chia lấy dư với số int (ví dụ: exponent % 2)
  int operator%(int v) const;

  // --- NHÓM 5: NHẬP/XUẤT (IN/OUT) ---
  // Yêu cầu: Cần để std::cout ra kết quả cuối cùng

  // Hàm "friend" để cho phép std::cout truy cập vào private members
  friend std::ostream &operator<<(std::ostream &stream, const big_int &v);
  // Hàm "friend" để đọc big_int từ std::cin
  friend std::istream &operator>>(std::istream &stream, big_int &v);
};