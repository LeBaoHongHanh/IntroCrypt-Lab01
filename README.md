# Lab 01: Số Nguyên Tố & Trao Đổi Khóa Diffie-Hellman

## 📝 Mô tả

Đây là bài tập triển khai giao thức trao đổi khóa Diffie-Hellman bằng ngôn ngữ C++14.

Do yêu cầu của bài toán là thao tác trên các số nguyên tố có độ lớn tối thiểu 512 bit, một thư viện số lớn (`BigInt`) tối thiểu đã được tự implement (trong `BigInt.h` và `BigInt.cpp`) để hỗ trợ các phép toán số học cần thiết.

## 🎯 Các nhiệm vụ chính

Dự án này hoàn thành các nhiệm vụ được yêu cầu trong `Lab01.pdf`:

1.  **Hệ thống xử lý số lớn (`BigInt`):**

    - Tự implement một lớp `BigInt` để hỗ trợ các phép toán cộng, trừ, nhân, chia, và modulo trên các số nguyên lớn.

2.  **Lũy thừa Mô-đun:**

    - Triển khai hàm `modular_exponentiation` để tính `(base^exponent) % mod` một cách hiệu quả (sử dụng thuật toán Bình phương và Nhân).

3.  **Sinh số nguyên tố an toàn:**

    - Triển khai hàm `generate_safe_prime` để sinh ra số nguyên tố an toàn `p` (sao cho `p` và `(p-1)/2` đều là số nguyên tố).
    - Việc này bao gồm cả việc tự implement thuật toán kiểm tra nguyên tố (ví dụ: Miller-Rabin).

4.  **Sinh khóa riêng:**

    - Triển khai hàm `generate_private_key` để tạo một số ngẫu nhiên trong khoảng `[2, p-2]`.

5.  **Hoàn thành Diffie-Hellman:**
    - Sử dụng các hàm trên để mô phỏng quá trình Alice và Bob tính toán và đi đến một bí mật chung.

## 🚀 Cách chạy chương trình

### Yêu cầu

- Một trình biên dịch C++ hỗ trợ C++14 (ví dụ: `g++` từ MSYS2/MinGW).

### 1. Biên dịch

Mở terminal tại thư mục gốc của dự án và chạy lệnh sau để biên dịch tất cả các file nguồn:

```bash
g++ -std=c++14 main.cpp crypto_utils.cpp BigInt.cpp -o main
```
