#ifndef TOOLBITSDK_I2C_H_
#define TOOLBITSDK_I2C_H_

#include "tbi_core.h"

typedef enum
{
	ATT_I2C_ADDR     = 0x00,
	ATT_I2C_RW_1BYTE = 0x01,
	ATT_I2C_RW_2BYTE = 0x02,
	ATT_I2C_RW_3BYTE = 0x03,
	ATT_I2C_RW_4BYTE = 0x04
} AttI2c;


class I2c
{
public:
	I2c(TbiService *tbisrv, ToolbitAttributionID base);
	~I2c();
	bool write(uint8_t addr, uint16_t val);
	uint16_t read(uint8_t addr);

protected:
	TbiService *mTbiSrv;
	Attribute *mAttI2cAddr;
	Attribute *mAttI2cRw1Byte;
	Attribute *mAttI2cRw2Byte;
	Attribute *mAttI2cRw3Byte;
	Attribute *mAttI2cRw4Byte;
};

#endif /* TOOLBITSDK_I2C_H_ */
