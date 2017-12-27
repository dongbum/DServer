#pragma once

#include "../define.h"

class BaseProtocol
{
public:
	typedef boost::function<uint32_t(std::shared_ptr<BasicSocket>, uint32_t&, char*, uint32_t)>	ProtocolFunction;
	typedef std::map<uint32_t, ProtocolFunction>										ProtocolMap;

	BaseProtocol(void);
	virtual ~BaseProtocol(void);

protected:
	bool ExecuteProtocol(std::shared_ptr<BasicSocket> socket, uint32_t protocol_no, char* data, uint32_t data_length);
	void AddProtocol(uint32_t protocol_no, BaseProtocol::ProtocolFunction protocol_function);

private:
	ProtocolMap	 protocol_map;

};