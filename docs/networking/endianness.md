# Endianness, Sockets, and x86 Architecture

## What Is Endianness?
Endianness defines the byte order of a multi-byte value in memory.

* Consider this 32-bit hexadecimal integer:
    * `0x12345678`
    * It consists of four bytes: `12 34 56 78`
- **Big-endian** (stores the leftmost significant byte first):
    * Address 100: `12`
    * Address 101: `34`
    * Address 102: `56`
    * Address 103: `78`
- **Little-endian** (stores the rightmost significant byte first):
    * Address 100: `78`
    * Address 101: `56`
    * Address 102: `34`
    * Address 103: `12`

The numeric value remains `0x12345678`; only its byte layout in memory differs.

## Relationship to x86 PCs
**x86 and x86-64 processors** use **little-endian** byte order. Therefore, `0x12345678` normally appears in memory as:

`78 56 34 12`

## Relationship to Sockets
Network protocols traditionally use **network byte order**, which is **big-endian**.

```c++
/*
 * Simple example showing where endian conversion is required.
 * Server listens on port 8080 and receives a 32-bit integer.
 * Client sends a 32-bit integer.
 *
 * The important parts are marked with comments.
 */

//////////////////// SERVER ////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080); // convert port to network byte order because port is a numeric value stored in host byte order and must be standardized to big-endian for transmission
    addr.sin_addr.s_addr = INADDR_ANY; // IP addresses are already provided in network byte order (big-endian), so no conversion is needed

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);

    printf("Server listening on port 8080...\n");

    client_fd = accept(server_fd, (struct sockaddr*)&addr, &addr_len);

    uint32_t received;
    recv(client_fd, &received, sizeof(received), 0);

    // the `ntoh<size>` conversion function: (the conversion function is about the size (e.g., 16-bit, 32-bit, 64-bit), not the actual type (e.g., int, char))
    //     ntohl:    network-to-host-short -> short -> 16-bit
    //     ntohl:    network-to-host-long  -> int   -> 32-bit
    //     ntohbe64: network-to-host-be64  -> long  -> 64-bit
    // Convert from network byte order to host byte order
    uint32_t value = ntohl(received);

    printf("Received value: %u\n", value);

    close(client_fd);
    close(server_fd);
    return 0;
}

//////////////////// CLIENT ////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080); // convert port to network byte order
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    uint32_t value = 123456;

    // the `ntoh<size>` conversion function: (the conversion function is about the size (e.g., 16-bit, 32-bit, 64-bit), not the actual type (e.g., int, char))
    //     htonl:    network-to-host-short -> short -> 16-bit
    //     htonl:    network-to-host-long  -> int   -> 32-bit
    //     be64ton:  network-to-host-be64  -> long  -> 64-bit
    // Convert from host byte order to network byte order
    uint32_t to_send = htonl(value);

    send(sock, &to_send, sizeof(to_send), 0);

    close(sock);
    return 0;
}
```
