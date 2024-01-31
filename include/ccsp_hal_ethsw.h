/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2023 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**
 * 
 * @file ccsp_hal_ethsw.h
 * @brief The ccsp_hal_ethsw provides an interface to get/set Ethernet Switch control features.
 */


#ifndef __CCSP_HAL_ETHSW_H__
#define __CCSP_HAL_ETHSW_H__

/**
* @defgroup ETHSW_HAL  Ethernet Switch HAL
*
* @defgroup ETHSW_HAL_TYPES  Ethernet Switch HAL Data Types
* @ingroup  ETHSW_HAL
*
* @defgroup ETHSW_HAL_APIS Ethernet Switch HAL  APIs
* @ingroup  ETHSW_HAL
*
**/


/**
 * @addtogroup ETHSW_HAL_TYPES
 * @{
 */

/**********************************************************************
               CONSTANT DEFINITIONS
**********************************************************************/

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef ULLONG
#define ULLONG unsigned long long
#endif

#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef BOOLEAN
#define BOOLEAN  UCHAR
#endif

#ifndef INT
#define INT   int
#endif

#ifndef UINT
#define UINT unsigned int
#endif

#ifndef TRUE
#define TRUE     1
#endif

#ifndef FALSE
#define FALSE    0
#endif

#ifndef ENABLE
#define ENABLE   1
#endif

#ifndef RETURN_OK
#define RETURN_OK   0
#endif

#ifndef RETURN_ERR
#define RETURN_ERR   -1
#endif

#ifndef ETHWAN_DEF_INTF_NUM
/*
* ETH WAN Physical Interface Number Assignment - Should eventually move away from Compile Time
* Utilized by Auto WAN feature in provisioning Apps & CCSP Eth Agent with Ethernet WAN Feature, CcspHalExtSw_setEthWanPort()
* ETh WAN HAL is 0 based
*/
#if defined (ETH_6_PORTS)
#define ETHWAN_DEF_INTF_NUM 5
#elif defined (ETH_4_PORTS)
#define ETHWAN_DEF_INTF_NUM 3
#elif defined (ETH_2_PORTS) && defined (MODEM_ONLY_SUPPORT)
#define ETHWAN_DEF_INTF_NUM 0 
#else
/* Default to Physical Port #1 for ETH WAN */
#define ETHWAN_DEF_INTF_NUM 0
#endif
#endif

#ifndef ETHWAN_INTERFACE_NAME_MAX_LENGTH
/*
* Define a MAX ETH WAN Interface Name Length for GetEthWanInterfaceName
* TO DO: GetEthWanInterfaceName HAL/API needs to be updated to pass in buffer size as well
*/
#define ETHWAN_INTERFACE_NAME_MAX_LENGTH   32
#endif

/**********************************************************************
                ENUMERATION DEFINITIONS
**********************************************************************/

/**
 * @brief Enumeration of Ethernet switch ports
 *
 * This enumeration is used to represent the different Ethernet switch ports.
 */
 
typedef enum
_CCSP_HAL_ETHSW_PORT
{
    CCSP_HAL_ETHSW_EthPort1  = 1,           /**< Ethernet port 1. */
    CCSP_HAL_ETHSW_EthPort2,                /**< Ethernet port 2. */
    CCSP_HAL_ETHSW_EthPort3,                /**< Ethernet port 3. */
    CCSP_HAL_ETHSW_EthPort4,                /**< Ethernet port 4. */
    CCSP_HAL_ETHSW_EthPort5,                /**< Ethernet port 5. */
    CCSP_HAL_ETHSW_EthPort6,                /**< Ethernet port 6. */
    CCSP_HAL_ETHSW_EthPort7,                /**< Ethernet port 7. */
    CCSP_HAL_ETHSW_EthPort8,                /**< Ethernet port 8. */

    CCSP_HAL_ETHSW_Moca1,                   /**< MoCA port 1. */
    CCSP_HAL_ETHSW_Moca2,                   /**< MoCA port 2. */

    CCSP_HAL_ETHSW_Wlan1,                   /**< WLAN port 1. */
    CCSP_HAL_ETHSW_Wlan2,                   /**< WLAN port 2. */
    CCSP_HAL_ETHSW_Wlan3,                   /**< WLAN port 3. */
    CCSP_HAL_ETHSW_Wlan4,                   /**< WLAN port 4. */

    CCSP_HAL_ETHSW_Processor1,              /**< Processor port 1. */
    CCSP_HAL_ETHSW_Processor2,              /**< Processor port 2. */

    CCSP_HAL_ETHSW_InterconnectPort1,       /**< Interconnect port 1. */
    CCSP_HAL_ETHSW_InterconnectPort2,       /**< Interconnect port 2. */

    CCSP_HAL_ETHSW_MgmtPort,                /**< Management port. */
    CCSP_HAL_ETHSW_PortMax                  /**< Maximum number of ports. */
}
CCSP_HAL_ETHSW_PORT, *PCCSP_HAL_ETHSW_PORT;

/**
 * @brief Enumeration of Ethernet switch link rates.
 *
 * This enumeration lists all the link rates.
 */

typedef enum
_CCSP_HAL_ETHSW_LINK_RATE
{
    CCSP_HAL_ETHSW_LINK_NULL      = 0,   /**< Null link rate. */
    CCSP_HAL_ETHSW_LINK_10Mbps,          /**< Link rate of 10 Mbps. */
    CCSP_HAL_ETHSW_LINK_100Mbps,         /**< Link rate of 100 Mbps. */
    CCSP_HAL_ETHSW_LINK_1Gbps,           /**< Link rate of 1 Gbps. */
    CCSP_HAL_ETHSW_LINK_2_5Gbps,         /**< Link rate of 2.5 Gbps. */
    CCSP_HAL_ETHSW_LINK_5Gbps,           /**< Link rate of 5 Gbps. */
    CCSP_HAL_ETHSW_LINK_10Gbps,          /**< Link rate of 10 Gbps. */
    CCSP_HAL_ETHSW_LINK_Auto             /**< Automatic link rate. */
}
CCSP_HAL_ETHSW_LINK_RATE, *PCCSP_HAL_ETHSW_LINK_RATE;

/**
 * @brief Enumeration of Ethernet switch duplex modes.
 *
 * This enumeration lists all the duplex modes available in the CCSP_HAL_ETHSW_DUPLEX_MODE.
 */

typedef enum
_CCSP_HAL_ETHSW_DUPLEX_MODE
{
    CCSP_HAL_ETHSW_DUPLEX_Auto    = 0,  /**< Automatic duplex mode. */
    CCSP_HAL_ETHSW_DUPLEX_Half,         /**< Half duplex mode. */
    CCSP_HAL_ETHSW_DUPLEX_Full          /**< Full duplex mode. */
}
CCSP_HAL_ETHSW_DUPLEX_MODE, *PCCSP_HAL_ETHSW_DUPLEX_MODE;

/**
 * @brief Enumeration of link status.
 *
 * @details This enumeration defines the possible link status values.
 */

typedef enum
_CCSP_HAL_ETHSW_LINK_STATUS
{
    CCSP_HAL_ETHSW_LINK_Up        = 0,  /**< Link is up. */
    CCSP_HAL_ETHSW_LINK_Down,           /**< Link is down. */
    CCSP_HAL_ETHSW_LINK_Disconnected    /**< Link is disconnected. */
}
CCSP_HAL_ETHSW_LINK_STATUS, *PCCSP_HAL_ETHSW_LINK_STATUS;

/**
 * @brief Enumeration of Ethernet Switch Admin status.
 *
 * @details This enumeration defines the possible link status values.
 */

typedef enum
_CCSP_HAL_ETHSW_ADMIN_STATUS
{
    CCSP_HAL_ETHSW_AdminUp        = 0,  /**< Admin status is up. */
    CCSP_HAL_ETHSW_AdminDown,           /**< Admin status is down. */
    CCSP_HAL_ETHSW_AdminTest            /**< Admin status is in test mode. */
}
CCSP_HAL_ETHSW_ADMIN_STATUS, *PCCSP_HAL_ETHSW_ADMIN_STATUS;

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

/**
 * @brief Represents ethernet port statistics.
 *
 * @note Ensure that any path specified does not exceed the buffer size
 * limit defined.
 */

typedef  struct
_CCSP_HAL_ETH_STATS
{
    ULLONG                          BytesSent;                          /**< Unsigned long long value that represents the number of bytes sent. It is a vendor specific value. */
    ULLONG                          BytesReceived;                      /**< Unsigned long long value that represents the number of bytes received. It is a vendor specific value. */
    ULONG                           PacketsSent;                        /**< Unsigned long value that represents the number of packets sent. It is a vendor specific value. */
    ULONG                           PacketsReceived;                    /**< Unsigned long value that represents the number of packets received. It is a vendor specific value. */
    ULONG                           ErrorsSent;                         /**< Unsigned long value that represents the number of errors sent. It is a vendor specific value. */
    ULONG                           ErrorsReceived;                     /**< Unsigned long value that represents the number of errors received. It is a vendor specific value. */
    ULONG                           UnicastPacketsSent;                 /**< Unsigned long value that represents the number of unicast packets sent. It is a vendor specific value. */
    ULONG                           UnicastPacketsReceived;             /**< Unsigned long value that represents the number of unicast packets received. It is a vendor specific value. */
    ULONG                           DiscardPacketsSent;                 /**< Unsigned long value that represents the number of discard packets sent. It is a vendor specific value. */
    ULONG                           DiscardPacketsReceived;             /**< Unsigned long value that represents the number of discard packets received. It is a vendor specific value. */
    ULONG                           MulticastPacketsSent;               /**< Unsigned long value that represents the number of multicast packets sent. It is a vendor specific value. */
    ULONG                           MulticastPacketsReceived;           /**< Unsigned long value that represents the number of multicast packets received. It is a vendor specific value. */
    ULONG                           BroadcastPacketsSent;               /**< Unsigned long value that represents the number of broadcast packets sent. It is a vendor specific value. */
    ULONG                           BroadcastPacketsReceived;           /**< Unsigned long value that represents the number of broadcast packets received. It is a vendor specific value. */
    ULONG                           UnknownProtoPacketsReceived;        /**< Unsigned long value that represents the number of unknown proto packets received. It is a vendor specific value. */
}
CCSP_HAL_ETH_STATS, *PCCSP_HAL_ETH_STATS;

/**
 * @}
 */


/**
 * @addtogroup ETHSW_HAL_APIS
 * @{
 */

/**********************************************************************************
 *
 *  Subsystem level function prototypes
 *
**********************************************************************************/

/*
 * TODO:
 *
 * 1. Extend the return codes by listing out the possible reasons of failure, to improve the interface in the future.
 *    This was reported during the review for header file migration to opensource github.
 *
 */

/**
* @brief Do what needed to intialize the Eth hal.
*
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*

*
*
*/
INT
CcspHalEthSwInit
    (
        void
    );


/**
* @brief Retrieve the current port status - link speed, duplex mode etc.

* @param[in] PortId Port ID as defined in CCSP_HAL_ETHSW_PORT enumeration.
*                   \n Port ID value ranges from 1 to 20.
* @param[out] pLinkRate Receives the current link rate, as in CCSP_HAL_ETHSW_LINK_RATE enumeration.
*                       \n The value ranges from 0 to 7.
* @param[out] pDuplexMode Receives the current duplex mode, as in CCSP_HAL_ETHSW_DUPLEX_MODE enumeration.
*                         \n The value ranges from 0 to 2.
* @param[out] pStatus Receives the current link status, as in CCSP_HAL_ETHSW_LINK_STATUS enumeration.
*                     \n The value ranges from 0 to 2.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
*

*
*
*/
INT
CcspHalEthSwGetPortStatus
    (
        CCSP_HAL_ETHSW_PORT         PortId,
        PCCSP_HAL_ETHSW_LINK_RATE   pLinkRate,
        PCCSP_HAL_ETHSW_DUPLEX_MODE pDuplexMode,
        PCCSP_HAL_ETHSW_LINK_STATUS pStatus
    );


/**
* @brief Retrieve the current port config - link speed, duplex mode, etc.

* @param[in] PortId Port ID as defined in CCSP_HAL_ETHSW_PORT enumeration.
*                   \n Port ID value ranges from 1 to 20.
* @param[out] pLinkRate Receives the current link rate, as in CCSP_HAL_ETHSW_LINK_RATE enumeration.
*                       \n The value ranges from 0 to 7.
* @param[out] pDuplexMode Receives the current duplex mode, as in CCSP_HAL_ETHSW_DUPLEX_MODE enumeration.
*                         \n The value ranges from 0 to 2.

*
* @return The status of the operation.
* @retval RETURN_OK if the operation is successful.
* @retval RETURN_ERR if any error is detected during the operation.
*
*
*

*
*
*/
INT
CcspHalEthSwGetPortCfg
    (
        CCSP_HAL_ETHSW_PORT         PortId,
        PCCSP_HAL_ETHSW_LINK_RATE   pLinkRate,
        PCCSP_HAL_ETHSW_DUPLEX_MODE pDuplexMode
    );


/**
* @brief Set the port configuration - link speed, duplex mode.

* @param[in] PortId Port ID as defined in enum CCSP_HAL_ETHSW_PORT enumeration.
*                   \n Port ID value ranges from 1 to 20.
* @param[in] LinkRate Set the link rate, as in CCSP_HAL_ETHSW_LINK_RATE enumeration.
*                     \n The value ranges from 0 to 7.
* @param[in] DuplexMode Set the duplex mode, as in CCSP_HAL_ETHSW_DUPLEX_MODE enumeration.
*                       \n The value ranges from 0 to 2.

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*

*
*
*/
INT
CcspHalEthSwSetPortCfg
    (
        CCSP_HAL_ETHSW_PORT         PortId,
        CCSP_HAL_ETHSW_LINK_RATE    LinkRate,
        CCSP_HAL_ETHSW_DUPLEX_MODE  DuplexMode
    );


/**
* @brief Retrieve the current port admin status.

* @param[in] PortId Port ID as defined in CCSP_HAL_ETHSW_PORT enumeration.
*                   \n Port ID value ranges from 1 to 20.
* @param[out] pAdminStatus  Receives the current admin status.
*                           \n The value ranges from 0 to 2 and is defined in CCSP_HAL_ETHSW_ADMIN_STATUS enumeration.
*

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
*

*
*
*/
INT
CcspHalEthSwGetPortAdminStatus
    (
        CCSP_HAL_ETHSW_PORT           PortId,
        PCCSP_HAL_ETHSW_ADMIN_STATUS  pAdminStatus
    );


/**
* @brief Set the ethernet port admin status.
* @param[in] PortId Port ID as defined in CCSP_HAL_ETHSW_PORT enumeration.
*                   \n Port ID value ranges from 1 to 20.
* @param[in] AdminStatus Set the admin status, as defined in CCSP_HAL_ETHSW_ADMIN_STATUS enumeration.
*                        \n The values that can be set are 0 and 1.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*

*
*
*/
INT
CcspHalEthSwSetPortAdminStatus
    (
        CCSP_HAL_ETHSW_PORT         PortId,
        CCSP_HAL_ETHSW_ADMIN_STATUS AdminStatus
    );


/**
* @brief Set the ethernet port configuration - admin up/down, link speed, duplex mode.

* @param[in] PortId Port ID as defined in CCSP_HAL_ETHSW_PORT enumeration.
*                   \n Port ID value ranges from 1 to 20.
* @param[in] AgingSpeed  Integer value of aging speed.
*                        \n It is a vendor specific value.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*

*
*
*/
INT
CcspHalEthSwSetAgingSpeed
    (
        CCSP_HAL_ETHSW_PORT         PortId,
        INT                         AgingSpeed
    );

/**
* @brief Query Moca and External switch port for the given MAC address.

* @param[in] mac Pointer to character array holding the MAC address to search for. The buffer size is 6 bytes.
*                \n The format of the MAC address is given as an example: "00:1A:2B:11:B2:33".
* @param[out] port Pointer to an integer value holding the external port. The possible return values are: 0: MoCA, 1-4: Ethernet port.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected or MAC address is not found.
*
*

*
*
*/
INT
CcspHalEthSwLocatePortByMacAddress
    (
        unsigned char * mac,
        INT * port
    );


//>>zqiu
//Ethernet HAL for client association/disassociation notification.

/**
 * @}
 */

/**
 * @addtogroup ETHSW_HAL_TYPES
 * @{
 */

/**
 * @brief Structure to hold the device details.
 * @note Ensure that any value specified does not exceed the buffer size
 * limit defined.
 */

typedef struct _eth_device {
    UCHAR eth_devMacAddress[6]; /**< It is an unsigned character array that represents the MAC Address.
                                     The format of the MAC address is given as an example: "00:1A:2B:11:B2:33". */
    INT  eth_port;              /**< Which external port the device attached to. It is an integer value.
                                     The valid range of eth_Port is from 0 to MaxEthPort-1, where MaxEthPort is platform specific.
                                     It is a vendor specific value. */
    INT  eth_vlanid;            /**< It is an integer value which represents what vlan ID the port is tagged.
                                     The valid VLAN IDs range from 1 to 4094.It is a vendor specific value. */
    INT  eth_devTxRate;         /**< Tx Speed. It is an unsigned integer value. It is a vendor specific value. */
    INT  eth_devRxRate;         /**< Rx Speed. IT is an unsigned integer value. It is a vendor specific value. */
    BOOLEAN eth_Active;         /**< It is a boolean value which represents whether the device is online/offline. */
} eth_device_t;
/**
 * @}
 */


/**
 * @addtogroup ETHSW_HAL_APIS
 * @{
 */

/**
* @brief The HAL need to allocate array and return the array size by output_array_size.

* @param[out] output_array_size Pointer to unsigned long integer holding the output array size to be returned.
*                              \n The range of acceptable values is 0 to 4,294,967,296.
* @param[out] output_struct Pointer to an array of structures of type eth_device_t.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected or MAC address is not found.
*
*

*
*
*/
INT CcspHalExtSw_getAssociatedDevice(ULONG *output_array_size, eth_device_t **output_struct);

/**
* @brief This call back will be invoked when new Ethernet client come to associate to AP, or existing Ethernet client left.
* @param[out] eth_dev Pointer to an array of structures of type eth_device_t.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected or MAC address is not found.
*
*

*
*
*/
typedef INT ( * CcspHalExtSw_ethAssociatedDevice_callback)(eth_device_t *eth_dev);

/**
* @brief Callback registration function.

* @param[in] callback_proc Callback prototype.
*            \n The parameters are defined below:
*            \n eth_dev - Output parameter which is a pointer to an array of structures of type eth_device_t.
*
*

*
*
*/
void CcspHalExtSw_ethAssociatedDevice_callback_register(CcspHalExtSw_ethAssociatedDevice_callback callback_proc); //!< Callback registration function.

#ifdef FEATURE_RDKB_WAN_MANAGER
#ifdef FEATURE_RDKB_AUTO_PORT_SWITCH

/**
* @brief Configure Ethernet port.

* @param[in] ifname A pointer to the character array that will hold the interface name.
*                   \n The possible values are: eth0, eth1, eth2, eth3.
*                   \n The buffer size should be atleast 32 bytes.
* @param[in] WanMode Boolean value to hold the EthernetWAN enable status.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected or MAC address is not found.
*
*

*
*
*/
int CcspHalExtSw_ethPortConfigure(char *ifname, BOOLEAN WanMode);

#endif  //FEATURE_RDKB_AUTO_PORT_SWITCH
#endif
//<<

/**
* @brief Get EthernetWAN enable status.
*
* @param[out] pFlag Pointer to BOOLEAN to store current EthernetWAN enable value which is returned.
*                   \n Values: 1- Enabled, 0- Disabled.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
*
*/
INT
CcspHalExtSw_getEthWanEnable
  (
    BOOLEAN * pFlag
  );

/**
* @brief Enable/Disable EthernetWAN functionality.
*
* @param[in] Flag   Boolean variable holding the EthernetWAN enable value.
*                   \n Possible values: 1- Enable, 0- Disable.

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
*/
INT
CcspHalExtSw_setEthWanEnable
  (
    BOOLEAN Flag
  );

#ifdef FEATURE_RDKB_AUTO_PORT_SWITCH

/**
* @brief Returns running HW configuration.
*
*
* @return Returns running HW configuration.
* @retval TRUE if WAN is enabled.
* @retval FALSE IF LAN is enabled.
*
*/
BOOLEAN CcspHalExtSw_getCurrentWanHWConf();
#endif

/**
* @brief Get EthernetWAN port number value.
*
* @param[out] pPort Pointer to unsigned integer value to store current EthernetWAN port number setting, to be returned.
*                   \n It is an unsigned integer value. It is a vendor specific value.
*                   \n The valid range of pPort is from 0 to MaxEthPort-1, where MaxEthPort is platform specific.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
*
*/
INT
CcspHalExtSw_getEthWanPort
  (
    UINT * pPort
  );

/**
* @brief Set EthernetWAN interface/port number.
*
* @param[in] Port Unsigned integer value to set the EthernetWAN interface/port number.
*                   \n It is an unsigned integer value. It is a vendor specific value.
*                   \n The valid range of Port is from 0 to MaxEthPort-1, where MaxEthPort is platform specific.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
*/
INT
CcspHalExtSw_setEthWanPort
  (
    UINT Port
  );

/**
* @brief Retrieve the current port's statistics.

* @param[in] PortId Port ID as defined in CCSP_HAL_ETHSW_PORT enumeration.
*                   \n Port ID value ranges from 1 to 20.
* @param[out] pStats Pointer to structure of type PCCSP_HAL_ETH_STATS to receive the current port statistics to be returned.

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
*

*
*
*/
INT
CcspHalEthSwGetEthPortStats
 (
    CCSP_HAL_ETHSW_PORT           PortId,
    PCCSP_HAL_ETH_STATS           pStats
 );
/**
 * @}
 */


/**
 * @addtogroup ETHSW_HAL_TYPES
 * @{
 */

/**
* @brief Define callback function pointers which needs to be called
* from provisioning abstraction layer when any provisioning
* event occurs.
*/
typedef void ( *fpEthWanLink_Up ) ( ) ;    /**< RDKB expects this callback once EthWan link is UP */
typedef void ( *fpEthWanLink_Down ) ( ) ;  /**< RDKB expects this callback once EthWan link is Down */

/**
*   @brief struct of pointers to the function pointers of callback functions.
*/

typedef struct __appCallBack
{
        fpEthWanLink_Up                    pGWP_act_EthWanLinkUP; /**< RDKB expects this callback once EthWan link is UP. */
        fpEthWanLink_Down          pGWP_act_EthWanLinkDown;       /**< RDKB expects this callback once EthWan link is Down. */
}appCallBack;

/**
 * @}
 */

/**
 * @addtogroup ETHSW_HAL_APIS
 * @{
 */

/**
* @brief This function will get used to register RDKB functions to the callback pointers.
*
* @param[in] obj struct of pointers to the function pointers as defined in appCallBack structure.
*
*/
void GWP_RegisterEthWan_Callback(appCallBack *obj);

/**
* @brief Get the Ethwan Link status.
*
*
* @return The status of Ethwan.
* @retval 1 if active(Link Up).
* @retval 0 if inactive(Link Down).
* @retval Less than 0 if failure, errno.
*

*
*
*/
INT GWP_GetEthWanLinkStatus();

/**
* @brief This function will get used to retrieve the ETHWAN interface name.
*
* @param[out] Interface Pointer to character array holding the interface name.  It is a vendor specific value.
*             \n The buffer size should be at least 64 bytes long.
* @param[in] maxSize Unsigned long integer which represents the maximum size.
*                    \n The range of maxsize is 11 to 262.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*

*
*
*/
INT
GWP_GetEthWanInterfaceName
    (
        unsigned char * Interface,
        ULONG maxSize
    );


#define UP "up"
#define DOWN "down"

#endif /* __CCSP_HAL_ETHSW_H__ */

/**
 * @}
 */


