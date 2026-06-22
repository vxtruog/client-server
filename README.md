# 1. GHI CHÚ
- Tài liệu tham khảo: https://beej.us/guide/bgnet/html/index-wide.html
- Tài liệu Youtube: https://www.youtube.com/@drtoshnazarov
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

## 1.2. Thứ tự byte mạng và chuyển đổi địa chỉ IP
- TCP/IP định nghĩa một thứ tự byte mạng duy nhất (big-endian) cho bất kỳ mục dữ liệu số nguyên nào chẳng hạn như địa chỉ IP được truyền qua mạng trong tiêu đề gói. Nhưng do thứ tự byte của máy chủ thường là (little-endian) nên Unix cung cấp các hàm sau để chuyển đổi giữa thứ tự byte mạng và thứ tự byte máy chủ:
```
#include <arpa/inet.h>
uint32_t htonl (uint32_t hostlong);
uint16_t htons (uint16_t hostshort);
  (trả về thứ tự byte của mạng)
uint32_t ntohl (uint32_t netlong);
uint16_t ntohs (uint16_t netshort);
  (trả về thứ tự byte của máy chủ)
```
- Các chương trình ứng dụng có thể chuyển đổi qua lại giữa địa chỉ IP và chuỗi thập phân có dấu chấm bằng các hàm sau:
```
#include <arpa/inet.h>
int inet_pton(protocol_family, const char *src, void *dst);
const char *inet_ntop(protocol_family, const void *src, char *dst);
```

## 1.3. Các cấu trúc cần thiết
- Cấu trúc `sockaddr`, lưu trữ thông tin địa chỉ socket một cách tổng quát để các hàm trong API socket sử dụng một cách đồng nhất
```
struct sockaddr {
  uint16_t  sa_family;              // protocol family (AF_INET, AF_INET6, ...)
  char      sa_data[14];            // Address data
};
```
- Cấu trúc `sockaddr_in`, lưu trữ thông tin địa chỉ cụ thể cho IPv4
```
struct sockaddr_in {
  uint16_t        sin_family;       // protocol family (AF_INET)
  uint16_t        sin_port;         // port number in network byte order
  struct in_addr  sin_addr          // IPv4 address in network byte order
  unsigned char   sin_zero[8]       // pad to sizeof(struct sockaddr)
};
```
- Cấu trúc `sockaddr_in6`, lưu trữ thông tin địa chỉ cụ thể cho IPv6
```
struct sockaddr_in6 {
    u_int16_t       sin6_family;   // protocol family (AF_INET6)
    u_int16_t       sin6_port;     // port number in network byte order
    u_int32_t       sin6_flowinfo; // IPv6 flow information
    struct in6_addr sin6_addr;     // IPv6 address
    u_int32_t       sin6_scope_id; // Scope ID
};
```
- Cấu trúc `sockaddr_storage`, một vùng nhớ đủ lớn để chứa bất kỳ loại địa chỉ của socket nào
```
struct sockaddr_storage {
    sa_family_t  ss_family;     // address family

    // all this is padding, implementation specific, ignore it:
    char      __ss_pad1[_SS_PAD1SIZE];
    int64_t   __ss_align;
    char      __ss_pad2[_SS_PAD2SIZE];
};
```
- Kernel sẽ đọc trường `sa_family` (tương ứng với `ss_family`) nằm ở đầu vùng nhớ địa chỉ socket, dựa vào giá trị này, kernel xác định dữ liệu đang được lưu trong `sockaddr_storage` thực chất là địa chỉ IPv4, IPv6 hay một họ địa chỉ khác, sau đó diễn giải các byte còn lại theo cấu trúc tương ứng.

## 1.4. Các lệnh gọi hệ thống
- Hàm `socket()` được máy khách và máy chủ sử dụng để tạo socket descriptor
```
#include <sys/types.h>
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
    (trả về chỉ số socket descriptor nếu thành công, -1 nếu thất bại)
```
- Hàm `bind()` yêu cầu kernel liên kết địa chỉ socket của máy chủ trong `addr` với socket descriptor `sockfd`
```
#include <sys/socket.h>
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
  (trả về 0 nếu thành công, -1 nếu thất bại)
```
- Hàm `listen()` để chuyển `sockfd` sang trạng thái lắng nghe để có thể chấp nhận các yêu cầu kết nối từ máy khách. Tham số `backlog` là số lượng yêu cầu kết nối đang chờ xử lý `accept()` tối đa có thể được phép trước khi hệ điều hành bắt đầu từ chối các yêu cầu.
```
#include <sys/socket.h>
int listen(int sockfd, int backlog);
  (trả về 0 nếu thành công, -1 nếu thất bại)
``` 
- Hàm `connect()`, một máy khách cố gắng thiết lập kết nối internet với máy chủ tại địa chỉ socket `addr`
```
#include <sys/socket.h>
int connect(int clientfd, const struct sockaddr *addr, socklen_t addrlen);
  (trả về 0 nếu thành công, -1 nếu thất bại)
```
- Hàm `connect()` sẽ chặn cho đến khi kết nối được thiết lập thành công hoặc xảy ra lỗi. Nếu thành công, bộ mô tả `clientfd` hiện đã sẵn sàng để đọc và ghi, và kết quả của việc kết nối được đặc trưng bởi cặp socket `(x:y, addr.sin_addr:addr.sin_port)`, trong đó `x` và `y` là địa chỉ bên phía máy khách, còn `addr.sin_addr` và `addr.sin_port` là địa chỉ bên phía máy chủ.
- Hàm `accept()`, khi ai đó đang cố gằng dùng `connect()` để kết nối đến máy của bạn trên một cổng mà bạn đang `listen()`. Kết nối của họ sẽ được xếp vào hàng đợi chờ được `accept()` xử lý. Nó sẽ trả về cho bạn một bộ socket descriptor hoàn toàn mới để sử dụng cho kết nối duy nhất này. Đột nhiên bạn có hai bộ socket descriptor với giá của một, bộ socket descriptor ban đầu vẫn đang lắng nghe các kết nối mới khác, và bộ socket descriptor mới được tạo cuối cùng đã sẵn sàng để `send()` và `recv()`.
```
#include <sys/types.h>
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```
- Hàm `memset()` dùng để thao tác với bộ nhớ, ghi giá trị theo byte
```
#include <string.h>
void *memset(void *s, int c, size_t n);
  (trong đó s là địa chỉ bắt đầu của vùng nhớ, c là giá trị byte sẽ được ghi, n là số byte cần ghi)
```
- Hàm `send()` và `recv()` dùng để trao đổi dữ liệu sau khi kết nối TCP được thiết lập
```
#include <sys/socket.h>
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```

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
