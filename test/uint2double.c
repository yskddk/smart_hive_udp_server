#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#if defined(ENABLE_POSIX_NONBLOCK)
#   include <fcntl.h>
#else /* defined(ENABLE_POSIX_NONBLOCK) */
#   include <sys/ioctl.h>
#endif /* defined(ENABLE_POSIX_NONBLOCK) */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>





static double le16_to_double_(const uint8_t *p_)
{
    uint16_t v = *(const uint16_t *)p_;
    return (double)v;
}



static double be16_to_double_(const uint8_t *p_)
{
    uint16_t v = 0;

    assert(p_);

    v |= *p_++;
    v <<= 8;
    v |= *p_;

    return (double)v;
}



static double le32_to_double_(const uint8_t *p_)
{
    uint32_t v = *(const uint32_t *)p_;
    return (double)v;
}



static double be32_to_double_(const uint8_t *p_)
{
    uint32_t v = 0;

    assert(p_);

    v |= *p_++;
    v <<= 8;
    v |= *p_++;
    v <<= 8;
    v |= *p_++;
    v <<= 8;
    v |= *p_;

    return (double)v;
}



int main(void)
{
    uint32_t lat = 121516909;
    uint32_t lon = 25052927;

    double dlat = 0.0;
    double dlon = 0.0;

    uint8_t lat_array[4];
    uint8_t lon_array[4];

    lat_array[0] =  lat         & 0xffU;
    lat_array[1] = (lat >> 8U)  & 0xffU;
    lat_array[2] = (lat >> 16U) & 0xffU;
    lat_array[3] = (lat >> 24U) & 0xffU;

    lon_array[0] =  lon         & 0xffU;
    lon_array[1] = (lon >> 8U)  & 0xffU;
    lon_array[2] = (lon >> 16U) & 0xffU;
    lon_array[3] = (lon >> 24U) & 0xffU;

    dlat = le32_to_double_(lat_array);
    dlon = le32_to_double_(lon_array);

    dlat /= 1000000;
    dlon /= 1000000;

    printf("lat=%lf, lon=%lf\n", dlat, dlon);

    return EXIT_SUCCESS;
}



/* vim: set ts=4 sts=4 sw=4 expandtab autoindent : */
