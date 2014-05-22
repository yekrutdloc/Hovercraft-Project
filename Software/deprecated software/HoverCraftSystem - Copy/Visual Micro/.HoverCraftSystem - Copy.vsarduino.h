/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Due (Programming Port), Platform=sam, Package=arduino
*/

#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
#define __SAM3X8E__
#define USB_VID 0x2341
#define USB_PID 0x003e
#define USBCON
#define USB_MANUFACTURER "\"Unknown\""
#define USB_PRODUCT "\"Arduino Due\""
#define ARDUINO 156
#define ARDUINO_MAIN
#define printf iprintf
#define __SAM__
#define __sam__
#define F_CPU 84000000L
#define __cplusplus
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__

#define __ICCARM__
#define __ASM
#define __INLINE
#define __GNUC__ 0
#define __ICCARM__
#define __ARMCC_VERSION 400678
#define __attribute__(noinline)

#define prog_void
#define PGM_VOID_P int
            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}




//
//
static msg_t Thread4(void *arg);
static msg_t Thread2(void *arg);
static void Thread1(void *arg);
void fr_DiffCalibration();
void fr_blackValueCalibration();
void fr_whiteValueCalibration();
void fr_findRange();
void fr_getPhotoArrayValues();
void fr_runBuzzerBeep();
static msg_t Thread5(void *arg);
static msg_t Thread3(void *arg);
void mainThread();
static msg_t Thread6(void *arg);
void br_DiffCalibration();
void br_blackValueCalibration();
void br_whiteValueCalibration();
void br_findRange();
void br_getPhotoArrayValues();
void br_runBuzzerBeep();
static msg_t Thread10(void *arg);
static msg_t Thread9(void *arg);

#include "C:\Program Files (x86)\Arduino\hardware\arduino\sam\cores\arduino\arduino.h"
#include "C:\Program Files (x86)\Arduino\hardware\arduino\sam\variants\arduino_due_x\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\sam\variants\arduino_due_x\variant.h" 
#include "\\psf\Workspaces\P2\Software\HoverCraftSystem - Copy\HoverCraftSystem.ino"
#include "\\psf\Workspaces\P2\Software\HoverCraftSystem - Copy\FrontLeftMotorControl.ino"
#include "\\psf\Workspaces\P2\Software\HoverCraftSystem - Copy\FrontLeftMotorPID.ino"
#include "\\psf\Workspaces\P2\Software\HoverCraftSystem - Copy\FrontLineSensorSystem.ino"
#include "\\psf\Workspaces\P2\Software\HoverCraftSystem - Copy\FrontRightMotorControl.ino"
#include "\\psf\Workspaces\P2\Software\HoverCraftSystem - Copy\FrontRightMotorPID.ino"
#include "\\psf\Workspaces\P2\Software\HoverCraftSystem - Copy\MainThread.ino"
#include "\\psf\Workspaces\P2\Software\HoverCraftSystem - Copy\RearLineSensorSystem.ino"
#include "\\psf\Workspaces\P2\Software\HoverCraftSystem - Copy\RearRightMotorControl.ino"
#include "\\psf\Workspaces\P2\Software\HoverCraftSystem - Copy\RearRightMotorPID.ino"
#include "\\psf\Workspaces\P2\Software\HoverCraftSystem - Copy\testC_file.c"
#include "\\psf\Workspaces\P2\Software\HoverCraftSystem - Copy\testC_file.h"
#endif
