#ifndef definitions
#define definitions

#define DOC			"test.txt"										//The name of the file with the camera results

#define CTRL_PATH	"/home/student/Desktop/Project/vehicleControl"	//Path to vehicle control
#define VEH_CTRL	"vehicleControl"								//Name of vehcile control executable	

#define CAM_PATH	"home/student/Desktop/Project/camera"			//Path to camera
#define CAM			"camera"										//Name of camera executable

#define NEXTPOS 45					//The degree rotation to next position

//The codes used for orientation
#define FORWARD 00					//The code for facing the ball
#define BACKWARD 11					//The code for facing away from the ball
#define RIGHT 01					//The code for facing 90deg clockwise away from the ball
#define LEFT 10						//The code for facing 90deg anticlockwise away from the ball

//The codes used by forward()
#define START 0						//The caller code for calling forward through start
#define AVOID 1						//The caller code for calling forward through avoid
#define NESTED 2					//The caller code resulting from calling avoid while avoiding

//The codes that define the direction of rotations for avoid()
#define CLOCKWISE 90				//Used by avoid for 90deg right turns
#define ANTICLOCKWISE -90			//Used by avoid for 90deg left turns
 
#endif