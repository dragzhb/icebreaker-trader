#ifdef LIBIBT_CLIENT_STATIC_EXPORTS
#define LIBIBT_CLIENT_API
#else
#ifdef LIBIBT_CLIENT_EXPORTS
#define LIBIBT_CLIENT_API __declspec(dllexport)
#else
#define LIBIBT_CLIENT_API __declspec(dllimport)
#endif
#endif

#ifndef __IBT_CLIENT_H__
#define __IBT_CLIENT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* ���� */
#ifndef IBT_Enum_Buy
#define IBT_Enum_Buy 0
#endif 

/* ���� */
#ifndef IBT_Enum_Sell
#define IBT_Enum_Sell 1
#endif

/* ���� */
#ifndef IBT_Enum_Entry
#define IBT_Enum_Entry 0
#endif

/* ƽ�� */
#ifndef IBT_Enum_Exit
#define IBT_Enum_Exit 1
#endif

/* ƽ�� */
#ifndef IBT_Enum_ExitToday
#define IBT_Enum_ExitToday 2
#endif

/* ��ʼ�� ibt_client */
LIBIBT_CLIENT_API int ibt_init(void);
/* ��ʼ�� ibt_client ����ָ����־�������ļ� */
LIBIBT_CLIENT_API int ibt_init_ex(const char* p_log_config_file);

/* �����µ�����*/
LIBIBT_CLIENT_API int ibt_send_order(int Policy_ID,
		int BuyOrSell,
		int EntryOrExit,
		int Lot);


/* =========== ������Ǹ������� =========== */

/* ��õ�ǰ·�� */
LIBIBT_CLIENT_API const char* ibt_current_dir();

/* ����Ƿ��Ѵ�DEBUG��Ϣ����, 0 - û�д򿪣� 1 - �� */
LIBIBT_CLIENT_API int ibt_is_debug();

/* ����Ƿ��Ѵ�INFO��Ϣ����, 0 - û�д򿪣� 1 - �� */
LIBIBT_CLIENT_API int ibt_is_info();

/* ����Ƿ��Ѵ�ERROR��Ϣ����, 0 - û�д򿪣� 1 - �� */
LIBIBT_CLIENT_API int ibt_is_error();

/* ��ӡDEBUG��Ϣ */
LIBIBT_CLIENT_API void ibt_debug(const char* p_text);
/* ��ӡINFO��Ϣ */
LIBIBT_CLIENT_API void ibt_info(const char* p_text);
/* ��ӡERROR��Ϣ */
LIBIBT_CLIENT_API void ibt_error(const char* p_text);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef __IBT_CLIENT_H__ */
