#pragma once

template <typename T>
class LockBasedStack
{
public:
	void Push(const T& value)
	{
		UniqueLock lg(_m);
		_s.push(value);

		_cv.notify_one();
	}
	
	bool TryPop(OUT T& output)
	{
		UniqueLock lg(_m); // cv는 unique_lock
		
		if (_s.empty()) // 이것부터 확인하고 pop을 하는 것
			return false;
		
		output = _s.top();
		_s.pop();

		return true;
	}

	void WaitPop(OUT T& output)
	{
		UniqueLock lg(_m); // cv는 unique_lock(event lock때 사용)
		_cv.wait(lg, [this]()->bool {return _s.empty() == false; });

		output = _s.top();
		_s.pop();
			
	}

private:
	stack<T> _s;
	mutex _m;
	ConditionV _cv;
};

