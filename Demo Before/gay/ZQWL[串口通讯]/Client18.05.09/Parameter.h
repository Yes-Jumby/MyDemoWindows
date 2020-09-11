//////////////////
#pragma once

#ifndef PARAMETERH
#define PARAMETERH
#endif

/*****************************************************************************************

 ************************** Definition of Telegram **************************
    SZ   ADR    L      Data_block              CRC
     |   |      |            |                 |
     |   |      |            |                 |------ check sum of data block bytes.
	 |   |      |            |                 
     |   |      |            |         
	 |   |      |            |-------- Numbers of bytes in the data block
     |   |      |   
     |   |      |
	 |   |      |-----Number of Data bytes-1
	 |   |      
	 |   |
	 |   |--------Address 
	 |
	 | --------- Start code of telegram. 

*******************************************************************************************/
#define SZ          0
#define ADR         1
#define L           2
#define CRCHi       13
#define CRCLo       14

class Parameter
{
public:
	int INT24;//24bits int
	int INT48;//48bits int
	int REAL;//Real 6bytes
	Parameter(void);
	~Parameter(void);
	double ParameterValue;
	char OutputBuff[8];
	char InputBuff[8];
	char CHAR_24[2];
	char CHAR_32[4];
	bool Open(int Port, int Retries);//Open the COM port
	BOOL Close();
	char CRC_check(char * Array);
	double ReadParameter(int CodeNumber,int index,int Datatype);
	short Read();
	BOOL WriteParameter(int CodeNumber,int ParameterValue,int index,int Datatype);
	unsigned short Do_crc(unsigned short reg_init, unsigned char *message, unsigned int len);
};