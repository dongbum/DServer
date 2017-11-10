#pragma once

class LinearBuffer
{
public:
	LinearBuffer(void)
		: read_position_(0)
		, write_position_(0)
	{

	};

	char* GetBuffer(void)
	{
		return &buffer_[0];
	};

	char* GetWritePtr(void) { return &buffer_[write_position_]; };
	char* GetReadPtr(void) { return &buffer_[read_position_]; };
	
	void SetWritePtr(uint32_t write_position) { write_position_ += write_position; };
	void SetReadPtr(uint32_t read_position) { read_position_ += read_position; };

	void Reset(void)
	{
		buffer_.clear();
		read_position_ = 0;
		write_position_ = 0;
	};

private:
	uint32_t read_position_;
	uint32_t write_position_;
	std::vector<char> buffer_;
};
