/////////////////////////////////////////////////////////////////////////
///@system 新一代交易所系统
///@company 上海期货信息技术有限公司
///@file FtdcUserApiStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
///20060106	赵鸿昊		创建该文件
///20151218	冯光成		NT-0286-API增加认证
/////////////////////////////////////////////////////////////////////////

#if !defined(_FTDCSTRUCT_H)
#define _FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FtdcUserApiDataType.h"

///信息分发
struct CShfeFtdcDisseminationField
{
	///序列系列号
	TShfeFtdcSequenceSeriesType	SequenceSeries;
	///序列号
	TShfeFtdcSequenceNoType	SequenceNo;
};

///响应信息
struct CShfeFtdcRspInfoField
{
	///错误代码
	TShfeFtdcErrorIDType	ErrorID;
	///错误信息
	TShfeFtdcErrorMsgType	ErrorMsg;
};

///用户登录请求
struct CShfeFtdcReqUserLoginField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///密码
	TShfeFtdcPasswordType	Password;
	///用户端产品信息
	TShfeFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TShfeFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TShfeFtdcProtocolInfoType	ProtocolInfo;
	///数据中心代码
	TShfeFtdcDataCenterIDType	DataCenterID;
};

///用户登录应答
struct CShfeFtdcRspUserLoginField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///登录成功时间
	TShfeFtdcTimeType	LoginTime;
	///最大本地报单号
	TShfeFtdcOrderLocalIDType	MaxOrderLocalID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///交易系统名称
	TShfeFtdcTradingSystemNameType	TradingSystemName;
	///数据中心代码
	TShfeFtdcDataCenterIDType	DataCenterID;
	///会员私有流当前长度
	TShfeFtdcSequenceNoType	PrivateFlowSize;
	///交易员私有流当前长度
	TShfeFtdcSequenceNoType	UserFlowSize;
	///业务发生日期
	TShfeFtdcDateType	ActionDay;
};

///用户登出请求
struct CShfeFtdcReqUserLogoutField
{
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
};

///用户登出应答
struct CShfeFtdcRspUserLogoutField
{
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
};

///输入报单
struct CShfeFtdcInputOrderField
{
	///报单编号
	TShfeFtdcOrderSysIDType	OrderSysID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///报单价格条件
	TShfeFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TShfeFtdcDirectionType	Direction;
	///组合开平标志
	TShfeFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TShfeFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TShfeFtdcPriceType	LimitPrice;
	///数量
	TShfeFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TShfeFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TShfeFtdcDateType	GTDDate;
	///成交量类型
	TShfeFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TShfeFtdcVolumeType	MinVolume;
	///触发条件
	TShfeFtdcContingentConditionType	ContingentCondition;
	///止损价
	TShfeFtdcPriceType	StopPrice;
	///强平原因
	TShfeFtdcForceCloseReasonType	ForceCloseReason;
	///本地报单编号
	TShfeFtdcOrderLocalIDType	OrderLocalID;
	///自动挂起标志
	TShfeFtdcBoolType	IsAutoSuspend;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
};

///报单操作
struct CShfeFtdcOrderActionField
{
	///报单编号
	TShfeFtdcOrderSysIDType	OrderSysID;
	///本地报单编号
	TShfeFtdcOrderLocalIDType	OrderLocalID;
	///报单操作标志
	TShfeFtdcActionFlagType	ActionFlag;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///价格
	TShfeFtdcPriceType	LimitPrice;
	///数量变化
	TShfeFtdcVolumeType	VolumeChange;
	///操作本地编号
	TShfeFtdcOrderLocalIDType	ActionLocalID;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
};

///输入报价
struct CShfeFtdcInputQuoteField
{
	///报价编号
	TShfeFtdcQuoteSysIDType	QuoteSysID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///数量
	TShfeFtdcVolumeType	Volume;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///本地报价编号
	TShfeFtdcOrderLocalIDType	QuoteLocalID;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///买方组合开平标志
	TShfeFtdcCombOffsetFlagType	BidCombOffsetFlag;
	///买方组合套保标志
	TShfeFtdcCombHedgeFlagType	BidCombHedgeFlag;
	///买方价格
	TShfeFtdcPriceType	BidPrice;
	///卖方组合开平标志
	TShfeFtdcCombOffsetFlagType	AskCombOffsetFlag;
	///卖方组合套保标志
	TShfeFtdcCombHedgeFlagType	AskCombHedgeFlag;
	///卖方价格
	TShfeFtdcPriceType	AskPrice;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
	///询价编号
	TShfeFtdcOrderSysIDType	QuoteDemandID;
};

///报价操作
struct CShfeFtdcQuoteActionField
{
	///报价编号
	TShfeFtdcQuoteSysIDType	QuoteSysID;
	///本地报价编号
	TShfeFtdcOrderLocalIDType	QuoteLocalID;
	///报单操作标志
	TShfeFtdcActionFlagType	ActionFlag;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///操作本地编号
	TShfeFtdcOrderLocalIDType	ActionLocalID;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
};

///输入执行宣告
struct CShfeFtdcInputExecOrderField
{
	///合约编号
	TShfeFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///本地执行宣告编号
	TShfeFtdcOrderLocalIDType	ExecOrderLocalID;
	///数量
	TShfeFtdcVolumeType	Volume;
	///开平标志
	TShfeFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TShfeFtdcHedgeFlagType	HedgeFlag;
	///持仓方向
	TShfeFtdcPosiDirectionType	PosiDirection;
	///期权行权后是否保留期货头寸的标记
	TShfeFtdcExecOrderPositionFlagType	ReservePositionFlag;
	///期权行权后生成的期货头寸是否自对冲
	TShfeFtdcExecOrderCloseFlagType	CloseFlag;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
};

///执行宣告操作
struct CShfeFtdcExecOrderActionField
{
	///执行宣告编号
	TShfeFtdcExecOrderSysIDType	ExecOrderSysID;
	///本地执行宣告编号
	TShfeFtdcOrderLocalIDType	ExecOrderLocalID;
	///报单操作标志
	TShfeFtdcActionFlagType	ActionFlag;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///操作本地编号
	TShfeFtdcOrderLocalIDType	ActionLocalID;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
};

///输入放弃执行宣告
struct CShfeFtdcInputAbandonExecOrderField
{
	///合约编号
	TShfeFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///本地放弃执行宣告编号
	TShfeFtdcOrderLocalIDType	AbandonExecOrderLocalID;
	///数量
	TShfeFtdcVolumeType	Volume;
	///开平标志
	TShfeFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TShfeFtdcHedgeFlagType	HedgeFlag;
	///申请放弃的头寸方向
	TShfeFtdcPosiDirectionType	PosiDirection;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
};

///放弃执行宣告操作
struct CShfeFtdcAbandonExecOrderActionField
{
	///放弃执行宣告编号
	TShfeFtdcExecOrderSysIDType	AbandonExecOrderSysID;
	///本地放弃执行宣告编号
	TShfeFtdcOrderLocalIDType	AbandonExecOrderLocalID;
	///报单操作标志
	TShfeFtdcActionFlagType	ActionFlag;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///操作本地编号
	TShfeFtdcOrderLocalIDType	ActionLocalID;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
};

///用户口令修改
struct CShfeFtdcUserPasswordUpdateField
{
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///旧密码
	TShfeFtdcPasswordType	OldPassword;
	///新密码
	TShfeFtdcPasswordType	NewPassword;
};

///输入非标组合报单
struct CShfeFtdcInputCombOrderField
{
	///组合报单编号
	TShfeFtdcOrderSysIDType	CombOrderSysID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///价格
	TShfeFtdcPriceType	LimitPrice;
	///数量
	TShfeFtdcVolumeType	VolumeTotalOriginal;
	///本地报单编号
	TShfeFtdcOrderLocalIDType	CombOrderLocalID;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///合约代码1
	TShfeFtdcInstrumentIDType	InstrumentID1;
	///买卖方向1
	TShfeFtdcDirectionType	Direction1;
	///分腿乘数1
	TShfeFtdcLegMultipleType	LegMultiple1;
	///开平标志1
	TShfeFtdcOffsetFlagType	OffsetFlag1;
	///投机套保标志1
	TShfeFtdcHedgeFlagType	HedgeFlag1;
	///合约代码2
	TShfeFtdcInstrumentIDType	InstrumentID2;
	///买卖方向2
	TShfeFtdcDirectionType	Direction2;
	///分腿乘数2
	TShfeFtdcLegMultipleType	LegMultiple2;
	///开平标志2
	TShfeFtdcOffsetFlagType	OffsetFlag2;
	///投机套保标志2
	TShfeFtdcHedgeFlagType	HedgeFlag2;
	///合约代码3
	TShfeFtdcInstrumentIDType	InstrumentID3;
	///买卖方向3
	TShfeFtdcDirectionType	Direction3;
	///分腿乘数3
	TShfeFtdcLegMultipleType	LegMultiple3;
	///开平标志3
	TShfeFtdcOffsetFlagType	OffsetFlag3;
	///投机套保标志3
	TShfeFtdcHedgeFlagType	HedgeFlag3;
	///合约代码4
	TShfeFtdcInstrumentIDType	InstrumentID4;
	///买卖方向4
	TShfeFtdcDirectionType	Direction4;
	///分腿乘数4
	TShfeFtdcLegMultipleType	LegMultiple4;
	///开平标志4
	TShfeFtdcOffsetFlagType	OffsetFlag4;
	///投机套保标志4
	TShfeFtdcHedgeFlagType	HedgeFlag4;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
};

///报单查询
struct CShfeFtdcQryOrderField
{
	///起始会员代码
	TShfeFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TShfeFtdcParticipantIDType	PartIDEnd;
	///报单编号
	TShfeFtdcOrderSysIDType	OrderSysID;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///开始时间
	TShfeFtdcTimeType	TimeStart;
	///结束时间
	TShfeFtdcTimeType	TimeEnd;
};

///报价查询
struct CShfeFtdcQryQuoteField
{
	///起始会员代码
	TShfeFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TShfeFtdcParticipantIDType	PartIDEnd;
	///报价编号
	TShfeFtdcQuoteSysIDType	QuoteSysID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
};

///成交查询
struct CShfeFtdcQryTradeField
{
	///起始会员代码
	TShfeFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TShfeFtdcParticipantIDType	PartIDEnd;
	///起始合约代码
	TShfeFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TShfeFtdcInstrumentIDType	InstIDEnd;
	///成交编号
	TShfeFtdcTradeIDType	TradeID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///开始时间
	TShfeFtdcTimeType	TimeStart;
	///结束时间
	TShfeFtdcTimeType	TimeEnd;
};

///行情查询
struct CShfeFtdcQryMarketDataField
{
	///产品代码
	TShfeFtdcProductIDType	ProductID;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
};

///客户查询
struct CShfeFtdcQryClientField
{
	///起始会员代码
	TShfeFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TShfeFtdcParticipantIDType	PartIDEnd;
	///起始客户代码
	TShfeFtdcClientIDType	ClientIDStart;
	///结束客户代码
	TShfeFtdcClientIDType	ClientIDEnd;
};

///会员持仓查询
struct CShfeFtdcQryPartPositionField
{
	///起始会员代码
	TShfeFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TShfeFtdcParticipantIDType	PartIDEnd;
	///起始合约代码
	TShfeFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TShfeFtdcInstrumentIDType	InstIDEnd;
};

///客户持仓查询
struct CShfeFtdcQryClientPositionField
{
	///起始会员代码
	TShfeFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TShfeFtdcParticipantIDType	PartIDEnd;
	///起始客户代码
	TShfeFtdcClientIDType	ClientIDStart;
	///结束客户代码
	TShfeFtdcClientIDType	ClientIDEnd;
	///起始合约代码
	TShfeFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TShfeFtdcInstrumentIDType	InstIDEnd;
	///客户类型
	TShfeFtdcClientTypeType	ClientType;
};

///交易资金查询
struct CShfeFtdcQryPartAccountField
{
	///起始会员代码
	TShfeFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TShfeFtdcParticipantIDType	PartIDEnd;
	///资金帐号
	TShfeFtdcAccountIDType	AccountID;
};

///合约查询
struct CShfeFtdcQryInstrumentField
{
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///产品组代码
	TShfeFtdcProductGroupIDType	ProductGroupID;
	///产品代码
	TShfeFtdcProductIDType	ProductID;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
};

///合约状态查询
struct CShfeFtdcQryInstrumentStatusField
{
	///起始合约代码
	TShfeFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TShfeFtdcInstrumentIDType	InstIDEnd;
};

///公告查询
struct CShfeFtdcQryBulletinField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///市场代码
	TShfeFtdcMarketIDType	MarketID;
	///公告编号
	TShfeFtdcBulletinIDType	BulletinID;
	///公告类型
	TShfeFtdcNewsTypeType	NewsType;
	///紧急程度
	TShfeFtdcNewsUrgencyType	NewsUrgency;
};

///保值额度查询
struct CShfeFtdcQryHedgeVolumeField
{
	///起始会员代码
	TShfeFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TShfeFtdcParticipantIDType	PartIDEnd;
	///起始客户代码
	TShfeFtdcClientIDType	ClientIDStart;
	///结束客户代码
	TShfeFtdcClientIDType	ClientIDEnd;
	///起始合约代码
	TShfeFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TShfeFtdcInstrumentIDType	InstIDEnd;
};

///合约价位查询
struct CShfeFtdcQryMBLMarketDataField
{
	///起始合约代码
	TShfeFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TShfeFtdcInstrumentIDType	InstIDEnd;
	///买卖方向
	TShfeFtdcDirectionType	Direction;
};

///信用限额查询
struct CShfeFtdcQryCreditLimitField
{
	///交易会员编号
	TShfeFtdcParticipantIDType	ParticipantID;
	///结算会员编号
	TShfeFtdcParticipantIDType	ClearingPartID;
};

///执行宣告查询
struct CShfeFtdcQryExecOrderField
{
	///起始会员代码
	TShfeFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TShfeFtdcParticipantIDType	PartIDEnd;
	///执行宣告编号
	TShfeFtdcExecOrderSysIDType	ExecOrderSysID;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///开始时间
	TShfeFtdcTimeType	TimeStart;
	///结束时间
	TShfeFtdcTimeType	TimeEnd;
};

///放弃执行宣告查询
struct CShfeFtdcQryAbandonExecOrderField
{
	///起始会员代码
	TShfeFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TShfeFtdcParticipantIDType	PartIDEnd;
	///放弃执行宣告编号
	TShfeFtdcExecOrderSysIDType	AbandonExecOrderSysID;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///开始时间
	TShfeFtdcTimeType	TimeStart;
	///结束时间
	TShfeFtdcTimeType	TimeEnd;
};

///非标组合报单查询
struct CShfeFtdcQryCombOrderField
{
	///起始会员代码
	TShfeFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TShfeFtdcParticipantIDType	PartIDEnd;
	///组合报单编号
	TShfeFtdcOrderSysIDType	CombOrderSysID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
};

///会员资金应答
struct CShfeFtdcRspPartAccountField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TShfeFtdcSettlementIDType	SettlementID;
	///上次结算准备金
	TShfeFtdcMoneyType	PreBalance;
	///当前保证金总额
	TShfeFtdcMoneyType	CurrMargin;
	///平仓盈亏
	TShfeFtdcMoneyType	CloseProfit;
	///期权权利金收支
	TShfeFtdcMoneyType	Premium;
	///入金金额
	TShfeFtdcMoneyType	Deposit;
	///出金金额
	TShfeFtdcMoneyType	Withdraw;
	///期货结算准备金
	TShfeFtdcMoneyType	Balance;
	///可提资金
	TShfeFtdcMoneyType	Available;
	///资金帐号
	TShfeFtdcAccountIDType	AccountID;
	///冻结的保证金
	TShfeFtdcMoneyType	FrozenMargin;
	///冻结的权利金
	TShfeFtdcMoneyType	FrozenPremium;
	///基本准备金
	TShfeFtdcMoneyType	BaseReserve;
};

///会员持仓应答
struct CShfeFtdcRspPartPositionField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TShfeFtdcSettlementIDType	SettlementID;
	///投机套保标志
	TShfeFtdcHedgeFlagType	HedgeFlag;
	///持仓多空方向
	TShfeFtdcPosiDirectionType	PosiDirection;
	///上日持仓
	TShfeFtdcVolumeType	YdPosition;
	///今日持仓
	TShfeFtdcVolumeType	Position;
	///多头冻结
	TShfeFtdcVolumeType	LongFrozen;
	///空头冻结
	TShfeFtdcVolumeType	ShortFrozen;
	///昨日多头冻结
	TShfeFtdcVolumeType	YdLongFrozen;
	///昨日空头冻结
	TShfeFtdcVolumeType	YdShortFrozen;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///交易角色
	TShfeFtdcTradingRoleType	TradingRole;
};

///客户持仓应答
struct CShfeFtdcRspClientPositionField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TShfeFtdcSettlementIDType	SettlementID;
	///投机套保标志
	TShfeFtdcHedgeFlagType	HedgeFlag;
	///持仓多空方向
	TShfeFtdcPosiDirectionType	PosiDirection;
	///上日持仓
	TShfeFtdcVolumeType	YdPosition;
	///今日持仓
	TShfeFtdcVolumeType	Position;
	///多头冻结
	TShfeFtdcVolumeType	LongFrozen;
	///空头冻结
	TShfeFtdcVolumeType	ShortFrozen;
	///昨日多头冻结
	TShfeFtdcVolumeType	YdLongFrozen;
	///昨日空头冻结
	TShfeFtdcVolumeType	YdShortFrozen;
	///当日买成交量
	TShfeFtdcVolumeType	BuyTradeVolume;
	///当日卖成交量
	TShfeFtdcVolumeType	SellTradeVolume;
	///持仓成本
	TShfeFtdcMoneyType	PositionCost;
	///昨日持仓成本
	TShfeFtdcMoneyType	YdPositionCost;
	///占用的保证金
	TShfeFtdcMoneyType	UseMargin;
	///冻结的保证金
	TShfeFtdcMoneyType	FrozenMargin;
	///多头冻结的保证金
	TShfeFtdcMoneyType	LongFrozenMargin;
	///空头冻结的保证金
	TShfeFtdcMoneyType	ShortFrozenMargin;
	///冻结的权利金
	TShfeFtdcMoneyType	FrozenPremium;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
};

///合约查询应答
struct CShfeFtdcRspInstrumentField
{
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///产品代码
	TShfeFtdcProductIDType	ProductID;
	///产品组代码
	TShfeFtdcProductGroupIDType	ProductGroupID;
	///基础商品代码
	TShfeFtdcInstrumentIDType	UnderlyingInstrID;
	///产品类型
	TShfeFtdcProductClassType	ProductClass;
	///持仓类型
	TShfeFtdcPositionTypeType	PositionType;
	///执行价
	TShfeFtdcPriceType	StrikePrice;
	///期权类型
	TShfeFtdcOptionsTypeType	OptionsType;
	///合约数量乘数
	TShfeFtdcVolumeMultipleType	VolumeMultiple;
	///合约基础商品乘数
	TShfeFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///合约名称
	TShfeFtdcInstrumentNameType	InstrumentName;
	///交割年份
	TShfeFtdcYearType	DeliveryYear;
	///交割月
	TShfeFtdcMonthType	DeliveryMonth;
	///提前月份
	TShfeFtdcAdvanceMonthType	AdvanceMonth;
	///当前是否交易
	TShfeFtdcBoolType	IsTrading;
	///创建日
	TShfeFtdcDateType	CreateDate;
	///上市日
	TShfeFtdcDateType	OpenDate;
	///到期日
	TShfeFtdcDateType	ExpireDate;
	///开始交割日
	TShfeFtdcDateType	StartDelivDate;
	///最后交割日
	TShfeFtdcDateType	EndDelivDate;
	///挂牌基准价
	TShfeFtdcPriceType	BasisPrice;
	///市价单最大下单量
	TShfeFtdcVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TShfeFtdcVolumeType	MinMarketOrderVolume;
	///限价单最大下单量
	TShfeFtdcVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TShfeFtdcVolumeType	MinLimitOrderVolume;
	///最小变动价位
	TShfeFtdcPriceType	PriceTick;
	///交割月自然人开仓
	TShfeFtdcMonthCountType	AllowDelivPersonOpen;
	///币种代码
	TShfeFtdcCurrencyIDType	CurrencyID;
};

///信息查询
struct CShfeFtdcQryInformationField
{
	///起始信息代码
	TShfeFtdcInformationIDType	InformationIDStart;
	///结束信息代码
	TShfeFtdcInformationIDType	InformationIDEnd;
};

///信息查询
struct CShfeFtdcInformationField
{
	///信息编号
	TShfeFtdcInformationIDType	InformationID;
	///序列号
	TShfeFtdcSequenceNoType	SequenceNo;
	///消息正文
	TShfeFtdcContentType	Content;
	///正文长度
	TShfeFtdcContentLengthType	ContentLength;
	///是否完成
	TShfeFtdcBoolType	IsAccomplished;
};

///信用限额
struct CShfeFtdcCreditLimitField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TShfeFtdcSettlementIDType	SettlementID;
	///上次结算准备金
	TShfeFtdcMoneyType	PreBalance;
	///当前保证金总额
	TShfeFtdcMoneyType	CurrMargin;
	///平仓盈亏
	TShfeFtdcMoneyType	CloseProfit;
	///期权权利金收支
	TShfeFtdcMoneyType	Premium;
	///入金金额
	TShfeFtdcMoneyType	Deposit;
	///出金金额
	TShfeFtdcMoneyType	Withdraw;
	///期货结算准备金
	TShfeFtdcMoneyType	Balance;
	///可提资金
	TShfeFtdcMoneyType	Available;
	///交易会员编号
	TShfeFtdcParticipantIDType	ParticipantID;
	///结算会员编号
	TShfeFtdcParticipantIDType	ClearingPartID;
	///冻结的保证金
	TShfeFtdcMoneyType	FrozenMargin;
	///冻结的权利金
	TShfeFtdcMoneyType	FrozenPremium;
};

///客户查询应答
struct CShfeFtdcRspClientField
{
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///客户名称
	TShfeFtdcPartyNameType	ClientName;
	///证件类型
	TShfeFtdcIdCardTypeType	IdentifiedCardType;
	///原证件号码
	TShfeFtdcIdentifiedCardNoV1Type	UseLess;
	///交易角色
	TShfeFtdcTradingRoleType	TradingRole;
	///客户类型
	TShfeFtdcClientTypeType	ClientType;
	///是否活跃
	TShfeFtdcBoolType	IsActive;
	///会员号
	TShfeFtdcParticipantIDType	ParticipantID;
	///证件号码
	TShfeFtdcIdentifiedCardNoType	IdentifiedCardNo;
};

///数据流回退
struct CShfeFtdcFlowMessageCancelField
{
	///序列系列号
	TShfeFtdcSequenceSeriesType	SequenceSeries;
	///交易日
	TShfeFtdcDateType	TradingDay;
	///数据中心代码
	TShfeFtdcDataCenterIDType	DataCenterID;
	///回退起始序列号
	TShfeFtdcSequenceNoType	StartSequenceNo;
	///回退结束序列号
	TShfeFtdcSequenceNoType	EndSequenceNo;
};

///汇率查询
struct CShfeFtdcQryExchangeRateField
{
	///币种代码
	TShfeFtdcCurrencyIDType	CurrencyID;
};

///汇率查询应答
struct CShfeFtdcRspExchangeRateField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///币种代码
	TShfeFtdcCurrencyIDType	CurrencyID;
	///外汇交易单位
	TShfeFtdcRateUnitType	RateUnit;
	///外汇中间价
	TShfeFtdcExRatePriceType	RatePrice;
};

///合约
struct CShfeFtdcInstrumentField
{
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///产品代码
	TShfeFtdcProductIDType	ProductID;
	///产品组代码
	TShfeFtdcProductGroupIDType	ProductGroupID;
	///基础商品代码
	TShfeFtdcInstrumentIDType	UnderlyingInstrID;
	///产品类型
	TShfeFtdcProductClassType	ProductClass;
	///持仓类型
	TShfeFtdcPositionTypeType	PositionType;
	///执行价
	TShfeFtdcPriceType	StrikePrice;
	///期权类型
	TShfeFtdcOptionsTypeType	OptionsType;
	///合约数量乘数
	TShfeFtdcVolumeMultipleType	VolumeMultiple;
	///合约基础商品乘数
	TShfeFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///合约名称
	TShfeFtdcInstrumentNameType	InstrumentName;
	///交割年份
	TShfeFtdcYearType	DeliveryYear;
	///交割月
	TShfeFtdcMonthType	DeliveryMonth;
	///提前月份
	TShfeFtdcAdvanceMonthType	AdvanceMonth;
	///当前是否交易
	TShfeFtdcBoolType	IsTrading;
	///币种代码
	TShfeFtdcCurrencyIDType	CurrencyID;
};

///组合交易合约的单腿
struct CShfeFtdcCombinationLegField
{
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///组合合约代码
	TShfeFtdcInstrumentIDType	CombInstrumentID;
	///单腿编号
	TShfeFtdcLegIDType	LegID;
	///单腿合约代码
	TShfeFtdcInstrumentIDType	LegInstrumentID;
	///买卖方向
	TShfeFtdcDirectionType	Direction;
	///单腿乘数
	TShfeFtdcLegMultipleType	LegMultiple;
	///推导层数
	TShfeFtdcImplyLevelType	ImplyLevel;
};

///保值额度量
struct CShfeFtdcHedgeVolumeField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TShfeFtdcSettlementIDType	SettlementID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///多头保值额度最初申请量
	TShfeFtdcVolumeType	LongVolumeOriginal;
	///空头保值额度最初申请量
	TShfeFtdcVolumeType	ShortVolumeOriginal;
	///多头保值额度
	TShfeFtdcVolumeType	LongVolume;
	///空头保值额度
	TShfeFtdcVolumeType	ShortVolume;
};

///市场行情
struct CShfeFtdcMarketDataField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TShfeFtdcSettlementIDType	SettlementID;
	///最新价
	TShfeFtdcPriceType	LastPrice;
	///昨结算
	TShfeFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TShfeFtdcPriceType	PreClosePrice;
	///昨持仓量
	TShfeFtdcLargeVolumeType	PreOpenInterest;
	///今开盘
	TShfeFtdcPriceType	OpenPrice;
	///最高价
	TShfeFtdcPriceType	HighestPrice;
	///最低价
	TShfeFtdcPriceType	LowestPrice;
	///数量
	TShfeFtdcVolumeType	Volume;
	///成交金额
	TShfeFtdcMoneyType	Turnover;
	///持仓量
	TShfeFtdcLargeVolumeType	OpenInterest;
	///今收盘
	TShfeFtdcPriceType	ClosePrice;
	///今结算
	TShfeFtdcPriceType	SettlementPrice;
	///涨停板价
	TShfeFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TShfeFtdcPriceType	LowerLimitPrice;
	///昨虚实度
	TShfeFtdcRatioType	PreDelta;
	///今虚实度
	TShfeFtdcRatioType	CurrDelta;
	///最后修改时间
	TShfeFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TShfeFtdcMillisecType	UpdateMillisec;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///业务发生日期
	TShfeFtdcDateType	ActionDay;
};

///深度市场行情
struct CShfeFtdcDepthMarketDataField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TShfeFtdcSettlementIDType	SettlementID;
	///最新价
	TShfeFtdcPriceType	LastPrice;
	///昨结算
	TShfeFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TShfeFtdcPriceType	PreClosePrice;
	///昨持仓量
	TShfeFtdcLargeVolumeType	PreOpenInterest;
	///今开盘
	TShfeFtdcPriceType	OpenPrice;
	///最高价
	TShfeFtdcPriceType	HighestPrice;
	///最低价
	TShfeFtdcPriceType	LowestPrice;
	///数量
	TShfeFtdcVolumeType	Volume;
	///成交金额
	TShfeFtdcMoneyType	Turnover;
	///持仓量
	TShfeFtdcLargeVolumeType	OpenInterest;
	///今收盘
	TShfeFtdcPriceType	ClosePrice;
	///今结算
	TShfeFtdcPriceType	SettlementPrice;
	///涨停板价
	TShfeFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TShfeFtdcPriceType	LowerLimitPrice;
	///昨虚实度
	TShfeFtdcRatioType	PreDelta;
	///今虚实度
	TShfeFtdcRatioType	CurrDelta;
	///最后修改时间
	TShfeFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TShfeFtdcMillisecType	UpdateMillisec;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///申买价一
	TShfeFtdcPriceType	BidPrice1;
	///申买量一
	TShfeFtdcVolumeType	BidVolume1;
	///申卖价一
	TShfeFtdcPriceType	AskPrice1;
	///申卖量一
	TShfeFtdcVolumeType	AskVolume1;
	///申买价二
	TShfeFtdcPriceType	BidPrice2;
	///申买量二
	TShfeFtdcVolumeType	BidVolume2;
	///申卖价二
	TShfeFtdcPriceType	AskPrice2;
	///申卖量二
	TShfeFtdcVolumeType	AskVolume2;
	///申买价三
	TShfeFtdcPriceType	BidPrice3;
	///申买量三
	TShfeFtdcVolumeType	BidVolume3;
	///申卖价三
	TShfeFtdcPriceType	AskPrice3;
	///申卖量三
	TShfeFtdcVolumeType	AskVolume3;
	///申买价四
	TShfeFtdcPriceType	BidPrice4;
	///申买量四
	TShfeFtdcVolumeType	BidVolume4;
	///申卖价四
	TShfeFtdcPriceType	AskPrice4;
	///申卖量四
	TShfeFtdcVolumeType	AskVolume4;
	///申买价五
	TShfeFtdcPriceType	BidPrice5;
	///申买量五
	TShfeFtdcVolumeType	BidVolume5;
	///申卖价五
	TShfeFtdcPriceType	AskPrice5;
	///申卖量五
	TShfeFtdcVolumeType	AskVolume5;
	///业务发生日期
	TShfeFtdcDateType	ActionDay;
};

///分价表
struct CShfeFtdcMBLMarketDataField
{
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TShfeFtdcDirectionType	Direction;
	///价格
	TShfeFtdcPriceType	Price;
	///数量
	TShfeFtdcVolumeType	Volume;
};

///别名定义
struct CShfeFtdcAliasDefineField
{
	///起始位置
	TShfeFtdcStartPosType	StartPos;
	///别名
	TShfeFtdcAliasType	Alias;
	///原文
	TShfeFtdcOriginalTextType	OriginalText;
};

///报价
struct CShfeFtdcQuoteField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TShfeFtdcSettlementIDType	SettlementID;
	///报价编号
	TShfeFtdcQuoteSysIDType	QuoteSysID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///数量
	TShfeFtdcVolumeType	Volume;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///本地报价编号
	TShfeFtdcOrderLocalIDType	QuoteLocalID;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///买方组合开平标志
	TShfeFtdcCombOffsetFlagType	BidCombOffsetFlag;
	///买方组合套保标志
	TShfeFtdcCombHedgeFlagType	BidCombHedgeFlag;
	///买方价格
	TShfeFtdcPriceType	BidPrice;
	///卖方组合开平标志
	TShfeFtdcCombOffsetFlagType	AskCombOffsetFlag;
	///卖方组合套保标志
	TShfeFtdcCombHedgeFlagType	AskCombHedgeFlag;
	///卖方价格
	TShfeFtdcPriceType	AskPrice;
	///插入时间
	TShfeFtdcTimeType	InsertTime;
	///撤销时间
	TShfeFtdcTimeType	CancelTime;
	///成交时间
	TShfeFtdcTimeType	TradeTime;
	///买方报单编号
	TShfeFtdcOrderSysIDType	BidOrderSysID;
	///卖方报单编号
	TShfeFtdcOrderSysIDType	AskOrderSysID;
	///结算会员编号
	TShfeFtdcParticipantIDType	ClearingPartID;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///业务发生日期
	TShfeFtdcDateType	ActionDay;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
	///询价编号
	TShfeFtdcOrderSysIDType	QuoteDemandID;
};

///成交
struct CShfeFtdcTradeField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TShfeFtdcSettlementIDType	SettlementID;
	///成交编号
	TShfeFtdcTradeIDType	TradeID;
	///买卖方向
	TShfeFtdcDirectionType	Direction;
	///报单编号
	TShfeFtdcOrderSysIDType	OrderSysID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易角色
	TShfeFtdcTradingRoleType	TradingRole;
	///资金帐号
	TShfeFtdcAccountIDType	AccountID;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///开平标志
	TShfeFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TShfeFtdcHedgeFlagType	HedgeFlag;
	///价格
	TShfeFtdcPriceType	Price;
	///数量
	TShfeFtdcVolumeType	Volume;
	///成交时间
	TShfeFtdcTimeType	TradeTime;
	///成交类型
	TShfeFtdcTradeTypeType	TradeType;
	///成交价来源
	TShfeFtdcPriceSourceType	PriceSource;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///本地报单编号
	TShfeFtdcOrderLocalIDType	OrderLocalID;
	///结算会员编号
	TShfeFtdcParticipantIDType	ClearingPartID;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///业务发生日期
	TShfeFtdcDateType	ActionDay;
};

///报单
struct CShfeFtdcOrderField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TShfeFtdcSettlementIDType	SettlementID;
	///报单编号
	TShfeFtdcOrderSysIDType	OrderSysID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///报单价格条件
	TShfeFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TShfeFtdcDirectionType	Direction;
	///组合开平标志
	TShfeFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TShfeFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TShfeFtdcPriceType	LimitPrice;
	///数量
	TShfeFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TShfeFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TShfeFtdcDateType	GTDDate;
	///成交量类型
	TShfeFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TShfeFtdcVolumeType	MinVolume;
	///触发条件
	TShfeFtdcContingentConditionType	ContingentCondition;
	///止损价
	TShfeFtdcPriceType	StopPrice;
	///强平原因
	TShfeFtdcForceCloseReasonType	ForceCloseReason;
	///本地报单编号
	TShfeFtdcOrderLocalIDType	OrderLocalID;
	///自动挂起标志
	TShfeFtdcBoolType	IsAutoSuspend;
	///报单来源
	TShfeFtdcOrderSourceType	OrderSource;
	///报单状态
	TShfeFtdcOrderStatusType	OrderStatus;
	///报单类型
	TShfeFtdcOrderTypeType	OrderType;
	///今成交数量
	TShfeFtdcVolumeType	VolumeTraded;
	///剩余数量
	TShfeFtdcVolumeType	VolumeTotal;
	///报单日期
	TShfeFtdcDateType	InsertDate;
	///插入时间
	TShfeFtdcTimeType	InsertTime;
	///激活时间
	TShfeFtdcTimeType	ActiveTime;
	///挂起时间
	TShfeFtdcTimeType	SuspendTime;
	///最后修改时间
	TShfeFtdcTimeType	UpdateTime;
	///撤销时间
	TShfeFtdcTimeType	CancelTime;
	///最后修改交易用户代码
	TShfeFtdcUserIDType	ActiveUserID;
	///优先权
	TShfeFtdcPriorityType	Priority;
	///按时间排队的序号
	TShfeFtdcTimeSortIDType	TimeSortID;
	///结算会员编号
	TShfeFtdcParticipantIDType	ClearingPartID;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///业务发生日期
	TShfeFtdcDateType	ActionDay;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
};

///执行宣告
struct CShfeFtdcExecOrderField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TShfeFtdcSettlementIDType	SettlementID;
	///合约编号
	TShfeFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///本地执行宣告编号
	TShfeFtdcOrderLocalIDType	ExecOrderLocalID;
	///数量
	TShfeFtdcVolumeType	Volume;
	///开平标志
	TShfeFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TShfeFtdcHedgeFlagType	HedgeFlag;
	///持仓方向
	TShfeFtdcPosiDirectionType	PosiDirection;
	///期权行权后是否保留期货头寸的标记
	TShfeFtdcExecOrderPositionFlagType	ReservePositionFlag;
	///期权行权后生成的期货头寸是否自对冲
	TShfeFtdcExecOrderCloseFlagType	CloseFlag;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///执行宣告编号
	TShfeFtdcExecOrderSysIDType	ExecOrderSysID;
	///报单日期
	TShfeFtdcDateType	InsertDate;
	///插入时间
	TShfeFtdcTimeType	InsertTime;
	///撤销时间
	TShfeFtdcTimeType	CancelTime;
	///执行结果
	TShfeFtdcExecResultType	ExecResult;
	///结算会员编号
	TShfeFtdcParticipantIDType	ClearingPartID;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///业务发生日期
	TShfeFtdcDateType	ActionDay;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
};

///非标组合报单
struct CShfeFtdcCombOrderField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TShfeFtdcSettlementIDType	SettlementID;
	///组合报单编号
	TShfeFtdcOrderSysIDType	CombOrderSysID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///价格
	TShfeFtdcPriceType	LimitPrice;
	///数量
	TShfeFtdcVolumeType	VolumeTotalOriginal;
	///本地报单编号
	TShfeFtdcOrderLocalIDType	CombOrderLocalID;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///合约代码1
	TShfeFtdcInstrumentIDType	InstrumentID1;
	///买卖方向1
	TShfeFtdcDirectionType	Direction1;
	///分腿乘数1
	TShfeFtdcLegMultipleType	LegMultiple1;
	///开平标志1
	TShfeFtdcOffsetFlagType	OffsetFlag1;
	///投机套保标志1
	TShfeFtdcHedgeFlagType	HedgeFlag1;
	///合约代码2
	TShfeFtdcInstrumentIDType	InstrumentID2;
	///买卖方向2
	TShfeFtdcDirectionType	Direction2;
	///分腿乘数2
	TShfeFtdcLegMultipleType	LegMultiple2;
	///开平标志2
	TShfeFtdcOffsetFlagType	OffsetFlag2;
	///投机套保标志2
	TShfeFtdcHedgeFlagType	HedgeFlag2;
	///合约代码3
	TShfeFtdcInstrumentIDType	InstrumentID3;
	///买卖方向3
	TShfeFtdcDirectionType	Direction3;
	///分腿乘数3
	TShfeFtdcLegMultipleType	LegMultiple3;
	///开平标志3
	TShfeFtdcOffsetFlagType	OffsetFlag3;
	///投机套保标志3
	TShfeFtdcHedgeFlagType	HedgeFlag3;
	///合约代码4
	TShfeFtdcInstrumentIDType	InstrumentID4;
	///买卖方向4
	TShfeFtdcDirectionType	Direction4;
	///分腿乘数4
	TShfeFtdcLegMultipleType	LegMultiple4;
	///开平标志4
	TShfeFtdcOffsetFlagType	OffsetFlag4;
	///投机套保标志4
	TShfeFtdcHedgeFlagType	HedgeFlag4;
	///报单来源
	TShfeFtdcOrderSourceType	OrderSource;
	///今成交数量
	TShfeFtdcVolumeType	VolumeTraded;
	///剩余数量
	TShfeFtdcVolumeType	VolumeTotal;
	///报单日期
	TShfeFtdcDateType	InsertDate;
	///插入时间
	TShfeFtdcTimeType	InsertTime;
	///结算会员编号
	TShfeFtdcParticipantIDType	ClearingPartID;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///业务发生日期
	TShfeFtdcDateType	ActionDay;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
};

///放弃执行宣告
struct CShfeFtdcAbandonExecOrderField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TShfeFtdcSettlementIDType	SettlementID;
	///合约编号
	TShfeFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///本地放弃执行宣告编号
	TShfeFtdcOrderLocalIDType	AbandonExecOrderLocalID;
	///数量
	TShfeFtdcVolumeType	Volume;
	///开平标志
	TShfeFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TShfeFtdcHedgeFlagType	HedgeFlag;
	///申请放弃的头寸方向
	TShfeFtdcPosiDirectionType	PosiDirection;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///放弃执行宣告编号
	TShfeFtdcExecOrderSysIDType	AbandonExecOrderSysID;
	///报单日期
	TShfeFtdcDateType	InsertDate;
	///插入时间
	TShfeFtdcTimeType	InsertTime;
	///撤销时间
	TShfeFtdcTimeType	CancelTime;
	///放弃执行结果
	TShfeFtdcExecResultType	AbandonExecResult;
	///结算会员编号
	TShfeFtdcParticipantIDType	ClearingPartID;
	///业务发生日期
	TShfeFtdcDateType	ActionDay;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
};

///管理报单输入
struct CShfeFtdcInputAdminOrderField
{
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///管理报单命令
	TShfeFtdcAdminOrderCommandFlagType	AdminOrderCommand;
	///结算会员编号
	TShfeFtdcParticipantIDType	ClearingPartID;
	///交易会员编号
	TShfeFtdcParticipantIDType	ParticipantID;
	///金额
	TShfeFtdcMoneyType	Amount;
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
};

///公告
struct CShfeFtdcBulletinField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///公告编号
	TShfeFtdcBulletinIDType	BulletinID;
	///序列号
	TShfeFtdcSequenceNoType	SequenceNo;
	///公告类型
	TShfeFtdcNewsTypeType	NewsType;
	///紧急程度
	TShfeFtdcNewsUrgencyType	NewsUrgency;
	///发送时间
	TShfeFtdcTimeType	SendTime;
	///消息摘要
	TShfeFtdcAbstractType	Abstract;
	///消息来源
	TShfeFtdcComeFromType	ComeFrom;
	///消息正文
	TShfeFtdcContentType	Content;
	///WEB地址
	TShfeFtdcURLLinkType	URLLink;
	///市场代码
	TShfeFtdcMarketIDType	MarketID;
};

///合约状态
struct CShfeFtdcInstrumentStatusField
{
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///合约交易状态
	TShfeFtdcInstrumentStatusType	InstrumentStatus;
	///交易阶段编号
	TShfeFtdcTradingSegmentSNType	TradingSegmentSN;
	///进入本状态时间
	TShfeFtdcTimeType	EnterTime;
	///进入本状态原因
	TShfeFtdcInstStatusEnterReasonType	EnterReason;
	///进入本状态日期
	TShfeFtdcDateType	EnterDate;
};

///询价录入请求
struct CShfeFtdcInputQuoteDemandField
{
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///本地询价编号
	TShfeFtdcOrderLocalIDType	QuoteDemandLocalID;
};

///询价信息
struct CShfeFtdcQuoteDemandInfoField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///本地询价编号
	TShfeFtdcOrderLocalIDType	QuoteDemandLocalID;
	///请求时间
	TShfeFtdcTimeType	DemandTime;
	///业务发生日期
	TShfeFtdcDateType	ActionDay;
};

///询价通知
struct CShfeFtdcQuoteDemandNotifyField
{
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///询价日期
	TShfeFtdcDateType	DemandDay;
	///询价时间
	TShfeFtdcTimeType	DemandTime;
	///询价编号
	TShfeFtdcOrderSysIDType	QuoteDemandID;
};

///期权自对冲更新请求
struct CShfeFtdcInputOptionSelfCloseField
{
	///合约编号
	TShfeFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///本地期权自对冲编号
	TShfeFtdcOrderLocalIDType	OptionSelfCloseLocalID;
	///数量
	TShfeFtdcVolumeType	Volume;
	///期权行权的头寸是否自对冲
	TShfeFtdcOptSelfCloseFlagType	SelfCloseFlag;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
};

///期权自对冲
struct CShfeFtdcOptionSelfCloseField
{
	///交易日
	TShfeFtdcDateType	TradingDay;
	///结算组代码
	TShfeFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TShfeFtdcSettlementIDType	SettlementID;
	///合约编号
	TShfeFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///本地期权自对冲编号
	TShfeFtdcOrderLocalIDType	OptionSelfCloseLocalID;
	///数量
	TShfeFtdcVolumeType	Volume;
	///期权行权的头寸是否自对冲
	TShfeFtdcOptSelfCloseFlagType	SelfCloseFlag;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
	///期权自对冲编号
	TShfeFtdcOptionSelfCloseSysIDType	OptionSelfCloseSysID;
	///期权自对冲结果
	TShfeFtdcExecResultType	SelfCloseResult;
	///报单日期
	TShfeFtdcDateType	InsertDate;
	///插入时间
	TShfeFtdcTimeType	InsertTime;
	///撤销时间
	TShfeFtdcTimeType	CancelTime;
	///结算会员编号
	TShfeFtdcParticipantIDType	ClearingPartID;
	///业务发生日期
	TShfeFtdcDateType	ActionDay;
};

///期权自对冲操作
struct CShfeFtdcOptionSelfCloseActionField
{
	///期权自对冲编号
	TShfeFtdcOptionSelfCloseSysIDType	OptionSelfCloseSysID;
	///本地期权自对冲编号
	TShfeFtdcOrderLocalIDType	OptionSelfCloseLocalID;
	///期权自对冲操作标志
	TShfeFtdcActionFlagType	ActionFlag;
	///会员代码
	TShfeFtdcParticipantIDType	ParticipantID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///操作本地编号
	TShfeFtdcOrderLocalIDType	ActionLocalID;
	///业务单元
	TShfeFtdcBusinessUnitType	BusinessUnit;
	///本地业务标识
	TShfeFtdcBusinessLocalIDType	BusinessLocalID;
	///IP地址
	TShfeFtdcIPAddressType	IPAddress;
	///Mac地址
	TShfeFtdcMacAddressType	MacAddress;
};

///期权自对冲查询
struct CShfeFtdcQryOptionSelfCloseField
{
	///起始会员代码
	TShfeFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TShfeFtdcParticipantIDType	PartIDEnd;
	///期权自对冲编号
	TShfeFtdcOptionSelfCloseSysIDType	OptionSelfCloseSysID;
	///合约代码
	TShfeFtdcInstrumentIDType	InstrumentID;
	///客户代码
	TShfeFtdcClientIDType	ClientID;
	///交易用户代码
	TShfeFtdcUserIDType	UserID;
	///开始时间
	TShfeFtdcTimeType	TimeStart;
	///结束时间
	TShfeFtdcTimeType	TimeEnd;
};

///终端产品认证信息
struct CShfeFtdcProductAuthField
{
	///交易终端名称
	TShfeFtdcProductInfoType	AppID;
	///终端认证授权码
	TShfeFtdcAuthCodeType	AuthCode;
};



#endif
