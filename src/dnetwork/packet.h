#pragma once

class Packet
{
public:
	Packet(void)
	{
		write_pos_ = 0;
		data_size_ = 0;
		end_pos_ = &buffer_[SEND_BUFFER_SIZE];
	}

	virtual ~Packet(void)
	{

	}

	void WriteData(const void* buffer, int size)
	{
		if (write_pos_ + size > end_pos_)
			throw(1);

		memcpy(write_pos_, buffer, size);
		write_pos_ += size;

		data_size_ += size;
	}

	template<typename T>
	Packet& operator << (T source)
	{
		WriteData(&source, sizeof(T));
		return *this;
	}

	template<typename T>
	Packet& operator >> (T& source)
	{

	}

	size_t GetSize(void)
	{
		return data_size_;
	}

	char* GetBuffer(void)
	{
		return buffer_;
	}

private:
	char	buffer_[SEND_BUFFER_SIZE];
	char*	write_pos_;
	char*	end_pos_;
	size_t	data_size_;
};