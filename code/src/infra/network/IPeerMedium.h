#ifndef IPEERMEDIUM
#define IPEERMEDIUM

#include <QObject>
#include "Utility/PropertyItem.h"

/*! @brief	A communication parameters. */
class ParameterSet;

class IPeerMedium {
public:
    /*! @brief	The parameter host address */
    static inline const std::string cParameter_HostAddress{ "HostAddress" };
    /*! @brief	The parameter host port */
    static inline const std::string cParameter_HostPort{ "HostPort" };
    /*! @brief	The parameter local port */
    static inline const std::string cParameter_LocalPort{ "LocalPort" };

    virtual ~IPeerMedium(){

    }

    /*!
     * @brief	Each communication medium configuration parameters should be passed via this API. The
     * 			list of parameters are dictated/known by communication medium itself
     *
     * @param	parameters	The parameter mapping (name/value)
     */
    virtual void assignParameters(const ParameterSet& parameters) = 0;

	/*! Perform necessary initializations required for UDP socket */
	virtual bool initialize() = 0;

    /*! @brief	Perform destruction and close activities required for given medium */
    virtual void finalize() = 0;

    /*!
     * @brief	Is communication medium initialized properly
     *
     * @returns	Initialization status.
     */
    virtual bool isInitialized() = 0;

	/*!
	 * @brief	Check if host is set correctly sending UDP datagram for preset host
	 *
	 * @returns	Initialization status.
	 */
    virtual bool isHostSet() = 0;

    /*!
     * @brief	Is communication medium ready for communication
     *
     * @returns	true => can be used for that purpose, false => not ready.
     */
    virtual bool isActive() = 0;

    /*!
     * @brief	Data APIs
     *
     * @returns	An int64_t.
     */
    virtual int64_t availableDataSize() = 0;

    /*!
     * @brief	Reads a data
     *
     * @param 		  	maxByteCount	Number of maximum bytes.
     * @param [in,out]	data			If non-null, the data.
     *
     * @returns	The data.
     */
    virtual int64_t readData(int64_t maxByteCount, int8_t* data,
                            QString* address = nullptr,
                            quint16* port = nullptr) = 0;
    /*!
     * @brief	Reads a data
     *
     * @param	maxByteCount	Number of maximum bytes.
	 * @note    extra copy required for QByteArray
     *
     * @returns	The data.
     */
    virtual QByteArray readData(int64_t maxByteCount,
                                QString* address = nullptr,
                                quint16* port = nullptr) = 0;

    /*!
     * @brief	Writes a data
     *
     * @param 		  	data   	The data.
     * @param 		  	maxSize	The maximum size of the.
     * @param 		  	address	The address.
     * @param [in,out]	port   	The port.
     *
     * @returns	An int64_t.
     */
    virtual int64_t writeData(const QByteArray& data, const QString& address, uint16_t& port) = 0;

    /*!
     * @brief	Writes a data
     *
     * @param	data   	The data.
     * @param	maxSize	The maximum size of the.
     *
     * @returns	An int64_t.
     */
    virtual int64_t writeData(const int8_t* data, int64_t maxSize) = 0;

    /*!
     * @brief	Writes a data
     *
     * @param	data	The data.
     *
     * @returns	An int64_t.
     */
    virtual int64_t writeData(const QByteArray& data) = 0;

	/*!
	 * @note	Just to demonstrate that this interface is required to provide this signal otherwise no code will be generated for this
	 */
signals:
    /*!
     * @brief	The signal is emitted when any kind of error is occurred
     *
     * @param	errorCode	The occurred error code.
     */
    void errorOccurred(int32_t errorCode);

    /*! @brief	There is data that need to be processed */
    void dataReadyToRead();
};


#endif /* IPEERMEDIUM */
