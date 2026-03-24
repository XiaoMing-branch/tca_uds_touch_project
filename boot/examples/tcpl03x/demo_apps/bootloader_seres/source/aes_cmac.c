/**
 *****************************************************************************
 * @brief   aes cmac source file.
 *
 * @file    aes_cmac.c
 * @author  AE/FAE team
 * @date    2024.01.01
 *****************************************************************************
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <b>&copy; Copyright (c) 2024 Tinychip Microelectronics Co.,Ltd.</b>
 *
 *****************************************************************************
 */

#include <string.h>
#include "aes_cmac.h"


/* For AES128 Calculation */
static const s32 S[16][16] =
{
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};
static const s32 S2[16][16] =
{
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

/* For CMAC Calculation */
unsigned char const_Rb[16] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87
};
unsigned char const_Zero[16] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

unsigned char gs_aKey[16] =
{
    0x82, 0x73, 0x53, 0x49, 0x82, 0xF8, 0xCD, 0xB6,
    0x55, 0x05, 0x6B, 0x07, 0x1B, 0x20, 0x29, 0xC0
};

static s32 getLeft4Bit(s32 num)
{
    s32 left = num & 0x000000f0;
    return left >> 4;
}
static s32 getRight4Bit(s32 num)
{
    return num & 0x0000000f;
}
static s32 getNumFromSBox(s32 index)
{
    s32 row = getLeft4Bit(index);
    s32 col = getRight4Bit(index);
    return S[row][col];
}
static s32 getIntFromChar(s8 c)
{
    s32 result = (s32)c;
    return result & 0x000000ff;
}
static void convertToIntArray(s8 *str, s32 pa[4][4])
{
    s32 k = 0;
    s32 i, j;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
        {
            pa[j][i] = getIntFromChar(str[k]);
            k++;
        }
}
static s32 getWordFromStr(s8 *str)
{
    s32 one, two, three, four;
    one = getIntFromChar(str[0]);
    one = one << 24;
    two = getIntFromChar(str[1]);
    two = two << 16;
    three = getIntFromChar(str[2]);
    three = three << 8;
    four = getIntFromChar(str[3]);
    return one | two | three | four;
}

static void splitIntToArray(s32 num, s32 array[4])
{
    s32 one, two, three;

    one = num >> 24;
    array[0] = one & 0x000000ff;
    two = num >> 16;
    array[1] = two & 0x000000ff;
    three = num >> 8;
    array[2] = three & 0x000000ff;
    array[3] = num & 0x000000ff;
}
static void leftLoop4int(s32 array[4], s32 step)
{
    s32 temp[4];
    s32 i;
    s32 index;

    for (i = 0; i < 4; i++)
        temp[i] = array[i];

    index = step % 4 == 0 ? 0 : step % 4;
    for (i = 0; i < 4; i++)
    {
        array[i] = temp[index];
        index++;
        index = index % 4;
    }
}
static s32 mergeArrayToInt(s32 array[4])
{
    s32 one = array[0] << 24;
    s32 two = array[1] << 16;
    s32 three = array[2] << 8;
    s32 four = array[3];
    return one | two | three | four;
}
static const s32 Rcon[10] =
{
    0x01000000, 0x02000000,
    0x04000000, 0x08000000,
    0x10000000, 0x20000000,
    0x40000000, 0x80000000,
    0x1b000000, 0x36000000
};
static s32 T(s32 num, s32 round)
{
    s32 numArray[4];
    s32 i;
    s32 result;

    splitIntToArray(num, numArray);
    leftLoop4int(numArray, 1);
    for (i = 0; i < 4; i++)
        numArray[i] = getNumFromSBox(numArray[i]);
    result = mergeArrayToInt(numArray);
    return result ^ Rcon[round];
}
static s32 w[44];
static void extendKey(s8 *key)
{
    s32 i;
    s32 j;
    for (i = 0; i < 4; i++)
        w[i] = getWordFromStr(key + i * 4);
    for (i = 4, j = 0; i < 44; i++)
    {
        if (i % 4 == 0)
        {
            w[i] = w[i - 4] ^ T(w[i - 1], j);
            j++;
        }
        else
        {
            w[i] = w[i - 4] ^ w[i - 1];
        }
    }
}

static void rightLoop4int(s32 array[4], s32 step)
{
    s32 temp[4];
    s32 i;
    s32 index;

    for (i = 0; i < 4; i++)
        temp[i] = array[i];

    /*  index = step % 4 == 0 ? 0 : step % 4;
        index = 3 - index;
        for(i = 3; i >= 0; i--) {
            array[i] = temp[index];
            index--;
            index = index == -1 ? 3 : index;
        } */
    if (step % 4 == 3)
    {
        array[3] = temp[0];
        array[2] = temp[3];
        array[1] = temp[2];
        array[0] = temp[1];
    }
    else if (step % 4 == 2)
    {
        array[3] = temp[1];
        array[2] = temp[0];
        array[1] = temp[3];
        array[0] = temp[2];
    }
    else if (step % 4 == 1)
    {
        array[3] = temp[2];
        array[2] = temp[1];
        array[1] = temp[0];
        array[0] = temp[3];
    }
    else if (step % 4 == 0)
    {
        array[3] = temp[3];
        array[2] = temp[2];
        array[1] = temp[1];
        array[0] = temp[0];
    }
}



static void addRoundKey(s32 array[4][4], s32 round)
{
    s32 warray[4];
    s32 i, j;
    for (i = 0; i < 4; i++)
    {
        splitIntToArray(w[round * 4 + i], warray);
        for (j = 0; j < 4; j++)
        {
            array[j][i] = array[j][i] ^ warray[j];
        }
    }
}

static s32 getNumFromS1Box(s32 index)
{
    s32 row = getLeft4Bit(index);
    s32 col = getRight4Bit(index);
    return S2[row][col];
}
static void deSubBytes(s32 array[4][4])
{
    s32 i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            array[i][j] = getNumFromS1Box(array[i][j]);
}

static void deShiftRows(s32 array[4][4])
{
    s32 rowTwo[4], rowThree[4], rowFour[4];
    s32 i;

    for (i = 0; i < 4; i++)
    {
        rowTwo[i] = array[1][i];
        rowThree[i] = array[2][i];
        rowFour[i] = array[3][i];
    }
    rightLoop4int(rowTwo, 1);
    rightLoop4int(rowThree, 2);
    rightLoop4int(rowFour, 3);

    for (i = 0; i < 4; i++)
    {
        array[1][i] = rowTwo[i];
        array[2][i] = rowThree[i];
        array[3][i] = rowFour[i];
    }
}

static const s32 colM[4][4] = {2, 3, 1, 1,
                               1, 2, 3, 1,
                               1, 1, 2, 3,
                               3, 1, 1, 2 };

static s32 GFMul2(s32 s)
{
    s32 result = s << 1;
    s32 a7 = result & 0x00000100;

    if (a7 != 0)
    {
        result = result & 0x000000ff;
        result = result ^ 0x1b;
    }

    return result;
}
static s32 GFMul3(s32 s)
{
    return GFMul2(s) ^ s;
}

static s32 GFMul4(s32 s)
{
    return GFMul2(GFMul2(s));
}

static s32 GFMul8(s32 s)
{
    return GFMul2(GFMul4(s));
}

static s32 GFMul9(s32 s)
{
    return GFMul8(s) ^ s;
}
static s32 GFMul11(s32 s)
{
    return GFMul9(s) ^ GFMul2(s);
}
static s32 GFMul12(s32 s)
{
    return GFMul8(s) ^ GFMul4(s);
}
static s32 GFMul13(s32 s)
{
    return GFMul12(s) ^ s;
}
static s32 GFMul14(s32 s)
{
    return GFMul12(s) ^ GFMul2(s);
}
static s32 GFMul(s32 n, s32 s)
{
    s32 result;

    if (n == 1)
        result = s;
    else if (n == 2)
        result = GFMul2(s);
    else if (n == 3)
        result = GFMul3(s);
    else if (n == 0x9)
        result = GFMul9(s);
    else if (n == 0xb) // 11
        result = GFMul11(s);
    else if (n == 0xd) // 13
        result = GFMul13(s);
    else if (n == 0xe) // 14
        result = GFMul14(s);
    return result;
}

static const s32 deColM[4][4] =
{
    0xe, 0xb, 0xd, 0x9,
    0x9, 0xe, 0xb, 0xd,
    0xd, 0x9, 0xe, 0xb,
    0xb, 0xd, 0x9, 0xe
};
static void deMixColumns(s32 array[4][4])
{
    s32 tempArray[4][4];
    s32 i, j;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            tempArray[i][j] = array[i][j];

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
        {
            array[i][j] = GFMul(deColM[i][0], tempArray[0][j]) ^ GFMul(deColM[i][1], tempArray[1][j]) ^ GFMul(deColM[i][2], tempArray[2][j]) ^ GFMul(deColM[i][3], tempArray[3][j]);
        }
}

static void getArrayFrom4W(s32 i, s32 array[4][4])
{
    s32 index = i * 4;
    s32 colOne[4], colTwo[4], colThree[4], colFour[4];
    s32 j;

    splitIntToArray(w[index], colOne);
    splitIntToArray(w[index + 1], colTwo);
    splitIntToArray(w[index + 2], colThree);
    splitIntToArray(w[index + 3], colFour);

    for (j = 0; j < 4; j++)
    {
        array[j][0] = colOne[j];
        array[j][1] = colTwo[j];
        array[j][2] = colThree[j];
        array[j][3] = colFour[j];
    }
}

static void addRoundTowArray(s32 aArray[4][4], s32 bArray[4][4])
{
    s32 i, j;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            aArray[i][j] = aArray[i][j] ^ bArray[i][j];
}

static void convertArrayToStr(s32 array[4][4], s8 *str)
{
    s32 i, j;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            *str++ = (s8)array[j][i];
}

// deAes((sint8 *)i_pCipherText, i_dataLen, (sint8 *)&gs_aKey[0], (sint8 *)o_pPlainText);
void deAes(s8 *c, s32 clen, s8 *key, s8 *pPlainText)
{
    // void AES_128(s8 *c, s32 clen, s8 *key, s8 * pPlainText){
    s32 keylen = 16;
    s32 k, i;
    s32 cArray[4][4];
    s32 wArray[4][4];
    //  if(clen == 0 || clen % 16 != 0) {       return; }
    //  if(!checkKeyLen(keylen)) {      return; }
    extendKey(key);
    for (k = 0; k < clen; k += 16)
    {
        convertToIntArray(c + k, cArray);
        addRoundKey(cArray, 10);
        for (i = 9; i >= 1; i--)
        {
            deSubBytes(cArray);
            deShiftRows(cArray);
            deMixColumns(cArray);
            getArrayFrom4W(i, wArray);
            deMixColumns(wArray);
            addRoundTowArray(cArray, wArray);
        }
        deSubBytes(cArray);
        deShiftRows(cArray);
        addRoundKey(cArray, 0);
        convertArrayToStr(cArray, pPlainText + k);
    }
}

static void subBytes(s32 array[4][4])
{
    s32 i, j;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            array[i][j] = getNumFromSBox(array[i][j]);
}
static void shiftRows(s32 array[4][4])
{
    s32 rowTwo[4], rowThree[4], rowFour[4];
    s32 i;

    for (i = 0; i < 4; i++)
    {
        rowTwo[i] = array[1][i];
        rowThree[i] = array[2][i];
        rowFour[i] = array[3][i];
    }

    leftLoop4int(rowTwo, 1);
    leftLoop4int(rowThree, 2);
    leftLoop4int(rowFour, 3);

    for (i = 0; i < 4; i++)
    {
        array[1][i] = rowTwo[i];
        array[2][i] = rowThree[i];
        array[3][i] = rowFour[i];
    }
}
static void mixColumns(s32 array[4][4])
{

    s32 tempArray[4][4];
    s32 i, j;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            tempArray[i][j] = array[i][j];

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
        {
            array[i][j] = GFMul(colM[i][0], tempArray[0][j]) ^ GFMul(colM[i][1], tempArray[1][j]) ^ GFMul(colM[i][2], tempArray[2][j]) ^ GFMul(colM[i][3], tempArray[3][j]);
        }
}

// void aes(s8 *p, s32 plen, s8 *key, s8 * cipher){
void AES_128(s8 *key, s32 plen, s8 *p, s8 *cipher)
{
    s32 pArray[4][4];
    s32 i, k;
    s32 keylen = 16;
    //  if(plen == 0 || plen % 16 != 0) { return;   }
    //  if(!checkKeyLen(keylen)) {return;   }
    extendKey(key);

    for (k = 0; k < plen; k += 16)
    {
        convertToIntArray(p + k, pArray);
        addRoundKey(pArray, 0);
        for (i = 1; i < 10; i++)
        {
            subBytes(pArray);
            shiftRows(pArray);
            mixColumns(pArray);
            addRoundKey(pArray, i);
        }
        subBytes(pArray);
        shiftRows(pArray);
        addRoundKey(pArray, 10);
        convertArrayToStr(pArray, cipher + k);
    }
}

/* CMAC Basic Functions */
void xor_128(unsigned char *a, unsigned char *b, unsigned char *out)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        out[i] = a[i] ^ b[i];
    }
}

#ifdef AES_PRINT_DEBUG
void print_hex(char *str, unsigned char *buf, int len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        if ((i % 16) == 0 && i != 0)
            _printf(str);      // printf(str);
        _putByteToHex(buf[i]); // printf("%02x", buf[i]);
        if ((i % 4) == 3)
            _printf(" "); // printf(" ");
        if ((i % 16) == 15)
            _printf("\r\n"); // printf("\n");
    }
    if ((i % 16) != 0)
        _printf("\r\n"); // printf("\n");
}

void print128(unsigned char *bytes)
{
    int j;
    for (j = 0; j < 16; j++)
    {
        _putByteToHex(bytes[j]); // printf("%02x",bytes[j]);
        if ((j % 4) == 3)
            _printf(" "); // if ( (j%4) == 3 ) printf(" ");
    }
}

void print96(unsigned char *bytes)
{
    int j;
    for (j = 0; j < 12; j++)
    {
        _putByteToHex(bytes[j]); // printf("%02x",bytes[j]);
        if ((j % 4) == 3)
            _printf(" "); // if ( (j%4) == 3 ) printf(" ");
    }
}
#endif

/* AES-CMAC Generation Function */
void leftshift_onebit(unsigned char *input, unsigned char *output)
{
    s8 i;
    unsigned char overflow = 0;

    for (i = 15; i >= 1; i--)
    {
        output[i] = input[i] << 1;
        output[i] |= overflow;
        overflow = (input[i] & 0x80) ? 1 : 0;
    }
    output[0] = input[0] << 1;
    output[0] |= overflow;
    overflow = (input[0] & 0x80) ? 1 : 0;
    return;
}

void generate_subkey(unsigned char *key, unsigned char *K1, unsigned char *K2)
{
    unsigned char L[16];
    unsigned char Z[16];
    unsigned char tmp[16];
    s8 i;

    for (i = 0; i < 16; i++)
        Z[i] = 0;
    AES_128(key, 16, Z, L);
    if ((L[0] & 0x80) == 0)
    {
        /* If MSB(L) = 0, then K1 = L << 1 */
        leftshift_onebit(L, K1);
    }
    else
    {
        /* Else K1 = ( L << 1 ) (+) Rb */
        leftshift_onebit(L, tmp);
        xor_128(tmp, const_Rb, K1);
    }

    if ((K1[0] & 0x80) == 0)
    {
        leftshift_onebit(K1, K2);
    }
    else
    {
        leftshift_onebit(K1, tmp);
        xor_128(tmp, const_Rb, K2);
    }
    return;
}

void padding(unsigned char *lastb, unsigned char *pad, s32 length)
{
    s8 j;

    /* original last block */
    for (j = 0; j < 16; j++)
    {
        if (j < length)
        {
            pad[j] = lastb[j];
        }
        else if (j == length)
        {
            pad[j] = 0x80;
        }
        else
        {
            pad[j] = 0x00;
        }
    }
}

/*****************************************************************************/
/* Public  application  Function                                            */
/*****************************************************************************/

// for a portion of AES-CMAC (init Gernarate K1,K2)
unsigned char gL[16], gK1[16], gK2[16];
unsigned char gX[16], gY[16], gM_last[16], gPadded[16];
void Gen_CMACkey(unsigned char *key)
{
    unsigned char i;
    for (i = 0; i < 16; i++)
    {
        gL[i] = 0;
        gK1[i] = 0, gK2[i] = 0; // gX[i] = 0;
        gY[i] = 0;
        gM_last[i] = 0;
        gPadded[i] = 0;
    }
    AES_128(key, 16, const_Zero, gL);
    generate_subkey(key, gK1, gK2);
}

/*
//for a portion of AES-CMAC calculation


void AES_CMAC_BLK ( unsigned char *key, unsigned char *input, int length,int frist)
{

    int n, i, flag;


    n = (length+15) / 16;   // n is number of rounds
    if ( n == 0 ) {
        n = 1;
        flag = 0;
    } else {
        if ( (length%16) == 0 ) { // last block is a complete block
            flag = 1;
        } else { // last block is not complete block
            flag = 0;
        }
    }

if(frist){
    if ( flag ) { // last block is complete block
        xor_128(&input[16*(n-1)],gK1,gM_last);
    } else {
        padding(&input[16*(n-1)],gPadded,length%16);
        xor_128(gPadded,gK2,gM_last);
    }


    for ( i=0; i<16; i++ ) gX[i] = 0;
    for ( i=0; i<n-1; i++ ) {
        xor_128(gX,&input[16*i],gY);    // Y := Mi (+) X
        AES_128(key,16,gY,gX);          //AES_128(key,Y,X);
    }
}else{

    for ( i=0; i<n; i++ ) {
        xor_128(gX,&input[16*i],gY);    // Y := Mi (+) X
        AES_128(key,16,gY,gX);          //AES_128(key,Y,X);
    }
}
}

//for a portion of AES-CMAC get
void Get_AES_CMAC ( unsigned char *key, unsigned char *mac)
{
    unsigned char i;
    xor_128(gX,gM_last,gY);
    AES_128(key,16,gY,gX);//AES_128(key,Y,X);

    for ( i=0; i<16; i++ ) {
        mac[i] = gX[i];
    }
}
*/
void sha256(const uint8_t *data, uint32_t len, uint8_t digest[32])
{
    uint32_t h[8] =
    {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    static const uint32_t k[64] =
    {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    uint64_t bit_len = (uint64_t)len * 8;

    uint32_t pad_len = 64 - (len % 64);
    if (pad_len < 9)
    {
        pad_len += 64;
    }
    uint32_t total_len = len + pad_len;
    uint32_t total_blocks = total_len / 64;

    uint8_t block[64];

    for (uint32_t block_num = 0; block_num < total_blocks; block_num++)
    {
        memset(block, 0, 64);

        if (block_num * 64 < len)
        {
            uint32_t copy_len = len - block_num * 64;

            if (copy_len > 64)
            {
                copy_len = 64;
            }
            memcpy(block, data + block_num * 64, copy_len);

            if (copy_len < 64)
            {
                block[copy_len] = 0x80;

                if (copy_len <= 55)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        block[56 + i] = (bit_len >> (56 - i * 8)) & 0xFF;
                    }
                }
            }
        }
        else
        {
            block[0] = 0x80;
            for (int i = 0; i < 8; i++)
            {
                block[56 + i] = (bit_len >> (56 - i * 8)) & 0xFF;
            }
        }

        uint32_t w[64];

        for (int i = 0; i < 16; i++)
        {
            w[i] = ((uint32_t)block[i * 4] << 24) |
                   ((uint32_t)block[i * 4 + 1] << 16) |
                   ((uint32_t)block[i * 4 + 2] << 8) |
                   ((uint32_t)block[i * 4 + 3]);
        }

        for (int i = 16; i < 64; i++)
        {
            uint32_t s0 = ((w[i - 15] >> 7) | (w[i - 15] << 25)) ^
                          ((w[i - 15] >> 18) | (w[i - 15] << 14)) ^
                          (w[i - 15] >> 3);
            uint32_t s1 = ((w[i - 2] >> 17) | (w[i - 2] << 15)) ^
                          ((w[i - 2] >> 19) | (w[i - 2] << 13)) ^
                          (w[i - 2] >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }

        uint32_t a = h[0], b = h[1], c = h[2], d = h[3];
        uint32_t e = h[4], f = h[5], g = h[6], hh = h[7];

        for (int i = 0; i < 64; i++)
        {
            uint32_t S1 = ((e >> 6) | (e << 26)) ^ ((e >> 11) | (e << 21)) ^ ((e >> 25) | (e << 7));
            uint32_t ch = (e & f) ^ (~e & g);
            uint32_t temp1 = hh + S1 + ch + k[i] + w[i];
            uint32_t S0 = ((a >> 2) | (a << 30)) ^ ((a >> 13) | (a << 19)) ^ ((a >> 22) | (a << 10));
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = S0 + maj;

            hh = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
        h[5] += f;
        h[6] += g;
        h[7] += hh;
    }

    for (int i = 0; i < 8; i++)
    {
        digest[i * 4] = (h[i] >> 24) & 0xFF;
        digest[i * 4 + 1] = (h[i] >> 16) & 0xFF;
        digest[i * 4 + 2] = (h[i] >> 8) & 0xFF;
        digest[i * 4 + 3] = h[i] & 0xFF;
    }
}

// for all function
void aes_cmac(unsigned char *key, unsigned char *input, s32 length, unsigned char *mac)
{
    unsigned char X[16], Y[16], M_last[16], padded[16];
    unsigned char K1[16], K2[16];
    s32 n, i, flag;
    generate_subkey(key, K1, K2);
    n = (length + 15) / 16; /* n is number of rounds */
    if (n == 0)
    {
        n = 1;
        flag = 0;
    }
    else
    {
        if ((length % 16) == 0)
        {
            /* last block is a complete block */
            flag = 1;
        }
        else
        {
            /* last block is not complete block */
            flag = 0;
        }
    }

    if (flag)
    {
        /* last block is complete block */
        xor_128(&input[16 * (n - 1)], K1, M_last);
    }
    else
    {
        padding(&input[16 * (n - 1)], padded, length % 16);
        xor_128(padded, K2, M_last);
    }

    for (i = 0; i < 16; i++)
        X[i] = 0;
    for (i = 0; i < n - 1; i++)
    {
        xor_128(X, &input[16 * i], Y); /* Y := Mi (+) X */
        AES_128(key, 16, Y, X);        // AES_128(key,Y,X); /* X := AES-128(KEY, Y); */
    }

    xor_128(X, M_last, Y);
    AES_128(key, 16, Y, X); // AES_128(key,Y,X);
    for (i = 0; i < 16; i++)
    {
        mac[i] = X[i];
    }
}

#ifdef AES_PRINT_DEBUG
int AES_CMAC_test(void)
{
    unsigned char L[16], K1[16], K2[16], T[16], TT[12];
    unsigned char M[64] =
    {
        // 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,
        0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
        0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
        0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c,
        0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
        0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11,
        0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
        0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17,
        0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10
    };

    /*
        // portion test
        _printf("\r\n--------------------------------------------------");
        _printf("\r\nSubkey Generation");
        _printf("\r\nK              "); print128(gs_aKey);
        //AES_128(gs_aKey,16,const_Zero,L);   //AES_128(key,const_Zero,L);
        Gen_CMACkey(gs_aKey);
        _printf("\r\nAES_128(key,0) "); print128(L);
        //generate_subkey(gs_aKey,K1,K2);
        _printf("\r\nK1             "); print128(gK1);
        _printf("\r\nK2             "); print128(gK2);

        _printf("\r\nExample 1: len = 0");
        _printf("\r\nM              "); _printf("<empty string>");
        //AES_CMAC(gs_aKey,M,0,T);
        AES_CMAC_BLK (gs_aKey,M,0,1);
        Get_AES_CMAC (gs_aKey,T);
        _printf("\r\nAES_CMAC       ");     print128(T);

        _printf("\r\nExample 2: len = 16");
        _printf("\r\nM              "); print_hex("                   ",M,16);
        //AES_CMAC(gs_aKey,M,16,T);
        AES_CMAC_BLK (gs_aKey,M,16,1);
        Get_AES_CMAC (gs_aKey,T);
        _printf("AES_CMAC       ");   print128(T);

        _printf("\r\nExample 3: len = 40");
        _printf("\r\nM              "); print_hex("                   ",M,40);
        //AES_CMAC(gs_aKey,M,40,T);
        AES_CMAC_BLK (gs_aKey,M,40,1);
        Get_AES_CMAC (gs_aKey,T);
        _printf("AES_CMAC       "); print128(T);

        _printf("\r\nExample 4: len = 64");
        _printf("\r\nM              "); print_hex("                   ",M,64);
        //AES_CMAC(gs_aKey,M,64,T);
        AES_CMAC_BLK (gs_aKey,M,32,1);
        AES_CMAC_BLK (gs_aKey,&M[32],32,0);
        Get_AES_CMAC (gs_aKey,T);
        _printf("AES_CMAC       "); print128(T);

        _printf("\r\n--------------------------------------------------");

    */

    // full test
    _printf("\r\n--------------------------------------------------");
    _printf("\r\nSubkey Generation");
    _printf("\r\nK              ");
    print128(gs_aKey);
    //  AES_128(gs_aKey,16,const_Zero,L);   //AES_128(key,const_Zero,L);
    _printf("\r\nAES_128(key,0) ");
    print128(L);
    //  generate_subkey(gs_aKey,K1,K2);
    _printf("\r\nK1             ");
    print128(K1);
    _printf("\r\nK2             ");
    print128(K2);

    _printf("\r\nExample 1: len = 0");
    _printf("\r\nM              ");
    _printf("<empty string>");
    AES_CMAC(gs_aKey, M, 0, T);
    _printf("\r\nAES_CMAC       ");
    print128(T);

    _printf("\r\nExample 2: len = 16");
    _printf("\r\nM              ");
    print_hex(" 	              ", M, 16);
    AES_CMAC(gs_aKey, M, 16, T);
    _printf("AES_CMAC       ");
    print128(T);

    _printf("\r\nExample 3: len = 40");
    _printf("\r\nM              ");
    print_hex(" 	              ", M, 40);
    AES_CMAC(gs_aKey, M, 40, T);
    _printf("AES_CMAC       ");
    print128(T);

    _printf("\r\nExample 4: len = 64");
    _printf("\r\nM              ");
    print_hex(" 	              ", M, 64);
    AES_CMAC(gs_aKey, M, 64, T);
    _printf("AES_CMAC       ");
    print128(T);

    _printf("\r\n--------------------------------------------------");

    /*output
    --------------------------------------------------
    Subkey Generation
    K              2B7E1516 28AED2A6 ABF71588 09CF4F3C
    AES_128(key,0) 7DF76B0C 1AB899B3 3E42F047 B91B546F
    K1             FBEED618 35713366 7C85E08F 7236A8DE
    K2             F7DDAC30 6AE266CC F90BC11E E46D513B
    Example 1: len = 0
    M              <empty string>
    AES_CMAC       BB1D6929 E9593728 7FA37D12 9B756746
    Example 2: len = 16
    M              6BC1BEE2 2E409F96 E93D7E11 7393172A
    AES_CMAC       070A16B4 6B4D4144 F79BDD9D D04A287C
    Example 3: len = 40
    M              6BC1BEE2 2E409F96 E93D7E11 7393172A
                   AE2D8A57 1E03AC9C 9EB76FAC 45AF8E51
                   30C81C46 A35CE411
    AES_CMAC       DFA66747 DE9AE630 30CA3261 1497C827
    Example 4: len = 64
    M              6BC1BEE2 2E409F96 E93D7E11 7393172A
                   AE2D8A57 1E03AC9C 9EB76FAC 45AF8E51
                   30C81C46 A35CE411 E5FBC119 1A0A52EF
                   F69F2445 DF4F9B17 AD2B417B E66C3710
    AES_CMAC       51F0BEBF 7E3B9D92 FC497417 79363CFE
    --------------------------------------------------
    */

    return 0;
}
#endif


