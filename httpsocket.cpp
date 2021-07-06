#include "httpsocket.hpp"

using namespace fb::http;

#ifdef SS
#    error SS is already defined
#endif
#define SS fb::utility::StringStream()

HttpSocket::HttpSocket() :
      socket(-1),
      threads(0),
      listeners(0)
{
}

HttpSocket::~HttpSocket()
{
    for (const auto& thread : this->threads) {
        pthread_join(thread, nullptr);
    }

    for (const auto& listener: this->listeners) {
        delete listener;
    }
}

void
HttpSocket::bind_http_port(const int port, const int max_connections)
{
    this->create_socket();
    this->set_socket_options();
    this->bind_socket(port);
    this->listen(max_connections);
    this->set_access_mode();
}

void
HttpSocket::create_socket()
{
    this->socket = ::socket(AF_INET, SOCK_STREAM, 0);

    if (this->socket < 0) {
        switch (errno) {
        case EACCES:
            throw std::runtime_error(SS << "Permission to create a socket of the specified type and/or protocol is denied. ");
        case EAFNOSUPPORT:
            throw std::runtime_error(SS << "The implementation does not support the specified address family. ");
        case EINVAL:
            throw std::runtime_error(SS << "Invalid flags in type. Unknown protocol, or protocol family not available. ");
        case EMFILE:
            throw std::runtime_error(SS << "Process file table overflow. ");
        case ENFILE:
            throw std::runtime_error(SS << "The system limit on the total number of open files has been reached. ");
        case ENOBUFS: /* fall through */
        case ENOMEM:
            throw std::runtime_error(SS << "Insufficient memory is available. The socket cannot be created until sufficient resources are freed. ");
        case EPROTONOSUPPORT:
            throw std::runtime_error(SS << "The protocol type or the specified protocol is not supported within this domain.");
        default:
            throw std::runtime_error(SS << "Unable to create communication endpoint socket.");
        }
    }
}

void
HttpSocket::set_socket_options()
{
    constexpr int one = 1;

    int setoption_result = setsockopt(this->socket,
                                      SOL_SOCKET,
                                      SO_REUSEADDR,
                                      (char*)&one,
                                      sizeof(one));

    if (setoption_result < 0) {
        switch (errno) {
        case EBADF:
            throw std::runtime_error(SS << "The socket parameter is not a valid socket descriptor.");
        case EFAULT:
            throw std::runtime_error(SS << "Using option_value and option_length parameters would result in an attempt to access storage outside the caller's address space.");
        case EINVAL:
            throw std::runtime_error(SS << "The specified option is invalid at the specified socket level or the socket has been shut down.");
        case ENOBUFS:
            throw std::runtime_error(SS << "Insufficient system resources are available to complete the call.");
        case ENOPROTOOPT:
            throw std::runtime_error(SS << "The option_name parameter is unrecognized, or the level parameter is not SOL_SOCKET.");
        case ENOSYS:
            throw std::runtime_error(SS << "The function is not implemented. You attempted to use a function that is not yet available.");
        default:
            throw std::runtime_error(SS << "Unable to set socket options.");
        }
    }
}

void
HttpSocket::bind_socket(const int port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(port);

    int bind_result = ::bind(this->socket, (struct sockaddr*)&addr, sizeof(addr));

    if (bind_result < 0) {
        switch (errno) {
        case EACCES:
            throw std::runtime_error(SS << "The address is protected, and the user is not the superuser. Search permission is denied on a component of the path prefix.");
        case EADDRINUSE:
            throw std::runtime_error(SS << "The given address is already in use.");
        case EBADF:
            throw std::runtime_error(SS << "sockfd is not a valid descriptor.");
        case EINVAL:
            throw std::runtime_error(SS << "The socket is already bound to an address or he addrlen is wrong, or the socket was not in the AF_UNIX family.");
        case ENOTSOCK:
            throw std::runtime_error(SS << "sockfd is a descriptor for a file, not a socket.");

#ifdef __linux__ /* The following errors are specific to UNIX domain (AF_UNIX) sockets: */
            case EADDRNOTAVAIL:
                throw std::runtime_error(SS << "A nonexistent interface was requested or the requested address was not local.");
            case EFAULT:
                throw std::runtime_error(SS << "addr points outside the user's accessible address space.");
            case ELOOP:
                throw std::runtime_error(SS << "Too many symbolic links were encountered in resolving addr.");
            case ENAMETOOLONG:
                throw std::runtime_error(SS << "addr is too long.");
            case ENOENT:
                throw std::runtime_error(SS << "The file does not exist.");
            case ENOMEM:
                throw std::runtime_error(SS << "Insufficient kernel memory was available.");
            case ENOTDIR:
                throw std::runtime_error(SS << "A component of the path prefix is not a directory.");
            case EROFS:
                throw std::runtime_error(SS << "The socket inode would reside on a read-only file system.");
#endif
        default:
            throw std::runtime_error(SS << "Unable to bind to socket.");
        }
    }
}

void
HttpSocket::listen(const int max_connections)
{
    int listen_result = ::listen(this->socket, max_connections);

    if (listen_result < 0) {
        switch (errno) {
        case EADDRINUSE:
            throw std::runtime_error(SS << "Another socket is already listening on the same port. ");
        case EBADF:
            throw std::runtime_error(SS << "The argument sockfd is not a valid descriptor. ");
        case ENOTSOCK:
            throw std::runtime_error(SS << "The argument sockfd is not a socket. ");
        case EOPNOTSUPP:
            throw std::runtime_error(SS << "The socket is not of a type that supports the listen() operation.");
        default:
            throw std::runtime_error(SS << "Unable to listen to socket.");
        }
    }
}

void
HttpSocket::set_access_mode()
{
    int set_result = 0;
    int flags      = fcntl(this->socket, F_GETFL, 0);

    if (flags >= 0) {
        set_result = fcntl(this->socket, F_SETFL, flags | O_NONBLOCK);
    }

    if (flags < 0 || set_result < 0) {
        switch (errno) {
        case EACCES : /* fall through */
        case EAGAIN:
            throw std::runtime_error(SS << "The operation is prohibited because the file has been memory-mapped by another process.");
        case EBADF:
            throw std::runtime_error(SS << "fd is not an open file descriptor, or the command was F_SETLK or F_SETLKW and the file descriptor open mode doesn't match with the type of lock requested.");
        case EDEADLK:
            throw std::runtime_error(SS << "It was detected that the specified F_SETLKW command would cause a deadlock. ");
        case EFAULT:
            throw std::runtime_error(SS << "lock is outside your accessible address space. ");
        default:
            throw std::runtime_error(SS << "Unable to change socket access mode.");
        }
    }
}

void
HttpSocket::create_threads(const int num_threads,
                           event_callback handler,
                           void* dispatcher)
{
    if (this->socket < 0) {
        throw std::runtime_error(SS << "");
    }

    this->threads   = std::vector<pthread_t>(num_threads);
    this->listeners = std::vector<HttpEventListener*>(num_threads);

    for (int i = 0; i < num_threads; i++) {
        HttpEventListener* event = new HttpEventListener(handler, dispatcher);

        event->listen(this->socket);

        this->listeners[i] = event;

        pthread_t t;

        int tr = pthread_create(&t, nullptr, HttpSocket::dispatch, event->base);

        if (tr != 0) {
            switch (errno) {
            case EAGAIN:
                throw std::runtime_error(SS << "Insufficient resources to create another thread. A system-imposed limit on the number of threads was encountered.");
            case EINVAL :
                throw std::runtime_error(SS << "Invalid settings in attr.");
            case EPERM  :
                throw std::runtime_error(SS << "No permission to set the scheduling policy and parameters specified in attr.");
            default:
                throw std::runtime_error(SS << "Unable to create thread.");
            }
        }

        this->threads[i] = t;
    }
}

void*
HttpSocket::dispatch(void* base)
{
    event_base_dispatch((struct event_base*)base);

    return nullptr;
}

#undef SS
