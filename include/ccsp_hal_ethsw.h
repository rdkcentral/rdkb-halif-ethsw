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
 * @file ccsp_hal_ethsw.h
 * @brief Provides an interface for controlling and querying the state of Ethernet switches, including port configuration, VLAN management, bridging, statistics retrieval, and link aggregation.
 */

#ifndef __CCSP_HAL_ETHSW_H__
#define __CCSP_HAL_ETHSW_H__

/**
 * @defgroup ETHSW_HAL Ethernet Switch HAL Interface
 * @brief Provides an interface for interacting with Ethernet switch hardware.
 *
 * This component enables control and monitoring of Ethernet switch functionality, including port configuration, link status, and statistics.
 *
 * @{
 * @defgroup ETHSW_HAL_TYPES Data Types
 * @defgroup ETHSW_HAL_APIS APIs
 * @}
 */

/**
 * @addtogroup ETHSW_HAL_TYPES
 * @{
 */

/**********************************************************************
               CONSTANT DEFINITIONS
**********************************************************************/

#define UP "up" /**!< Indicates that a network interface is up. */
#define DOWN "down" /**!< Indicates that a network interface is down. */

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

/**
 *  @brief Default Ethernet WAN Interface Number
 *
 *  Defines the default physical interface number for the Ethernet WAN connection. This value is utilized by the Auto WAN feature in provisioning apps, the CCSP Eth Agent with Ethernet WAN Feature (`CcspHalExtSw_setEthWanPort()`), and the Eth WAN HAL.
 *
 *  Note that Eth WAN HAL is 0-based, meaning the first physical port is represented by 0.
 * 
 *  The default interface is selected based on the following hardware configurations:
 *  * 6 Ethernet ports: Port 5 (index 5)
 *  * 4 Ethernet ports: Port 3 (index 3)
 *  * 2 Ethernet ports (modem-only support): Port 0 (index 0)
 *  * Otherwise (default): Port 0 (index 0)
 *
 *  TODO: Transition to Dynamic Configuration
 *  - Consider moving away from compile-time configuration of the default Ethernet WAN interface.
 *  - Explore using runtime configuration mechanisms (e.g., configuration files, environment variables) to allow for more flexibility and easier customization.
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

/**
 *  @brief Maximum Ethernet WAN Interface Name Length
 *  
 * Defines the maximum length of the interface name string returned by `GetEthWanInterfaceName`.
 * 
 * Note that the current implementation does not allow the caller to specify a buffer size, potentially leading to buffer overflow issues. 
 *
 * TODO: Update GetEthWanInterfaceName:
 *   - Modify the `GetEthWanInterfaceName` function to accept a buffer size parameter from the caller.
 *   - Implement appropriate error handling if the provided buffer is too small to accommodate the interface name.
 */
#define ETHWAN_INTERFACE_NAME_MAX_LENGTH 32
#endif

/**********************************************************************
                ENUMERATION DEFINITIONS
**********************************************************************/

/**<! Represents the available ports on an Ethernet switch. */
 
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

    CCSP_HAL_ETHSW_MgmtPort,                /**!< Maximum number of ports (not a valid port value). */
    CCSP_HAL_ETHSW_PortMax                  /**< Maximum number of ports. */
}
CCSP_HAL_ETHSW_PORT, *PCCSP_HAL_ETHSW_PORT;

/* TODO: Evaluate if the pointer typedef (`_CCSP_HAL_ETHSW_PORT,*PCCSP_HAL_ETHSW_PORT`) are necessary. */

/**!< Lists possible link rates for an Ethernet switch. */
typedef enum _CCSP_HAL_ETHSW_LINK_RATE {
    CCSP_HAL_ETHSW_LINK_NULL = 0,  /**!< No link. */
    CCSP_HAL_ETHSW_LINK_10Mbps,   /**!< 10 Mbps. */
    CCSP_HAL_ETHSW_LINK_100Mbps,  /**!< 100 Mbps. */
    CCSP_HAL_ETHSW_LINK_1Gbps,    /**!< 1 Gbps. */
    CCSP_HAL_ETHSW_LINK_2_5Gbps,  /**!< 2.5 Gbps. */
    CCSP_HAL_ETHSW_LINK_5Gbps,    /**!< 5 Gbps. */
    CCSP_HAL_ETHSW_LINK_10Gbps,   /**!< 10 Gbps. */
    CCSP_HAL_ETHSW_LINK_Auto     /**!< Automatic negotiation. */
} CCSP_HAL_ETHSW_LINK_RATE, *PCCSP_HAL_ETHSW_LINK_RATE;

/* TODO: Evaluate if the pointer typedef (`_CCSP_HAL_ETHSW_LINK_RATE, *PCCSP_HAL_ETHSW_LINK_RATE`) are necessary. */

/**! Lists possible duplex modes for an Ethernet switch. */
typedef enum _CCSP_HAL_ETHSW_DUPLEX_MODE
{
    CCSP_HAL_ETHSW_DUPLEX_Auto = 0, /**!< Automatic duplex mode (negotiated). */
    CCSP_HAL_ETHSW_DUPLEX_Half,     /**!< Half duplex mode (one direction at a time). */
    CCSP_HAL_ETHSW_DUPLEX_Full      /**!< Full duplex mode (both directions simultaneously). */
} CCSP_HAL_ETHSW_DUPLEX_MODE, *PCCSP_HAL_ETHSW_DUPLEX_MODE;
/*
* TODO:  Evaluate if the pointer typedef (`CCSP_HAL_ETHSW_DUPLEX_MODE  & *PCCSP_HAL_ETHSW_DUPLEX_MODE`) is necessary.
*/ 

/**! Indicates the status of an Ethernet switch link. */
typedef enum _CCSP_HAL_ETHSW_LINK_STATUS
{
    CCSP_HAL_ETHSW_LINK_Up = 0,         /**!< Link is up. */
    CCSP_HAL_ETHSW_LINK_Down,           /**!< Link is down. */
    CCSP_HAL_ETHSW_LINK_Disconnected   /**!< Link is disconnected. */
} CCSP_HAL_ETHSW_LINK_STATUS, *PCCSP_HAL_ETHSW_LINK_STATUS;

/*
* TODO: Evaluate if the pointer typedef (`_CCSP_HAL_ETHSW_LINK_STATUS & *PCCSP_HAL_ETHSW_LINK_STATUS`) is necessary.
*/ 

/**! Represents the administrative status of an Ethernet switch. */
typedef enum _CCSP_HAL_ETHSW_ADMIN_STATUS {
    CCSP_HAL_ETHSW_AdminUp = 0,   /**!< Admin status is up (enabled). */
    CCSP_HAL_ETHSW_AdminDown,     /**!< Admin status is down (disabled). */
    CCSP_HAL_ETHSW_AdminTest      /**!< Admin status is in test mode. */ 
} CCSP_HAL_ETHSW_ADMIN_STATUS, *PCCSP_HAL_ETHSW_ADMIN_STATUS;

/* 
* TODO: Evaluate if the typedef (`_CCSP_HAL_ETHSW_ADMIN_STATUS & *PCCSP_HAL_ETHSW_ADMIN_STATUS`) is necessary.
*/

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

/**! Represents Ethernet port statistics. */
typedef struct _CCSP_HAL_ETH_STATS {
    ULLONG BytesSent;           /**!< Number of bytes sent. */
    ULLONG BytesReceived;        /**!< Number of bytes received. */
    ULONG PacketsSent;          /**!< Number of packets sent. */
    ULONG PacketsReceived;       /**!< Number of packets received. */
    ULONG ErrorsSent;           /**!< Number of errors sent. */
    ULONG ErrorsReceived;        /**!< Number of errors received. */
    ULONG UnicastPacketsSent;   /**!< Number of unicast packets sent. */
    ULONG UnicastPacketsReceived; /**!< Number of unicast packets received. */
    ULONG DiscardPacketsSent;    /**!< Number of discarded packets sent. */
    ULONG DiscardPacketsReceived; /**!< Number of discarded packets received. */
    ULONG MulticastPacketsSent;  /**!< Number of multicast packets sent. */
    ULONG MulticastPacketsReceived; /**!< Number of multicast packets received. */
    ULONG BroadcastPacketsSent;   /**!< Number of broadcast packets sent. */
    ULONG BroadcastPacketsReceived; /**!< Number of broadcast packets received. */
    ULONG UnknownProtoPacketsReceived; /**!< Number of packets received with unknown protocols. */
} CCSP_HAL_ETH_STATS,*PCCSP_HAL_ETH_STATS;

/* 
* TODO: Evaluate if the typedef  `_CCSP_HAL_ETH_STATS & *PCCSP_HAL_ETH_STATS` is necessary.
*   - Verify and document the specific units for each statistic (e.g., bytes, packets, errors per second or total).
*/

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
 * TODO (Enhance Error Reporting):
 *   - Replace generic `RETURN_ERR` with an enumerated error code type for improved clarity and debugging.
 *   - Define specific error codes to pinpoint various failure scenarios, including:
 *       - Invalid input parameters (e.g., null pointers, out-of-range values)
 *       - Resource allocation failures (e.g., out-of-memory)
 *       - Communication or timeout issues with external systems (e.g., Ethernet switch)
 *       - Internal errors within the HAL
 *   - Document the new error codes thoroughly in the header file and any relevant guides.
 */

/**!
 * @brief Initializes the Ethernet Switch (EthSW) HAL.
 *
 * This function sets up the necessary resources and configurations for the EthSW HAL to function.
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On successful initialization.
 * @retval RETURN_ERR - On failure (check for specific error details).
 */
INT CcspHalEthSwInit(void); 

/**!
 * @brief Retrieves the status information for a specified Ethernet switch port.
 *
 * This function fetches the link rate, duplex mode, and link status of the given port.
 *
 * @param[in] PortId - Identifier of the Ethernet switch port (see `CCSP_HAL_ETHSW_PORT`).
 * @param[out] pLinkRate - Pointer to a `CCSP_HAL_ETHSW_LINK_RATE` variable to store the link rate.
 * @param[out] pDuplexMode - Pointer to a `CCSP_HAL_ETHSW_DUPLEX_MODE` variable to store the duplex mode.
 * @param[out] pStatus - Pointer to a `CCSP_HAL_ETHSW_LINK_STATUS` variable to store the link status.
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On success.
 * @retval RETURN_ERR - On failure (e.g., invalid port ID, retrieval error).
 */
INT CcspHalEthSwGetPortStatus (
    CCSP_HAL_ETHSW_PORT PortId, 
    PCCSP_HAL_ETHSW_LINK_RATE pLinkRate, 
    PCCSP_HAL_ETHSW_DUPLEX_MODE pDuplexMode, 
    PCCSP_HAL_ETHSW_LINK_STATUS pStatus
);

/**!
 * @brief Retrieves the configuration of a specified Ethernet switch port.
 *
 * This function fetches the configured link rate and duplex mode of the given port.
 *
 * @param[in]  PortId - Identifier of the Ethernet switch port (see `CCSP_HAL_ETHSW_PORT`).
 * @param[out] pLinkRate - Pointer to a `CCSP_HAL_ETHSW_LINK_RATE` variable to store the link rate.
 * @param[out] pDuplexMode - Pointer to a `CCSP_HAL_ETHSW_DUPLEX_MODE` variable to store the duplex mode.
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On success.
 * @retval RETURN_ERR - On failure (e.g., invalid port ID, retrieval error).
 */
INT CcspHalEthSwGetPortCfg (
    CCSP_HAL_ETHSW_PORT PortId, 
    PCCSP_HAL_ETHSW_LINK_RATE pLinkRate, 
    PCCSP_HAL_ETHSW_DUPLEX_MODE pDuplexMode
);

/**!
 * @brief Configures the link rate and duplex mode for a specific Ethernet switch port.
 *
 * @param[in] PortId - Identifier of the Ethernet switch port to configure (see `CCSP_HAL_ETHSW_PORT`).
 * @param[in] LinkRate - Desired link rate (see `CCSP_HAL_ETHSW_LINK_RATE`).
 * @param[in] DuplexMode - Desired duplex mode (see `CCSP_HAL_ETHSW_DUPLEX_MODE`).
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On success.
 * @retval RETURN_ERR - On failure (e.g., invalid port ID, invalid configuration values).
 */
INT CcspHalEthSwSetPortCfg(
    CCSP_HAL_ETHSW_PORT PortId,
    CCSP_HAL_ETHSW_LINK_RATE LinkRate,
    CCSP_HAL_ETHSW_DUPLEX_MODE DuplexMode
);

/**!
 * @brief Retrieves the administrative status of a specified Ethernet switch port.
 *
 * @param[in] PortId - Identifier of the Ethernet switch port (see `CCSP_HAL_ETHSW_PORT`).
 * @param[out] pAdminStatus - Pointer to a `CCSP_HAL_ETHSW_ADMIN_STATUS` variable to store the admin status.
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On success.
 * @retval RETURN_ERR - On failure (e.g., invalid port ID, retrieval error).
 */
INT CcspHalEthSwGetPortAdminStatus (
    CCSP_HAL_ETHSW_PORT PortId, 
    PCCSP_HAL_ETHSW_ADMIN_STATUS pAdminStatus
);

/**!
 * @brief Sets the administrative status of a specific Ethernet switch port.
 *
 * @param[in] PortId - Identifier of the Ethernet switch port (see `CCSP_HAL_ETHSW_PORT`).
 * @param[in] AdminStatus - New administrative status (0: Down, 1: Up).
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On success.
 * @retval RETURN_ERR - On failure (e.g., invalid port ID, invalid admin status value).
 */
INT CcspHalEthSwSetPortAdminStatus(
    CCSP_HAL_ETHSW_PORT PortId,
    CCSP_HAL_ETHSW_ADMIN_STATUS AdminStatus
); 

/**!
 * @brief Sets the aging speed for the specified Ethernet switch port.
 *
 * This function configures the aging speed for a given port on the Ethernet switch. The aging speed determines how long a MAC address entry remains in the switch's forwarding table without receiving traffic.
 *
 * @param[in] PortId - Identifier of the Ethernet switch port (see `CCSP_HAL_ETHSW_PORT`).
 * @param[in] AgingSpeed - New aging speed value (vendor-specific).
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On success.
 * @retval RETURN_ERR - On failure (e.g., invalid port ID, invalid aging speed value).
 */
INT CcspHalEthSwSetAgingSpeed(CCSP_HAL_ETHSW_PORT PortId, INT AgingSpeed); 

/**!
 * @brief Locates the port associated with a given MAC address on a MoCA or Ethernet switch.
 *
 * This function searches for a specific MAC address in the MoCA or Ethernet switch's MAC address tables.
 *
 * @param[in] mac - Pointer to a 6-byte array containing the MAC address (e.g., "00:1A:2B:11:B2:33").
 * @param[out] port - Pointer to an integer where the port number will be stored:
 *                   - 0: MoCA port
 *                   - 1-4: Ethernet port
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On success (MAC address found and port stored in `port`).
 * @retval RETURN_ERR - On failure (e.g., MAC address not found, invalid input parameters).
 */
INT CcspHalEthSwLocatePortByMacAddress(unsigned char *mac, INT *port);

/** Ethernet HAL Callback for Client Association/Disassociation Notifications */

/**
 * @}
 */

/**
 * @addtogroup ETHSW_HAL_TYPES
 * @{
 */

/**! Represents details of an Ethernet device connected to a switch port. */
typedef struct _eth_device {
    UCHAR eth_devMacAddress[6];  /**!< MAC address (e.g., "00:1A:2B:11:B2:33"). */
    INT eth_port;               /**!< External port the device is attached to (0 to MaxEthPort-1). */
    INT eth_vlanid;             /**!< VLAN ID the port is tagged with (1 to 4094). */
    INT eth_devTxRate;          /**!< Transmit speed (vendor-specific). */
    INT eth_devRxRate;          /**!< Receive speed (vendor-specific). */
    BOOLEAN eth_Active;         /**!< Indicates if the device is online (true) or offline (false). */
} eth_device_t;

/*
* TODO:
*   - Document the units for `eth_devTxRate` and `eth_devRxRate` (e.g., Mbps).
*   - Evaluate `_eth_device` for removal since typedef is used it's optional and not required.
*/

/**
 * @}
 */


/**
 * @addtogroup ETHSW_HAL_APIS
 * @{
 */

/**!
 * @brief Retrieves information about associated Ethernet devices.
 *
 * This function populates an array with details of connected devices and returns the array size.
 *
 * **Important:** The HAL allocates memory for the device array (`output_struct`). The caller is responsible for freeing this memory.
 *
 * @param[out] output_array_size - Pointer to an unsigned long integer where the size of the array will be stored.
 * @param[out] output_struct - Pointer to an array of `eth_device_t` structures to be populated with device details.
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On success.
 * @retval RETURN_ERR - On failure (e.g., null pointers, memory allocation issues, or retrieval errors).
 */
INT CcspHalExtSw_getAssociatedDevice(ULONG *output_array_size, eth_device_t **output_struct);

/**!
 * @brief Callback function invoked for Ethernet client association/disassociation events.
 * 
 * This callback is triggered when a new Ethernet client associates with the access point (AP) or an existing client disassociates. It provides details about the associated/disassociated device.
 *
 * @param[in] eth_dev - Pointer to an `eth_device_t` structure containing information about the associated/disassociated Ethernet device.
 *
 * @returns Status of the callback operation:
 * @retval RETURN_OK - On successful processing of the event.
 * @retval RETURN_ERR - On error.  (e.g. null pointers, or mac address not found)
 */
typedef INT (*CcspHalExtSw_ethAssociatedDevice_callback)(eth_device_t *eth_dev);

/**!
 * @brief Registers a callback function for Ethernet client association/disassociation events.
 *
 * @param[in] callback_proc - Pointer to the `CcspHalExtSw_ethAssociatedDevice_callback` function to be registered.
 */
void CcspHalExtSw_ethAssociatedDevice_callback_register(CcspHalExtSw_ethAssociatedDevice_callback callback_proc);

/*
 *TODO: Ensure the upper layers have a consistent interface for all platforms and configurations. Functions on unsupported platforms should return a NOT_SUPPORTED enum. Remove build flags for features in the interface between layers, allowing the same binary upper layer to run against any vendor implementation without rebuilding.
 */

#ifdef FEATURE_RDKB_WAN_MANAGER
#ifdef FEATURE_RDKB_AUTO_PORT_SWITCH

/**!
 * @brief Configures an Ethernet port for WAN functionality.
 *
 * This function enables or disables the Ethernet WAN feature on a specific port. 
 *
 * @param[in] ifname - Name of the Ethernet interface to configure (e.g., "eth0", "eth1", etc.).
 * @param[in] WanMode - Boolean value indicating whether to enable (true) or disable (false) Ethernet WAN on the port.
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On success.
 * @retval RETURN_ERR - On failure (e.g., invalid interface name, configuration error).
 */
int CcspHalExtSw_ethPortConfigure(char *ifname, BOOLEAN WanMode);

#endif // FEATURE_RDKB_AUTO_PORT_SWITCH
#endif // FEATURE_RDKB_WAN_MANAGER

//<<

/**!
 * @brief Retrieves the Ethernet WAN enable status.
 *
 * @param[out] pFlag - Pointer to a BOOLEAN variable to store the Ethernet WAN enable status.
 *                      - true (1): Ethernet WAN is enabled.
 *                      - false (0): Ethernet WAN is disabled.
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On success.
 * @retval RETURN_ERR - On failure (e.g., null pointer).
 */
INT CcspHalExtSw_getEthWanEnable(BOOLEAN *pFlag);

/**!
 * @brief Enables or disables Ethernet WAN functionality.
 *
 * @param[in] Flag - Boolean value:
 *                     - true (1): Enable Ethernet WAN.
 *                     - false (0): Disable Ethernet WAN.
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On success.
 * @retval RETURN_ERR - On failure.
 */
INT CcspHalExtSw_setEthWanEnable(BOOLEAN Flag);
#ifdef FEATURE_RDKB_AUTO_PORT_SWITCH
/**!
 * @brief Retrieves the current hardware (HW) WAN configuration status.
 *
 * @returns The current WAN HW configuration status:
 * @retval TRUE - WAN is enabled.
 * @retval FALSE - LAN is enabled.
 */
BOOLEAN CcspHalExtSw_getCurrentWanHWConf();
#endif

/**!
 * @brief Retrieves the Ethernet WAN port number.
 *
 * This function retrieves the numerical index of the Ethernet port currently configured for WAN functionality.
 *
 * @param[out] pPort - Pointer to an unsigned integer variable where the port number will be stored. Valid range: 0 to (MaxEthPort - 1).
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On success.
 * @retval RETURN_ERR - On failure (e.g., invalid pointer, retrieval error).
 */
INT CcspHalExtSw_getEthWanPort(UINT *pPort);

/**!
 * @brief Sets the Ethernet WAN interface/port number.
 *
 * This function configures which Ethernet port will be used for the WAN connection.
 *
 * @param[in] Port - The port number to set as the Ethernet WAN port. Valid range: 0 to (MaxEthPort - 1).
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On success.
 * @retval RETURN_ERR - On failure (e.g., invalid port number, configuration error).
 */
INT CcspHalExtSw_setEthWanPort(UINT Port);

/**!
 * @brief Retrieves statistics for a specified Ethernet switch port.
 *
 * This function populates the provided structure with various statistics about the specified Ethernet switch port.
 *
 * @param[in]  PortId - Identifier of the Ethernet switch port (see `CCSP_HAL_ETHSW_PORT`).
 * @param[out] pStats - Pointer to a `CCSP_HAL_ETH_STATS` structure to store the retrieved statistics.
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On success.
 * @retval RETURN_ERR - On failure (e.g., invalid port ID, retrieval error).
 */
INT CcspHalEthSwGetEthPortStats(CCSP_HAL_ETHSW_PORT PortId, PCCSP_HAL_ETH_STATS pStats);

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

/**! Callback function to be invoked when the Ethernet WAN link goes up. */
typedef void (*fpEthWanLink_Up)(); 

/**! Callback function to be invoked when the Ethernet WAN link goes down. */
typedef void (*fpEthWanLink_Down)();

/**! Stores callback functions for Ethernet WAN link status changes. */
typedef struct __appCallBack {
    fpEthWanLink_Up pGWP_act_EthWanLinkUP; /**!< Callback for EthWan link up event. */
    fpEthWanLink_Down pGWP_act_EthWanLinkDown; /**!< Callback for EthWan link down event. */
} appCallBack;

/**
 * @}
 */

/**
 * @addtogroup ETHSW_HAL_APIS
 * @{
 */

/**!
 * @brief Registers RDKB callback functions for Ethernet WAN events.
 *
 * @param[in] obj - Pointer to an `appCallBack` struct containing the callback functions to be registered.
 */
void GWP_RegisterEthWan_Callback(appCallBack *obj);

/**!
 * @brief Retrieves the current status of the Ethernet WAN (EthWAN) link.
 *
 * @returns Status of the EthWAN link:
 * @retval 1 - Link is up (active).
 * @retval 0 - Link is down (inactive).
 * @retval < 0 - Error occurred (check errno for details).
 */
INT GWP_GetEthWanLinkStatus();

/**!
 * @brief Retrieves the name of the Ethernet WAN (EthWAN) interface.
 *
 * This function populates the provided buffer with the name of the currently active EthWAN interface.
 *
 * @param[out] Interface - Buffer (min. 64 bytes) to store the interface name (vendor-specific).
 * @param[in]  maxSize   - Maximum size of the buffer (11 to 262 bytes).
 *
 * @returns Status of the operation:
 * @retval RETURN_OK - On success.
 * @retval RETURN_ERR - On failure (e.g., null pointer, insufficient buffer size).
 */
INT GWP_GetEthWanInterfaceName(unsigned char *Interface, ULONG maxSize);

#endif /* __CCSP_HAL_ETHSW_H__ */

/**
 * @}
 */


