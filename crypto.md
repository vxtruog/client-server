```
Có hai nhóm khóa chính:
- Mật mã khóa đối xứng
  + Người gửi và người nhận sử dụng cùng một khóa bí mật để mã hóa và giải mã.
- Mật mã khóa công khai
  + Nhiều người gửi dùng chung khóa công khai để mã hóa.
  + Người nhận có khóa bí mật để giải mã.
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
