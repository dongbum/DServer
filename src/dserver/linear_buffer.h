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

	void Push(char* data, int size)
	{
		memcpy(&buffer_[write_position_], data, size);
		write_position_ += size;
	};

	void Pop(OUT void* target, int size)
	{
		memcpy(target, &buffer_[0], size);
		memmove(&buffer_[0], &buffer_[size], write_position_ - size);
		write_position_ -= size;
	};

	void Reset(void)
	{
		memset(buffer_, 0, sizeof(RECV_BUFFER_SIZE));
		read_position_ = 0;
		write_position_ = 0;
	};

private:
	uint32_t read_position_;
	uint32_t write_position_;
	char buffer_[RECV_BUFFER_SIZE];
};
