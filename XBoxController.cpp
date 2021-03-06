// XBoxController.cpp : Defines the entry point for the console application.
//
#include <Windows.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <Xinput.h>
#include "XboxHeader.h"
#include "XInputWrapper.h"

// According the XINPUT on MS docs, max expected value is 32767
#define MAX_RADIUS_LEFT 32768.0
#define MAX_RADIUS_RIGHT 32768.0 /*Some placeholder number*/
#define PI 3.14159265

#define Player1 0
#define Player2 1
#define Player3 2
#define Player4 3

//void ButtonPresses(GamePad::XBoxController *controller);


GamePad::XBoxController::XBoxController(XInputWrapper* xinput, DWORD id) {
	this->xinput = xinput;
	ID = id;
}

bool GamePad::XBoxController::IsConnected() {
	if (xinput->XInputGetState(this->ID, &State) == ERROR_SUCCESS) {
		return true;
	}
	return false;
}

XINPUT_STATE *GamePad::XBoxController::GetState() {
	return &State;
}
DWORD GamePad::XBoxController::GetControllerId() {
	return ID;
}


bool GamePad::XBoxController::PressedA() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		return true;
	}
	return false;
}
bool GamePad::XBoxController::PressedB() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
		return true;
	}
	return false;
}
bool GamePad::XBoxController::PressedX() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		return true;
	}
	return false;
}
bool GamePad::XBoxController::PressedY() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
		return true;
	}
	return false;
}
bool GamePad::XBoxController::PressedLeftShoulder() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
		return true;
	}
	return false;
}
bool GamePad::XBoxController::PressedRightShoulder() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		return true;
	}
	return false;
}
bool GamePad::XBoxController::PressedLeftDpad() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
		return true;
	}
	return false;
}
bool GamePad::XBoxController::PressedRightDpad() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
		return true;
	}
	return false;
}
bool GamePad::XBoxController::PressedUpDpad() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
		return true;
	}
	return false;
}
bool GamePad::XBoxController::PressedDownDpad() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
		return true;
	}
	return false;
}
bool GamePad::XBoxController::PressedStart() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_START) {
		return true;
	}
	return false;
}
bool GamePad::XBoxController::PressedBack() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) {
		return true;
	}
	return false;
}
bool GamePad::XBoxController::PressedLeftThumb() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) {
		return true;
	}
	return false;
}
bool GamePad::XBoxController::PressedRightThumb() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) {
		return true;
	}
	return false;
}
BYTE GamePad::XBoxController::LeftTriggerLocation() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
		BYTE output = int(17.0 / 15.0 * State.Gamepad.bLeftTrigger - 34.0);
		return output;
		//std::cout << output << std::endl;
	}
	return 0;
}
BYTE GamePad::XBoxController::RightTriggerLocation() {
	xinput->XInputGetState(this->ID, &State);
	if (State.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
		BYTE output = int(17.0 / 15.0 * State.Gamepad.bRightTrigger - 34.0);
		//	std::cout << output << std::endl;
		return output;

	}
	return 0;
}
void GamePad::XBoxController::Vibrate(WORD left, WORD right) {
	VibrateState.wLeftMotorSpeed = left;
	VibrateState.wRightMotorSpeed = right;
	xinput->XInputSetState(GetControllerId(), &VibrateState);
}
GamePad::Coordinate GamePad::XBoxController::LeftThumbLocation() {
	xinput->XInputGetState(this->ID, &State);
	SHORT lx = State.Gamepad.sThumbLX;
	SHORT ly = State.Gamepad.sThumbLY;
	double Radius = sqrt(lx * lx + ly * ly);

	// Deadzone check
	if (Radius < StickDeadzone) {
		return Coordinate(0, 0);
	}
	// Capping the radius
	if (Radius > MAX_RADIUS_LEFT) {
		Radius = MAX_RADIUS_LEFT;
	}

	double Angle;
	// Need conditions that prevent it from shitting itself (division by zero)
	// -> Compute magnitude and angle. 
	if (lx == 0 && ly > 0) {
		Angle = PI / 2;
	}
	else if (lx == 0 && ly < 0) {
		Angle = -PI / 2;
	}
	else {
		Angle = atan2(ly, lx);
	}

	// Perform transformation
	double Gradient = MAX_RADIUS_LEFT / (MAX_RADIUS_LEFT - StickDeadzone);
	double r_O = Gradient * (Radius - StickDeadzone);

	
	lx = SHORT(r_O * cos(Angle));
	ly = SHORT(r_O * sin(Angle));
	return GamePad::Coordinate(lx, ly);
}

GamePad::Coordinate GamePad::XBoxController::RightThumbLocation() {
	xinput->XInputGetState(this->ID, &State);
	SHORT Rx = State.Gamepad.sThumbRX;
	SHORT Ry = State.Gamepad.sThumbRY;
	double Radius = sqrt(Rx * Rx + Ry * Ry);
	if (Radius < StickDeadzone) {
		return Coordinate(0, 0);
	}
	// Capping the radius -> REVISE THIS NUMBER, I DON'T BELIEVE IT IS WORKING AS INTENDED
	if (Radius > MAX_RADIUS_RIGHT) {
		Radius = MAX_RADIUS_RIGHT;
	}

	double Angle;
	// -> Compute magnitude and angle. 
	if (Rx == 0 && Ry > 0) {
		Angle = PI / 2;
	}
	else if (Rx == 0 && Ry < 0) {
		Angle = -PI / 2;
	}
	else {
		Angle = atan2(Ry, Rx);
	}

	// -> Perform transformation
	double Gradient = MAX_RADIUS_RIGHT / (MAX_RADIUS_RIGHT - StickDeadzone);
	double r_O = Gradient * (Radius - StickDeadzone);
	//std::cout << Radius <<"	"<< Radius * cos(Angle) << "		" << Radius * sin(Angle) << "	" << Angle << std::endl;
	// Returned transformed numbers as rectangular coordinates
	Rx = SHORT(r_O * cos(Angle));
	Ry = SHORT(r_O * sin(Angle));
	return GamePad::Coordinate(Rx, Ry);
}


void GamePad::XBoxController::SetDeadzone(unsigned int radius) {
	StickDeadzone = radius;
}
XINPUT_BATTERY_INFORMATION * GamePad::XBoxController::GetBattery() {
	return &Battery;
}



/*
int main()
{
	XInputWrapper xinput;



	GamePad::XBoxController P1controller(&xinput, Player1);
	GamePad::XBoxController P2controller(&xinput, Player2);


	//xinput.XInputGetBatteryInformation(Player2, BATTERY_DEVTYPE_GAMEPAD, P2controller.GetBattery());
	//XINPUT_BATTERY_INFORMATION* temp = P2controller.GetBattery();
	//int b = temp->BatteryLevel;
	//std::cout << b << std::endl;
	//getchar();

	while (1) {
		if (P1controller.IsConnected() != true) {
			std::cout << "P1 is not connected" << std::endl;
			getchar();
			return 1;
		}
		xinput.XInputGetState(P1controller.GetControllerId(), P1controller.GetState());
		xinput.XInputGetState(P2controller.GetControllerId(), P2controller.GetState());
		//std::cout << (int) P1controller.LeftTriggerLocation() << std::endl;

		ButtonPresses(&P1controller);
		ButtonPresses(&P2controller);
		//Trigger test -> Succesfull



		GamePad::Coordinate *LeftThumbpos = &P1controller.LeftThumbLocation();
		GamePad::Coordinate *RightThumbpos = &P1controller.RightThumbLocation();
		std::cout << LeftThumbpos->GetX() << "		" << LeftThumbpos->GetY() << "	  " << RightThumbpos->GetX() << "	   " << RightThumbpos->GetY() << "		" << (int)P1controller.LeftTriggerLocation() << "		" << (int)P1controller.RightTriggerLocation() << std::endl;


	}


	return 0;
}

void ButtonPresses(GamePad::XBoxController  *controller) {
	controller->SetDeadzone(10000);
	// Button tests -> successfull, including multi button input
	if (controller->PressedA()) {
		std::cout << "A was pressed" << std::endl;
	}
	if (controller->PressedB()) {
		std::cout << "B was pressed" << std::endl;
	}
	if (controller->PressedX()) {
		std::cout << "X was pressed" << std::endl;
	}
	if (controller->PressedY()) {
		std::cout << "Y was pressed" << std::endl;
	}
	if (controller->PressedLeftShoulder()) {
		std::cout << "Left Shoulder was pressed" << std::endl;
	}
	if (controller->PressedRightShoulder()) {
		std::cout << "Right Shoulder was pressed" << std::endl;
	}
	if (controller->PressedRightThumb()) {
		std::cout << "Right thumb was pressed" << std::endl;
	}
	if (controller->PressedLeftThumb()) {
		std::cout << "Left thumb was pressed" << std::endl;
	}
	if (controller->PressedDownDpad()) {
		std::cout << "Dpad down was pressed" << std::endl;
	}
	if (controller->PressedUpDpad()) {
		std::cout << "Dpad up was pressed" << std::endl;
	}
	if (controller->PressedLeftDpad()) {
		std::cout << "Dpad left was pressed" << std::endl;
	}
	if (controller->PressedRightDpad()) {
		std::cout << "Dpad right was pressed" << std::endl;
	}
	if (controller->PressedStart()) {
		std::cout << "Start was pressed" << std::endl;
	}
	if (controller->PressedBack()) {
		std::cout << "Back was pressed" << std::endl;
	}
	if (controller->PressedA()) {
		controller->Vibrate(20000, 65000);
	}
	else if (controller->PressedB()) {
		controller->Vibrate(0, 0);
	}
}*/
