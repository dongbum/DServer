#pragma once

template<typename TaskType>
class ThreadSafeQueue
{
public:
	void Push(const TaskType& task)
	{
		std::unique_lock<std::mutex> lock(queue_mutex_);
		queue_.push_back(task);
		lock.unlock();
		cond_var_.notify_one();
	}

	TaskType TryPop(void)
	{
		TaskType result;

		std::lock_guard<std::mutex> lock(queue_mutex_);
		if (false == queue_.empty())
		{
			result = queue_.front();
			queue_.pop_front();
		}

		return result;
	}

	TaskType Pop(void)
	{
		std::unique_lock<std::mutex> lock(queue_mutex_);

		while (queue_.empty())
		{
			cond_var_.wait(lock);
		}

		TaskType result = queue_.front();
		queue_.pop_front();

		return result;
	}

	size_t Size(void)
	{
		return queue_.size();
	}

private:
	std::deque<TaskType>		queue_;
	std::mutex					queue_mutex_;
	std::condition_variable		cond_var_;
};