#pragma once

template<typename T>
class ObjectPool
{
public:
	ObjectPool(void);
	virtual ~ObjectPool(void);

private:
	std::shared_ptr<T>	GetPoolObject(void);
	void				ReleasePoolObject(void);
	size_t				Size(void);

};