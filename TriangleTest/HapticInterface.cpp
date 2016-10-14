#include "HapticInterface.h"
#include <iostream>
#include <GL\GL.h>

using std::cerr;
using std::cout;
using std::endl;

typedef struct {
	HDint flag;
	HDdouble data[3];
} UpdateStructure;


HapticInterface::HapticInterface()
	: device(HD_INVALID_HANDLE), context(0), enabled(false),
	cursorPixelSize(20), stiffness(1.0f), damping(0.0f),
	staticFriction(0.0f), dynamicFriction(0.0f), pop(1.0f)
{
	anchor[0] = anchor[1] = anchor[2] = 0.0f;
}


HapticInterface::~HapticInterface()
{
}

HDCallbackCode HDCALLBACK HapticInterface::calibrationLoop(void* userData)
{
	HDenum * aux = static_cast<HDenum*>(userData);
	hlBeginFrame();
	*aux = hdCheckCalibration();
	hlEndFrame();
	return HD_CALLBACK_DONE;
}

bool HapticInterface::checkCalibration()
{
	getCalibrationStatus();
	if (calibrationStatus == HD_CALIBRATION_NEEDS_UPDATE) {
		hdScheduleSynchronous(updateCalibration, &calibrationType,
			HD_DEFAULT_SCHEDULER_PRIORITY);
		if (hdGetError().errorCode != HD_SUCCESS) {
			cerr << "Falha ao atualizar a calibracao." << endl;
			return false;
		}
		else return true;
	}
	else if (calibrationStatus == HD_CALIBRATION_NEEDS_MANUAL_INPUT)
		return false;
	else if (calibrationStatus == HD_CALIBRATION_OK)
		return true;
	else return false;
}

void HapticInterface::checkCalibrationStatus()
{
	HDint styles;
	hdGetIntegerv(HD_CALIBRATION_STYLE, &styles);

	if (styles & HD_CALIBRATION_AUTO) {
		calibrationType = HD_CALIBRATION_AUTO;
		return;
	}

	if (styles & HD_CALIBRATION_INKWELL) {
		calibrationType = HD_CALIBRATION_INKWELL;
		return;
	}

	if (styles & HD_CALIBRATION_ENCODER_RESET) {
		calibrationType = HD_CALIBRATION_ENCODER_RESET;
		cerr << "Calibracao nao implementada" << endl;
	}
}

HDenum HapticInterface::getCalibrationStatus()
{
	hdScheduleSynchronous(calibrationLoop, &calibrationStatus,
		HD_MIN_SCHEDULER_PRIORITY);
	return calibrationStatus;
}

HHD HapticInterface::getDevice()
{
	return device;
}

vec3& HapticInterface::getDevicePosition()
{
	HLdouble aux[4];
	hlGetDoublev(HL_DEVICE_POSITION, aux);
	aux[3] = 1.0;
	vec4 wpos;

	for (int i = 0; i < 4; ++i)
		wpos[i] = static_cast<float>(aux[i]);

	wpos = wpos * workspaceMatrix;

	for (int i = 0; i < 3; ++i)
		position[i] = wpos[i];

	return position;
}

void HapticInterface::getDeviceRotation(vec3& rotation)
{
	HLdouble aux[3];
	hlGetDoublev(HL_DEVICE_ROTATION, aux);
	for (int i = 0; i < 3; ++i)
		rotation[i] = static_cast<float>(aux[i]);
}

void HapticInterface::getForceIntensity(vec3& force)
{
	updateState(0, force);
	this->force = force;
}

void HapticInterface::getLastProxyPosition(vec3& lastPosition)
{
	updateState(5, lastPosition);
}

vec3& HapticInterface::getPosition()
{
	return position;
}

void HapticInterface::getProxyPosition(vec3& position)
{
	updateState(1, position);
	this->position = position;
}

double HapticInterface::getScaleFactor()
{
	return scaleFactor;
}

void HapticInterface::idleFunction()
{
	HLerror error;
	while(HL_ERROR(error = hlGetError())){
		cerr << "Erro: " << error.errorCode << endl;
	}

	/*if(!workspaceUpdated){
		updateHapticWorkspace();
		workspaceUpdated = true;
	}*/
}

void HapticInterface::initializeHL()
{
	device = hdInitDevice(HD_DEFAULT_DEVICE);
	if(hdGetError().errorCode != HD_SUCCESS){
		cerr << "Falha ao inicializar o dispositivo haptico" << endl;
		return;
	}

	context = hlCreateContext(device);
	hlMakeCurrent(context);
	hlTouchableFace(HL_FRONT_AND_BACK);
	hdEnable(HD_FORCE_OUTPUT);
	hdStartScheduler();
	//contextCreated = true;
	//hlEnable(HL_HAPTIC_CAMERA_VIEW);
}

bool HapticInterface::isEnabled()
{
	return (device != HD_INVALID_HANDLE);
}

void HapticInterface::showDeviceInformation()
{
	cout << "Dispositivo: " << hdGetString(HD_DEVICE_MODEL_TYPE) << endl;
}

HDCallbackCode HDCALLBACK HapticInterface::stateCallback(void* userData)
{
	UpdateStructure* us = static_cast<UpdateStructure*>(userData);
	if (us->flag == 0) 
		hdGetDoublev(HD_CURRENT_FORCE, us->data);
	else if (us->flag == 1)
		hdGetDoublev(HD_CURRENT_POSITION, us->data);

	return HD_CALLBACK_DONE;
}

void HapticInterface::setAnchorPosition(const vec3& anchor)
{
	this->anchor = anchor;
}

void HapticInterface::setForce(const vec3& force)
{
	UpdateStructure us;
	us.flag = HD_CURRENT_FORCE;
	for (int i = 0; i < 3; ++i)
		us.data[i] = force[i];

	hdScheduleSynchronous(setForce, &us, HD_MAX_SCHEDULER_PRIORITY);
}

HDCallbackCode HDCALLBACK HapticInterface::setForce(void* userData)
{
	UpdateStructure* us = static_cast<UpdateStructure*>(userData);

	hdSetDoublev(HD_CURRENT_FORCE, us->data);
	return HD_CALLBACK_DONE;
}

void HapticInterface::setModelviewMatrix(const mat4& modelview)
{
	this->modelview = modelview;
}

void HapticInterface::setProjectionMatrix(const mat4& projection)
{
	this->projection = projection;
}

void HapticInterface::terminateHL()
{
	hlMakeCurrent(NULL);
	hlDeleteContext(context);
	hdStopScheduler();
	hdDisableDevice(device);
	device = HD_INVALID_HANDLE;	
}

HDCallbackCode HDCALLBACK HapticInterface::updateCalibration(void* userData)
{
	HDenum status = hdCheckCalibration();
	HDenum* type = static_cast<HDenum*>(userData);
	if (status == HD_CALIBRATION_NEEDS_UPDATE)
		hdUpdateCalibration(*type);
	return HD_CALLBACK_DONE;
}

void HapticInterface::updateHapticWorkspace()
{
	double mv[4][4], p[4][4];
	HDdouble wMatrix[16];
	int vp[4];

	glGetIntegerv(GL_VIEWPORT, vp);

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			mv[i][j] = modelview[i][j];
			p[i][j] = projection[i][j];
		}
	}

	hlWorkspace(-1, -1, -1, 1, 1, 1);
	hlMatrixMode(HL_TOUCHWORKSPACE);
	hduMapWorkspaceModel(&(mv[0][0]), &(p[0][0]), wMatrix);
	scaleFactor = cursorPixelSize *
		hduScreenToWorkspaceScale(&(mv[0][0]), &(p[0][0]), vp, wMatrix);

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			workspaceMatrix[i][j] = static_cast<float>(wMatrix[4 * i + j]);
		}
	}
}

void HapticInterface::updateState(int flag, vec3& data)
{
	updateFlag = flag;
	UpdateStructure us;
	us.flag = updateFlag;

	hdScheduleSynchronous(stateCallback, &us, HD_MIN_SCHEDULER_PRIORITY);

	for (int i = 0; i < 3; ++i)
		data[i] = static_cast<float>(us.data[i]);
}
