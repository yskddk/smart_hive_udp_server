#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#   include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>



#define LORA_HEADER_SIZE  (3)
#define LORA_PAYLOAD_SIZE (40)
#define LORA_PACKET_SIZE  (LORA_HEADER_SIZE + LORA_PAYLOAD_SIZE)
#define MAX_LORA_CLIENTS  (100)

#define UDP_PROTOCOL_VERSION  (0x12)
#define UDP_PKTID_PUSH_DATA   (0)
#define UDP_HEADER_SIZE       (4)
#define UDP_PACKET_SIZE       (UDP_HEADER_SIZE + LORA_PACKET_SIZE)
#define MAX_UDP_CLIENTS       (2)

#define UDP_SERVER_PORT (50812)
#define UDP_SERVER_ADDR ("127.0.0.1")



static void uint16_to_be16_(uint16_t val_, uint8_t *p_)
{
    assert(p_);

    *p_++ = ((val_ >>  8) & 0xffU);
    *p_   = ( val_        & 0xffU);

    return;
}



static uint16_t be16_to_uint16_(const uint8_t *p_)
{
    uint16_t ret = 0;

    assert(p_);

    ret |= *p_++;
    ret <<= 8;
    ret |= *p_;

    return ret;
}



static void uint32_to_be32_(uint32_t val_, uint8_t *p_)
{
    assert(p_);

    *p_++ = ((val_ >> 24) & 0xffU);
    *p_++ = ((val_ >> 16) & 0xffU);
    *p_++ = ((val_ >>  8) & 0xffU);
    *p_   = ( val_        & 0xffU);

    return;
}



static uint32_t be32_to_uint32_(const uint8_t *p_)
{
    uint32_t ret = 0;

    assert(p_);

    ret |= *p_++;
    ret <<= 8;
    ret |= *p_++;
    ret <<= 8;
    ret |= *p_++;
    ret <<= 8;
    ret |= *p_;

    return ret;
}

int main(void)
{
    int fd = -1;
    struct sockaddr_in sa = { 0 };
    uint8_t buf[UDP_PACKET_SIZE] = { 0 };
    uint8_t *p_lora = NULL;
    ssize_t nr = 0;

    fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd < 0) {
        perror("client socket");
        return EXIT_FAILURE;
    }

    sa.sin_family = AF_INET;
    sa.sin_port = htons(UDP_SERVER_PORT);
    inet_pton(AF_INET, UDP_SERVER_ADDR, &sa.sin_addr.s_addr);

    /*
     * UDP packet format:
     *
     *  |<----------- B bytes ----------->|
     *  |               |<-- B-4 bytes -->|
     *  +---+---+---+---+-----.......-----+
     *  | A | B | C | D |        E        |
     *  +---+---+---+---+-----.......-----+
     *
     *      * A (1 byte) : Protocol version
     *      * B (1 byte) : Length (from A to E)
     *      * C (1 byte) : UDP client ID
     *      * D (1 byte) : Packet type
     *      * E (B-4 bytes) : LoRa data (max 127 bytes)
     */
    buf[0] = UDP_PROTOCOL_VERSION;
    buf[1] = UDP_PACKET_SIZE;
    buf[2] = 0;
    buf[3] = UDP_PKTID_PUSH_DATA;
    p_lora = &buf[4];

    /*
     * LoRa data format:
     *
     *  All multi-byte fields are big endian.
     *
     *  |<------------------------ 43 bytes -------------------------->|
     *  |<- 3 bytes ->|<---------------- 40 bytes -------------------->|
     *  +----+---+----+------+------+-----+--------+------+-------+----+
     *  | ID | N | PI | DATE | TIME | GPS | TEMPx4 | RHx4 | VOLx4 | WT |
     *  +----+---+----+------+------+-----+--------+------+-------+----+
     *
     *      * Header (3 bytes)
     *          * ID (1 byte) : Device ID
     *          * N (1 byte) : Packet serial number
     *          * PI (1 byte) : Reserved (always 1)
     *      * Payload (40 bytes)
     *          * DATE (3 bytes) year, month, day
     *          * TIME (3 bytes) hour, minute, second
     *          * GPS (8 bytes) lat-N (4 bytes), lon-E (4 bytes)
     *          * TEMPx4 (8 bytes) temperature (each 2 bytes) x 4
     *          * RHx4 (8 bytes) RH. (each 2 bytes) x 4
     *          * VOLx4 (8 bytes) volume (each 2 bytes) x 4
     *          * WT (2 bytes) weight
     */
    p_lora[0] = 1;
    p_lora[1] = 2;
    p_lora[2] = 1;
    p_lora[3] = 18;     /* yy */
    p_lora[4] = 8;      /* mm */
    p_lora[5] = 12;     /* dd */
    p_lora[6] = 15;     /* HH */
    p_lora[7] = 25;     /* MM */
    p_lora[8] = 30;     /* SS */

    uint32_to_be32_( 35681167, &p_lora[9]);
    uint32_to_be32_(139767052, &p_lora[13]);
    uint16_to_be16_(101,       &p_lora[17]);
    uint16_to_be16_(201,       &p_lora[19]);
    uint16_to_be16_(301,       &p_lora[21]);
    uint16_to_be16_(401,       &p_lora[23]);
    uint16_to_be16_(112,       &p_lora[25]);
    uint16_to_be16_(222,       &p_lora[27]);
    uint16_to_be16_(332,       &p_lora[29]);
    uint16_to_be16_(442,       &p_lora[31]);
    uint16_to_be16_(123,       &p_lora[33]);
    uint16_to_be16_(223,       &p_lora[35]);
    uint16_to_be16_(323,       &p_lora[37]);
    uint16_to_be16_(423,       &p_lora[39]);
    uint16_to_be16_(501,       &p_lora[41]);

    nr = sendto(fd, buf, sizeof(buf), 0, (struct sockaddr *)&sa, sizeof(sa));
    printf("sendto() returned %ld\n", nr);

    close(fd);
    fd = -1;

    return EXIT_SUCCESS;
}



/* vim: set ts=4 sts=4 sw=4 expandtab autoindent : */
