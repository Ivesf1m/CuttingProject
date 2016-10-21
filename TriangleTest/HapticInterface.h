#pragma once

#include "glm.hpp"

#include <HD/hd.h>
#include <HL/hl.h>
#include <HDU/hdu.h>

#include "CollisionDetector.h"
#include "ray.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

class HapticInterface
{
public:
	HapticInterface();
	~HapticInterface();

	HHD getDevice();
	vec3& getDevicePosition();
	void getDeviceRotation(vec3& rotation);
	vec3& getPosition();
	double getScaleFactor();

	void setAnchorPosition(const vec3& anchor);
	void setCollisionDetector(CollisionDetector* detector);
	void setInterator(Ray* interator);
	void setForce(const vec3& force);

	//Matrices
	void setModelviewMatrix(const mat4& modelview);
	void setProjectionMatrix(const mat4& projection);

	void idleFunction();
	void initializeHL();
	bool isEnabled();
	void showDeviceInformation();
	void terminateHL();
	void updateHapticWorkspace();

	//Main callback
	static HDCallbackCode HDCALLBACK mainHapticCallback(void* data);

private:
	HHD device;
	HHLRC context;
	HLenum** properties;
	mat4 workspaceMatrix;
	bool workspaceUpdated;
	mat4 modelview;
	mat4 projection;
	vec3 anchor;
	vec3 position;
	vec3 force;
	double scaleFactor;
	double cursorPixelSize;
	bool enabled;
	bool contextCreated;
	bool endThread;
	int updateFlag;

	//Variables for the main haptic loop
	CollisionDetector* colDetector; //reference to the current collision detector
	Ray* interator; //reference to the current interator

	//Calibration variables
	bool calibrated;
	HDenum calibrationType;
	HDenum calibrationStatus;

	//Properties
	float stiffness;
	float damping;
	float staticFriction;
	float dynamicFriction;
	float pop;

	//Calibration functions
	bool checkCalibration();
	void checkCalibrationStatus();
	HDenum getCalibrationStatus();

	//Callbacks
	static HDCallbackCode HDCALLBACK calibrationLoop(void* userData);
	void HLCALLBACK checkCalibration(HLenum event, HLuint obj, HLenum thread,
		HLcache* cache, void* userData);
	static HDCallbackCode HDCALLBACK setForce(void* userData);
	static HDCallbackCode HDCALLBACK updateCalibration(void* userData);
};

