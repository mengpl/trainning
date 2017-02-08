#ifdef __BASE_SOCKET_H__
#include <socket.h>

namespace base
{
    class CBaseSocket
    {
    public:
        CBaseSocket();
        ~CBaseSocket();

    public:
        static int bind (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len); //just a bind function
        int getsockname (int __fd, __SOCKADDR_ARG __addr,socklen_t *__restrict __len);
        int connect (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len);
        ssize_t send (int __fd, const void *__buf, size_t __n, int __flags);
        ssize_t recv (int __fd, void *__buf, size_t __n, int __flags);
        int listen (int __fd, int __n);
        int setsockopt (int __fd, int __level, int __optname, const void *__optval, socklen_t __optlen);
        int shutdown (int __fd, int __how);
    }

}

#endif // !__BASE_SOCKET_H__