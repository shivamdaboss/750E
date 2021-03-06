/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

FILE *outputFile;

#define LF 4
#define LB 5
#define RF 6
#define RB 7

void moveArm() {
	if (joystickGetDigital(1, 7, JOY_LEFT)) {
		motorSet(RB, -70);
		motorSet(RF, -70);
		motorSet(LB, 70);
		motorSet(LF, 70);
	} else if (joystickGetDigital(1, 7, JOY_DOWN)) {
		motorSet(RB, 70);
		motorSet(RF, 70);
		motorSet(LB, -70);
		motorSet(LF, -70);
	} else {
		if (joystickGetDigital(1, 6, JOY_UP)) {
			motorSet(RB, -40);
			motorSet(RF, -40);
		} else if (joystickGetDigital(1, 6, JOY_DOWN)) {
			motorSet(RB, 40);
			motorSet(RF, 40);
		} else {
			motorSet(RB, 0);
			motorSet(RF, 0);
		}

		if (joystickGetDigital(1, 5, JOY_UP)) {
			motorSet(LB, 40);
			motorSet(LF, 40);
		} else if (joystickGetDigital(1, 5, JOY_DOWN)) {
			motorSet(LB, -40);
			motorSet(LF, -40);
		} else {
			motorSet(LB, 0);
			motorSet(LF, 0);
		}
	}
}

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {
	outputFile = fopen("arm.csv", "w");
	print("Uncalibrated. Press the left 8 button to calibrate.\n\r");
	while (1) {
		moveArm();
		if (joystickGetDigital(1, 8, JOY_UP)) {
			fprintf(outputFile, "%d,%d\n", analogRead(1), analogRead(2));
			printf("Values recorded: %d %d\n\r", analogRead(1), analogRead(2));
			while (joystickGetDigital(1, 8, JOY_UP)) { delay(20); }
		} else if (joystickGetDigital(1, 8, JOY_DOWN)) {
			fclose(outputFile);
			print("File ready to be read.\n\r");
			while (joystickGetDigital(1, 8, JOY_DOWN)) { delay(20); }
		} else if (joystickGetDigital(1, 8, JOY_LEFT)) {
			print("Calibrating...\n\r");
			analogCalibrate(1);
			analogCalibrate(2);
			print("Calibrated arm.\n\r");
			while (joystickGetDigital(1, 8, JOY_LEFT)) { delay(20); }
		}
		delay(20);
	}
}
