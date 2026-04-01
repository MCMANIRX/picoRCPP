
#ifndef RC_CONFIG
#define RC_CONFIG

#define STATIC_HOST_IP   "192.168.1.137" // IP of my laptop 
#define HOTSPOT_IP       "192.168.137.1"
#define SSID             "XboxOne"
#define PASS             "ctgprshouldbearomhack"
#define ASSIGN_TOPIC     "/rc_ctrl/assign"  // for ID assignment
#define CTRL_TOPIC       "/rc_ctrl/+"       // for cient control
#define RC_TOPIC         "/rc/com"          // outbound car client channel
#define ASSIGN_REQ       "unassigned"       // to request id

#define TOPIC_SIZE      64
#define MESSAGE_SIZE    256

#define ENQ              0x5  // incoming tracking
#define ACK              0x6  // tracking reply

// operation codes (opcodes recieved from ctrl_client)
#define MOVE_OP          0x0  // move with x and y (drive and steer)
#define SCRIPT_OP        0x1  // denotes script-related message
#define WAIT_OP          0x2  // wait some amount of ms
#define MSG_OP           0x3  // script "echo" command
#define YMOVE_OP         0x4  // move with y (drive only)
#define PRINT_OP         0xe  // value to send back to print "echo" message in ctrl_client
#define ASSIGN_OP        0x1a // assign/reassign car ID
#define PARAMS_OP        0x1f // denotes sensor-data-related mesage
#define CAM_OP           0x20 // movement message from OpenCV-Python and MediaPipe camera logic


#define CAM_EVADE        0x0  // dodge obstacle
#define CAM_STOP_SIGN    0x1  // run stop sign detected routine
#define CAM_HARD_STOP    0x2  // hard stop to avoid crashes

// request codes
#define RSSI_REQ         0x21 // denotes RSSI-data-related message


// flags
#define SCRIPT_INCOMING  0x1  // car prepares to recieve script
#define SCRIPT_BEGIN     0xd  // car begins command sequence execution
#define SCRIPT_END       0x4  // command tx finished OR command sequence execution finished               
#define SCRIPT_RECEIVED  (ACK << 4) | SCRIPT_END  // send back to ctrl_client to begin sync command execution
#define SYNC_STATUS      0x2  // script flag

#define MATLAB_FLAG      0x40 // for decoding encrypted MATLAB communications

 

// drive related constants
#define SPEED_MULT      512   // converts int8 to int16 for 16-bit PWM register
#define STEER_MULT      1.15  // traction for different wheeled cars
#define STEER_THRESH    30    // threshold to steer motors
#define DRIVE_THRESH    10    //threshold to drive motors

// pins
#define DRIVE_B         14    // b
#define DRIVE_F         15    // f
#define STEER_L         12    // l
#define STEER_R         13    // r




// pins to ESP32-CAM to collect IP address
#define UART_TX         8    
#define UART_RX         9

#define TRIGGER_GPIO    3
#define ECHO_GPIO       2
#define ULT_LED_PIN     17

//I2C pins are default 
//#define SDA           4
//#define SCL           5


// multicore-related constants

#define IMU_PARAM_COUNT 1
#define IMU_BUF_LEN     (IMU_PARAM_COUNT * 2)+3
#define ULT_BUF_LEN     6
#define BAT_BUF_LEN     5 //avoid crash
#define ESP_BUF_LEN     7
#define SETTLE_THRESH   0.0005
#define RESET_THRESH    20

#define EULER_NORM      180.0f // to normalize half-float before transmission

#define YAW             0x0    // heading
#define IMU_INIT        0x1    // tell ctrl_client car is ready to drive
#define ULT_DIST        0x2    // ultrasonic distance
#define ULT_FLAG        0x3    // within range (80cm)
#define IMU_REHOME      0x4    // set IMU to 0
#define IMU_REF_SET     0xef   // reference yaw set from dashboard
#define BAT             0x5    // battery percentage
#define ESP_IP          0x6    // esp-32 IP address


#define ULT_THRESH      80     // threshold for detection of object
#define ULT_INTERVAL    10     // time interval between scans


const float Kp = 5109.0;       // proportional constant 

#endif



