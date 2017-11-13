#include "base_protocol.h"

BaseProtocol::BaseProtocol(void)
{
}

BaseProtocol::~BaseProtocol(void)
{
}

bool BaseProtocol::ExecuteProtocol(std::shared_ptr<BasicSocket> socket, uint32_t protocol_no, char * data, uint32_t data_length)
{
	BaseProtocol::ProtocolMap::iterator iter = protocol_map.find(protocol_no);
	if (iter == protocol_map.end())
		return false;

	ProtocolFunction protocol_function = (*iter).second;
	protocol_function(socket, protocol_no, data, data_length);

	return true;
}

void BaseProtocol::AddProtocol(uint32_t protocol_no, BaseProtocol::ProtocolFunction protocol_function)
{
	protocol_map.insert(BaseProtocol::ProtocolMap::value_type(protocol_no, protocol_function));
}
