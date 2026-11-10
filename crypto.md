```
Có hai nhóm khóa chính:
- Mật mã khóa đối xứng
  + Người gửi và người nhận sử dụng cùng một khóa bí mật để mã hóa và giải mã.
  + Có hai loại mã hóa đối xứng khác nhau:
    ++ Stream cipher: mã hóa dữ liệu từng bit hoặc từng byte liên tục (như one-time pad)
    ++ Block cipher: chia dữ liệu thành các khối có kích thước cố định rồi mã hóa từng khối.
- Mật mã khóa công khai
  + Nhiều người gửi dùng chung khóa công khai để mã hóa.
  + Người nhận có khóa bí mật để giải mã.
Ngoài ra còn có thuật toán băm (mã hóa một chiều)
```

```
Mật mã Caesar:
- Mỗi chữ cái được dịch chuyển đi n vị trí trong bảng chữ cái.
- Giả sử không biết n bằng bao nhiêu thì sao, có thể thử thống kê tần số số lượng chữ cái/các cặp chữ cái xuất hiện, ...
```

```
Mật mã Double Transposition:
- Xếp các chữ cái lên một ma trận, chuyển vị các hàng và các cột.
- Có thể dùng từ điển, thống kê tần số số lượng chữ cái và sự kết hợp thành từ, ...
```

```
Mật mã One-time Pad:
- Chuyển các chữ thành các cụm bit, tạo một mã khóa bit tương ứng, XOR mã khóa bit để mã hóa/giải mã.
- Khá an toàn, nhưng mã khóa bit phải dài bằng cụm bit của văn bản cần mã hóa.
```

```
Nguyên lý thiết kế mật mã:
- Confusion: Làm cho mối quan hệ giữa khóa bí mật và ciphertext trở nên phức tạp.
- Diffusion: Làm cho ảnh hưởng của một bit trong plaintext lan rộng ra nhiều bit trong ciphertext.
```

```
A5/1 Stream Cipher:
- A5/1 có ba thanh ghi LFSR (Linear Feedback Shift Register)
  + R1 - 19 bit - vị trí tap XOR (13, 16, 17, 18)
  + R2 - 22 bit - vị trí tap XOR (20, 21)
  + R3 - 23 bit - vị trí tap XOR (7, 20, 21, 22)
  + Ban đầu các thanh ghi được khởi tạo bằng 0.
- Nạp khóa K
  + A5/1 lấy từng bit của khóa K, từ bit thấp đến bit cao.
  + F1 = R1[13] XOR R1[16] XOR R1[17] XOR R1[18]
  + F2 = R2[20] XOR R2[21]
  + F3 = R3[7] XOR R3[20] XOR R3[21] XOR R3[22]
  + Bit đầu vào F1' = F1 XOR K[i]
  + Bit đầu vào F2' = F2 XOR K[i]
  + Bit đầu vào F3' = F3 XOR K[i]
- Nạp Frame Number (FN - 22 bit) - số thứ tự khung thời gian trong GSM
  + Tương tự như nạp khóa K
  + Bit đầu vào F1' = F1 XOR FN[i]
  + Bit đầu vào F2' = F2 XOR FN[i]
  + Bit đầu vào F3' = F3 XOR FN[i]
- Thực hiện 100 chu kỳ warm-up
  + Lấy ba bit điều khiển:
    ++ x = R1[8]
    ++ y = R2[10]
    ++ z = R3[10]
  + Tính majority: M = (x AND y) OR (x AND z) OR (y AND z)
  + M = 0, thì chỉ dịch thanh ghi có bit điều khiển bằng 0
  + M = 1, thì chỉ dịch thanh ghi có bit điều khiển bằng 1
  + Giá trị bit đầu vào tương ứng là:
    ++ F1 = R1[13] XOR R1[16] XOR R1[17] XOR R1[18]
    ++ F2 = R2[20] XOR R2[21]
    ++ F3 = R3[7] XOR R3[20] XOR R3[21] XOR R3[22]
- Tạo keystream
  + Tương tự như chạy 100 chu kỳ warm-up
  + Mỗi lần dịch thanh ghi sẽ lấy ba bit R1[18], R2[21] và R3[22] làm giá trị tạo keystream
  + Keystream[i] = R1[18] XOR R2[21] XOR R3[22]
  + Lặp lại cho đến khi tạo đủ số bit keystream cần thiết.
```

```
RC4 Stream Cipher:
- Mảng trạng thái S
  + Gồm 256 phần tử, mỗi phần tử là một byte, ban đầu khởi tạo theo thứ tự tăng dần từ 0 -> 255
    ++ S[i] = i
  + Trong quá trình hoạt động, RC4 sẽ tráo đổi thứ tự các phần tử của S
- KSA (Key Scheduling Algorithm)
  + Đầu vào là mảng trạng thái S và mảng khóa bí mật K
  + Mỗi phần tử của khóa bí mật K là một byte, độ dài của mảng khóa bí mật K thường từ 1 đến 256 byte.
    ++ K = (K[0], K[1], ..., K[L-1])
  + Xáo trộn S, ban đầu khởi tạo j = 0, thực hiện 256 vòng:
    ++ j = (j + S[i] + K[i mod L]) mod 256
    ++ Tráo đổi S[i] và S[j]
- PRGA (Pseudo-Random Generation Algorithm)
  + Giữ nguyên mảng trạng thái S sau KSA, khởi tạo lại i = 0 và j = 0
  + Thực hiện các bước sau, lặp lại cho đến khi tạo đủ số byte keystream cần thiết
    ++ i = (i + 1) mod 256
    ++ j = (j + S[i]) mod 256
    ++ Tráo đổi S[i] và S[j]
    ++ t = (S[i] + S[j]) mod 256
    ++ Keystream: Z = S[t]
  + Có thể bỏ qua một số lượng byte keystream đầu tiên để an toàn hơn.
```

```
Hàm băm mật mã, cần đáp ứng:
  + Khả năng nén: kích thước đầu ra phải nhỏ
  + Độ hiệu quả: dễ dàng tính toán và nhanh
  + Hàm một chiều: không thể dịch ngược được hàm băm
  + Không thể tìm thấy hai thứ bất kỳ nào có cùng giá trị băm
Hàm băm mật mã bao gồm:
  + Hàm băm không mật mã: CRC

```

```
CRC (Cyclic Redundancy Check)

```
