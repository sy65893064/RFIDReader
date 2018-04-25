#include <stdio.h>

char CheckSum(char buf[], int len)
{
    char checksum;
    checksum = 0;
    for (int i = 0; i < (buf[1] - 1); ++i)
    {
        checksum ^= buf[i]; //异或
    }
    return ~checksum; //按位取反
}

int main()
{
    char cmd[] = { 0x03, 0x08, 0xC0, 0x00, 0x20, 0x00, 0x00 };
    char check = CheckSum(cmd, sizeof(cmd));
    printf("%02x\n", check);
    return 0;
}
