#pragma once

struct Header
{
	Header(void)
	{
		total_length_ = 0;
		protocol_no_ = 0;
		data_length_ = 0;
	}

	int32_t total_length_;
	int32_t protocol_no_;
	int32_t data_length_;

	int32_t			GetTotalLength(void) { return total_length_; };
	int32_t			GetProtocolNo(void) { return protocol_no_; };
	int32_t			GetDataLength(void) { return data_length_; };

	void			SetTotalLength(int32_t total_length) { total_length_ = total_length; };
	void			SetProtocolNo(int32_t protocol_no) { protocol_no_ = protocol_no; };
	void			SetDataLength(int32_t data_length) { data_length_ = data_length; };
};
