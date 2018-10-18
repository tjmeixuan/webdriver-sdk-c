#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "webdriver.h"
#include "wdvalue.h"

const char* APPID = "5b4564eaab00093b641e99b5";
const char* ACCESSKEY = "a59836a11b76dda496bac68c";
const char* SECRETKEY = "3dcc2142b326020d92b77b1c";
const char* PAGEID = "5b45b741aa4a3a3f5840d15b";
const char* PAGEID2 = "5bbc30e769516e40e8366d17";
const char* CIRCLE = "WDVZ6DE5OF";	// 页面1中的圆形组件，演示改变背景颜色
const char* BUTTON1 = "WDJTLFVEQQ";	// 页面1中的切换页面按钮
const char* BUTTON2 = "WDCIILJPWO";	// 页面1中的显示消息按钮
const char* BUTTON3 = "WDWLABJ5JW";	// 页面2中的切换页面按钮

void __stdcall fNoticeCallback(const char* appid, const char* pageid, const char* wid, const char* name, const char* sid, const char* value, void* user)
{
	printf("rcv data wid = %s , name = %s, value = %s\r\n",  wid, name, value);

	if (strcmp(pageid, PAGEID) == 0)
	{
		if(strcmp(wid, BUTTON1) == 0)
		{
			// 第一页的按钮 id
			printf("收到 第一页 按钮的 点击事件, 准备跳转到第二页\n");

			// 跳转到第二页
			wd_showPage(APPID, PAGEID, PAGEID2, "0");
		} 
		else if (strcmp(wid, BUTTON2) == 0)
		{
			// 显示消息
			const char* title = "hello";
			const char* message = "welcome to webdriver";

			wd_sendMessage(APPID, PAGEID, "success", title, message, 3, sid);
		}
	}
	else if (strcmp(pageid, PAGEID2) == 0)
	{
		if (strcmp(wid, BUTTON3) == 0){
			// 第二页的按钮 id
			printf("收到 第二页 按钮的 点击事件, 准备跳转到第一页\n");
			// 跳转到第一页
			wd_showPage(APPID, PAGEID2, PAGEID, sid);
		} 
	}
}

void __stdcall fConnectStateCallback(const char* appid, bool state){
	printf("connect state, appid = %s , state = %d\r\n",  appid, state);
}

int main()
{
	char* colors[]  = {"red", "blue", "yellow"};
	const char* serverip = "127.0.0.1";
	int index = 0;
	char* str = "123456.123456789";
	char des[250] = {0};
	int a1;
	wd_uint a2;
	double a3;
	bool a4;
	char* d1, *d2, *d3, *d4;
	char des1[100] = {0};
	char des2[100] = {0};
	char des3[100] = {0};
	char des4[100] = {0};

	// 测试辅助函数
	a1 = wd_to_int((void*)str);
	a2 = wd_to_uint((void*)str);
	a3 = wd_to_double((void*)str);
	a4 = wd_to_bool((void*)str);

	printf("a1=%d a2=%d a4=%.03f d4=%d\n",a1, a2, a3, a4);

	d1 = wd_int_to_str(des1, a1);
	d2 = wd_uint_to_str(des2, a2);
	d3 = wd_double_to_str(des3, a3, 10);
	d4 = wd_bool_to_str(des4, a4);

	printf("d1=%s d2=%s d3=%s d4=%s\n",d1, d2, d3, d4);


	// 测试接口
	wd_config(serverip);
	wd_connect(APPID, ACCESSKEY, SECRETKEY, fNoticeCallback, fConnectStateCallback);
	while(1){
		Sleep(1000);
		// 改变圆形的背景颜色
		wd_write(APPID, PAGEID, CIRCLE, "bg", "0", colors[index]);
		index++;
		if(index >= 3) index = 0;
	}
	return 0;
}