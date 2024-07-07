# TCP-Server-Performance
Concurrent TCP Server Implementations
This repository explores the performance of various concurrent TCP server implementations using different techniques:

#1. Multi-Process Server (fork)

This server creates child processes (using fork) for each incoming connection.
Each child process handles a single client request, leveraging multiple CPU cores for improved concurrency.
Be mindful of resource limitations and potential overhead from excessive process creation.
#2. Multi-threaded Server (pthreads)

This server creates threads within a single process (using pthreads) to handle multiple client requests.
Threads share the same memory space as the main process, reducing context switching overhead compared to processes.
However, threading introduces challenges like thread synchronization.
#3. Non-Blocking I/O Server (select/poll/epoll)

This server employs a non-blocking I/O model, allowing it to efficiently handle multiple connections simultaneously.
It uses system calls like select, poll, or epoll to monitor multiple file descriptors (sockets) for activity.
This approach offers high performance and scalability for handling numerous concurrent connections.
Implementation Details:

The code for each server type will be implemented in separate files (sync_server.c, multiprocess_server.c, multithread_server.c, 
and nonblocking_server.c) with for connection management, data exchange, and client request processing.

#Performance Evaluation:

Each server implementation will be tested with varying numbers of concurrent connections (500 and 1000).
Tools like Wireshark is  used to capture network packets and measure performance metrics like average throughput and latency.
[plots.pdf](https://github.com/user-attachments/files/16117701/plots.pdf)
