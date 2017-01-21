#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "pic16f145x.h"

#define USB_VID 0x4d8
#define USB_PID 0x3f

Picbit::Picbit() :
	mAttGpioInoutMode(ATT_GPIO_INOUT_MODE, 0x00, 0x00),
	mAttGpioPullUp(ATT_GPIO_PULL_UP, 0x00, 0x00),
	mAttGpioPullDown(ATT_GPIO_PULL_DOWN, 0x00, 0x00),
	mAttGpioRw(ATT_GPIO_RW, 0x00, 0x00),
	mAttI2C0Addr(ATT_I2C0_ADDR, 0x00, 0x00),
	mAttI2C0RW1Byte(ATT_I2C0_RW_1BYTE, 0x00, 0x00),
	mAttI2C0RW2Byte(ATT_I2C0_RW_2BYTE, 0x00, 0x00)
{
	// Get current status
	mTbiService->readAttribute(&mAttGpioInoutMode);
	mTbiService->readAttribute(&mAttGpioPullUp);
	mTbiService->readAttribute(&mAttGpioPullDown);
	mTbiService->readAttribute(&mAttGpioRw);
}

Picbit::~Picbit()
{
}

bool Picbit::setGpioPinMode(uint8_t pin, PinMode mode)
{
	bool status;

	if (pin > 3)
		return false;

	if (mode == OUTPUT_PIN) {
		mAttGpioInoutMode.setValue(mAttGpioInoutMode.getValueUint32() & ~(1 << pin));
	}
	else {
		if (mode == INPUT_PIN)
		mAttGpioPullUp.setValue(mAttGpioPullUp.getValueUint32() & ~(1 << pin));
		else if (mode == INPUT_PULLUP_PIN)
		mAttGpioPullUp.setValue(mAttGpioPullUp.getValueUint32() | 1 << pin);
		else
		return false;  // error because INPUT_PULLDOWN_PIN is not supported yet

		status = mTbiService->writeAttribute(mAttGpioPullUp);
		if (!status)
		return false;  // error

		mAttGpioInoutMode.setValue(mAttGpioInoutMode.getValueUint32() | 1 << pin);
	}

	status = mTbiService->writeAttribute(mAttGpioInoutMode);
	if (!status)
		return false;  // error

	return true;
}

bool Picbit::writeGpio(uint32_t dat)
{
	mAttGpioRw.setValue(dat);
	bool status = mTbiService->writeAttribute(mAttGpioRw);
	if (!status)
		return false;   // error
	return true;
}

uint32_t Picbit::readGpio()
{
	bool status = mTbiService->readAttribute(&mAttGpioRw);
	if (!status)
		return false;   // error
	return mAttGpioRw.getValueUint32();
}

bool Picbit::digitalWrite(uint8_t pin, bool val)
{
	if (val)
		mAttGpioRw.setValue(mAttGpioRw.getValueUint32() | 1 << pin);
	else
		mAttGpioRw.setValue(mAttGpioRw.getValueUint32() & ~(1 << pin));

	bool status = mTbiService->writeAttribute(mAttGpioRw);
	if (!status)
		return false;   // error
	return true;
}

bool Picbit::digitalRead(uint8_t pin)
{
	return readGpio() & 1 << pin;
}

uint16_t Picbit::readReg(uint8_t addr)
{
	bool status;

	mAttI2C0Addr.setValue(addr);
	status = mTbiService->writeAttribute(mAttI2C0Addr);
	if (!status) {
		// error
		return 0;
	}

	status = mTbiService->readAttribute(&mAttI2C0RW2Byte);
	if (!status) {
		// error
		return 0;
	}
	return mAttI2C0RW2Byte.getValueInt16();
}

bool Picbit::writeReg(uint8_t addr, uint16_t val)
{
	bool status;

	mAttI2C0Addr.setValue(addr);
	status = mTbiService->writeAttribute(mAttI2C0Addr);
	if (!status) {
		// error
		return false;
	}

	mAttI2C0RW2Byte.setValue(val);
	status = mTbiService->writeAttribute(mAttI2C0RW2Byte);
	if (!status) {
		// error
		return false;
	}

	return true;
}
