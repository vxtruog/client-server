# 1. Ghi chú
## 1.1. Lý thuyết mạng
- Có hai loại socket internet cơ bản: Stream Sockets (SOCK_STREAM) và Datagram Sockets (SOCK_DGRAM).
- Stream Sockets là các luồng giao tiếp hai chiều đáng tin cậy, chúng sử dụng một giao thức gọi là TCP (The Transmission Control Protocol), đảm bảo dữ liệu của bạn được truyền đến một cách tuần tự và không có lỗi.
- Datagram Sockets, chúng sử dụng giao thức gọi là UDP (User Datagram Protocol), thường được dùng khi ngăn xếp TCP không khả dụng hoặc khi một vài gói tin bị mất không phải là vấn đề nghiêm trọng. À, không đáng tin cậy nhưng tốc độ của nó lại xịn hơn hẳn TCP :))
- Linux không coi socket là một file thông thường, nhưng Linux cung cấp một giao diện I/O thống nhất thông qua file descriptor để lập trình viên có thể thao tác với file, socket, pipe, terminal... theo cách tương tự nhau. Đây chính là triết lý nổi tiếng của Unix: "Everything is a file".
- Mô hình mạng phân lớp phù hợp với Unix
  + Application Layer (telnet, ftp, ...)
  + Host-to-Host Transport Layer (TCP, UDP)
  + Internet Layer (IP and routing)
  + Network Access Layer (Ethernet, Wi-fi, ...)
- Mã hoá dữ liệu: Một gói dữ liệu được tạo ra, gói dữ liệu được bao bọc trong phần tiêu đề bởi giao thức đầu tiên (ví dụ TFTP), sau đó toàn bộ gói dữ liệu được mã hoá lại bởi giao thức tiếp theo (ví dụ UDP), rồi lại bởi giao thức tiếp theo nữa (ví dụ IP), và cuối cùng là bởi giao thức cuối cùng ở lớp vật lý (ví dụ Ethernet). Khi một máy tính khác nhận được gói dữ liệu, phần cứng sẽ loại bỏ phần tiêu đề Ethernet, nhân hệ điều hành sẽ loại bỏ các tiêu đề IP và UDP, chương trình TFTP sẽ loại bỏ tiêu đề TFTP và cuối cùng máy tính đó sẽ nhận được dữ liệu.
- Địa chỉ IP (Internet Protocol Address) là một dãy số dùng để định danh một thiết bị trên mạng Internet hoặc mạng nội bộ. Khi chỉ định một địa chỉ IP, bạn đang xác định thiết bị đích mà bạn muốn gửi dữ liệu đến trên mạng.
  + IPv4 (số nguyên 32 bit không dấu, mỗi byte được phân tách bởi dấu chấm), địa chỉ loopback `127.0.0.1`
  + IPv6 (số nguyên 128 bit không dấu, mỗi khối hai byte được phân tách bởi dấu hai chấm), địa chỉ loopback `::1`
- Số cổng là một địa chỉ logic dùng để phân biệt các ứng dụng và dịch vụ mạng khác nhau trên cùng một địa chỉ IP. Khi chỉ định số cổng, bạn đang cho biết ứng dụng hoặc dịch vụ nào trên thiết bị đích mà bạn muốn gửi dữ liệu đến. Các dịch vụ khác nhau trên internet có các số cổng quen thuộc khác nhau, có thể xem chúng trong tệp `/etc/services`. Các cổng dưới 1024 thường được coi là đặc biệt và thường yêu cầu quyền truy cập đặc biệt của hệ điều hành để sử dụng.

# 2. Vòng đời của TCP-server và TCP-client
<img src="/image/tcp.jpeg" alt="Hình 1" width="90%">

# 3. UDP client-server connection
```
5 steps of UDP server
- Create UDP socket.
- Bind the socket to server address.
- Wait until datagram packet arrives from client.
- Process the datagram packet and send a reply to client.
- Go back to Step 3.

5 steps of UDP client
- Create UDP socket.
- Send message to server.
- Wait until response from server is recieved.
- Process reply and go back to step 2, if necessary.
- Close socket descriptor and exit.
```
