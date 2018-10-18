// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� WEBDRIVER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// WEBDRIVER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

/** @file webdriver.h
  * @brief webdriver sdk �ӿ�
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
  * ֪ͨ��Ϣ�Ļص���������
  * @param[out] appid	Ӧ��ID
  * @param[out] pageid	ҳ��ID
  * @param[out] wid		���ID
  * @param[out] name	��������
  * @param[out] sid		��ǰ�ỰID��һ���Ự��ʾһ��Ӧ��ʵ����SDK������
  * @param[out] value	����ֵ
  * @param[out] user	�û����
  * @return void �޷���ֵ
  */
typedef void (__stdcall *WD_NOTICE_CALLBACK)(const char* appid, const char* pageid, const char* wid, const char* name, const char* sid, const char* value, void* user);

/** @typedef void (*WD_CONNECTSTATE_CALLBACK)(const char* appid, bool state)
  * ֪ͨ��Ϣ�Ļص���������
  * @param[out] appid	Ӧ��ID
  * @param[out] state	����״̬, true-���ӳɹ�, false-����ʧ��
  * @return void �޷���ֵ
  */
typedef void (__stdcall *WD_CONNECTSTATE_CALLBACK)(const char* appid, bool state);

/** @fn int __stdcall wd_config(const char* serverip)
  * ����ȫ�����ӵķ����IP��Ĭ�ϲ���Ҫ���ã���Ҫ���ڲ���
  * @param[in] serverip		�����IP��ַ
  * @return int 0:��ʾ�ɹ�
  */
WEBDRIVER_API int __stdcall wd_config(const char* serverip);

/** @fn int __stdcall wd_connect(const char* appid, const char* accesskey, const char* secretkey, WD_NOTICE_CALLBACK noticeCallback, WD_CONNECTSTATE_CALLBACK connectStateCallback)
  * ����Ӧ��
  * @param[in] appid				Ӧ��ID
  * @param[in] accesskey			Ӧ�õ�accesskey
  * @param[in] secretkey			Ӧ�õ�secretkey
  * @param[in] noticeCallback		֪ͨ��Ϣ�ص����� WD_NOTICE_CALLBACK
  * @param[in] connectStateCallback ����״̬�ص����� WD_CONNECTSTATE_CALLBACK
  * @return int 0:��ʾ�ɹ�
  */
WEBDRIVER_API int __stdcall wd_connect(const char* appid, const char* accesskey, const char* secretkey, WD_NOTICE_CALLBACK noticeCallback, WD_CONNECTSTATE_CALLBACK connectStateCallback);

/** @fn int __stdcall wd_disconnect(const char* appid)
  * �Ͽ�ȫ��Ӧ�û���ָ����Ӧ��
  * @param[in] appid Ӧ��ID�����Ϊ0, ��ʾ�Ͽ�ȫ��Ӧ��
  * @return int 0:��ʾ�ɹ�
  */
WEBDRIVER_API int __stdcall wd_disconnect(const char* appid);

/** @fn int __stdcall wd_writeString(const char* appid, const char* pageid, const char* wid, const char* name, const char* sid, const char* value)
  * ���ñ�����ֵ
  * @param[in] appid	Ӧ��ID
  * @param[in] pageid	ҳ��ID
  * @param[in] wid		���ID
  * @param[in] name		����
  * @param[in] sid		�ỰID, "0"��ʾ��ָ��Ӧ�õ����лỰ�ı���������ֵ������ֻ���ø��Ƕ��ĻỰ
  * @param[in] value	ֵ���ַ���/ ���� int, uint,bool, json_object����Ҫת���ַ�����ʽ����write
  * @return int 0:��ʾ�ɹ�
  */
WEBDRIVER_API int __stdcall wd_write(const char* appid, const char* pageid, const char* wid, const char* name, const char* sid, const char* value);

/** @fn int __stdcall wd_read(const char* appid, const char* pageid, const char* wid, const char* name, void* value)
  * ��ȡ������ֵ
  * @param[in] appid	Ӧ��ID
  * @param[in] pageid	ҳ��ID
  * @param[in] wid		���ID
  * @param[in] name		����
  * @param[in] value	ֵ��void*���ͣ���ǰ����ֱ��תΪchar*����Ҫ����wid/name�ľ������ͣ�������һ����ת��
  * @return int 0:��ʾ�ɹ�
  */
WEBDRIVER_API int __stdcall wd_read(const char* appid, const char* pageid, const char* wid, const char* name, void* value);

/** @fn int __stdcall wd_showPage(const char* appid, const char* pageid, const char* targetpageid, const char* sid)
  * ��ʾָ��ҳ��/�л���ָ����Ŀ��ҳ��
  * @param[in] appid			Ӧ��ID
  * @param[in] pageid			��ǰҳ��ID
  * @param[in] targetpageid		Ŀ��ҳ��ID
  * @param[in] sid				�ỰID
  * @return int 0:��ʾ�ɹ�
  */
WEBDRIVER_API int __stdcall wd_showPage(const char* appid, const char* pageid, const char* targetpageid, const char* sid);

/** @fn int __stdcall wd_sendMessage(const char* appid, const char* pageid, const char* type, const char* title, const char* message, int duration, const char* sid)
  * ��ָ��Ӧ�÷���ȫ�ֵ���Ϣ
  * @param[in] appid	Ӧ��ID
  * @param[in] pageid	��ǰҳ��ID
  * @param[in] type		Ŀ��ҳ��ID
  * @param[in] title	��Ϣ���� "success"-�ɹ� "warning"-���� "error"-����
  * @param[in] message	��Ϣ����
  * @param[in] duration ��Ϣ��ʾ����ڵ�ʱ�� 0-��ʾһֱ���ڣ�>0��ʾ����duration����Զ���ʧ
  * @param[in] sid		�ỰID
  * @return int 0:��ʾ�ɹ�
  */
WEBDRIVER_API int __stdcall wd_sendMessage(const char* appid, const char* pageid, const char* type, const char* title, const char* message, int duration, const char* sid);

#ifdef __cplusplus
}
#endif

#endif //!_WEBDRIVER_H_