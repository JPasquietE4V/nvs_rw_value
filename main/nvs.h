#define STRLN 65
#define STREND (STRLN-1)

typedef struct
{
char msg_get[STRLN];
char new_msg[STRLN];
uint32_t CRC32;
}ts_credentials;