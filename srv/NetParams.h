#pragma once

struct NET_PARAMS
{
	enum { NetworkBufferSize = 8192};
};


struct PACKET_PARAMS
{
	enum PACKET_TYPE
	{
		UNKNOWN = -1,

		RQ_PROXY,

	};

};


struct PACKET_STATUS
{
	enum STATUS
	{
		UNKNOWN = -1,
		READY_TO_FORWARD,
		PENDING,
		READY_TO_BACKWARD,

	};

};