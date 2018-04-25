#ifndef SERIALPORT_H_  
#define SERIALPORT_H_ 
#include <Windows.h>  

#pragma once
class SerialPort
{
	public:
		SerialPort();
		~SerialPort();
	public:
		bool InitPort(UINT  portNo = 2, UINT  baud = CBR_9600, char  parity = 'N', UINT  databits = 8, UINT  stopsbits = 1, DWORD dwCommEvents = EV_RXCHAR);
		bool InitPort(UINT  portNo, const LPDCB& plDCB);
		//bool OpenListenThread();
		//bool CloseListenTread();
		bool WriteData(unsigned char* pData, unsigned int length);
		UINT GetBytesInCOM();
		bool ReadChar(UCHAR &cRecved);
	private:
		bool openPort(UINT  portNo);
		void ClosePort();
		//static UINT WINAPI ListenThread(void* pParam);
	private:
		HANDLE  m_hComm; //���ھ�� 
		static bool s_bExit; //�߳��˳���־���� 
		//volatile HANDLE    m_hListenThread;	//�߳̾�� 
		CRITICAL_SECTION   m_csCommunicationSync; //ͬ������,�ٽ�������,!< �����������  
};
#endif



