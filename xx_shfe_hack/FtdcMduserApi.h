/////////////////////////////////////////////////////////////////////////
///@system ��һ��������ϵͳ
///@company �Ϻ��ڻ���Ϣ�������޹�˾
///@file FtdcMduserApi.h
///@brief �����˿ͻ��˽ӿ�
///@history 
///20060106	�Ժ��		�������ļ�
///20181106	����		NT-0350-�滻openssl��֧�ֹ����㷨
/////////////////////////////////////////////////////////////////////////

#if !defined(_FTDCMDUSERAPI_H)
#define _FTDCMDUSERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_MDUSER_API_EXPORT
#define MDUSER_API_EXPORT __declspec(dllexport)
#else
#define MDUSER_API_EXPORT __declspec(dllimport)
#endif
#else
#if defined(LIB_MDUSER_API_EXPORT) && defined(ISLIB) && defined(UNIX)
#define MDUSER_API_EXPORT  __attribute__ ((visibility("default")))
#else
#define MDUSER_API_EXPORT
#endif 
#endif

class CShfeFtdcMduserSpi
{
public:
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected(){};
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason){};
		
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse){};
	
	///���Ļص���ʼ֪ͨ����API�յ�һ�����ĺ����ȵ��ñ�������Ȼ���Ǹ�������Ļص�������Ǳ��Ļص�����֪ͨ��
	///@param nTopicID ������루��˽���������������������ȣ�
	///@param nSequenceNo �������
	virtual void OnPackageStart(int nTopicID, int nSequenceNo){};
	
	///���Ļص�����֪ͨ����API�յ�һ�����ĺ����ȵ��ñ��Ļص���ʼ֪ͨ��Ȼ���Ǹ�������Ļص��������ñ�������
	///@param nTopicID ������루��˽���������������������ȣ�
	///@param nSequenceNo �������
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo){};


	///����Ӧ��
	virtual void OnRspError(CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�û���¼Ӧ��
	virtual void OnRspUserLogin(CShfeFtdcRspUserLoginField *pRspUserLogin, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�û��˳�Ӧ��
	virtual void OnRspUserLogout(CShfeFtdcRspUserLogoutField *pRspUserLogout, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������Ӧ��
	virtual void OnRspSubscribeTopic(CShfeFtdcDisseminationField *pDissemination, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯӦ��
	virtual void OnRspQryTopic(CShfeFtdcDisseminationField *pDissemination, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����������֪ͨ
	virtual void OnRtnFlowMessageCancel(CShfeFtdcFlowMessageCancelField *pFlowMessageCancel) {};

	///�������֪ͨ
	virtual void OnRtnDepthMarketData(CShfeFtdcDepthMarketDataField *pDepthMarketData) {};
};

class MDUSER_API_EXPORT CShfeFtdcMduserApi
{
public:
	///����MduserApi
	///@param pszFlowPath ����������Ϣ�ļ���Ŀ¼��Ĭ��Ϊ��ǰĿ¼
	///@return ��������UserApi
	static CShfeFtdcMduserApi *CreateFtdcMduserApi(const char *pszFlowPath = "");
	
	///��ȡϵͳ�汾��
	///@param nMajorVersion ���汾��
	///@param nMinorVersion �Ӱ汾��
	///@return ϵͳ��ʶ�ַ���
	static const char *GetVersion(int &nMajorVersion, int &nMinorVersion);
	
	///ɾ���ӿڶ�����
	///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	virtual void Release() = 0;
	
	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	virtual void Init() = 0;
	
	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	virtual int Join() = 0;
	
	///��ȡ��ǰ������
	///@retrun ��ȡ���Ľ�����
	///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
	virtual const char *GetTradingDay() = 0;
	
	///ע��ǰ�û������ַ
	///@param pszFrontAddress��ǰ�û������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///ע�����ַ����������ַ
	///@param pszNsAddress�����ַ����������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
	///@remark RegisterFront������RegisterNameServer
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	///ע��ص��ӿ�
	///@param pSpi �����Իص��ӿ����ʵ��
	virtual void RegisterSpi(CShfeFtdcMduserSpi *pSpi) = 0;
	
	///����֤��
	///@param pszCertFileName �û�֤���ļ���
	///@param pszKeyFileName �û�˽Կ�ļ���
	///@param pszCaFileName ������CA֤���ļ���
	///@param pszKeyFilePassword �û�˽Կ�ļ�����
	///@return 0 �����ɹ�
	///@return -1 ������CA֤������ʧ��
	///@return -2 �û�֤������ʧ��
	///@return -3 �û�˽Կ����ʧ��	
	///@return -4 �û�֤��У��ʧ��
	virtual int RegisterCertificateFile(const char *pszCertFileName, const char *pszKeyFileName, 
		const char *pszCaFileName, const char *pszKeyFilePassword) = 0;
		
	///���ع���֤��
	///@param pszCAFileName ������֤�����CA֤���ļ���
	///@param pszSigCertFileName �û�ǩ��֤���ļ�����
	///@param pszSigKeyFileName �û�ǩ��֤��˽Կ�ļ���
	///@param pszSigKeyFilePassword �û�ǩ��֤��˽Կ�ļ�����
	///@param pszEncCertFileName �û�����֤���ļ�����
	///@param pszEncKeyFileName �û�����֤��˽Կ�ļ���
	///@param pszEncKeyFilePassword �û�����֤��˽Կ�ļ�����
	///@return 0 �����ɹ�
	///@return -1 ������CA֤������ʧ��
	///@return -2 �û�ǩ��֤������ʧ��
	///@return -3 �û�ǩ��˽Կ����ʧ��	
	///@return -4 �û�ǩ��֤��У��ʧ��
	///@return -5 �û�����֤������ʧ��
	///@return -6 �û�����˽Կ����ʧ��	
	///@return -7 �û�����֤��У��ʧ��
	virtual int RegisterGMCertificateFile(const char *pszCAFileName, 
		const char *pszSigCertFileName, const char *pszSigKeyFileName, const char *pszSigKeyFilePassword, 
		const char *pszEncCertFileName, const char *pszEncKeyFileName, const char *pszEncKeyFilePassword) = 0;
				
	///ע������㷨
	///@param pszKeyFileName ��Կ�ļ�
	///@param pszKeyFilePassword ��Կ�ļ�����
	///@param nEncryptType ��Կ����
	///@return 0 �����ɹ�
	///@return -1 ��ȡ��Կ�ļ�ʧ��
	///@return -2 �û���Կ����ʧ��
	///@return -3 ��֧�ֵ��㷨����
	virtual int RegisterCryptAlgorithm(const char* pszKeyFileName, const char *pszKeyFilePassword, 
		TShfeFtdcEncryptTypeType nEncryptType = SHFE_FTDC_ET_RSA) = 0;
		
	///�����г����顣
	///@param nTopicID �г���������  
	///@param nResumeType �г������ش���ʽ  
	///        TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        TERT_RESUME:���ϴ��յ�������
	///        TERT_QUICK:�ȴ��͵�ǰ�������,�ٴ��͵�¼���г����������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�˽���������ݡ�
	virtual void SubscribeMarketDataTopic(int nTopicID, TE_RESUME_TYPE nResumeType) = 0;

	///����������ʱʱ�䡣
	///@param timeout ������ʱʱ��(��)  
	virtual void SetHeartbeatTimeout(unsigned int timeout) = 0;


	///�û���¼����
	virtual int ReqUserLogin(CShfeFtdcReqUserLoginField *pReqUserLogin, int nRequestID) = 0;

	///�û��˳�����
	virtual int ReqUserLogout(CShfeFtdcReqUserLogoutField *pReqUserLogout, int nRequestID) = 0;

	///������������
	virtual int ReqSubscribeTopic(CShfeFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///�����ѯ����
	virtual int ReqQryTopic(CShfeFtdcDisseminationField *pDissemination, int nRequestID) = 0;
protected:
	~CShfeFtdcMduserApi(){};
};

#endif
