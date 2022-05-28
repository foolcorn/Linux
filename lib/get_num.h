#ifndef GET_NUM_H
#define GET_NUM_H

#define GN_NONNEG        01 //-flags的备选值，在低有效位，如果设置该标志不支持转成负数
#define GN_GT_O          02 //-flags的备选值，在低有效位，如果设置该标志只支持正数（不包括0）
// * 上面和下面的标志位可以用|组合
#define GN_ANY_BASE    0100 //-flags的备选值，在高有效位，如果设置该标志支持自动识别转换
                            //-如果不加前缀按十进制，如果加了0，八进制，加了0x前缀，十六进制
#define GN_BASE_8      0200 //-flags的备选值，在高有效位，如果设置该标志会将字符串按八进制来转换
#define GN_BASE_16     0400 //-flags的备选值，在高有效位，如果设置该标志会将字符串按十六进制来转换

//-字符串转int flags为进制，
int getInt(const char* arg, int flags, const char* name);
//-字符串转long
long getLong(const char* arg, int flags, const char* name);

#endif