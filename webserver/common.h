#ifndef __COMMON_H__
#define __COMMON_H__

namespace web_server
{
    #define EPOLL_OPEN_MAX 1024

    static inline uint32_t simple_hash(const char *name) 
    {
        unsigned char *s = (unsigned char *) name;
        uint32_t hval = 0x811c9dc5;
        while (*s) {
            hval *= 16777619;
            hval ^= (uint32_t) *s++;
        }
        return hval;
    };

    

}

#endif // __COMMON_H__