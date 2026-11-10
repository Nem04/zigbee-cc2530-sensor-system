
#ifndef GENERICAPP_H
#define GENERICAPP_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "ZComDef.h"

/*********************************************************************
 * CONSTANTS
 */

// These constants are only for example and should be changed to the
// device's needs
#define GENERICAPP_ENDPOINT           10

#define GENERICAPP_PROFID             0x0F04
#define GENERICAPP_DEVICEID           0x0001
#define GENERICAPP_DEVICE_VERSION     0
#define GENERICAPP_FLAGS              0

#define GENERICAPP_MAX_CLUSTERS   1
#define GENERICAPP_END_CLA 1


  

#define GENERICAPP_DETECT_SENSOR_MSG_TIMEOUT 2000  // Every 2 seconds
#define GENERICAPP_TRANSFER_RECV_DATA_TIMEOUT 100  // Every 200 mseconds


#define GENERICAPP_DETECT_SENSOR_MSG_EVT        0x0001
#define GENERICAPP_TRANSFER_RECV_DATA_EVT        0x0002
#define GENERICAPP_Stepper_motor_EVT        0x0004



#define HAL_USER_KEY_2 HAL_KEY_SW_1
#define HAL_USER_KEY_1 HAL_KEY_SW_6






/*********************************************************************
 * FUNCTIONS
 */

/*
 * Task Initialization for the Generic Application
 */
extern void GenericApp_Init( byte task_id );

/*
 * Task Event Processor for the Generic Application
 */
extern UINT16 GenericApp_ProcessEvent( byte task_id, UINT16 events );

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* GENERICAPP_H */
