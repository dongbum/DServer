#pragma once

class BasicService
{
public:
	BasicService(void) {};
	virtual ~BasicService(void) {};

protected:
	virtual void StartHandler(void) = 0;

private:

};