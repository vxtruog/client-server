# 1. Ghi chú
- Linux không coi socket là một file thông thường, nhưng Linux cung cấp một giao diện I/O thống nhất thông qua file descriptor để lập trình viên có thể thao tác với file, socket, pipe, terminal... theo cách tương tự nhau. Đây chính là triết lý nổi tiếng của Unix: "Everything is a file".
- Địa chỉ IP (Internet Protocol Address) là một dãy số dùng để định danh một thiết bị trên mạng Internet hoặc mạng nội bộ. Khi chỉ định một địa chỉ IP, bạn đang xác định thiết bị đích mà bạn muốn gửi dữ liệu đến trên mạng.
- Số cổng là một địa chỉ logic dùng để phân biệt các ứng dụng và dịch vụ mạng khác nhau trên cùng một địa chỉ IP. Khi chỉ định số cổng, bạn đang cho biết ứng dụng hoặc dịch vụ nào trên thiết bị đích mà bạn muốn gửi dữ liệu đến.

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
