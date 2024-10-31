#pragma once

template <typename T>
class LockBasedQueue
{
public:
	void Push(const T& value)
	{
		UniqueLock lg(_m);
		_q.push(value);

		_cv.notify_one();
	}
	
	bool TryPop(OUT T& output)
	{
		UniqueLock lg(_m);
		
		if (_q.empty())
			return false;

		output = _q.front();
		_q.pop();

		return true;
	}
	void WaitPop(OUT T& output)
	{
		UniqueLock lg(_m); // cv는 unique_lock(event lock때 사용)
		_cv.wait(lg, [this]()->bool {return _q.empty() == false; });

		output = _q.front();
		_q.pop();

	}

private:
	queue<T> _q;
	mutex _m;
	ConditionV _cv;
};

