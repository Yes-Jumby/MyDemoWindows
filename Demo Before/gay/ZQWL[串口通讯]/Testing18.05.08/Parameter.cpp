#include "StdAfx.h"
#include "Parameter.h"
#include "PCOMM.h"
#include "math.h"

int m_nPort, m_nRetries;
Parameter::Parameter(void)
{
	INT24=0;
	INT48=1;
	REAL=2;
}
	
Parameter::~Parameter(void)
{
}

bool Parameter::Open(int Port, int Retries)
{
	 m_nPort = Port; m_nRetries = Retries;
    int ret = sio_open(m_nPort);
    ret |= sio_ioctl(m_nPort,B9600,BIT_8|STOP_1);
    ret |= sio_SetReadTimeouts(m_nPort,200,0);
    ret |= sio_SetWriteTimeouts(m_nPort,200);
    ret |= sio_flush(m_nPort,2);
    return (ret==SIO_OK)?true:false ;
}

BOOL Parameter::Close()
{
	return (sio_close(m_nPort) == SIO_OK)?true:false;
}

char Parameter::CRC_check(char * Array)
{
	unsigned char CheckSum = 0;
        for(int i=0; i<1+Array[8]; i++)
        {
                CheckSum = CheckSum^Array[i];//XOR all elements
        }
        return CheckSum;
}



BOOL Parameter::WriteParameter(int CodeNumber,int ParameterValue,int index,int Datatype)
{
	//写参数到驱动器中
	int retry=m_nRetries;
	if(Datatype == INT24)
	{
		OutputBuff[SZ] =  0xC5;   //Write command      
		OutputBuff[ADR] = 0x00;   //RS232 the address is meaningless
		OutputBuff[L] = 0x05;     //写字节的长度-1,一般为REAL48格式,6个数值字节
		OutputBuff[3] = (CodeNumber >>8)&0xFF;//命令字高八位
		OutputBuff[4] =  CodeNumber&0xFF;//命令的低八位
		OutputBuff[5] = index; //命名的子位
		OutputBuff[6] = 0x00;
		OutputBuff[7] = (ParameterValue>>8)&0xFF;//6是命名数值
		OutputBuff[8] = ParameterValue&0xFF;
		
		unsigned char CRCMsg[20]={OutputBuff[0],OutputBuff[1],OutputBuff[2],OutputBuff[3],OutputBuff[4],OutputBuff[5],
			OutputBuff[6],OutputBuff[7],OutputBuff[8]};
		int len=9;//The length of CRC bytes
		unsigned short code = Do_crc(0x0000, CRCMsg, len);
		CRCMsg[len+1] = code & 0x00ff;
		CRCMsg[len] = (code >> 8) & 0x00ff; 
		OutputBuff[9] = CRCMsg[len]; //12,13 CRC checksum
		OutputBuff[10] = CRCMsg[len+1];
	}
	else if(Datatype == INT48)
	{
		OutputBuff[SZ] =  0xC5;   //Write command      
		OutputBuff[ADR] = 0x00;   //RS232 the address is meaningless
		OutputBuff[L] = 0x08;     //写字节的长度-1,一般为REAL48格式,6个数值字节
		OutputBuff[3] = (CodeNumber >>8)&0xFF;//命令字高八位
		OutputBuff[4] =  CodeNumber&0xFF;//命令的低八位
		OutputBuff[5] = index; //命名的子位
		OutputBuff[6] = 0x00; //9,10,11是命令字数值的小数部分
		OutputBuff[7] = 0x00;
		OutputBuff[8] = 0x00;
		OutputBuff[9] = (ParameterValue >> 16)&0xFF;//6,7,8是命名数值的整数部分
		OutputBuff[10] = (ParameterValue >> 8)&0xFF;
		OutputBuff[11] = ParameterValue&0xFF;	
		unsigned char CRCMsg[20]={OutputBuff[0],OutputBuff[1],OutputBuff[2],OutputBuff[3],OutputBuff[4],OutputBuff[5],
			OutputBuff[6],OutputBuff[7],OutputBuff[8],OutputBuff[9],OutputBuff[10],OutputBuff[11]};
		int len=12;//The length of CRC bytes
		unsigned short code = Do_crc(0x0000, CRCMsg, len);
		CRCMsg[len+1] = code & 0x00ff;
		CRCMsg[len] = (code >> 8) & 0x00ff; 
		OutputBuff[12] = CRCMsg[len]; //12,13 CRC checksum
		OutputBuff[13] = CRCMsg[len+1];
	}
	else //Real
	{
		OutputBuff[SZ] =  0xC5;   //Write command      
		OutputBuff[ADR] = 0x00;   //RS232 the address is meaningless
		OutputBuff[L] = 0x08;     //写字节的长度-1,一般为REAL48格式,6个数值字节
		OutputBuff[3] = (CodeNumber >>8)&0xFF;//命令字高八位
		OutputBuff[4] =  CodeNumber&0xFF;//命令的低八位
		OutputBuff[5] = index; //命名的子位
		OutputBuff[6] = (ParameterValue >> 16)&0xFF;//6,7,8是命名数值的整数部分
		OutputBuff[7] = (ParameterValue >> 8)&0xFF;
		OutputBuff[8] = ParameterValue&0xFF;
		OutputBuff[9] = 0x00; //9,10,11是命令字数值的小数部分
		OutputBuff[10] = 0x00;
		OutputBuff[11] = 0x00;
		
		unsigned char CRCMsg[20]={OutputBuff[0],OutputBuff[1],OutputBuff[2],OutputBuff[3],OutputBuff[4],OutputBuff[5],
			OutputBuff[6],OutputBuff[7],OutputBuff[8],OutputBuff[9],OutputBuff[10],OutputBuff[11]};
		int len=12;//The length of CRC bytes
		unsigned short code = Do_crc(0x0000, CRCMsg, len);
		CRCMsg[len+1] = code & 0x00ff;
		CRCMsg[len] = (code >> 8) & 0x00ff; 
		OutputBuff[12] = CRCMsg[len]; //12,13 CRC checksum
		OutputBuff[13] = CRCMsg[len+1];
	}
	
	do
	{
		sio_flush(m_nPort,2); 
		sio_write(m_nPort,OutputBuff,14);
		Sleep(4);
        sio_read(m_nPort, InputBuff,10);
	}while((InputBuff[0] != 0x06) && retry--);
	if(InputBuff[0] != 0x06)
		return FALSE;
	else
		return TRUE;
}

double Parameter::ReadParameter(int CodeNumber,int index,int Datatype)
{
	int retry=m_nRetries;
	int Number_Bytes;
	OutputBuff[SZ] =  0xA5;   //Read command      
	OutputBuff[ADR] = 0x03;  
	if(CodeNumber > 65536)//The number of data bytes >=3
	{
		OutputBuff[L] = 0x03;
		OutputBuff[3] = (CodeNumber>>16)&0XFF;
		OutputBuff[4] = (CodeNumber>>8)&0XFF;
		OutputBuff[5] = CodeNumber&0XFF;
		Number_Bytes = 3;
	}
	else if(CodeNumber > 255)//The number of data bytes = 2
	{
		OutputBuff[L] = 0x02;
		OutputBuff[3] = (CodeNumber>>8)&0XFF;
		OutputBuff[4] = CodeNumber&0XFF;
		Number_Bytes = 2;
	}
    else  //The number of data bytes = 1
	{
		OutputBuff[L] = 0x01;
		OutputBuff[3] = CodeNumber&0xFF;
		Number_Bytes = 1;
	}
	OutputBuff[3+Number_Bytes] = index;

	unsigned char CRCMsg[20]={OutputBuff[0],OutputBuff[1],OutputBuff[2],OutputBuff[3],OutputBuff[4],OutputBuff[5],OutputBuff[6]};
	int len=4+Number_Bytes;//The length of CRC bytes
	unsigned short code = Do_crc(0x0000, CRCMsg, len);
	CRCMsg[len+1] = code & 0x00ff;
	CRCMsg[len] = (code >> 8) & 0x00ff; 
	OutputBuff[4+Number_Bytes] = CRCMsg[len];
	OutputBuff[5+Number_Bytes] = CRCMsg[len+1];
	do
	{
		sio_flush(m_nPort,2); 
		sio_write(m_nPort,OutputBuff,6+Number_Bytes);
		//Sleep(10);
        sio_read(m_nPort, InputBuff,10);
	}while((InputBuff[0] != 0x05) && retry--);
	//data_format = 1;//E2_6
	if(InputBuff[1] == 0x02)//05 02 3 4 5  CRC CRC
	{
		CHAR_32[0]=InputBuff[4];
		CHAR_32[1]=InputBuff[3];
		ParameterValue = (double)*(short*)CHAR_32;
		/*if((InputBuff[2]&0x80) == 0x80)//负数
			{
				ParameterValue=(double)-(~(((InputBuff[2]<<16)+(InputBuff[3]<<8)+InputBuff[4])-1));
			}
		else
		{
			ParameterValue=(double)((InputBuff[2]<<16)+(InputBuff[3]<<8)+InputBuff[4]);
		}*/
	}
	if(InputBuff[1] == 0x05)//05 05 3 4 5 6 7 8 CRC CRC
	{
		if(Datatype == INT48)
		{
			CHAR_32[0]=InputBuff[7];
			CHAR_32[1]=InputBuff[6];
			CHAR_32[2]=InputBuff[5];
			CHAR_32[3]=InputBuff[4];
			ParameterValue=(double)*(int*)CHAR_32;

		/*if((InputBuff[2]&0x80) == 0x80)//负数
		{
				ParameterValue=(double)-(~(((InputBuff[2]<<40)+(InputBuff[3]<<32)+(InputBuff[4]<<24)+(InputBuff[5]<<16)+(InputBuff[6]<<8)+InputBuff[7])-1));
		}
		else
		{
			ParameterValue=(double)((InputBuff[2]<<40)+(InputBuff[3]<<32)+(InputBuff[4]<<24)+(InputBuff[5]<<16)+(InputBuff[6]<<8)+InputBuff[7]);
		}*/
		}
		else
		{
			int m_Integer = 0;//整数部分
			double m_Frac = 0;//小数部分
			if((InputBuff[2]&0x80) == 0x80)//负数
			{
				m_Integer = (~(InputBuff[2])<<16)&0xFF0000;
				m_Integer = m_Integer + (~(InputBuff[3]<<8))&0xFF00;
				m_Integer = m_Integer + ~(InputBuff[4]);
				m_Integer = 0 - m_Integer;
				m_Frac = (~(InputBuff[5]>>4)&0x0F)*pow(double(16),-1)+~(InputBuff[5]&0x0F)*pow(double(16),-2)
					+(~(InputBuff[6]>>4)&0x0F)*pow(double(16),-3)+~(InputBuff[6]&0x0F)*pow(double(16),-4)
					+(~(InputBuff[7]>>4)&0x0F)*pow(double(16),-5)+~(InputBuff[7]&0x0F)*pow(double(16),-6);
				m_Frac = 0-m_Frac;
			}
			else
			{
				m_Integer = (InputBuff[2]<<16) + (InputBuff[3]<<8) + InputBuff[4];
				m_Frac = ((InputBuff[5]>>4)&0x0F)*pow(double(16),-1)+(InputBuff[5]&0x0F)*pow(double(16),-2)
					+((InputBuff[6]>>4)&0x0F)*pow(double(16),-3)+(InputBuff[6]&0x0F)*pow(double(16),-4)
					+((InputBuff[7]>>4)&0x0F)*pow(double(16),-5)+(InputBuff[7]&0x0F)*pow(double(16),-6);
				
			}
			ParameterValue = m_Integer + m_Frac;
		}	
	}	
	if(InputBuff[0] == 0x00)
	{
		//AfxMessageBox("Fail to read Parker parameter!");
		return 0;
	}
	else
		return ParameterValue;
}

short Parameter::Read()
{
	int retry=m_nRetries;
	
	OutputBuff[0] = 0x01;//固定格式        
	OutputBuff[1] = 0x03;  
    OutputBuff[2] = 0x00;//起始位        
	OutputBuff[3] = 0x00;  
    OutputBuff[4] = 0x00;//长度        
	OutputBuff[5] = 0x01;  
    OutputBuff[6] = 0x84;//CRC校验 
	OutputBuff[7] = 0x0A; 

	/*unsigned char CRCMsg[20]={OutputBuff[0],OutputBuff[1],OutputBuff[2],OutputBuff[3],OutputBuff[4],OutputBuff[5]};
	int len=6;//The length of CRC bytes
	unsigned short code = Do_crc(0x0000, CRCMsg, len);
	CRCMsg[len+1] = code & 0x00ff;
	CRCMsg[len] = (code >> 8) & 0x00ff; 
	OutputBuff[6] = CRCMsg[len];
	OutputBuff[7] = CRCMsg[len+1];*/
	do
	{
		sio_flush(m_nPort,2); 
		sio_write(m_nPort,OutputBuff,8);
		//Sleep(100);
        sio_read(m_nPort, InputBuff,8);
	}while((InputBuff[0] != 0x01) && retry--);
    	CHAR_32[0]=InputBuff[4];
		CHAR_32[1]=InputBuff[3];
	return *(short*)CHAR_32;
}

const unsigned int CRC16_table[256] = 
{  0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7, 
   0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef, 
   0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6, 
   0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de, 
   0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485, 
   0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d, 
   0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4, 
   0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc, 
   0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823, 
   0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b, 
   0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12, 
   0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a, 
   0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41, 
   0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49, 
   0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70, 
   0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78, 
   0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f, 
   0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067, 
   0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e, 
   0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256, 
   0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d, 
   0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 
   0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c, 
   0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634, 
   0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab, 
   0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3, 
   0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a, 
   0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92, 
   0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9, 
   0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1, 
   0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8, 
   0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0 
}; 

unsigned short Parameter::Do_crc(unsigned short reg_init, unsigned char *message, unsigned int len) 
{
    unsigned short crc_reg = reg_init; 
          
    while (len--) 
		crc_reg = (CRC16_table[(crc_reg >> 8) & 0x00FF] ^ (crc_reg << 8) ^ (unsigned int)(*message++));         
    return crc_reg;
} 
