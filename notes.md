# 5 chi tiết nền tảng phải biết của lập trình socket trong ngôn ngữ C
1. Tạo một mô tả socket bằng hàm `socket`
2. Liên kết socket bằng hàm `bind`
3. Lắng nghe bằng hàm `listen`
4. Chấp nhận một yêu cầu kết nối bằng hàm `accept`
5. Thiết lập một kết nối bằng hàm `connect`

#
- Linux không coi socket là một file thông thường, nhưng Linux cung cấp một giao diện I/O thống nhất thông qua file descriptor để lập trình viên có thể thao tác với file, socket, pipe, terminal... theo cách tương tự nhau. Đây chính là triết lý nổi tiếng của Unix: "Everything is a file".
- Địa chỉ IP (Internet Protocol Address) là một dãy số dùng để định danh một thiết bị trên mạng Internet hoặc mạng nội bộ. Khi chỉ định một địa chỉ IP, bạn đang xác định thiết bị đích mà bạn muốn gửi dữ liệu đến trên mạng.
- Số cổng là một địa chỉ logic dùng để phân biệt các ứng dụng và dịch vụ mạng khác nhau trên cùng một địa chỉ IP. Khi chỉ định số cổng, bạn đang cho biết ứng dụng hoặc dịch vụ nào trên thiết bị đích mà bạn muốn gửi dữ liệu đến.
