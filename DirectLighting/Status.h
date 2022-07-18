#pragma once
#include <string>
namespace EngineStatus
{
	enum class Status
	{
		sRUNNING = 0,
		sSTOPPED = 1,
		sERRORED = 2
	}; 
	static Status m_status = Status::sSTOPPED;
	
	struct Log
	{
		std::string message = "";
		void Set(std::string _message)
		{	
			message = _message;
		}
	};
	static Log m_log;
	
}