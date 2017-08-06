#include "adc.h"


Adc::Adc(TbiService *tbisrv, ToolbitAttributionID base)
{
	mTbiSrv = tbisrv;
	for (int i = 0; i<8; i++)
		mAttAdcR[i] = new Attribute(base + i, 0x00, 0x00);
}

Adc::~Adc()
{
	for (int i = 0; i < 8; i++)
		delete mAttAdcR[i];
}

uint32_t Adc::analogRead(uint8_t pin)
{
	if (pin >= 8)
		return false;  // error

	bool status = mTbiSrv->readAttribute(mAttAdcR[pin]);
	if (!status)
		return false;   // error
	return mAttAdcR[pin]->getValueUint32();
}