#include "HapticInterface.h"
#include <iostream>

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

void HapticInterface::getDevicePosition(vec3& position)
{
	HLdouble aux[3];
	hlGetDoublev(HL_DEVICE_POSITION, aux);
	for (int i = 0; i < 3; ++i)
		position[i] = static_cast<float>(aux[i]);
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
	updateState(0);
	force = this->force;
}

void HapticInterface::getLastProxyPosition(vec3& lastPosition)
{
	updateState(5);
	lastPosition = this->position;
}

void HapticInterface::getProxyPosition(vec3& position)
{
	updateState(1);
	position = this->position;
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
	hlTouchableFace(HL_FRONT);
	hlEnable(HL_HAPTIC_CAMERA_VIEW);
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

/*HDCallbackCode HDCALLBACK HapticInterface::setForce(void* userData)
{
	HDdouble faux[3];
	float anchorStiffness = 0.1f;
	hdBeginFrame(device);
	hdGetDoublev(HD_CURRENT_POSITION, faux);

	for (int i = 0; i < 3; ++i)
		force[i] = static_cast<float>(faux[i]);

	force = position - anchor;
	force = force * anchorStiffness;

	for (int i = 0; i < 3; ++i)
		faux[i] = force[i];

	hdSetDoublev(HD_CURRENT_FORCE, faux);
	hdEndFrame(device);
	return HD_CALLBACK_DONE;
}*/

void HapticInterface::terminateHL()
{
	hlMakeCurrent(NULL);
	hlDeleteContext(context);
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

void HapticInterface::updateHapticWorkspace(const mat4& modelview, 
	const mat4& projection, const vec4& viewport)
{
	double mv[16], p[16];
	HDdouble wMatrix[16];
	int vp[4];

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; i < 4; ++j) {
			mv[i] = modelview[i][j];
			p[i] = projection[i][j];
		}
		vp[i] = static_cast<int>(viewport[i]);
	}

	hlWorkspace(-80, -80, -80, 80, 80, 80);
	hlMatrixMode(HL_TOUCHWORKSPACE);
	hduMapWorkspaceModel(mv, p, wMatrix);
	scaleFactor = cursorPixelSize *
		hduScreenToWorkspaceScale(mv, p, vp, wMatrix);

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; i < 4; ++j) {
			workspaceMatrix[i][j] = static_cast<float>(wMatrix[4 * i + j]);
		}
	}
}

void HapticInterface::updateState(int flag)
{
	updateFlag = flag;
	UpdateStructure us;
	us.flag = updateFlag;
	hdScheduleSynchronous(stateCallback, &us, HD_MIN_SCHEDULER_PRIORITY);
}
