// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 WEBDRIVER_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// WEBDRIVER_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。

/** @file webdriver.h
  * @brief webdriver sdk 接口
  * @copyright (c) 2018-2018, MeiXuan All rights reserved
  * @author MeiXuan01
  * @date 2018/10/10
  */

#ifndef _WEBDRIVER_H_
#define _WEBDRIVER_H_

#ifdef WEBDRIVER_EXPORTS
#define WEBDRIVER_API __declspec(dllexport)
#else
#define WEBDRIVER_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern"C"
{
#else

#ifndef bool
#define bool char
#define true 1
#define false 0
#endif

#endif

/** @typedef void (*WD_NOTICE_CALLBACK)(const char* appid, const char* pageid, const char* wid, const char* name, const char* sid, const char* value, void* user)
  * 通知消息的回调函数定义
  * @param[out] appid	应用ID
  * @param[out] pageid	页面ID
  * @param[out] wid		组件ID
  * @param[out] name	变量名称
  * @param[out] sid		当前会话ID，一个会话表示一个应用实例与SDK的连接
  * @param[out] value	变量值
  * @param[out] user	用户句柄
  * @return void 无返回值
  */
typedef void (__stdcall *WD_NOTICE_CALLBACK)(const char* appid, const char* pageid, const char* wid, const char* name, const char* sid, const char* value, void* user);

/** @typedef void (*WD_CONNECTSTATE_CALLBACK)(const char* appid, bool state)
  * 通知消息的回调函数定义
  * @param[out] appid	应用ID
  * @param[out] state	连接状态, true-连接成功, false-连接失败
  * @return void 无返回值
  */
typedef void (__stdcall *WD_CONNECTSTATE_CALLBACK)(const char* appid, bool state);

/** @fn int __stdcall wd_config(const char* serverip)
  * 配置全局连接的服务端IP，默认不需要配置，主要用于测试
  * @param[in] serverip		服务端IP地址
  * @return int 0:表示成功
  */
WEBDRIVER_API int __stdcall wd_config(const char* serverip);

/** @fn int __stdcall wd_connect(const char* appid, const char* accesskey, const char* secretkey, WD_NOTICE_CALLBACK noticeCallback, WD_CONNECTSTATE_CALLBACK connectStateCallback)
  * 连接应用
  * @param[in] appid				应用ID
  * @param[in] accesskey			应用的accesskey
  * @param[in] secretkey			应用的secretkey
  * @param[in] noticeCallback		通知消息回调函数 WD_NOTICE_CALLBACK
  * @param[in] connectStateCallback 连接状态回调函数 WD_CONNECTSTATE_CALLBACK
  * @return int 0:表示成功
  */
WEBDRIVER_API int __stdcall wd_connect(const char* appid, const char* accesskey, const char* secretkey, WD_NOTICE_CALLBACK noticeCallback, WD_CONNECTSTATE_CALLBACK connectStateCallback);

/** @fn int __stdcall wd_disconnect(const char* appid)
  * 断开全部应用或者指定的应用
  * @param[in] appid 应用ID，如果为0, 表示断开全部应用
  * @return int 0:表示成功
  */
WEBDRIVER_API int __stdcall wd_disconnect(const char* appid);

/** @fn int __stdcall wd_writeString(const char* appid, const char* pageid, const char* wid, const char* name, const char* sid, const char* value)
  * 设置变量的值
  * @param[in] appid	应用ID
  * @param[in] pageid	页面ID
  * @param[in] wid		组件ID
  * @param[in] name		变量
  * @param[in] sid		会话ID, "0"表示给指定应用的所有会话的变量都设置值，否则只设置给是定的会话
  * @param[in] value	值，字符串/ 所有 int, uint,bool, json_object都需要转成字符串形式，再write
  * @return int 0:表示成功
  */
WEBDRIVER_API int __stdcall wd_write(const char* appid, const char* pageid, const char* wid, const char* name, const char* sid, const char* value);

/** @fn int __stdcall wd_read(const char* appid, const char* pageid, const char* wid, const char* name, void* value)
  * 读取变量的值
  * @param[in] appid	应用ID
  * @param[in] pageid	页面ID
  * @param[in] wid		组件ID
  * @param[in] name		变量
  * @param[in] value	值，void*类型，当前可以直接转为char*，需要根据wid/name的具体类型，再做进一步的转换
  * @return int 0:表示成功
  */
WEBDRIVER_API int __stdcall wd_read(const char* appid, const char* pageid, const char* wid, const char* name, void* value);

/** @fn int __stdcall wd_showPage(const char* appid, const char* pageid, const char* targetpageid, const char* sid)
  * 显示指定页面/切换到指定的目标页面
  * @param[in] appid			应用ID
  * @param[in] pageid			当前页面ID
  * @param[in] targetpageid		目标页面ID
  * @param[in] sid				会话ID
  * @return int 0:表示成功
  */
WEBDRIVER_API int __stdcall wd_showPage(const char* appid, const char* pageid, const char* targetpageid, const char* sid);

/** @fn int __stdcall wd_sendMessage(const char* appid, const char* pageid, const char* type, const char* title, const char* message, int duration, const char* sid)
  * 给指定应用发送全局的消息
  * @param[in] appid	应用ID
  * @param[in] pageid	当前页面ID
  * @param[in] type		目标页面ID
  * @param[in] title	消息类型 "success"-成功 "warning"-警告 "error"-错误
  * @param[in] message	消息内容
  * @param[in] duration 消息提示后存在的时间 0-表示一直存在，>0表示存在duration秒后，自动消失
  * @param[in] sid		会话ID
  * @return int 0:表示成功
  */
WEBDRIVER_API int __stdcall wd_sendMessage(const char* appid, const char* pageid, const char* type, const char* title, const char* message, int duration, const char* sid);

#ifdef __cplusplus
}
#endif

#endif //!_WEBDRIVER_H_