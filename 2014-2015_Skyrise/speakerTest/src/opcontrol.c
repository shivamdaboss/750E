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
	speakerInit();
	// Play a tune on the speaker
//	speakerPlayRtttl("Super Mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,"
//		"8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,"
//		"8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,"
//		"8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,"
//		"8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,8p.,"
//		"8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,"
//		"8p,16d#6,8p,16d6,8p,16c6");
	// Play a polyphonic tune on the speaker with 2 tracks
//	const char * rtttl[] = {
//			"BlackSabbath_Iron_Man:d=4,o=5,b=85:2g#.6, 2p, g#6, g#6, g#6, 2g#.6, 2p, g#6, g#6, g#6, 2g#.6, 2p, g#6, g#6, g#6, d6, f6, 8f6, 8g6, g6, 16a#6, 16a6, 16a#6, 16a6, 16a#6, 16a6, 8f6, 8f6, 8g6, g6, d6, f6, 8f6, 8g6, g6, 16a#6, 16a6, 16a#6, 16a6, 16a#6, 16a6, 8f6, 8f6, 8g6, g6, d6, f6, 8f6, 8g6, g6, 16a#6, 16a6, 16a#6, 16a6, 16a#6, 16a6"	,NULL};
//	while (1) {
	const char * rtttl[] = {
	        "Super Mario:d=4,o=5,b=100:"
	        "16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,"
	        "8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,"
	        "8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,"
	        "8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,"
	        "8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,8p.,"
	        "8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,"
	        "8p,16d#6,8p,16d6,8p,16c6",
	        "Super Mario:d=4,o=4,b=100:"
	        "16d,16d,32p,8d,16d,8d,8g5,8p,8g,8p,"
	        "8g5,16p,8e,16p,8c,16p,8f,8g,16f#,8f,16e.,16c5,16e5,8f5,16d5,8e5,8c5,16a,16b,8g,16p,"
	        "8g5,16p,8e,16p,8c,16p,8f,8g,16f#,8f,16e.,16c5,16e5,8f5,16d5,8e5,8c5,16a,16b,8g,16p,"
	        "8c,16p,16g,8p,8c5,8f,16p,16c5,16c5,16c5,8f,"
	        "8c,16p,16e,8p,16g,16c5,p.,8g,"
	        "8c,16p,16g,8p,8c5,8f,16p,16c5,16c5,16c5,8f,"
	        "8c,16g#,8p,16a#,8p,16c5",
	        NULL
	    };
	    speakerPlayArray(rtttl);
//	speakerPlayRtttl("Mission Impossible (Long):d=4,o=6,b=100:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,16g,8p,16g,8p,16a#,16p,16c7,16p,16g,8p,16g,8p,16f,16p,16f#,16p,16g,8p,16g,8p,16a#,16p,16c7,16p,16g,8p,16g,8p,16f,16p,16f#,16p,16a#,16g,2d,32p,16a#,16g,2c#,32p,16a#,16g,2c,16p,16a#5,16c");
//  speakerPlayRtttl("Axel F:d=8,o=6,b=125:4e,g.,e,16e,a,e,d,4e,b.,e,16e,c7,b,g,e,b,e7,16e,d,16d,b5,f#,4e,2p,4e,g.,e,16e,a,e,d,4e,b.,e,16e,c7,b,g,e,b,e7,16e,d,16d,b5,f#,4e");
//	speakerPlayRtttl("Ghostbusters:d=4,o=5,b=112:");
//		delay(20);
//	}
}