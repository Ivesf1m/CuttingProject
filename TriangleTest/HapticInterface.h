#pragma once

#include "glm.hpp"

#include <HD/hd.h>
#include <HL/hl.h>
#include <HDU/hdu.h>

using glm::vec3;
using glm::vec4;
using glm::mat4;

class HapticInterface
{
public:
	HapticInterface();
	~HapticInterface();

	HHD getDevice();
	void getDevicePosition(vec3& position);
	void getDeviceRotation(vec3& rotation);
	void getForceIntensity(vec3& force);
	//void getLastForceIntensity(vec3& lastForce);
	void getLastProxyPosition(vec3& lastPosition);
	void getProxyPosition(vec3& position);
	//void getProxyRotation(vec3& rotation);
	double getScaleFactor();

	void setAnchorPosition(const vec3& anchor);

	void drawHapticScene();
	void idleFunction();
	void initializeHL();
	bool isEnabled();
	void showDeviceInformation();
	void terminateHL();
	void updateHapticWorkspace(const mat4& modelview, const mat4& projection,
		const vec4& viewport);
	void updateState(int flag);

private:
	HHD device;
	HHLRC context;
	HLenum** properties;
	mat4 workspaceMatrix;
	bool workspaceUpdated;
	vec3 anchor;
	vec3 position;
	vec3 force;
	double scaleFactor;
	double cursorPixelSize;
	bool enabled;
	int updateFlag;

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
	static HDCallbackCode HDCALLBACK stateCallback(void* userData);
	//static HDCallbackCode HDCALLBACK setForce(void* userData);
	static HDCallbackCode HDCALLBACK updateCalibration(void* userData);
};

