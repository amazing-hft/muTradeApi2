#ifndef SHARED_RESPONSE_H
#define SHARED_RESPONSE_H
#include "apiDataTypes.h"
#include "sharedCommands.h"
#include <string>
namespace API2 
{
  /**
   * @brief The Strategy class contains response sent by strategy for different states like run, modify, terminate etc.
   */
  class Strategy
  {
    public:
      Strategy();
      Strategy(const char* buf);
      int serialize(char* buf);

      DATA_TYPES::UCHAR getResponseType() const { return _responseType;}
      DATA_TYPES::UCHAR getRiskStatus() const { return _riskStatus;}
      DATA_TYPES::UCHAR getIsOffline() const { return _isOffline;}
      DATA_TYPES::UINTEGER32 getStrategyId() const { return _strategyId;}
      DATA_TYPES::UINTEGER32 getParentId() const { return _parentId;}
      DATA_TYPES::UINTEGER64 getAdminTokenId() const { return _adminTokenId;}
      DATA_TYPES::UINTEGER64 getSequenceNumber() const { return _sequenceNumber;}
      DATA_TYPES::UCHAR getStrategyComment() const { return _strategyComment; }
      DATA_TYPES::TerminationReasonType getTerminationReasonType() const { return _terminationReasonType; }

      void setResponseType(DATA_TYPES::UCHAR responseType){ _responseType = responseType;}
      void setRiskStatus(DATA_TYPES::UCHAR riskStatus){ _riskStatus = riskStatus;}
      void setIsOffline(DATA_TYPES::UCHAR isOffline){ _isOffline = isOffline;}
      void setStrategyId(DATA_TYPES::UINTEGER32 strategyId) { _strategyId = strategyId;}
      void setParentId(DATA_TYPES::UINTEGER32 pId) { _parentId = pId;}
      void setAdminTokenId(DATA_TYPES::UINTEGER64 adminTokenId) { _adminTokenId = adminTokenId;}
      void setSequenceNumber(DATA_TYPES::UINTEGER64 sequenceNumber) { _sequenceNumber = sequenceNumber;}
      void setStrategyComment(DATA_TYPES::UCHAR strategyComment) { _strategyComment = strategyComment; }
      void setTerminationReasonType(DATA_TYPES::TerminationReasonType terminationReasonType) { _terminationReasonType = terminationReasonType; }
      void dump();
    private:
      DATA_TYPES::UCHAR _responseType;    // Value (SUCCESS / FAILURE)
      DATA_TYPES::UCHAR _riskStatus;     // Reason for RMS Failure
      DATA_TYPES::UCHAR _strategyComment;
      DATA_TYPES::UCHAR _isOffline;
      DATA_TYPES::UINTEGER32 _strategyId;
      DATA_TYPES::UINTEGER32 _parentId; //Id of parent strategy(strategy from which another strategy is invoked)
      DATA_TYPES::UINTEGER64 _adminTokenId;
      DATA_TYPES::UINTEGER64 _sequenceNumber; // Sequence number to sync up offline responses to RMS/Admin screen
      DATA_TYPES::TerminationReasonType _terminationReasonType; // Strategy termination reason
  };

  class OrderConfirmationImpl;

  /**
   * @brief The OrderConfirmation class contains the Exchange Order Confirmation Message data.
   */
  class OrderConfirmation
  {
    /**
     * @brief pimpl
     */
    //    OrderConfirmationImpl *pimpl;

    DATA_TYPES::CLORDER_ID _clOrderId;
    DATA_TYPES::SYMBOL_ID _symbolId;
    DATA_TYPES::QTY _lastFillQuantity;
    DATA_TYPES::PRICE  _lastFillPrice;
    DATA_TYPES::PRICE  _origLastFillPrice;

    /**
     * @brief _exchangeEntryTime  - for nse, it'll contain last activity reference time,
     *                              for other exchanges, it's entry time
     *                              Note : in case of NSE, in confirmed confirmation,
     *                                      entry time, last modify time, and last activity reference time
     *                                      all are same
     */
    DATA_TYPES::EXCHANGE_TIME  _exchangeEntryTime;
    DATA_TYPES::EXCHANGE_TIME  _exchangeModifyTime;
    DATA_TYPES::STRATEGY_ID  _strategyId;
    DATA_TYPES::CLIENT_ID  _clientId;
    // Limit price will come in Market to Limit order conversion
    DATA_TYPES::PRICE _limitPrice;
    DATA_TYPES::PRICE _origLimitPrice;
    UNSIGNED_CHARACTER _orderStatus;
    UNSIGNED_CHARACTER _orderMode;
    // Adding following two fields for market making
    DATA_TYPES::QTY _orderQuantity;
    DATA_TYPES::PRICE _orderPrice;
    DATA_TYPES::PRICE _origOrderPrice;
    DATA_TYPES::QTY _iocCanceledQuantity;
    DATA_TYPES::CLORDER_ID _originalClOrderId;
    DATA_TYPES::SEQUENCE_NUMBER _sequenceNumber;
    DATA_TYPES::TRADER_ID _traderId;
    DATA_TYPES::ERROR_CODE _errorCode;
    DATA_TYPES::ENUM _orderCategory;
    DATA_TYPES::PRICE  _lastFillPrice1;
    DATA_TYPES::PRICE  _lastFillPrice2;
    char _exchangeOrderId[EXCHANGE_ORDERID_SIZE];
    char _tradeId[TRADEID_SIZE];
    char _strategyTypeSqnNo[STRATEGY_TYPE_SQNNO_SIZE];
    API2::DATA_TYPES::OrderValidity _orderValidity;
    API2::DATA_TYPES::GTD_Date _gtdDate;
    API2::DATA_TYPES::CLORDER_ID _quoteId;
    API2::DATA_TYPES::ConfirmationType _confirmationType;
    char _fixClOrderId[FIX_ORDERID_SIZE];

    //Adding following two fields for Trade Backup
    DATA_TYPES::ENUM _bookType;
    char _openCloseFlag;

    //Adding following two fields for Stop Orders Support in OrderBook
    DATA_TYPES::PRICE _stopPrice;
    DATA_TYPES::OrderType _orderType;

    //Adding this field to identify portfolio and client id for uhedge
    API2::DATA_TYPES::STRATEGY_ID _childStrategyId;

    API2::DATA_TYPES::STRATEGY_ID _parentStrategyId;

    CREATE_FIELD_ACCESS_SPECIFIER(API2::ExchangeAdapterDetails,ExchangeAdapterDetails,protected);

    CREATE_FIELD_CHAR(ErrorText,ERROR_TEXT_SIZE);

    DATA_TYPES::ProductType _productType;

    DATA_TYPES::PlatformType _platformType;
	
	CREATE_FIELD( DATA_TYPES::HOLDING_TYPE , HoldingType );

    /**
     * @brief _algoId
     */
    DATA_TYPES::AlgoId  _algoId;

    /**
     * @brief _algoCategory
     */
    DATA_TYPES::AlgoCategory _algoCategory;

    public:


    OrderConfirmation(const OrderConfirmation& other);
    OrderConfirmation &operator =(const OrderConfirmation& );

    void clone(const OrderConfirmation& other);

    /**
     * @brief ~OrderConfirmation
     */
    virtual ~OrderConfirmation();

    /**
     * @brief OrderConfirmation Constructor
     */
    OrderConfirmation();

    OrderConfirmation(
        DATA_TYPES::CLORDER_ID &clientOrderId,
        DATA_TYPES::SYMBOL_ID &symbolId,
        DATA_TYPES::STRATEGY_ID &strategyId,
        DATA_TYPES::CLIENT_ID &clientId,
        DATA_TYPES::OrderStatus &orderStatus,
        DATA_TYPES::OrderMode &orderMode,
        DATA_TYPES::QTY &orderQty,
        DATA_TYPES::PRICE &orderPrice,
        DATA_TYPES::CLORDER_ID &origClOrdId);



    /**
     * @brief OrderConfirmation
     * @param clientOrderId
     * @param symbolId
     * @param strategyId
     * @param clientId
     * @param orderStatus
     * @param orderMode
     * @param orderType
     * @param orderQty
     * @param orderPrice
     * @param origClOrdId
     * @param stopPrice
     * @param productType
     * @param platformType
     */
    OrderConfirmation(
        DATA_TYPES::CLORDER_ID &clientOrderId,
        DATA_TYPES::SYMBOL_ID &symbolId,
        DATA_TYPES::STRATEGY_ID &strategyId,
        DATA_TYPES::CLIENT_ID &clientId,
        DATA_TYPES::OrderStatus &orderStatus,
        DATA_TYPES::OrderMode &orderMode,
        DATA_TYPES::OrderType &orderType,
        DATA_TYPES::QTY &orderQty,
        DATA_TYPES::PRICE &orderPrice,
        DATA_TYPES::CLORDER_ID &origClOrdId,
        const DATA_TYPES::PRICE &stopPrice,
        const DATA_TYPES::ProductType &productType,
        const DATA_TYPES::PlatformType &platformType);


    /**
     * @brief initialize
     */
    void initialize();

    /**
     * @brief getClOrderId To get Unique Client Order Id, sent to exchange at the time of Order Sending
     * @return ClientOrderId as API2::DATA_TYPES::CLORDER_ID
     */
    DATA_TYPES::CLORDER_ID getClOrderId() const;

    /**
     * @brief getExchangeOrderId To get Exchange Order Id of the Order.
     * @return exchangeOrderId as API2::DATA_TYPES::String
     */
    DATA_TYPES::String getExchangeOrderId() const ;

    /**
     * @brief getSymbolId To get unique SymbolID, which is a unique Identifier for an Instrument in the system.
     * @return SymbolId as API2::DATA_TYPES::SYMBOL_ID
     */
    DATA_TYPES::SYMBOL_ID getSymbolId() const ;

    /**
     * @brief getLastFillQuantity To get Last filled quantity
     * @return LastFillQuantity as API2::DATA_TYPES::QTY
     */
    DATA_TYPES::QTY  getLastFillQuantity() const;

    /**
     * @brief getOrigLastFillPrice To get last filled Price
     * @return origLastFillPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getOrigLastFillPrice() const;

    /**
     * @brief getLastFillPrice To get last filled Price
     * @return LastFillPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getLastFillPrice() const;

    /**
     * @brief getExchangeEntryTime To get Time of Order Entry in the exchange
     * @return ExchangeEntryTime as API2::DATA_TYPES::EXCHANGE_TIME
     */
    DATA_TYPES::EXCHANGE_TIME  getExchangeEntryTime() const;

    /**
     * @brief getExchangeModifyTime To get Time of Order Modification in the exchange
     * @return ExchangeModifyTime as API2::DATA_TYPES::EXCHANGE_TIME
     */
    DATA_TYPES::EXCHANGE_TIME  getExchangeModifyTime() const;

    /**
     * @brief getStrategyId To get The Strategy Id to which this Order belongs to
     * @return StrategyId as API2::DATA_TYPES::STRATEGY_ID
     */
    DATA_TYPES::STRATEGY_ID  getStrategyId() const ;

    /**
     * @brief getClientId To get the client Id for which this Order belongs
     * @return ClientId as API2::DATA_TYPES::CLIENT_ID
     */
    DATA_TYPES::CLIENT_ID  getClientId() const ;

    /**
     * @brief getLimitPrice To get Limit Price set for Order
     * @return LimitPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getLimitPrice() const;



    /**
     * @brief getOrigLimitPrice To get Limit Price set for Order
     * @return LimitPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getOrigLimitPrice() const;

    /**
     * @brief getOrigOrderPrice To get the Original Order Price
     * @return OrderPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getOrigOrderPrice() const;

    /**
     * @brief setOrigLastFillPrice
     * @param price
     */
    void setOrigLastFillPrice(DATA_TYPES::PRICE price);

    /**
     * @brief setLimitPrice
     * @param limitPrice
     */
    void setOrigLimitPrice(DATA_TYPES::PRICE limitPrice);


    /**
     * @brief getOrderStatus To get the OrderStatus
     * @return returns OrderStatus as API2::DATA_TYPES::OrderStatus
     */
    DATA_TYPES::OrderStatus getOrderStatus() const ;

    /**
     * @brief getOrderMode To getOrderMode (Buy/Sell) for the order
     * @return OrderMode as API2::DATA_TYPES::OrderMode
     */
    DATA_TYPES::OrderMode getOrderMode() const ;

    /**
     * @brief getOrderQuantity To get th Order Quantity
     * @return OrderQuantity as API2::DATA_TYPES::QTY
     */
    DATA_TYPES::QTY  getOrderQuantity() const ;

    /**
     * @brief getOrderPrice To get the Order Price
     * @return OrderPrice as API2::DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE  getOrderPrice() const;

    /**
     * @brief getIOCCanceledQuantity
     * @return
     */
    DATA_TYPES::QTY getIOCCanceledQuantity() const ;

    /**
     * @brief getOriginalClOrderId
     * @return
     */
    DATA_TYPES::CLORDER_ID getOriginalClOrderId() const ;

    /**
     * @brief getTradeId
     * @return Trade Id as API2::DATA_TYPES::String
     */
    DATA_TYPES::String getTradeId() const ;

    const char *getTradeIdCharPtr() const;

    const char *getExchangeOrderIdCharPtr() const;

    /**
     * @brief getErrorCode
     * @return
     */
    DATA_TYPES::ERROR_CODE getErrorCode() const ;

    /**
     * @brief getTraderId
     * @return
     */
    DATA_TYPES::TRADER_ID getTraderId() const ;

    /**
     * @brief getStrategyTypeSqnNo
     * @return
     */
    DATA_TYPES::String getStrategyTypeSqnNo() const ;

    /**
     * @brief getOrderValidity
     * @return
     */
    API2::DATA_TYPES::OrderValidity getOrderValidity() const ;

    /**
     * @brief getGTDDate
     * @return
     */
    API2::DATA_TYPES::GTD_Date getGTDDate() const ;

    /**
     * @brief getQuoteId To get Unique Quote Order Id, sent to exchange at the time of Mass Quote Sending
     * @return QuoteId as API2::DATA_TYPES::CLORDER_ID
     */
    DATA_TYPES::CLORDER_ID getQuoteId() const;

    /**
     * @brief getConfirmationType To get whether the confirmation is self made or from exchange
     * @return API2::DATA_TYPES::ConfirmationType
     */
    API2::DATA_TYPES::ConfirmationType getConfirmationType() const;

    /**
     * @brief getFixClOrderId To get Fix Client OrderId of the order
     * @return FixClOrderId as API2::DATA_TYPES::String
     */
    DATA_TYPES::String getFixClOrderId() const ;

    /**
     * @brief getFixClOrderIdCharPtr To get Fix Client OrderId of the order
     * @return FixClOrderId as char*
     */
    char* getFixClOrderIdCharPtr() ;

    /**
     * @brief getAlgoId
     * @return
     */
    API2::DATA_TYPES::AlgoId getAlgoId() const;


    /**
     * @brief getAlgoCategory
     * @return
     */
    API2::DATA_TYPES::AlgoCategory getAlgoCategory() const;

    /**
     * @brief setStrategytypeSqnNo
     * @param strategyTypeSqnNo
     */
    void setStrategyTypeSqnNo( char strategyTypeSqnNo[]);

    /**
     * @brief setStrategytypeSqnNo
     * @param strategyTypeSqnNo
     */
    void setStrategyTypeSqnNo( std::string strategyTypeSqnNo);
    /**
     * @brief setStrategytypeSqnNo
     * @param strategyTypeSqnNo
     */
    void setStrategyTypeSqnNo( const char * strategyTypeSqnNo);

    /**
     * @brief setClOrderId
     * @param clOrderId
     */

    void setClOrderId(DATA_TYPES::CLORDER_ID clOrderId);

    /**
     * @brief setExchangeOrderId
     * @param exchangeOrderId
     */
    void setExchangeOrderId(char exchangeOrderId[]);

    /**
     * @brief setExchangeOrderId
     * @param exchangeOrderId
     */
    void setExchangeOrderId(std::string exchangeOrderId);

    /**
     * @brief setSymbolId
     * @param symbolId
     */
    void setSymbolId(DATA_TYPES::SYMBOL_ID symbolId);

    /**
     * @brief setLastFillQuantity
     * @param qty
     */
    void setLastFillQuantity(DATA_TYPES::QTY qty);

    /**
     * @brief setLastFillPrice
     * @param price
     */
    void setLastFillPrice(DATA_TYPES::PRICE price);

    /**
     * @brief setExchangeEntryTime
     * @param exchangeEntryTime
     */
    void setExchangeEntryTime(DATA_TYPES::EXCHANGE_TIME exchangeEntryTime);

    /**
     * @brief setExchangeModifyTime
     * @param exchangeModifyTime
     */
    void setExchangeModifyTime(DATA_TYPES::EXCHANGE_TIME exchangeModifyTime);

    /**
     * @brief setStrategyId
     * @param strategyId
     */
    void setStrategyId(DATA_TYPES::STRATEGY_ID strategyId) ;

    /**
     * @brief setClientId
     * @param clientId
     */
    void setClientId(DATA_TYPES::CLIENT_ID clientId);

    /**
     * @brief setLimitPrice
     * @param limitPrice
     */
    void setLimitPrice(DATA_TYPES::PRICE limitPrice);

    /**
     * @brief setOrderStatus
     * @param orderStatus
     */
    void setOrderStatus(DATA_TYPES::OrderStatus orderStatus) ;

    /**
     * @brief setOrderMode
     * @param orderMode
     */
    void setOrderMode(DATA_TYPES::OrderMode orderMode) ;

    /**
     * @brief setOrderQuantity
     * @param quantity
     */
    void setOrderQuantity(DATA_TYPES::QTY quantity);

    /**
     * @brief setOrderPrice
     * @param price
     */
    void setOrderPrice(DATA_TYPES::PRICE price) ;

    /**
     * @brief setOrigOrderPrice
     * @param price
     */
    void setOrigOrderPrice(DATA_TYPES::PRICE price) ;

    /**
     * @brief setIOCCanceledQuantity
     * @param quantity
     */
    void setIOCCanceledQuantity(DATA_TYPES::QTY quantity) ;

    /**
     * @brief setOriginalClOrderId
     * @param originalClOrderId
     */
    void setOriginalClOrderId(DATA_TYPES::CLORDER_ID originalClOrderId);

    /**
     * @brief setSequenceNumber
     * @param sequenceNumber
     */
    void setSequenceNumber(DATA_TYPES::SEQUENCE_NUMBER sequenceNumber);

    /**
     * @brief setTradeId
     * @param tradeId
     */
    void setTradeId(char tradeId[]);

    /**
     * @brief setTradeId
     * @param tradeId
     */
    void setTradeId(std::string tradeId);

    /**
     * @brief setErrorCode
     * @param errorCode
     */
    void setErrorCode(DATA_TYPES::ERROR_CODE errorCode);

    /**
     * @brief setTraderId
     * @param traderId
     */
    void setTraderId(DATA_TYPES::TRADER_ID traderId);

    /**
     * @brief setOrderCategory
     * @param orderCategory
     */
    void setOrderCategory(DATA_TYPES::ENUM orderCategory);

    /**
     * @brief setLastFillPrice1
     * @param lastFillPrice1
     */
    void setLastFillPrice1(DATA_TYPES::PRICE lastFillPrice1);

    /**
     * @brief setLastFillPrice2
     * @param lastFillPrice2
     */
    void setLastFillPrice2(DATA_TYPES::PRICE lastFillPrice2);

    /**
     * @brief setOrderValidity
     * @param orderValidity
     */
    void setOrderValidity( API2::DATA_TYPES::OrderValidity orderValidity );

    /**
     * @brief getGTDDate
     * @param gtdDate
     */
    void setGTDDate( DATA_TYPES::GTD_Date gtdDate );

    /**
     * @brief setQuoteId To set Unique Quote Order Id
     * @param quoteId
     */
    void setQuoteId( DATA_TYPES::CLORDER_ID quoteId );

    /**
     * @brief setConfirmationType To set the confirmation is self made or from exchange
     * @param API2::DATA_TYPES::ConfirmationType
     */
    void setConfirmationType( API2::DATA_TYPES::ConfirmationType confType ) ;

    /**
     * @brief setFixClOrderId To set Fix Client OrderId of the order
     * @return
     */
    void setFixClOrderId( char fixOrderId[]) ;

    /**
     * @brief setFixClOrderId To set Fix Client OrderId of the order
     * @return
     */
    void setFixClOrderId(std::string fixOrderId);

    /**
     * @brief dump
     */
    void dump() const;

    /**
     * @brief getOrderCategory
     * @return
     */
    DATA_TYPES::ENUM getOrderCategory() const;

    /**
     * @brief getLastFillPrice1
     * @return
     */
    DATA_TYPES::PRICE getLastFillPrice1() const;

    /**
     * @brief getLastFillPrice2
     * @return
     */
    DATA_TYPES::PRICE getLastFillPrice2() const;

    /**
     * @brief getBookType
     * @return DATA_TYPES::ENUM
     */
    DATA_TYPES::ENUM getBookType() const;

    /**
     * @brief getOpenCloseFlag
     * @return char
     */
    char getOpenCloseFlag() const;

    /**
     * @brief setBookType
     * @param DATA_TYPES::ENUM
     */
    void setBookType(DATA_TYPES::ENUM bookType);

    /**
     * @brief setOpenCloseFlag
     * @param char
     */
    void setOpenCloseFlag(char openCloseFlag);

    /**
     * @brief getStopPrice
     * @return DATA_TYPES::PRICE
     */
    DATA_TYPES::PRICE getStopPrice() const;

    /**
     * @brief getOrderType
     * @return DATA_TYPES::OrderType
     */
    DATA_TYPES::OrderType getOrderType() const;

    /**
     * @brief setStopPrice
     * @param DATAT_TYPES::PRICE
     */
    void setStopPrice(DATA_TYPES::PRICE stopPrice);

    /**
     * @brief setOrderType
     * @param DATA_TYPES::OrderType
     */
    void setOrderType(DATA_TYPES::OrderType orderType);

    /* @brief getChildStrategyId
     *  @return
     **/
    DATA_TYPES::STRATEGY_ID getChildStrategyId() const;


    /**
     * @brief getParentStrategyId
     * @return
     */
    DATA_TYPES::STRATEGY_ID getParentStrategyId() const;
      
    /**
     * @brief setParentStrategyId
     * @param strategyId
     */
    void setParentStrategyId(DATA_TYPES::STRATEGY_ID strategyId);

    /**
     * @brief setChildStrategyId
     * @param strategyId
     **/
    void setChildStrategyId(DATA_TYPES::STRATEGY_ID strategyId);

    /**
     * @brief getProductType
     * @return DATA_TYPES::ProductType
     */
    DATA_TYPES::ProductType getProductType() const;

    /**
     * @brief getPlatformType
     * @return DATA_TYPES::PlatformType
     */
    DATA_TYPES::PlatformType getPlatformType() const;

    /**
     * @brief setPlatformType
     * @param platformType
     */
    void setPlatformType(DATA_TYPES::PlatformType platformType);

    /**
     * @brief setProductType
     * @param productType
     */
    void setProductType(DATA_TYPES::ProductType productType);

    /**
     * @brief setAlgoId
     * @param algoId
     */
    void setAlgoId(const DATA_TYPES::AlgoId algoId);

    /**
     * @brief setAlgoCategory
     * @param AlgoCategory
     */
    void setAlgoCategory(const DATA_TYPES::AlgoCategory AlgoCategory);

    /**
     * @brief getExchangeModifyTimeEpoch  - get modify time in epoch
     * @return
     */
    const ::API2::DATA_TYPES::EXCHANGE_TIME getExchangeModifyTimeEpoch() const;

    /**
     * @brief getExchangeEntryTimeEpoch - get entry time in epoch
     * @return
     */
    const ::API2::DATA_TYPES::EXCHANGE_TIME getExchangeEntryTimeEpoch() const;

	
	/**
     * @brief getString - This method returns string for confirmation dump.
     * @return
     */
    const std::string getString() const;
  };


#ifndef FRONTEND_COMPILATION

  class PreTradeConfirmation
  {
    DATA_TYPES::CLORDER_ID _clOrderId;
    std::string _exchangeOrderId;
    DATA_TYPES::SYMBOL_ID _symbolId;
    DATA_TYPES::QTY _orderQuantity;
    DATA_TYPES::PRICE _orderPrice;
    DATA_TYPES::QTY _lastFillQuantity;
    DATA_TYPES::PRICE _lastFillPrice;
    DATA_TYPES::EXCHANGE_TIME _exchangeModifyTime;
    DATA_TYPES::STRATEGY_ID _strategyId;
    DATA_TYPES::CLIENT_ID _clientId;
    UNSIGNED_CHARACTER _orderMode;

    public:
    PreTradeConfirmation();
    PreTradeConfirmation(
        const DATA_TYPES::CLORDER_ID& clOrderId,
        const std::string& exchangeOrderId,
        const DATA_TYPES::SYMBOL_ID& symbolId,
        const DATA_TYPES::QTY& orderQuantity,
        const DATA_TYPES::PRICE& orderPrice,
        const DATA_TYPES::QTY& lastFillQuantity,
        const DATA_TYPES::PRICE& lastFillPrice,
        const DATA_TYPES::EXCHANGE_TIME& exchangeModifyTime,
        const DATA_TYPES::STRATEGY_ID& strategyId,
        const DATA_TYPES::CLIENT_ID& clientId,
        UNSIGNED_CHARACTER orderMode
        );

    std::string getString();

    void setClOrderId(DATA_TYPES::CLORDER_ID clOrderId);
    void setExchangeOrderId(const std::string& exchangeOrderId);
    void setSymbolId(DATA_TYPES::SYMBOL_ID symbolId);
    void setOrderQuantity(DATA_TYPES::QTY orderQuantity);
    void setOrderPrice(DATA_TYPES::PRICE orderPrice);
    void setLastFillQuantity(DATA_TYPES::QTY lastFillQuantity);
    void setLastFillPrice(DATA_TYPES::PRICE lastFillPrice);
    void setExchangeModifyTime(DATA_TYPES::EXCHANGE_TIME exchangeModifyTime);
    void setStrategyId(DATA_TYPES::STRATEGY_ID strategyId);
    void setClientId(DATA_TYPES::CLIENT_ID clientId);
    void setOrderMode(UNSIGNED_CHARACTER orderMode);

    DATA_TYPES::CLORDER_ID getClOrderId() const;
    std::string getExchangeOrderId() const;
    const std::string& getRefExchangeOrderId() const;
    DATA_TYPES::SYMBOL_ID getSymbolId() const;
    DATA_TYPES::QTY getOrderQuantity() const;
    DATA_TYPES::PRICE getOrderPrice() const;
    DATA_TYPES::QTY getLastFillQuantity() const;
    DATA_TYPES::PRICE getLastFillPrice() const;
    DATA_TYPES::EXCHANGE_TIME getExchangeModifyTime() const;
    DATA_TYPES::STRATEGY_ID getStrategyId() const;
    DATA_TYPES::CLIENT_ID getClientId() const;
    UNSIGNED_CHARACTER getOrderMode() const;
  };

#endif 

}
#endif 

