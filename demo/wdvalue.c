/** @file wdvalue.c
  * @brief 值和字符串互转辅助方法
  * @copyright (c) 2018, MeiXuan All rights reserved
  * @author MeiXuan01
  * @date 2018/10/10
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wdvalue.h"

// 字符串转值类型
int wd_to_int(void* value)
{	
	const char *r = (const char*)value;
	if(r == NULL)
	{
		 return 0;
	}	
	return atoi(r);
};
wd_uint wd_to_uint(void* value)
{
	char* r = (char*)value;
	if(r == NULL) return 0;	
	return strtoul(r, NULL, 10);
};
double wd_to_double(const char* value)
{
	char* r = (char*)value;
	if(r == NULL) return 0;
	return atof(r);
}
bool wd_to_bool(void* value)
{
	char* r = (char*)value;
	if(r == NULL) return false;	
	if(strcmp(r, "\0") == 0) {
		return false;
	}
	else if(strcmp(r, "0\0") == 0) 
	{
		return false;
	}
	else if(strcmp(r, "false\0") == 0)
	{
		return false;
	}
	return true;
}

// 值类型转字符串
char* wd_int_to_str(char* des, int value)
{
	return itoa(value, des, 10);
}
char* wd_uint_to_str(char* des, wd_uint value)
{
	return ultoa((unsigned long)value, des, 10);
}
char* wd_double_to_str(char* des, double value, int _NumOfDigits)
{
	return gcvt(value, _NumOfDigits, des);
}
char* wd_bool_to_str(char* des, bool value)
{
	*des = (value == true)?'1':'0';
	return des;
}