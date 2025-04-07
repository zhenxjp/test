/////////////////////////////////////////////////////////////////////////
///@system ��һ��������ϵͳ
///@company �Ϻ��ڻ���Ϣ�������޹�˾
///@file FtdcTraderApi.h
///@brief �����˿ͻ��˽ӿ�
///@history 
///20060106	�Ժ��		�������ļ�
///20151218	����		NT-0286-API������֤
///20181023	���� 		NT-0358-���ӶԽ����ն˲ɼ���Ϣ��֧��
///20181106	����		NT-0350-�滻openssl��֧�ֹ����㷨
/////////////////////////////////////////////////////////////////////////

#if !defined(_FTDCTRADERAPI_H)
#define _FTDCTRADERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport)
#else
#define TRADER_API_EXPORT __declspec(dllimport)
#endif
#else
#if defined(LIB_TRADER_API_EXPORT) && defined(ISLIB) && defined(UNIX)
#define TRADER_API_EXPORT  __attribute__ ((visibility("default")))
#else
#define TRADER_API_EXPORT
#endif 
#endif

class CShfeFtdcTraderSpi
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

	///����¼��Ӧ��
	virtual void OnRspOrderInsert(CShfeFtdcInputOrderField *pInputOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������Ӧ��
	virtual void OnRspOrderAction(CShfeFtdcOrderActionField *pOrderAction, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����¼��Ӧ��
	virtual void OnRspQuoteInsert(CShfeFtdcInputQuoteField *pInputQuote, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///���۲���Ӧ��
	virtual void OnRspQuoteAction(CShfeFtdcQuoteActionField *pQuoteAction, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�û������޸�Ӧ��
	virtual void OnRspUserPasswordUpdate(CShfeFtdcUserPasswordUpdateField *pUserPasswordUpdate, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///ִ������¼��Ӧ��
	virtual void OnRspExecOrderInsert(CShfeFtdcInputExecOrderField *pInputExecOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///ִ���������Ӧ��
	virtual void OnRspExecOrderAction(CShfeFtdcExecOrderActionField *pExecOrderAction, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///������¼��Ӧ��
	virtual void OnRspAdminOrderInsert(CShfeFtdcInputAdminOrderField *pInputAdminOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�Ǳ���ϱ���¼��Ӧ��
	virtual void OnRspCombOrderInsert(CShfeFtdcInputCombOrderField *pInputCombOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����ִ������¼��Ӧ��
	virtual void OnRspAbandonExecOrderInsert(CShfeFtdcInputAbandonExecOrderField *pInputAbandonExecOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����ִ���������Ӧ��
	virtual void OnRspAbandonExecOrderAction(CShfeFtdcAbandonExecOrderActionField *pAbandonExecOrderAction, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///ѯ��¼��Ӧ��
	virtual void OnRspQuoteDemand(CShfeFtdcQuoteDemandInfoField *pQuoteDemandInfo, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������Ӧ��
	virtual void OnRspSubscribeTopic(CShfeFtdcDisseminationField *pDissemination, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Ա�ʽ��ѯӦ��
	virtual void OnRspQryPartAccount(CShfeFtdcRspPartAccountField *pRspPartAccount, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///������ѯӦ��
	virtual void OnRspQryOrder(CShfeFtdcOrderField *pOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///���۲�ѯӦ��
	virtual void OnRspQryQuote(CShfeFtdcQuoteField *pQuote, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ɽ�����ѯӦ��
	virtual void OnRspQryTrade(CShfeFtdcTradeField *pTrade, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Ա�ͻ���ѯӦ��
	virtual void OnRspQryClient(CShfeFtdcRspClientField *pRspClient, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Ա�ֲֲ�ѯӦ��
	virtual void OnRspQryPartPosition(CShfeFtdcRspPartPositionField *pRspPartPosition, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ͻ��ֲֲ�ѯӦ��
	virtual void OnRspQryClientPosition(CShfeFtdcRspClientPositionField *pRspClientPosition, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Լ��ѯӦ��
	virtual void OnRspQryInstrument(CShfeFtdcRspInstrumentField *pRspInstrument, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Լ����״̬��ѯӦ��
	virtual void OnRspQryInstrumentStatus(CShfeFtdcInstrumentStatusField *pInstrumentStatus, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��ֵ���Ӧ��
	virtual void OnRspQryHedgeVolume(CShfeFtdcHedgeVolumeField *pHedgeVolume, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����޶��ѯӦ��
	virtual void OnRspQryCreditLimit(CShfeFtdcCreditLimitField *pCreditLimit, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�Ǳ���ϱ�����ѯӦ��
	virtual void OnRspQryCombOrder(CShfeFtdcCombOrderField *pCombOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///ִ�������ѯӦ��
	virtual void OnRspQryExecOrder(CShfeFtdcExecOrderField *pExecOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����ִ�������ѯӦ��
	virtual void OnRspQryAbandonExecOrder(CShfeFtdcAbandonExecOrderField *pAbandonExecOrder, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��ͨ�����ѯӦ��
	virtual void OnRspQryMarketData(CShfeFtdcMarketDataField *pMarketData, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����������ѯ����Ӧ��
	virtual void OnRspQryBulletin(CShfeFtdcBulletinField *pBulletin, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯӦ��
	virtual void OnRspQryTopic(CShfeFtdcDisseminationField *pDissemination, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Լ��λ��ѯӦ��
	virtual void OnRspQryMBLMarketData(CShfeFtdcMBLMarketDataField *pMBLMarketData, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Ϣ��ѯӦ��
	virtual void OnRspQryInformation(CShfeFtdcInformationField *pInformation, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ɽ��ر�
	virtual void OnRtnTrade(CShfeFtdcTradeField *pTrade) {};

	///�����ر�
	virtual void OnRtnOrder(CShfeFtdcOrderField *pOrder) {};

	///ִ������ر�
	virtual void OnRtnExecOrder(CShfeFtdcExecOrderField *pExecOrder) {};

	///���ۻر�
	virtual void OnRtnQuote(CShfeFtdcQuoteField *pQuote) {};

	///�Ǳ���ϱ����ر�
	virtual void OnRtnCombOrder(CShfeFtdcCombOrderField *pCombOrder) {};

	///����ִ������ر�
	virtual void OnRtnAbandonExecOrder(CShfeFtdcAbandonExecOrderField *pAbandonExecOrder) {};

	///��Լ����״̬֪ͨ
	virtual void OnRtnInstrumentStatus(CShfeFtdcInstrumentStatusField *pInstrumentStatus) {};

	///���Ӻ�Լ֪ͨ
	virtual void OnRtnInsInstrument(CShfeFtdcInstrumentField *pInstrument) {};

	///ɾ����Լ֪ͨ
	virtual void OnRtnDelInstrument(CShfeFtdcInstrumentField *pInstrument) {};

	///���Ӻ�Լ����֪ͨ
	virtual void OnRtnInsCombinationLeg(CShfeFtdcCombinationLegField *pCombinationLeg) {};

	///ɾ����Լ����֪ͨ
	virtual void OnRtnDelCombinationLeg(CShfeFtdcCombinationLegField *pCombinationLeg) {};

	///��������֪ͨ
	virtual void OnRtnAliasDefine(CShfeFtdcAliasDefineField *pAliasDefine) {};

	///����������֪ͨ
	virtual void OnRtnFlowMessageCancel(CShfeFtdcFlowMessageCancelField *pFlowMessageCancel) {};

	///����֪ͨ
	virtual void OnRtnBulletin(CShfeFtdcBulletinField *pBulletin) {};

	///����¼�����ر�
	virtual void OnErrRtnOrderInsert(CShfeFtdcInputOrderField *pInputOrder, CShfeFtdcRspInfoField *pRspInfo) {};

	///������������ر�
	virtual void OnErrRtnOrderAction(CShfeFtdcOrderActionField *pOrderAction, CShfeFtdcRspInfoField *pRspInfo) {};

	///����¼�����ر�
	virtual void OnErrRtnQuoteInsert(CShfeFtdcInputQuoteField *pInputQuote, CShfeFtdcRspInfoField *pRspInfo) {};

	///���۲�������ر�
	virtual void OnErrRtnQuoteAction(CShfeFtdcQuoteActionField *pQuoteAction, CShfeFtdcRspInfoField *pRspInfo) {};

	///ִ������¼�����ر�
	virtual void OnErrRtnExecOrderInsert(CShfeFtdcInputExecOrderField *pInputExecOrder, CShfeFtdcRspInfoField *pRspInfo) {};

	///ִ�������������ر�
	virtual void OnErrRtnExecOrderAction(CShfeFtdcExecOrderActionField *pExecOrderAction, CShfeFtdcRspInfoField *pRspInfo) {};

	///�Ǳ���ϱ���¼�����ر�
	virtual void OnErrRtnCombOrderInsert(CShfeFtdcInputCombOrderField *pInputCombOrder, CShfeFtdcRspInfoField *pRspInfo) {};

	///����ִ������¼�����ر�
	virtual void OnErrRtnAbandonExecOrderInsert(CShfeFtdcInputAbandonExecOrderField *pInputAbandonExecOrder, CShfeFtdcRspInfoField *pRspInfo) {};

	///����ִ�������������ر�
	virtual void OnErrRtnAbandonExecOrderAction(CShfeFtdcAbandonExecOrderActionField *pAbandonExecOrderAction, CShfeFtdcRspInfoField *pRspInfo) {};

	///ѯ������ַ�
	virtual void OnRtnQuoteDemandNotify(CShfeFtdcQuoteDemandNotifyField *pQuoteDemandNotify) {};

	///���ʲ�ѯӦ��
	virtual void OnRspQryExchangeRate(CShfeFtdcRspExchangeRateField *pRspExchangeRate, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Ȩ�ԶԳ����Ӧ��
	virtual void OnRspOptionSelfCloseUpdate(CShfeFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Ȩ�ԶԳ���´���ر�
	virtual void OnErrRtnOptionSelfCloseUpdate(CShfeFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CShfeFtdcRspInfoField *pRspInfo) {};

	///��Ȩ�ԶԳ���»ر�
	virtual void OnRtnOptionSelfCloseUpdate(CShfeFtdcOptionSelfCloseField *pOptionSelfClose) {};

	///��Ȩ�ԶԳ����Ӧ��
	virtual void OnRspOptionSelfCloseAction(CShfeFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Ȩ�ԶԳ��������ر�
	virtual void OnErrRtnOptionSelfCloseAction(CShfeFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CShfeFtdcRspInfoField *pRspInfo) {};

	///ִ��Ȩ�ԶԳ��ѯӦ��
	virtual void OnRspQryOptionSelfClose(CShfeFtdcOptionSelfCloseField *pOptionSelfClose, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ն���֤Ӧ��
	virtual void OnRspAuthenticate(CShfeFtdcProductAuthField *pProductAuth, CShfeFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
};

class TRADER_API_EXPORT CShfeFtdcTraderApi
{
public:
	///����TraderApi
	///@param pszFlowPath ����������Ϣ�ļ���Ŀ¼��Ĭ��Ϊ��ǰĿ¼
	///@return ��������UserApi
	static CShfeFtdcTraderApi *CreateFtdcTraderApi(const char *pszFlowPath = "");
	
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
	virtual void RegisterSpi(CShfeFtdcTraderSpi *pSpi) = 0;
	
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
		
	///����˽������
	///@param nResumeType ˽�����ش���ʽ  
	///        TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        TERT_RESUME:���ϴ��յ�������
	///        TERT_QUICK:ֻ���͵�¼��˽����������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�˽���������ݡ�
	virtual void SubscribePrivateTopic(TE_RESUME_TYPE nResumeType) = 0;
	
	///���Ĺ�������
	///@param nResumeType �������ش���ʽ  
	///        TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        TERT_RESUME:���ϴ��յ�������
	///        TERT_QUICK:ֻ���͵�¼�󹫹���������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ������������ݡ�
	virtual void SubscribePublicTopic(TE_RESUME_TYPE nResumeType) = 0;

	///���Ľ���Ա����
	///@param nResumeType ����Ա���ش���ʽ  
	///        TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        TERT_RESUME:���ϴ��յ�������
	///        TERT_QUICK:ֻ���͵�¼����Ա��������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�����Ա�������ݡ�
	virtual void SubscribeUserTopic(TE_RESUME_TYPE nResumeType) = 0;
	
	///����������ʱʱ�䡣
	///@param timeout ������ʱʱ��(��)  
	virtual void SetHeartbeatTimeout(unsigned int timeout) = 0;
	
	///��������־�ļ�
	///@param pszReqLogFileName ������־�ļ���  
	///@return 0 �����ɹ�
	///@return -1 ����־�ļ�ʧ��
	virtual int OpenRequestLog(const char *pszReqLogFileName) = 0;

	///��Ӧ����־�ļ�
	///@param pszRspLogFileName Ӧ����־�ļ���  
	///@return 0 �����ɹ�
	///@return -1 ����־�ļ�ʧ��
	virtual int OpenResponseLog(const char *pszRspLogFileName) = 0;


	///�û���¼����
	virtual int ReqUserLogin(CShfeFtdcReqUserLoginField *pReqUserLogin, int nRequestID) = 0;

	///�û��˳�����
	virtual int ReqUserLogout(CShfeFtdcReqUserLogoutField *pReqUserLogout, int nRequestID) = 0;

	///����¼������
	virtual int ReqOrderInsert(CShfeFtdcInputOrderField *pInputOrder, int nRequestID) = 0;

	///������������
	virtual int ReqOrderAction(CShfeFtdcOrderActionField *pOrderAction, int nRequestID) = 0;

	///����¼������
	virtual int ReqQuoteInsert(CShfeFtdcInputQuoteField *pInputQuote, int nRequestID) = 0;

	///���۲�������
	virtual int ReqQuoteAction(CShfeFtdcQuoteActionField *pQuoteAction, int nRequestID) = 0;

	///�û������޸�����
	virtual int ReqUserPasswordUpdate(CShfeFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) = 0;

	///ִ������¼������
	virtual int ReqExecOrderInsert(CShfeFtdcInputExecOrderField *pInputExecOrder, int nRequestID) = 0;

	///ִ�������������
	virtual int ReqExecOrderAction(CShfeFtdcExecOrderActionField *pExecOrderAction, int nRequestID) = 0;

	///������¼������
	virtual int ReqAdminOrderInsert(CShfeFtdcInputAdminOrderField *pInputAdminOrder, int nRequestID) = 0;

	///�Ǳ���ϱ���¼������
	virtual int ReqCombOrderInsert(CShfeFtdcInputCombOrderField *pInputCombOrder, int nRequestID) = 0;

	///����ִ������¼������
	virtual int ReqAbandonExecOrderInsert(CShfeFtdcInputAbandonExecOrderField *pInputAbandonExecOrder, int nRequestID) = 0;

	///����ִ�������������
	virtual int ReqAbandonExecOrderAction(CShfeFtdcAbandonExecOrderActionField *pAbandonExecOrderAction, int nRequestID) = 0;

	///ѯ��¼������
	virtual int ReqQuoteDemand(CShfeFtdcInputQuoteDemandField *pInputQuoteDemand, int nRequestID) = 0;

	///������������
	virtual int ReqSubscribeTopic(CShfeFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///��Ա�ʽ��ѯ����
	virtual int ReqQryPartAccount(CShfeFtdcQryPartAccountField *pQryPartAccount, int nRequestID) = 0;

	///������ѯ����
	virtual int ReqQryOrder(CShfeFtdcQryOrderField *pQryOrder, int nRequestID) = 0;

	///���۲�ѯ����
	virtual int ReqQryQuote(CShfeFtdcQryQuoteField *pQryQuote, int nRequestID) = 0;

	///�ɽ�����ѯ����
	virtual int ReqQryTrade(CShfeFtdcQryTradeField *pQryTrade, int nRequestID) = 0;

	///��Ա�ͻ���ѯ����
	virtual int ReqQryClient(CShfeFtdcQryClientField *pQryClient, int nRequestID) = 0;

	///��Ա�ֲֲ�ѯ����
	virtual int ReqQryPartPosition(CShfeFtdcQryPartPositionField *pQryPartPosition, int nRequestID) = 0;

	///�ͻ��ֲֲ�ѯ����
	virtual int ReqQryClientPosition(CShfeFtdcQryClientPositionField *pQryClientPosition, int nRequestID) = 0;

	///��Լ��ѯ����
	virtual int ReqQryInstrument(CShfeFtdcQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///��Լ����״̬��ѯ����
	virtual int ReqQryInstrumentStatus(CShfeFtdcQryInstrumentStatusField *pQryInstrumentStatus, int nRequestID) = 0;

	///��ֵ��Ȳ�ѯ
	virtual int ReqQryHedgeVolume(CShfeFtdcQryHedgeVolumeField *pQryHedgeVolume, int nRequestID) = 0;

	///�����޶��ѯ����
	virtual int ReqQryCreditLimit(CShfeFtdcQryCreditLimitField *pQryCreditLimit, int nRequestID) = 0;

	///�Ǳ���ϱ�����ѯ����
	virtual int ReqQryCombOrder(CShfeFtdcQryCombOrderField *pQryCombOrder, int nRequestID) = 0;

	///ִ�������ѯ����
	virtual int ReqQryExecOrder(CShfeFtdcQryExecOrderField *pQryExecOrder, int nRequestID) = 0;

	///����ִ�������ѯ����
	virtual int ReqQryAbandonExecOrder(CShfeFtdcQryAbandonExecOrderField *pQryAbandonExecOrder, int nRequestID) = 0;

	///��ͨ�����ѯ����
	virtual int ReqQryMarketData(CShfeFtdcQryMarketDataField *pQryMarketData, int nRequestID) = 0;

	///�����������ѯ����
	virtual int ReqQryBulletin(CShfeFtdcQryBulletinField *pQryBulletin, int nRequestID) = 0;

	///�����ѯ����
	virtual int ReqQryTopic(CShfeFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///��Լ��λ��ѯ
	virtual int ReqQryMBLMarketData(CShfeFtdcQryMBLMarketDataField *pQryMBLMarketData, int nRequestID) = 0;

	///��Ϣ��ѯ
	virtual int ReqQryInformation(CShfeFtdcQryInformationField *pQryInformation, int nRequestID) = 0;

	///���ʲ�ѯ����
	virtual int ReqQryExchangeRate(CShfeFtdcQryExchangeRateField *pQryExchangeRate, int nRequestID) = 0;

	///��Ȩ�ԶԳ��������
	virtual int ReqOptionSelfCloseUpdate(CShfeFtdcInputOptionSelfCloseField *pInputOptionSelfClose, int nRequestID) = 0;

	///��Ȩ�ԶԳ��������
	virtual int ReqOptionSelfCloseAction(CShfeFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, int nRequestID) = 0;

	///��Ȩ�ԶԳ��ѯ����
	virtual int ReqQryOptionSelfClose(CShfeFtdcQryOptionSelfCloseField *pQryOptionSelfClose, int nRequestID) = 0;

	///�ն���֤����
	virtual int ReqAuthenticate(CShfeFtdcProductAuthField *pProductAuth, int nRequestID) = 0;
protected:
	~CShfeFtdcTraderApi(){};
};

#endif
