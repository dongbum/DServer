#pragma once

template< std::size_t BUF_SIZE >
class LinearBuffer
{
public:
	LinearBuffer(void)
	{
		memset(m_szBuf, 0, BUF_SIZE);
		ClearBuf();
	}
	virtual ~LinearBuffer(void)	{ ClearBuf(); }

	void MoveBufferPtr(void);
	bool MoveWritePos(const uint16_t& nMovePos);
	bool MoveReadPos(const uint16_t& nMovePos);

	void	ClearBuf(void)			{ clearReadPos(), clearWritePos(); }

	uint16_t	GetUseSize(void)		{ return m_nWritePos - m_nReadPos; }
	uint16_t	GetFreeSize(void)		{ return BUF_SIZE - GetUseSize(); }

	char*	GetReadBufferPtr(void)	{ return &m_szBuf[m_nReadPos]; }
	char*	GetWriteBufferPtr(void)	{ return &m_szBuf[m_nWritePos]; }

protected:
	void clearReadPos(void)			{ m_nReadPos = 0; }
	void clearWritePos(void)		{ m_nWritePos = 0; }

private:
	LinearBuffer(const LinearBuffer& rhs) = delete;
	LinearBuffer& operator=(const LinearBuffer& rhs) = delete;

protected:
	char		m_szBuf[BUF_SIZE];
	uint16_t	m_nReadPos;
	uint16_t	m_nWritePos;
};


template<std::size_t BUF_SIZE>
void LinearBuffer<BUF_SIZE>::MoveBufferPtr(void)
{
	if ( m_nReadPos <= 0 )
		return;

	m_nWritePos -= m_nReadPos;
	if ( 0 < m_nWritePos )	// no move(clear all packet)
		memmove(&m_szBuf[0], &m_szBuf[m_nReadPos], m_nWritePos);

	clearReadPos();
}


template<std::size_t BUF_SIZE>
bool LinearBuffer<BUF_SIZE>::MoveWritePos(const uint16_t& nMovePos)
{
	if ( BUF_SIZE < m_nWritePos+nMovePos )
		return false;

	m_nWritePos += nMovePos;
	return true;
}


template<std::size_t BUF_SIZE>
bool LinearBuffer<BUF_SIZE>::MoveReadPos(const uint16_t& nMovePos)
{
	if ( m_nWritePos < m_nReadPos+nMovePos )
		return false;

	m_nReadPos += nMovePos;
	return true;
}
