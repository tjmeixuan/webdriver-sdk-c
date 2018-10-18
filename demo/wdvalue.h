/** @file wdvalue.h
  * @brief 字符串和值互转辅助方法
  * @copyright (c) 2018, MeiXuan All rights reserved
  * @author MeiXuan01
  * @date 2018/10/10
  */
#ifndef __WDVALUE_H__
#define __WDVALUE_H__

typedef unsigned int wd_uint;

#ifndef __cplusplus
#ifndef bool
#define bool char
#define true 1
#define false 0
#endif
#endif

// 字符串转值类型
int wd_to_int(void* value);
wd_uint wd_to_uint(void* value);
double wd_to_double(void* value);
bool wd_to_bool(void* value);

// 值类型转字符串
char* wd_int_to_str(char* des, int value);
char* wd_uint_to_str(char* des, wd_uint value);
char* wd_double_to_str(char* des, double value, int _NumOfDigits);
char* wd_bool_to_str(char* des, bool value);

#endif //!__WDVALUE_H__