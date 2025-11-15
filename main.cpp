#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include "BigInt.h"
#include "crypto_utils.h"

int main()
{
  try
  {
    // --- KHỞI TẠO MỘT LẦN ---
    // QUAN TRỌNG: Chỉ gọi srand() 1 lần duy nhất
    srand(time(NULL));

    std::cout << "============================================" << std::endl;
    std::cout << "  CHUONG TRINH DIFFIE-HELLMAN KEY EXCHANGE  " << std::endl;
    std::cout << "============================================" << std::endl
              << std::endl;

    // --- BƯỚC 1: SINH SỐ NGUYÊN TỐ LỚN p VÀ PHẦN TỬ SINH g ---
    // - 64-128 bit: Rất nhanh
    // - 256 bit: Vài phút - Vẫn chấp nhận được
    // - 512 bit: 3-5 phút

    int bit_size = 512;

    std::cout << "[BUOC 1] Sinh so nguyen to an toan p" << std::endl;
    std::cout << "         Kich thuoc: " << bit_size << " bit" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    // Đo thời gian sinh số nguyên tố
    clock_t start_time = clock();
    BigInt p = generate_safe_prime(bit_size);
    clock_t end_time = clock();

    double elapsed = double(end_time - start_time) / CLOCKS_PER_SEC;

    // Kiểm tra xem có tìm được số nguyên tố không
    if (p == 0)
    {
      std::cerr << "[LOI] Khong the sinh safe prime!" << std::endl;
      std::cerr << "      Thu giam bit_size xuong hoac tang max_attempts." << std::endl;
      return 1;
    }

    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "[THANH CONG] Da tim thay p!" << std::endl;
    std::cout << "   + Thoi gian: " << elapsed << " giay" << std::endl;
    std::cout << "   + p = " << p << std::endl;
    std::cout << "   + So chu so: " << p.get_num_digits() << std::endl
              << std::endl;

    // Chọn phần tử sinh g = 2
    BigInt g = BigInt(2);
    std::cout << "[BUOC 1] Chon phan tu sinh g = " << g << std::endl
              << std::endl;

    // --- BƯỚC 2: SINH KHÓA RIÊNG (PRIVATE KEY) ---
    std::cout << "[BUOC 2] Sinh khoa rieng cho Alice va Bob..." << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    BigInt a = generate_private_key(p); // Khóa riêng của Alice
    BigInt b = generate_private_key(p); // Khóa riêng của Bob

    std::cout << "   + Khoa rieng Alice (a): " << a << std::endl;
    std::cout << "   + Khoa rieng Bob (b):   " << b << std::endl
              << std::endl;

    // --- BƯỚC 3: TÍNH KHÓA CÔNG KHAI (PUBLIC KEY) ---
    std::cout << "[BUOC 3] Tinh khoa cong khai..." << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    // Alice tính A = (g^a) % p
    std::cout << "   Alice dang tinh A = g^a mod p..." << std::endl;
    BigInt A = modular_exponentiation(g, a, p);
    std::cout << "   + Khoa cong khai Alice (A): " << A << std::endl;

    // Bob tính B = (g^b) % p
    std::cout << "   Bob dang tinh B = g^b mod p..." << std::endl;
    BigInt B = modular_exponentiation(g, b, p);
    std::cout << "   + Khoa cong khai Bob (B):   " << B << std::endl
              << std::endl;

    // --- BƯỚC 4: TRAO ĐỔI VÀ TÍNH BÍ MẬT CHUNG ---
    std::cout << "[BUOC 4] Trao doi khoa cong khai va tinh shared secret..." << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "   (Alice nhan B tu Bob, Bob nhan A tu Alice)" << std::endl
              << std::endl;

    // Alice tính bí mật: s_alice = (B^a) % p
    std::cout << "   Alice dang tinh s = B^a mod p..." << std::endl;
    BigInt alice_shared_secret = modular_exponentiation(B, a, p);
    std::cout << "   + Alice's shared secret: " << alice_shared_secret << std::endl;

    // Bob tính bí mật: s_bob = (A^b) % p
    std::cout << "   Bob dang tinh s = A^b mod p..." << std::endl;
    BigInt bob_shared_secret = modular_exponentiation(A, b, p);
    std::cout << "   + Bob's shared secret:   " << bob_shared_secret << std::endl
              << std::endl;

    // --- BƯỚC 5: XÁC MINH KẾT QUẢ ---
    std::cout << "=========================================" << std::endl;
    std::cout << "         KET QUA XAC MINH" << std::endl;
    std::cout << "=========================================" << std::endl;

    if (alice_shared_secret == bob_shared_secret)
    {
      std::cout << "  THANH CONG!" << std::endl;
      std::cout << "  Alice va Bob da thoa thuan duoc bi mat chung!" << std::endl;
      std::cout << "  Shared Secret = " << alice_shared_secret << std::endl;
    }
    else
    {
      std::cout << "  ✗ THAT BAI!" << std::endl;
      std::cout << "  Bi mat chung KHONG TRUNG KHOP!" << std::endl;
      std::cout << "  Day la loi nghiem trong!" << std::endl;
    }

    std::cout << "=========================================" << std::endl;
    std::cout << std::endl;

    // --- THÔNG TIN BỔ SUNG ---
    std::cout << "[THONG TIN BO SUNG]" << std::endl;
    std::cout << "   + Kich thuoc p: " << bit_size << " bit" << std::endl;
    std::cout << "   + Thoi gian sinh p: " << elapsed << " giay" << std::endl;
    std::cout << "   + Phan tu sinh g: " << g << std::endl;
    std::cout << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cerr << "=========================================" << std::endl;
    std::cerr << "  LOI: " << e.what() << std::endl;
    std::cerr << "=========================================" << std::endl;
    return 1;
  }

  return 0;
}