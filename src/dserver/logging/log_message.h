#pragma once
	
class LogMessage
{
public:
	LogMessage(void)
		: position_(0)
	{
		memset(buffer_, 0, MAX_LOG_MESSAGE_LENGTH);
	}

	void	AddPosition(unsigned int position)
	{
		position_ += position;
	}

	void	WriteBuffer(char* data, unsigned int size)
	{
		memcpy(&buffer_[position_], data, size);
		position_ += size;
	}

	char*	GetBuffer(void)			{ return &buffer_[position_]; }
	char*	GetBufferStart(void)	{ return &buffer_[0]; }
	unsigned int	GetPosition(void)	{ return position_; }

private:
	char			buffer_[MAX_LOG_MESSAGE_LENGTH];
	unsigned int	position_;

};
