#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;
#include <winsock2.h>
#include <MEMORY.H>
#pragma comment(lib,"ws2_32.lib")

typedef struct{
	char NodeNo;
	char GroupNo;
	char Type;
	short int PointNum;
	short int DataLen;
	//数据区
	void * Data;
	//校验和
	unsigned char Checksum;
}DataNode;

typedef unsigned char byte;
typedef byte BYTE;

bool FileWrite( const char * pstrFileName, DataNode dataNode )
{
	//Debug版往控制台输出，Release版用ofstream往文件中写
#ifndef _DEBUG
	ofstream MY_OUT( pstrFileName, ios::out|ios::binary|ios::app );
	if (!MY_OUT) exit(-1);
#else
#define MY_OUT cout
#endif

	MY_OUT << "Type: " << (int)dataNode.Type << " \t" ;
	//MY_OUT << "GroupNo: " << (int)dataNode.GroupNo << " \t" ;
	MY_OUT << "SendLength: " << dataNode.DataLen+8 << " \n" ;
	MY_OUT << "DataBegin================" << endl;


	switch( dataNode.Type )
	{
	case 1://float
		for ( int i = 0; i < dataNode.PointNum; i++ )
		{
			MY_OUT << "[" << (int)dataNode.GroupNo << "]" << "[" << i+1 << "]: ";
			MY_OUT << *( (float*)dataNode.Data+i ) << "\t";
		}
		MY_OUT << endl;
		 break;
	case 2://int
		for ( int i = 0; i < dataNode.PointNum; i++ )
		{
			MY_OUT << "[" << (int)dataNode.GroupNo << "]" << "[" << i+1 << "]: ";
			MY_OUT << *( (int*)dataNode.Data+i ) << "\t";
		}
		MY_OUT << endl;		
		 break;
	case 3://short int
		for ( int i = 0; i < dataNode.PointNum; i++ )
		{
			MY_OUT << "[" << (int)dataNode.GroupNo << "]" << "[" << i+1 << "]: ";
			MY_OUT << *( (short int*)dataNode.Data+i ) << "\t";
		}
		MY_OUT << endl;		
		 break;
	case 4://char
		for ( int i = 0; i < dataNode.PointNum; i++ )
		{
			MY_OUT << "[" << (int)dataNode.GroupNo << "]" << "[" << i+1 << "]: ";
			char c = *( (char*)dataNode.Data+i ); 
			MY_OUT << c << "\t";
		}
		MY_OUT << endl;	
		 break;
	case 5://bit
		for ( int i = 0; i < dataNode.DataLen; i++ )
		{
			BYTE b = *( (BYTE*)dataNode.Data+i );	
			bitset<8> bs(b);

			MY_OUT << "\n" << bs << "\n";
	
			for ( int j = 0; j < 8; j++ )
			{
				MY_OUT << "[" << (int)dataNode.GroupNo << "]" << "[" << i+1 << "]";
				MY_OUT << "[" << j+1 << "]: ";
				MY_OUT << bs[8-j-1] << " ";
			}
			MY_OUT << '\t';
		}
		MY_OUT << endl;		
		 break;
	default:
		 throw "数据类型错误!";
		 break;
	}	
	MY_OUT << "DataEnd================\n" << endl;

#ifndef _DEBUG
	MY_OUT.close();
#endif

	return true;
}

int main()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR)
		printf("Error at WSAStartup()\n");

	SOCKET fd;//socket描述符号
	struct sockaddr_in ad;//本机的IP地址
	char buf[1024];//接收数据缓冲

	struct sockaddr_in ad_snd;//发送者IP地址
	int len;//发送者IP的长度
	int r;

	fd=socket(AF_INET,SOCK_DGRAM,17);
	if(fd==-1) printf("socket:%m\n"),exit(-1);
	printf("建立socket成功!\n");

	ad.sin_family=AF_INET;
	ad.sin_port=htons(6000);
	ad.sin_addr.s_addr=inet_addr("127.0.0.1");	
	r=bind(fd,(struct sockaddr*)&ad,sizeof(ad));
	if(r==-1) printf("bind err:%m\n"),exit(-1);
	printf("绑定成功!\n");

	while(1)
	{
		len=sizeof(ad_snd);
		r=recvfrom(fd,buf,sizeof(buf)-1,0,
			(struct sockaddr*)&ad_snd,&len);

		if(r>0){
			buf[r]=0;

			DataNode dataNode;
			dataNode.NodeNo = buf[0];
			//printf( "节点编号:%d\n", dataNode.NodeNo );

			dataNode.GroupNo = buf[1];
			dataNode.Type = buf[2];
			
			memcpy( &(dataNode.PointNum), buf+3, 2 );
			//printf( "数据点数:%d\n", dataNode.PointNum );

			memcpy( &(dataNode.DataLen), buf+5, 2 );

			dataNode.Data = malloc( dataNode.DataLen );
			memcpy( dataNode.Data, buf+7, dataNode.DataLen );

			memcpy( &dataNode.Checksum, buf+7+(dataNode.DataLen), 1 );

			printf( "Type:%d\t", dataNode.Type );
			printf( "GroupNo:%d\t", dataNode.GroupNo );
			printf( "SendLength:%d\n", dataNode.DataLen+8 );

			const char * szFileName = "Data.dat";
			FileWrite( szFileName, dataNode );

			/*printf( "recvfrom returned: r=%d\n", r );
			printf( "Checksum:%d\n", dataNode.Checksum );*/

			free( dataNode.Data );
			dataNode.Data = NULL;
		}

		if(r==0)
		{
			printf("关闭!\n");	
			break;
		}
		if(r==-1)
		{
			printf("网络故障!\n");			
			break;
		}
	}

	closesocket(fd);

	return 0;
}










