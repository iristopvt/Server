//#include "pch.h"
//
//
//// window
//// linux           운영체제
//
//// thread 멤버함수
//// - join                   : t가 끝날때까지 기다려서 합친다는 뜻 (thread 종료와 같은뜻)
//// - joinable  
//// - detach                 : 쓰레드 분리
//// - hardware_concurrency   : 현재 운용가능한 쓰레드 개수
//// - get_id                 : 쓰레드 아이디
//
//
//
////void HelloThread()
////{
////    cout << "Hello Thread!!" << endl;
////}
////
////void HelloThread_One(int number)
////{
////    cout << number << endl;
////}
//
//
////int32 sum = 0; // all or notiong : 이것으로 아래의 더하고 빼는값을 각각 진행해도 결과는 0이나오지않는다. 그래서 atomic사용
//atomic<int32> sum = 0; // 원자적 접근
//
//void AddSum()
//{
//    for (int i = 0; i < 100000; i++)
//    {
//       /* sum++;
//        int eax = sum;
//        eax++;
//        sum = eax;*/
//       
//        sum.fetch_add(1);
//
//    }
//}
//void SubSum()
//{
//    for (int i = 0; i < 100000; i++)
//    {
//       /* sum--;
//        int eax = sum;
//        eax--;
//        sum = eax;*/
//
//        sum.fetch_sub(1);
//    }
//}
//
//int main()
//{
//    // 쓰레드 생성
//    // - t는 새로운 쓰레드
//   /* std::thread t(HelloThread_One, 1);*/
//
//   /* cout << t.hardware_concurrency() << endl;
//    cout << t.get_id() << endl;*/
//   /* cout << "Hello Main" << endl;*/
//
//    /* t.join();*/
//   
//
//
//    vector<std::thread> threads;
//    //std::thread t;
//    //t = std::thread(AddSum);  // t에다가 함수를 넣을수 있다.
//    threads.resize(10);
//
//    //5개의 쓰레드가 AddSum 일감을 각각 갖는다
//    for (int i = 0; i < 5; i++)
//    {
//        threads[i] = std::thread(AddSum);
//    }
//
//    //5개의 쓰레드가 SubSum 일감을 각각 갖는다
//    for (int i = 5; i < 10; i++)
//    {
//        threads[i] = std::thread(SubSum);
//    }
//
//
//    for (int i = 0; i < 10; i++)
//    {
//        if (threads[i].joinable())
//            threads[i].join();
//    }
//
//    cout << sum << endl;
//   
//}

//vector<int> v; 
//// vector : size, capacity 중요시할것
//// - vector에 새로운 원소를 추가할때 맨 뒤 공간에 원소를 복사한 뒤 ++size만 일어남 
//// - capacity가 증가한 새로운 연속된 공간을 할당 (capacity > size인 상황)
//// -- vector size가 10이라 가정했을때 11의 수를 push_back 하면 capacity는 15공간 만들고(1.5배) 기존것 카피하고 복사하고 넣고 기존것 지움
//// 
//// 그래서 반복적으로 pushback사용시 느려지지않도록 자주 reserve(지운다는 예약) 사용권유
//
//
//// mutual exclusion : 상호배타적의 약자 // 아무도 자신에게 접근하지말라는 의미
//// -> lock
//std::mutex m; // 자물쇄의 역할
//
//// RAII : 디자인패턴
//template<typename T>
//class LockGuard
//{
//public:
//	LockGuard(T* mutex) : _mutex(mutex) { _mutex->lock(); }
//	~LockGuard() { _mutex->unlock(); }
//
//private:
//	T* _mutex;
//};
//
//void Push(int count)
//{
//// 1 ~ 9번째는 대기
//	/*m.lock();*/
//
//	LockGuard<std::mutex> lockguard(&m);
//
//	for (int i = 0; i < count; i++)
//	{
//		// 이중 락일때 문제가 발생할 수 있음
//		v.push_back(1);
//	}
//
//	//m.unlock(); // 안풀면 무한대기... 즉 데드락(다운되는것임)
//
//	return;
//}
//
//int main()
//{
//	v.reserve(100000); // 그래서 사용.
//
//	vector<std::thread> threads;
//	threads.resize(10);
//
//	for (int i = 0; i < 10; i++)
//	{
//		threads[i] = std::thread(Push, 1000);
//	}
//
//	for (int i = 0; i < 10; i++)
//	{
//		threads[i].join();
//	}
//	
//	cout << v.size() << endl;
//
//}


// spinlock, 슬립, 이벤트기반 락, 
// 
// 데드락 : 교착된 상태
// Lock 종류
// 
// - Spinlock	: 화장실앞에서 가만히 대기하고 기다리는 상태 (프로세스나 스레드가 락을 얻을 수 있을 때까지 계속 CPU를 사용하며 바쁘게 대기)
// --- 장점		: 락이 짧은 시간 동안만 필요할 때 효율적
// --- 단점		: CPU 자원을 많이 소모
// 
// - Sleep : 쓰레드가 빙의를 안함 / 락이 해제될 때까지 **대기 상태(잠)**로 들어가며 CPU를 사용하지 않는 락
// --- 장점		: CPU 자원을 절약
// --- 단점		: 락을 기다리는 동안 문맥 전환(context switching) 오버헤드가 발생
// 
// - Event : 특정 이벤트가 발생할 때까지 락이 해제되지 않는 방식 (이벤트가 발생하면 락이 해제되면서 스레드나 프로세스가 진행)
// --- 장점		: 조건이 충족될 때만 락이 해제되므로 정확한 타이밍 제어가 가능
// --- 단점		: 복잡한 조건 처리를 요할 수 있음

// Context Switch
// - 한 프로세스로 부터 CPU를 다른 프로세스로 넘겨주는 행동 (운영체제에게 넘겨주는 것)



//#include "AccountManager.h"
//#include "UserManager.h"

//std::mutex m;

//void Func1()
//{
//
//	for (int32 i = 0; i < 10000; i++)
//	{
//		UserManager::GetInstance()->Save();
//	}
//}
//
//void Func2()
//{
//
//	for (int32 i = 0; i < 10000; i++)
//	{
//		AccountManager::GetInstance()->Login();
//	}
//}

// Lock 구현
// 1. Spin Lock(Busy Waiting)
// 2. Sleep 기반 Lock
// 3. Event 기반 Lock

// Spin Lock

//class SpinLock
//{
//public:
//	void lock()
//	{
//		// add와 sum 둘이 동시에 일어났다.
//		
//		// check와 setting하는 작업이 원자적으로 처리되어야 해결된다.
//		// => Compare And Swap 약자 : CAS
//		bool expected = false;  // flag의 예상결과 값.
//		bool desired = true;    // flag 원하는 결과 true였으면 좋겠다는 의미.
//
//		//// compare_exchange_strong 의 내용의미 (의사코드)
//		//if (flag == expected)
//		//{
//		//	expected = flag;
//		//	flag = desired;
//		//	return true;
//		//}
//		//else // flag가 dedired와 같다는 의미
//		//{
//		//	expected = flag;
//		//	return false;
//		//}
//
//		while (flag.compare_exchange_strong(expected, desired) == false)
//		{
//			expected = false;
//
//			// 이것은 Sleep Lock : Add가 먼저일하고 끝나면 Sub실행됨
//			this_thread::sleep_for(std::chrono::seconds(5));
//			
//			//this_thread::yield(); 이것은 양보
//
//		}
//
//	}
//
//	void unlock()
//	{
//		flag = false;
//	}
//
//private:
//	atomic<bool> flag = false;
//};
//
//int32 sum = 0;
//SpinLock myLock;
//
//void Add()
//{
//	for (int32 i = 0; i < 100'0000; i++)
//	{
//		// 실행시 첫 look... -> false
//		std::lock_guard<SpinLock> lg(myLock); 
//		// look... -> true
//		sum++;
//	}
//}
//
//void Sub()
//{
//	for (int32 i = 0; i < 100'0000; i++)
//	{
//		// look... -> true
//		std::lock_guard<SpinLock> lg(myLock);
//		sum--;
//	}
//}

//int main()
//{
//	//AccountManager::Create();
//	//UserManager::Create();
//
//	/*std::thread t1(Func1); 
//	std::thread t2(Func2);
//
//	t1.join();
//	t2.join();*/
//
//	/*cout << "Done" << endl;
//
//	AccountManager::Delete();
//	UserManager::Delete();*/
//
//
//	// Spin Lock
//	std::thread t1(Add);
//	std::thread t2(Sub);
//
//	t1.join();
//	t2.join();
//
//	cout << sum << endl;
//
//}
	

// 3... Linux에서도? (윈도우에서 핸들말고)
// => cv(condition_variable) : 조건을 걸고 조건이 참일때만 락을 걸어잠그고 실행
// => 멀티쓰레드 환경에서 sleep을 시키지않으면 올바르게 동작하지 않을 수 있다.
// .....동시성이 생길때 Produce를 더 할수도 있다.

// Produce And Consumer 패턴 ... Queue로 많이 진행

//// Event Lock (cv로 해결)
//queue<int32> q;
//mutex m;
////HANDLE handle;
//condition_variable cv;
//
//void Producer() // 1초에 1개씩 수행
//{
//	while (true)
//	{
//		// cv
//		// 1. Lock을 잡고 (lock(m))
//		// 2. 공유변수 값을 수정 (q.push(100))
//		// 3. Lock을 풀고
//		// 4. 조건 변수를 통해 다른 쓰레드에게 통지
//		{
//			unique_lock<std::mutex> lock(m); //1
//			q.push(100); //2
//		}//3
//
//		//::SetEvent(handle);
//
//		//this_thread::sleep_for(1000ms);
//
//		//cv
//		cv.notify_one(); //4 // wait중인 Thread가 있으면 딱 1개를 깨운다.
//	}
//}
//
//void Consumer() // 빨리 뽑으려고하는 상태
//{
//	while (true)
//	{
//		//::WaitForSingleObject(handle, INFINITE);
//
//
//		// P_A_C : Consumer
//		//1. Lock을 잡고
//		//2. 조건확인
//		// -만족했다 => 이어서 코드진행
//		// -불만족 => 'Lock을 풀어주고' 대기상태
//
//		unique_lock<std::mutex> lock(m); //1
//
//		cv.wait(lock, []()->bool {return q.empty() == false; }); //2
//
//
//		//if (q.empty() == false)
//		{
//			int32 data = q.front();
//			q.pop();
//			cout << data << endl;
//
//		}
//	}
//}

//int main()
//{
//			// 1. NULL : 보안속성, 2. FALSE : 메뉴얼 리셋관련, 3. FALSE : 초기상태, 4. NULL : 이름설정
//			// 메뉴얼 : 수동이라는 뜻
//	//handle = ::CreateEvent(NULL, FALSE, FALSE, NULL);
//
//	std::thread t1(Producer);
//	std::thread t2(Consumer);
//
//	t1.join();
//	t2.join();
//
//	//::CloseHandle(handle);
//
//	return 0;
//}


//int64 Caculate()
//{
//	int64 sum = 0;
//
//	for (int i = 0; i < 100'0000; i++)
//	{
//		sum++;
//	}
//
//	for (int i = 0; i < 10; i++)
//	{
//		int temp = 0; // 동기로 실행시 temp가 먼저 잡히고 비동기로 실행됬을때는 예측할수 없다.
//	}
//
//	return sum;
//}
//
//void PromiseWorker(std::promise<string>&& promise)
//{
//	promise.set_value("Set Message");
//}
//
//void TaskWorker(std::packaged_task<int64(void)>&& task)
//{
//	task();
//}
//
//int main()
//{
//	//// 동기화박식(synchronous)
//	//int64 sum = Caculate();
//
//	//future : 미래
//	{
//		// 비동기방식 (asynchronous)
//		// std::launch::deferred => 지연해서 실행시켜주세요 방식
//		// std::launch::async => 쓰레드를 하나 따로 만들어서 실행방식
//
//		std::future<int64> future = std::async(std::launch::async, Caculate); // 비동기방식만 쓴다고 했을때 사용 async
//		// = future가 끝나던지 끝나지 않던지간에 이 내용들이 실행
//		int t = 1;
//
//		int64 sum = future.get(); // get : 함수가 끝날때 까지 기달려서 리턴값
//
//		cout << sum << endl;
//	}
//
//	// promise : 
//	// 미래(future)에 결과물을 반환할 것이라는 약속(promise)을 해줘 ==== 계약서
//	{
//		std::promise<string> promise;
//		std::future<string> future = promise.get_future(); // future에 반환약속
//
//		thread t(PromiseWorker, std::move(promise)); // promise한테 일 시키기
//
//		// future.wait(); // future가 잘 세팅되어있는지 (함수가 잘 끝났는지) 확인하고 대기(끝날때까지 대기)
//		std::future_status status = future.wait_for(10ms); // 0.01초동안 future가 끝났는지 대기하면서 확인.
//		if (status == std::future_status::ready)
//		{
//			// future가 세팅이 잘 되어있다 = > 즉시 실행가능
//		}
//
//		string value = future.get(); // 비동기 방식으로 future에 값이 잘 세팅이 되어있는지 확인하고 반환.
//
//		cout << value << endl;
//
//		t.join();
//	}
//
//
//	// packaged_task : 일감을 만들어서 넘겨주는 방법. (promise랑 비슷하지만 promoise는 값만 세팅을 해주고 끝난다는점)
//	{
//		std::packaged_task<int64()> task(Caculate);
//		std::future<int64> future = task.get_future();
//
//		thread t(TaskWorker, std::move(task));
//
//		int64 sum = future.get();
//
//		cout << sum << endl;
//
//		t.join();
//	}
//
//	// Caculate 하는데 Event 방식, SpinLock 방식처럼 Lock, thread 만들고 하는 작업들을 최소화
//	// 작은작업들을 비동기 방식으로 할때 자주쓴다.
//	// => future
//
//	return 0;
//}

// 10월 2일
// 캐시
// - CPU에 있는 임시 저장공간
// - 코어마다 있다 (L1, L2), 아닌것도 있다(L3)
//
// 캐시 철학
// -- Temporal Locality : 시간적 지역 -> '방금'본 메모리에서 또 다시 접근할 일이 생길 것 같다.
// -- Spatial Locality : 공간적 지역 -> 봤던 메모리 '주변'에 또 접근할 일이 생길 것 같다.
// => 메모리 탐색을 최소화 시키려는 전략

//int32 buffer[10000][10000];
//
//int main()
//{
//	memset(buffer, 0, sizeof(buffer));
//
//	{
//		uint32 start = GetTickCount64();
//
//		int64 sum = 0;
//		for (int32 i = 0; i < 10000; i++)
//		{
//			for (int32 j = 0; j < 10000; j++)
//			{
//				sum += buffer[i][j];
//			}
//		}
//
//		uint32 end = GetTickCount64();
//
//		cout << "Elipsed Time : " << end - start << endl;
//	}
//	
//	{
//		uint32 start = GetTickCount64();
//
//		int64 sum = 0;
//		for (int32 i = 0; i < 10000; i++)
//		{
//			for (int32 j = 0; j < 10000; j++)
//			{
//				sum += buffer[j][i];
//			}
//		}
//
//		uint32 end = GetTickCount64();
//
//		cout << "Elipsed Time : " << end - start << endl;
//	}
//
//	return 0;
//}


//// CPU PipeLine
//int32 x;
//int32 y;
//int32 result1;
//int32 result2;
//
//volatile bool ready;
//
//// 1. 실제 메모리에 정말 x,y가 1이라고 되어있을까?
//// 코어마다 cache가 있다.
//// 멀티쓰레드환경에서만 발생할 수 있는 문제
//// => 캐쉬를 통해서 메모리에 접근해서 값을 넣기 전에 동시에 실행된다면?
//// ------------------> 가시성 문제
//
//// 2. CPU 파이프라인 4단계를 쪼개서 작업하는 과정.
//// - Fetch			: 읽기
//// - Decode			: 해석
//// - Excute			: 실행
//// - Memory Access	: 메모리 접근
//// 일감을 병렬로 처리하기 위해 큰 작업부터 실행한다.
//// ------------------> 코드 재배치
//
//void Thread_1()
//{
//	while (ready)
//	;
//
//	y = 1;
//	result1 = x; // x의 값을 가져와서 대입하는게 좀 더 시간이 걸리는 작업 (그래서 먼저 들어가게되어있음)
//}
//void Thread_2()
//{
//	while (ready)
//	;
//
//	x = 1;
//	result2 = y;
//}
//int main()
//{
//	int32 count = 0;
//
//	while (true)
//	{
//		ready = true;
//
//		count++;
//		x = y = result1 = result2 = 0;
//
//		thread t1(Thread_1);
//		thread t2(Thread_2);
//
//		ready = false;
//
//		t1.join();
//		t2.join();
//
//		if (result1 == 0 && result2 == 0)
//			break;
//	}
//
//	cout << count << "번만에 탈출 성공!!!" << endl;
//
//	return 0;
//}


// 메모리 모델
// 1. 여러 쓰레드가 동일한 메모리(공유 변수)에 동시에 접근, 쓰기(write)할 때 생기는 문제들 파악
// 2. 이 때 경합조건(Race Condition)
// 3. Race Condition을 어떻게 막을 것이냐
// ... Undefined Behavior(정의되지 않은 행동)
// => atomic
// => Lock(mutex) ,,, Mutual Exclusion(상호 베타)

// 우리의 메모리 정책
// 1. atomic을 이용해서 코드 재배치를 막고, 가시성을 지킨다. 

// atomic 연산에 한해, 모든 쓰레드가 동일 객체에 대해서''''동일한 수정 순서''''를 관찰
// => 가시성

// atiomic... 메모리 정책
// => 코드 재배치


// 1004

//int main() // Memory 정책 Atomic (1)
//{
//	atomic<bool> flag = false;
//
//	// atomic 변수 flag에 값을 저장 => 쓰기
//	flag.store(true, memory_order::memory_order_seq_cst); // memory_order_seq_cst  = 순차적으로 해달라(순차적 일관성)
//
//	// atomic 변수를 읽어오는 것 => 읽기
//	bool val = flag.load(memory_order::memory_order_seq_cst);
//
//	// prev에다 flag의 바꾸기 전 값을 넣고 , flag를 수정
//	{
//		bool prev = flag.exchange(true);
//	}
//
//	// 조건부 수정 : condition variable 
//	// => cv라는 객체가 내 예상이 맞으면 바꿔주고, 아니면 말고 (이벤트락에서 사용했었음)
//	{
//		bool expected = false; // 내 예상은 이게 false일 것이다.
//		bool desired = true; // 내 예상이 맞으면 desired로 바꿔줘.
//	
//		flag.compare_exchange_strong(expected, desired); // 주로 strong으로 사용.
//		// flag.compare_exchange_weak(expected, desired); => while(true) weak는 한번만 체크한다.while true랑 같이간다.
//	}
//
//	return 0;
//}


//atomic<int32> flag;
//int32 value;
//
//void Producer()
//{
//	value = 10;
//
//	flag.store(1, memory_order_release); // seq_cst  사용한다면 이 위로 모든 값들이 보장된다.
//}
//
//void Consumer()
//{
//	while (flag.load(memory_order_acquire) != 1)
//	{
//
//	};
//
//	cout << value << endl;
//}
//
//int main()
//{
//	//flag.store(0, memory_order_seq_cst);
//	flag.store(0);
//	value = 0;
//
//	thread t1(Producer);
//	thread t2(Consumer);
//
//	t1.join();
//	t2.join();
//
//	// Memory 정책
//	// 1. seq_cst (sequential consistency) // 순서적 일관성 => 매우 엄격
//	// - 코트 재배치 x, 가시성 o
//	// 
//	// 2. acquire - release => 중도
//	// 3. relaxed => 컴파일러 최적화 여지가 많다.
//
//	return 0;
//}

//// TLS 영역이란..
//// 각 쓰레드마다 갖고있는 고유 메모리 저장공간
//
//// 거실에 일감이 있다.
//// -> 거실에 있는 일감을 4명이서 분배해서 일을 하고 싶다.
//// -> 4명이서 거실에 다같이 일을 하려고한다
//// -> 일감을 조금씩 때어서 각자 자기방에 들어가서 일을 해놓고
////		다시 거실에 갖다놓는다면?
//
//// TLS (Thread Local Storage)
//
//thread_local int32 L_ThreadID; // TLS영역 변수
////int G_aInt = 1; // 공용변수
//
//void MySetThreadId(int32 id)
//{
//	L_ThreadID = id;
//
//	while (true)
//	{
//		cout << "Hi Im thread : " << L_ThreadID << endl;
//		this_thread::sleep_for(1000ms);
//	}
//}
//
//int main()
//{
//	vector <thread> threads;
//
//	for (int i = 0; i < 10; i++)
//	{
//		threads.push_back(thread(MySetThreadId, (i + 1)));
//	}
//	
//	for (auto& t : threads)
//	{
//		t.join();
//	}
//
//	return 0;
//}

// Lock based Stack
// Lock based Queue

//#include "LockBasedQueue.h"
//#include "LockBasedStack.h"
//
//#include "ThreadManager.h"
//#include "Lock.h"
//void Push()
//{
//	while (true)
//	{
//		int32 value = rand() % 100;
//		q.Push(value);
//
//		this_thread::sleep_for(100ms);
//	}
//}
//
//void Pop()
//{
//
//	while (true)
//	{
//		int32 data = 0;
//		
//		//s.WaitPop(data); 사용할수 있지만 TryPop으로 확인하고하는게 낫겠다.
//		
//		if (q.TryPop(data))
//		{
//			cout << data << endl;
//		}
//	}
//}

//class TestJob
//{
//	USE_LOCK
//public:
//	int TestRead()
//	{
//		READ_LOCK;
//		if (q.empty() == false)
//			return q.front();
//
//	}
//
//	void TestPush()
//	{
//		WRITE_LOCK;
//
//		q.push(rand() % 100);
//	}
//
//	void TestPop()
//	{
//		WRITE_LOCK;
//		if (q.empty() == false)
//			q.pop();
//	}
//
//private:
//	queue<int> q;
//};
//
//TestJob GJob;
//
//void ThreadRead()
//{
//	while (true)
//	{
//		int num = GJob.TestRead();
//		cout << num << endl;
//	}
//}
//
//void ThreadWrite()
//{
//	while (true)
//	{
//		GJob.TestPush();
//		this_thread::sleep_for(100ms);
//		GJob.TestPop();
//	}
//}
//
//int main()
//{
//
//	CoreGlobal::Create();
//
//	// Read And Wirte Lock
//	for(int i = 0; i < 2; i++)
//	CoreGlobal::Instance()->TM()->Launch(ThreadWrite);
//
//	for (int i = 0; i < 5; i++)
//		CoreGlobal::Instance()->TM()->Launch(ThreadRead);
//		
//	CoreGlobal::Delete();
//
//	return 0;
//}

//const int MAX_NUMBER = 100'0000;
//
//bool IsPrime(int num)
//{
//	if (num == 0 || num == 1) return false;
//	if (num == 2 || num == 3) return true;
//
//	int findNum = (int)sqrtf(num);
//
//	for (int i = 2; i <= findNum; i++)
//	{
//		if (num % i == 0)
//			return false;
//	}
//	return true;
//}
//
//atomic<int> result = 0;
//
//void PrimeRange(int start, int end)
//{
//	// primeNum이면 result를 올린다.
//	for (int i = start; i < end; i++)
//	{
//		if (IsPrime(i))
//		{
//			result.fetch_add(1);
//		}
//	}
//}
//
//int solution()
//{
//	vector<thread> threads;
//
//	int coreCount = thread::hardware_concurrency();
//	int temp = MAX_NUMBER / coreCount;
//	//int count = 0;
//	//for (int i = 2; i < MAX_NUMBER; i++)
//	//{
//	//	//i가 소수인가?
//	//	// 소수이면 count++
//	//	// 아니면 continue;
//	//	if (IsPrime(i))
//	//		count++;
//	//}
//
//
//	for (int i = 0; i < coreCount; i++)
//	{
//		// 0 ~ MAX
//		int start = temp * i;
//		int end = temp * (i + 1);
//		if(end > MAX_NUMBER || i== coreCount -1) end = MAX_NUMBER;
//		threads.push_back(thread(PrimeRange, start, end));
//	}
//
//	for (auto& thread : threads)
//		thread.join();
//		
//	return result;
//}

//int main()
//{
//	CoreGlobal::Create();
//
//	int64 start = ::GetTickCount64();
//
//	int answer = 0;
//
//	answer = solution();
//
//	cout << answer << endl;
//
//	int64 end = ::GetTickCount64();
//
//	cout << "걸린 시간 : " << end - start << "ms" << endl;
//
//	CoreGlobal::Delete();
//	return 0;
//}

//void Login()
//{
//	while (true)
//	{
//		AccountManager::GetInstance()->Login();
//	}
//}
//void Save()
//{
//	while (true)
//	{
//		UserManager::GetInstance()->Save();
//	}
//}
//
//int main()
//{
//	CoreGlobal::Create();
//
//	AccountManager::Create();
//	UserManager::Create();
//
//	TM_M->Launch(Login);
//	TM_M->Launch(Save);
//
//	TM_M->Join();
//
//
//	AccountManager::Delete();
//	UserManager::Delete();
//
//	CoreGlobal::Delete();
//	return 0;
//}

//#include "RefCounting.h"
//
//using PlayerRef = shared_ptr<class Player>;
//using InventoryRef = shared_ptr<class Inventory>;
//
//class Player
//{
//public:
//	Player() : _hp(0), _atk(0) 
//	{
//		cout << "생성자 호출" << endl;
//	}
//
//	Player(int hp, int atk)
//		: _hp(hp), _atk(atk)
//	{
//		cout << "타임변환 생성자 호출" << endl;
//	}
//
//	virtual ~Player()
//	{
//		cout << "소멸자 호출" << endl;
//	}
//
//	//static void* operator new(size_t t)
//	//{
//	//	cout << "Player new!!" << endl;
//	//	void* ptr = std::malloc(t);
//	//	
//	//	return ptr;
//	//}
//
//	//static void operator delete(void* ptr)
//	//{
//	//	cout << "Player delete!!!" << endl;
//	//	std::free(ptr);
//
//	//	return;
//	//}
//
//	bool IsDead()
//	{
//		return _hp <= 0;
//	}
//
//public:
//
//	int _hp;
//	int _atk;
//};
////
////class Inventory
////{
////public:
////	Inventory(PlayerRef p) : _owner(p) {} //: _owner(**p) {} // 스마트포인터의 참조카운트를 올리지 않으면서 참조
////
////	void OpenInven()
////	{
////		if (_owner.expired() == false)
////		{
////			auto ptr = _owner.lock();
////			if (ptr != nullptr)
////				cout << ptr->_hp << ptr->_atk << endl;
////		}
////	}
////public:
////	// Player& _owner;
////	weak_ptr<Player> _owner;
////};
//
////int main()
////{
////	// shared_ptr
////	// - 참조 카운팅
////	// - 순환 참조 문제
////
////	// weak_ptr
////	// - Weak Counting을 한다.
////	// - 순환 참조 문제를 해결하기 위해 쓰이는 ptr
////	// - 생성주기에 관여하지 않는다.
////
////
////	CoreGlobal::Create();
////
////
////
////	//PlayerRef p = make_shared<Player>();
////	//InventoryRef inven = make_shared<Inventory>(p);
////	//p->_inven = inven;
////	//// => 순환참조
////
////	//inven->OpenInven();
////
////	////p->_inven = nullptr;
////	////inven->_owner = nullptr;
////	//// => 순환참조 고리 끊기
////
////	CoreGlobal::Delete();
////
////	return 0;
////}
//
//class Knight : public Player
//{
//public:
//	int _stamina = 0;
//};

//void* operator new(size_t t)
//{
//	cout << "new!! " << endl;
//	void* result = std::malloc(t);
//
//	return result;
//}
//
//void operator delete(void* ptr)
//{
//	cout << "delete !!" << endl;
//	std::free(ptr);
//
//}
//int main()
//{
//
//	CoreGlobal::Create();
//
//	Player* p = xnew<Player,int,int>(100,10);
//
//	xdelete(p);
//
//	CoreGlobal::Delete();
//
//	return 0;
//}

// 선수지식
// - 허상포인터로 인한 메모리 오염
// - 가상메모리와 물리적메모리
// - 사실 new delete는 바로바로 일을 해준 것이 아니였다. => delete가 실제로 바로 삭제하는게 아니였다.
//	=> 허상포인터에 데이터를 수정할 수 있었다.

// Stomp allocator의 의미
// 1. DEBUG 환경에서 메모리 오염 방지
// 2. DEBUG 환경에서 다운캐스팅 후 메모리 오버플로우 방지 

//
//int main()
//{
//
//	CoreGlobal::Create();
//
//	Player* P = new Player();
//
//	//허상 포인터(Dangling Ptr)
//	//P->_atk = 10;
//	//P->_hp = 20;
//	//delete P;
//	//P->_hp = 50; //메모리 오염
//	//// 가상메모리
//	//P = nullptr;
//	//P = new Player();
//	
//	//// ------다른 프로그램-------
//	//int64* temp = (int64*)(0x0000019B32DC2318);
//	//*temp = 500;
//	// ----------------------------
//	
//	// 물리 메모리 
//	 
//	// 운영체제 페이징 
//	// 운영체자가 메모리를 할당하고 관리할 떄는 페이지 단위로 관리를 하나.
//	// 각 프로세스한테 가상메모리를 주고 유저레벨에서 서로 간섭할 수 없게 만든다.
//	// => 물리적 메모리는 운영체자가 담당한다
//
//	SYSTEM_INFO s_info;
//	::GetSystemInfo(&s_info);
//
//	s_info.dwPageSize; // 페이지 한 개당 사이즈 4KB
//	s_info.dwAllocationGranularity; // 메모리를 할당할 떄 이 숫자의 배수로 할당이 된다,
//
//	int* temp = (int*)::VirtualAlloc(nullptr, 4, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
//	*temp = 100;
//
//	::VirtualFree(temp,0,MEM_RELEASE);
//
//	//*temp = 200; // 런타임 에러 바로 남.
//	// => new/delete 바로 VirtualAlloc, VirtualFree를 바로 해주지 않는다.
//
//
//
//	//test
//	Knight* k = reinterpret_cast<Knight*>(new Player());
//	//K->_stamina = 100;  => 메모리 오버플로우
//	// std:: new/delete Allocator 경우 상속 구조에서 메모리 오버플로우를 허용하지 않음 
//
//	delete k;
//	
//	k->_hp = 100;
//
//	// 4096 bytes
//	// [[p2]                   ]  // 꽉차면 할당하지않음
//	// [                  [p2] ] [100] // 꽉차면 할당하지않음
//
//	Knight* p2 = reinterpret_cast<Knight*>(xnew<Player>());
//	
//	p2->_stamina = 100; // 메모리 오버플로우 막음
//
//
//	xdelete (p2);
//
//	// ??????
//	vector<Player*, StompAllocator> v;
//	//v.push_back(1);
//
//
//	CoreGlobal::Delete();
//
//	return 0;
//} 

//int main()
//{
//	CoreGlobal::Create();
//
//	vector<Knight*> t;
//
//	MemoryPool temp(100);
//
//	MemoryHeader* header = temp.Pop();
//	Knight* k = reinterpret_cast<Knight*>(MemoryHeader::AttachHeader(header, sizeof(Knight)));
//
//	k->_hp = 0;
//	k->_atk = 1;
//	k->_stamina = 2;
//	//reinterpret_cast<Knight*>(k)->_hp = 1;
//
//	
//
//
//	for (int i = 0; i < 10; i++)
//	{
//		t.push_back(xnew<Knight>());
//	}
//
//	for (auto k : t)
//	{
//		xdelete<Knight>(k);
//	}
//
//
//	CoreGlobal::Delete();
//
//	return 0;
//}

//int main()
//{
//	CoreGlobal::Create();
//	
//	for (int32 i = 0; i < 5; i++)
//	{
//		TM_M->Launch([]()-> void
//			{
//				while (true)
//				{
//					Vector<Knight> v(10);
//
//					Map<int32, Knight> m;
//					m[1] = Knight();
//
//					this_thread::sleep_for(500ms);
//
//				}
//			});
//	}
//	
//	TM_M->Join();
//	
//
//
//	CoreGlobal::Delete();
//
//	return 0;
//}

#include "pch.h"
#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib") // 위에 선언한 헤더파일들을 가져다 쓰기위한 링크 

const int32 BuffSize = 1000;

struct  Session
{
	SOCKET socket = INVALID_SOCKET;
	char recvBuffer[BuffSize] = {};
	char sendBuffer[100] = "Hello Im Server!!";
	int32 recvBytes = 0;
	int32 sendBytes = 0;


};

enum IO_TYPE
{
	READ,
	WRITE,
	ACCEPT,
	CONNET
	// ... 추가됨 packet Header
};

struct OverlappedEx
{
	WSAOVERLAPPED overlapped = {};
	int32 type = 0; // read write accept connet ...

};

// 쓰레드 5개에 부여될 일감 -> 결과 보기
void WorkerThreadMain(HANDLE iocpHandle)
{
	while (true)
	{
		// GetQueuedCompletionStatus
		DWORD bytesTranferred = 0; // 전송된 크기
		Session* session = nullptr;
		OverlappedEx* overlappedEx = nullptr;
		
		// ret == true였다.
		// -> recv 완료 상태
		BOOL ret = ::GetQueuedCompletionStatus(iocpHandle, &bytesTranferred, /*Key*/(ULONG_PTR*)&session,
			(LPOVERLAPPED*)&overlappedEx, INFINITE);

		if (ret == FALSE || bytesTranferred == 0)
		{
			// 연결 끊김
			continue;

			// 읽기
		}

		// session과, overlapped 세팅완료
		
		// 처리
		switch (overlappedEx->type)
		{
		case IO_TYPE::READ:
		{
			cout << session->recvBuffer << endl;

			WSABUF wsaBuf;
			wsaBuf.buf = session->recvBuffer;
			wsaBuf.len = BuffSize;

			DWORD recvLen = 0;
			DWORD flags = 0;
			// 다시 recv할 수 있게 재예약
			::WSARecv(session->socket, &wsaBuf, 1, &recvLen, &flags, &overlappedEx->overlapped, NULL);
			break;
		}
		
		// TODO 
		// send 
		// WSASend
		default:
			break;
		}
	}
}
// Completion Port
// 윈도우 비동기 I/O방법중 가장 뛰어난 ?
// IO 데이터를 전송하는  작업 ?
// 
// 쓰레드마다 APC 들고있음 ?
// 쓰레드마다 TLS 갖고잇음
int main()
{
	CoreGlobal::Create();

	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	// SELECT 기반 소켓프로그래밍 
	// 소켓 함수 호출이 성공할 시점을 미리 알 수 있다.
	// ...문제
	// recvBuff에 데이터가 없는데 recv해서 읽을려고한다. (X)
	// sendBuff(커널)에 꽉 찼는데 send함수(유저레벨 sendBuffer -> 커널레벨 sendBuffer에 복사) 호출 (X)

	// socket set
	// 1) 읽기, 쓰기, 예외... 관찰 대상 등록
	// 2) select(readSet, writeSet, exceptSet); => 관찰
	// 3) 적어도 하나의 소켓이 준비되면 리턴
	// 4) 남은 소켓 체크해서 진행

	// 블로킹 소켓
	// 블로킹 함수들
	// accept -> 접속한 클라가 있을 때
	// connect -> 서버에 접속이 성공했을 때
	// send -> sendBuff에 요청한 데이터를 복사했을 때
	// recv -> recvBuff에 도착한 데이터가 있고, 이를 성공적으로 복사했을 때

	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
		return 0;

	u_long on = 1;
	if (::ioctlsocket(listenSocket, FIONBIO, &on) == INVALID_SOCKET) // 논블로킹 소켓 만드는 함수
		return 0;

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	serverAddr.sin_port = ::htons(7777);

	// listenSocket Setting
	if (::bind(listenSocket, (sockaddr*)(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
		return 0;

	if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
		return 0;

	cout << "Accept" << endl;

	//Overlapped 모델 (Completion Routine 콜백기반) => 비동기 + 논블락
	// 장점 : 비동기 + 논블락
	// 단점 : 쓰레드마다 APC큐가 있다.
	//..... 쓰레드를 Alertable Wait 부담
	//..... 이벤트 방식 소켓 : 이벤트 1 : 1 대응

	// IOCP (Input Output Completion Port) 모델
	// - APC큐 => Completion Port로 바뀜 (* 쓰레드마다 한개씩 있는게 아니라 중앙관리)
	// - Aleratable Wait >CP 결과 처리를 GetQueuedCompletionStatus
	// => 멀티쓰레드환경에 매우 적합;
	// - 이벤트 소켓 1:1 대응 (X)

	// CreateIoCompletionPort => CP 생성/ CP에 소켓연동
	// GetQueuedCompletionStatus => 결과 처리 

	vector<Session*> sessionManger;

	// CP 생성 
	HANDLE iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// 멀티쓰레드 환경 만들기
	for (int32 i = 0; i < 5; i++)
	{
		// 일감 부여
		TM_M->Launch([=]() {WorkerThreadMain(iocpHandle); });
	}

	// Main Thread Accept
	while (true)
	{
		SOCKADDR_IN clientAddr;
		int32 addrLen = sizeof(clientAddr);

		// TODO
		// accept = > AcceptEx
		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET) continue;

		Session* session = xnew<Session>();
		session->socket = clientSocket;
		sessionManger.push_back(session);

		cout << "Client Connected!" << endl;

		// 소켓을 CP에 등록 : CP한테 소켓을 관찰해달라...
		::CreateIoCompletionPort((HANDLE)clientSocket, iocpHandle, /* Key */(ULONG_PTR)session, 0);


		// Recv 예약
		WSABUF wsaBuf;
		wsaBuf.buf = session->recvBuffer;
		wsaBuf.len = BuffSize;

		OverlappedEx* overlappedEx = xnew<OverlappedEx>();
		overlappedEx->type = IO_TYPE::READ;

		DWORD recvLen = 0;
		DWORD flags = 0;
		::WSARecv(clientSocket, &wsaBuf, 1, &recvLen, &flags, &overlappedEx->overlapped, NULL); // Overlapped 동일한 WSARecv
		

	}

	TM_M->Join();

	::WSACleanup();

	CoreGlobal::Delete();

	return 0;
}

// 1. Select 기반 Socket IO(소켓 입출력)
// 2. WSAEventSelect 기반 Socket IO

// WSAEventSelect 기반 => WSAEventSelect가 핵심
// (소켓 - 이벤트객체) 네트워크 이벤트를 (이벤트 객체로) 감지

// 이벤트 객체 관련 함수
// 생성 : WSACreateEvent
// 삭제 : WSACloseEvent
// (여러 이벤트들의)신호상태감지 : WSAWaitforMultipleEvents
// 구체적인 네트워크 이벤트 확인 : WSAEnumNetworkEvents

// (소켓 - 이벤트객체) 연동
// WSAEventSelect(socket, event, netWorkEvents);
// - 주로쓰는 네트워크 이벤트
// -- FD_ACCPET => accept
// -- FD_READ => recv
// -- FD_WRITE => send
// -- FD_CLOSE : 상대가 접속 종료
// -- FD_CONNECT : 상대 접속 확인


// Overapped Socket IO(비동기 + 논블로킹 소켓 입출력 방식)
// WSASend, WSARecv
// (AcceptEx,ConntectEx)
// 1. OverLapped 함수를 건다.
// 2. Overlapped  함수가 성공했는지 확인
// 3. -> 성공했으면 결과 얻어서 처리
//    -> 실패했으면 사유 확인하고(Pending 상태면 그대로 다음 꺼 진행)

// OverLappend Event 기반 ID 모델의 장점
// 1. (비동기, 넌블록킹)
// 
// OverLappend Event 기반 ID 모델의 단점
// 1. 성능 
// -> session과 wsaevent를 묶어줘야한다.
// -> 1000명의 session(Client)의 네트워크를 위해서 1000개의 wsaEvent가 필요하다.
// ... 최대 64개 
// 결론 : 서버에 적합한 모델이 아니다.
// 

// -----------------Oerlapped Callback based----------------------
// APC Queue
// 쓰레드가 알람 가능한 상태? 가 되었을 때 호출할 콜백 함수를 모아둔 Queue


// cout << "Accept" << endl 다음꺼임
//while (true)
//{
//	SOCKADDR_IN clientAddr;
//	int32 addrLen = sizeof(clientAddr);
//
//	SOCKET clientSocket;
//
//	// accpt 준비
//	while (true)
//	{
//		clientSocket = accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
//		if (clientSocket != INVALID_SOCKET)
//			break;
//
//		if (::WSAGetLastError() == WSAEWOULDBLOCK)
//			continue;
//
//		// 문제 있는 상황....
//
//		return 0;
//	}
//	Session session = Session{ clientSocket };
//	WSAEVENT wsaEvent = ::WSACreateEvent(); // WSASend or WSARecv 했을 떄 상태를 체크 
//	session.overlapped.hEvent = wsaEvent;
//
//	cout << "Client Connected!" << endl;
//
//	while (true)
//	{
//
//
//		WSABUF wsaBuf;
//		wsaBuf.buf = session.recvBuffer;
//		wsaBuf.len = BuffSize;
//
//		DWORD recvLen = 0;
//		DWORD flags = 0;
//
//		// 비동기 WSARecv
//		if (::WSARecv(clientSocket, &wsaBuf, 1, &recvLen, &flags, &session.overlapped, &RecvCallBack) == SOCKET_ERROR)
//		{
//			// WSARecv가실패
//
//			if (::WSAGetLastError() == WSA_IO_PENDING)
//			{
//				// Pending :: 보류하고 나중에 확인
//				// Alertable Wais 상태로 변경
//				::SleepEx(INFINITE, TRUE);
//
//			}
//			else
//			{
//				// TODO : 문제가 있는 상황
//				break;
//			}
//		}
//		cout << "Data Recv Len = " << recvLen << endl;
//
//		for (int i = 0; i < recvLen; i++)
//		{
//			if (session.recvBuffer[i] == 0)
//				break;
//
//			cout << session.recvBuffer[i];
//		}
//		cout << endl;
//
//		// send? 
//		// 과제 ?
//
//		wsaBuf.buf = session.sendBuffer;
//		wsaBuf.len = sizeof(session.sendBuffer);
//
//		DWORD sendLen = 0;
//		//DWORD flags = 0;
//
//		// send
//		if (::WSASend(clientSocket, &wsaBuf, 1, &sendLen, flags, &session.overlapped, nullptr) == SOCKET_ERROR)
//		{
//			// WSARecv가실패
//
//			if (::WSAGetLastError() == WSA_IO_PENDING)
//			{
//				// Pending :: 보류하고 나중에 확인
//				::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, FALSE);
//				::WSAGetOverlappedResult(clientSocket, &session.overlapped, &recvLen, FALSE, &flags);
//
//			}
//			else
//			{
//				// TODO : 문제가 있는 상황
//				break;
//			}
//		}
//
//		cout << "send Data! Len1212 = " << sendLen << endl;
//
//	}
//
//	::closesocket(session.socket);
//
//}
//



	//// SELECT 기반 소켓프로그래밍
	//// 소켓 함수 호출이 성공할 시점을 미리 알 수 있다.
	//// ... 문제
	//// recvBuff에 데이터가 없는데 recv해서 읽을려고한다 (X)
	//// sendBuff(커널)에 꽉 찼는데 send함수 (유저레벨 sendBuffer -> 커널레벨 sendBuffer에 복사) 호출 (x)

	//// socket set
	//// 1) 읽기, 쓰기, 예외...관찰 대상 등록
	//// 2) select(readSet, writeSet, exceptSet); => 관찰
	//// 3) 적어도 하나으 ㅣ소켓이 준비되면 리턴
	//// 4) 남은 소켓 체크해서 진행 

	//// 블로킹 소켓
	//// 블로킹 함수들
	//// accept -> 접속한 클라가 있을 때
	//// connect -> 서버에 접속이 성공했을 때
	//// send -> sendBuff에 요청한 데이터를 복사했을 때
	//// recv -> recvBuff에 도착한 데이터가 있고, 이를 성공적으로 복사했을 때


	//WSAData wsaData;
	//if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	//	return 0;

	//// SELECT 기반 소켓프로그래밍 
	//// 소켓 함수 호출이 성공할 시점을 미리 알 수 있다.
	//// ...문제
	//// recvBuff에 데이터가 없는데 recv해서 읽을려고한다. (X)
	//// sendBuff(커널)에 꽉 찼는데 send함수(유저레벨 sendBuffer -> 커널레벨 sendBuffer에 복사) 호출 (X)

	//// socket set
	//// 1) 읽기, 쓰기, 예외... 관찰 대상 등록
	//// 2) select(readSet, writeSet, exceptSet); => 관찰
	//// 3) 적어도 하나의 소켓이 준비되면 리턴
	//// 4) 남은 소켓 체크해서 진행

	//// 블로킹 소켓
	//// 블로킹 함수들
	//// accept -> 접속한 클라가 있을 때
	//// connect -> 서버에 접속이 성공했을 때
	//// send -> sendBuff에 요청한 데이터를 복사했을 때
	//// recv -> recvBuff에 도착한 데이터가 있고, 이를 성공적으로 복사했을 때

	//SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	//if (listenSocket == INVALID_SOCKET)
	//	return 0;

	//u_long on = 1;
	//if (::ioctlsocket(listenSocket, FIONBIO, &on) == INVALID_SOCKET) // 논블로킹 소켓 만드는 함수
	//	return 0;

	//SOCKADDR_IN serverAddr;
	//::memset(&serverAddr, 0, sizeof(serverAddr));
	//serverAddr.sin_family = AF_INET;
	//serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	//serverAddr.sin_port = ::htons(7777);

	//// listenSocket Setting
	//if (::bind(listenSocket, (sockaddr*)(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
	//	return 0;

	//if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	//	return 0;

	//cout << "Accept" << endl;

	//
	//// Select 기반 Socket

	//vector<Session> sessions;
	//sessions.reserve(100);

	//// 소켓 Set
	//fd_set reads;
	//fd_set writes;


	//while (true)
	//{
	//	// 소켓 셋 초기화
	//	FD_ZERO(&reads);
	//	FD_ZERO(&writes);

	//	// ListenSocket 등록 
	//	FD_SET(listenSocket, &reads);

	//	// clients 소켓 등록
	//	for (auto& session : sessions)
	//	{
	//		if (session.recvBytes <= session.sendBytes)
	//		{
	//			FD_SET(session.socket, &reads);

	//		}
	//		else
	//		{
	//			FD_SET(session.socket, &writes);
	//		}
	//	}

	//	int32 retVal = ::select(0, &reads, &writes, nullptr, nullptr);
	//	if (retVal == SOCKET_ERROR)
	//		break;

	//	// Listener 소켓 체크
	//	if (FD_ISSET(listenSocket, &reads))
	//	{
	//		SOCKADDR_IN clientAddr;
	//		int32 addrLen = sizeof(clientAddr);
	//		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
	//		if (clientSocket != INVALID_SOCKET)
	//		{
	//			// 클리이언트 접속
	//			cout << "Client Connected" << endl;
	//			sessions.push_back(Session{ clientSocket });

	//		}
	//	}

	//	// 나머지 소켓 체크
	//	for (Session& session : sessions)
	//	{
	//		// Read
	//		if (FD_ISSET(session.socket, &reads))
	//		{
	//			int32 recvLen = ::recv(session.socket, session.recvBuffer, BuffSize, 0);

	//			if (recvLen <= 0)
	//			{
	//				continue;
	//			}

	//			session.recvBytes = recvLen;
	//			cout << "recv Size :" << session.recvBytes << endl;


	//		}

	//		// 현재 상황
	//		// - client가 10개짜리 문자열을 보냈고, 10개를 바은 상황
	//		// - 처음 recv 받고, 첫 send하기 시작
	//		// recvBytes = 10
	//		// sendBytes = 0
	//		// 
	//		// write
	//		if (FD_ISSET(session.socket, &writes))
	//		{
	//			// 블로킹 모드 -> 모든 데이터를 다 보낼 떄까지 대기
	//			// 논블로킹 모드 -> 이 ㄹ부만 보낼 수 있음. (상대방의 recvBuffer에 따라서)
	//			int32 sendLen = ::send(session.socket, session.recvBuffer, session.recvBytes - session.sendBytes, 0);

	//			// sendLen : 보냈을 떄 그 길이
	//			if (sendLen == SOCKET_ERROR)
	//			{
	//				// TODO : DisConnect
	//				continue;
	//			}

	//			session.sendBytes += sendLen; // 7 ? 
	//			cout << "Send Size :" << session.sendBytes << endl;

	//			if (session.recvBytes == session.sendBytes)
	//			{
	//				session.sendBytes = 0;
	//				session.recvBytes = 0;
	//			}

	//		}
	//	}

	//}
	//	::WSACleanup();

	//	return 0;
	//}


	//SOCKET serverSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	//if (serverSocket == INVALID_SOCKET)
	//{
	//	int32 errCode = ::WSAGetLastError();
	//	cout << "Socket ErroCode: " << errCode << endl;
	//	return 0;
	//}

	//SOCKADDR_IN serverAddr;
	//::memset(&serverAddr, 0, sizeof(serverAddr));
	//serverAddr.sin_family = AF_INET;
	//serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	//serverAddr.sin_port = ::htons(7777);

	//// Socket level
	//// 옵션을 해석, 처리하는 주체 
	//// 소켓코드 -> SOL_SOCKET
	//// IPv4 -> IPROTO_IP
	//// TCP -> IPPROTO_TCP

	//// Socket 옵션 
	//// SO_KEEPALIVE => 주기적으로 연결이 끊겼는지 확인하는 옵션
	//bool enble = true;
	//::setsockopt(serverSocket, IPPROTO_IP, SO_KEEPALIVE, (char*)(&enble), sizeof(enble));

	//// 소켓 만들기
	//// => 운영체제 ... Socket 번호
	//// => 운영체제 ... SendBuff, RecvBuff

	//// 우리가 하던 거
	//// sendBuff를 stack이나 heap에 사용자정의로 만든다.
	//char arr[100] = "temp";
	//// send(serverSocket, arr, nullptr); => 사용자가 만든 sendBuffer를 운영체제가 만들어놓은 sendBuffer에 복사

	//// 소켓을 닫을려고함
	//// -> Send("~~")
	//// -> SendBuff에 복사 
	//// -> Socket이 닫힘
	//LINGER linger;
	//linger.l_onoff = 1;
	//linger.l_linger = 5;
	//::setsockopt(serverSocket, SOL_SOCKET, SO_LINGER, (char*)(&linger), sizeof(linger));
	//
	//// SendBuff의 크기 가져오기
	//int32 sendBuffsize;
	//int32 optionLen= sizeof(sendBuffsize);

	//::getsockopt(serverSocket, SOL_SOCKET, SO_SNDBUF, (char*)(&sendBuffsize), &optionLen);
	//cout << "SendBuffer Size : " << sendBuffsize << endl;

	//// recvBuff의 크기 가져오기
	//int32 recvBuffSize;
	//optionLen = sizeof(recvBuffSize);

	//::getsockopt(serverSocket, SOL_SOCKET, SO_RCVBUF, (char*)(&recvBuffSize), &optionLen);
	//cout << "SendBuffer Size : " << recvBuffSize << endl;

	//// SO_REUSEADDR
	//// IP주소 및 포트번호 재사용
	//{
	//	bool enable = true;
	//	::setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)(&enable), sizeof(enable));
	//}

	//// 네이글 알고리즘
	//// 작은 패킷들을 한번에 모아서 보내는 알고리즘
	//// 장점 : 작은 패킷이 불필요하게 많이 생성되는 일을 방지
	//// 단점: 반은 시간 손해
	//// => 네이글 알고리즘이 처리하기 전에 프로그래머(무리)가 패킷 설계를 하고 보낼 거기 떄문에

	//{
	//	bool enable = false;
	//		::setsockopt(serverSocket, IPPROTO_TCP, TCP_NODELAY, (char*)(&enable), sizeof(enable));
	//}

	//// 모아서 한번에 전송 ?
	//

	//::WSACleanup();

	//if (::bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	//{
	//	int32 errCode = ::WSAGetLastError();
	//	cout << "Bind ErrorCode : " << errCode << endl;
	//	return 0;
	//}

	//// UDP
	//// ServerSocket.
	//// - 여러명의 socket들이 serverSocket한테 직접 정보를 전달
	//while (true)
	//{
	//	SOCKADDR_IN clientAddr;
	//	::memset(&clientAddr, 0, sizeof(clientAddr));
	//	int32 addrLen = sizeof(clientAddr);

	//	this_thread::sleep_for(1s);

	//	char recvBuffer[1000];

	//	// UDP
	//	// 1:1 연결이 아니라, 1: 다 연결 가능
	//	// listener가 없고 SeverSocket으로 나한테 정보를 보낸 것을 Recv한다.
	//	int32 recvLen = ::recvfrom(serverSocket, recvBuffer, sizeof(recvBuffer), 0, (SOCKADDR*)&clientAddr, &addrLen);
	//	if (recvLen <= 0)
	//	{
	//		int32 errCode = ::WSAGetLastError();
	//		cout << "Recv ErrorCode " << endl;
	//		return 0;
	//	}

	//	cout << "Recv Data : " << recvBuffer << endl;
	//	cout << "Recv Len : " << recvLen;

	//	char sendBuffer[100] = "Hello Client I'm Server";
	//	int32 sendCode = ::sendto(serverSocket, sendBuffer, sizeof(sendBuffer), 0, (SOCKADDR*)&clientAddr, sizeof(clientAddr));
	//	if (sendCode == SOCKET_ERROR)
	//	{
	//		int32 errorCode = ::WSAGetLastError();
	//		cout << "Send ErrorCode : " << errorCode << endl;
	//		return 0;
	//	}
	//}
	//::WSACleanup();

	//return 0;

//int main()
//{
//    // 원속 초기화(ws2_32 라이브러리 초기화)
//   //관련정보가 wsaData에 채워짐
//    WSAData wsaData;
//    if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//        return 0;
//
//    // 1. listener Socket 만들기 => 연결 시도를 받아줌
//    // AF_INET vs AT_INET6 ... IPv4 vs IPv6
//    // SOCK_STREAM vs SOCK_DGRAM ... TCP vs UDP => 면접문제
//    //  TCP : 연결지향형 소켓, 연결된 대상 외에 다른 대상과는 통신 불가능, 
//    //  -> 연결지향형 소켓은 데이터를 보내고 중간중간 확인작업, 안정적으로 데이터를 보낼수있음 UDP에 비해 속도가 느림 
//    //  UDP : 비연결지향형 소켓 
//    //  -> 데이터를 보내고 난 후에 확인작업을 하지 않아서 데이터가 다 수신 됬는지 확인 불가능 , 속도는 빠르지만 데이터 소실 가능성 있음 
//    // 
//    //  0 : 자동으로 protocol 설정
//
//    SOCKET serverSocket = ::socket(AF_INET, SOCK_DGRAM, 0); // socket의 번호를 발급받음 // 소켓생성,IPv4
//    if (serverSocket == INVALID_SOCKET)
//    {
//        int32 errCode = ::WSAGetLastError();
//        cout << "Socket ErroCode: " << errCode << endl;
//        return 0;
//    }
//
//    // 2 .내가 어떻게 받아야 할지... Listener 에 세팅
//    SOCKADDR_IN serverAddr; // IPv4
//    ::memset(&serverAddr, 0, sizeof(serverAddr)); // serverAddr 0으로 다 밀어버리기
//    serverAddr.sin_family = AF_INET; // IPv4로 연결하겠다는 것
//    //::inet_pton(AF_INET, "192.168.0.9", &serverAddr.sin_addr);
//    serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY); // << 니가 알아서 IP주소 써줘.
//    serverAddr.sin_port = ::htons(7777); // 1 ~ 1000 여기는 건들면 안됌.
//    // 3. Listener 세팅
//    if (::bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
//    {
//        int32 errCode = ::WSAGetLastError();
//        cout << "Bind ErrorCode : " << errCode << endl;
//
//        return 0;
//    }
//
//    //4. 연결(Listen) 준비 혹은 대기
//    // backlog : 대기자
//    //if (::listen(listener, 10) == SOCKET_ERROR)
//    //{
//    //    int32 errCode = ::WSAGetLastError();
//    //    cout << "Listen ErrorCode : " << errCode << endl;
//    //    return 0;
//    //}
//
//    // ------------------연결 준비 끝-------------------
//
//    while (true)
//    {
//        // 5. Accept
//        SOCKADDR_IN clientAddr; // IPv4
//        ::memset(&clientAddr, 0, sizeof(clientAddr));
//        int32 addrLen = sizeof(clientAddr);
//
//        // listner한테 현재 대기중인 클라이언트를 받아서 정보 추출(client Addr)
//    /*    SOCKET clientSocket = ::accept(serverSocket, (SOCKADDR*)&clientAddr, &addrLen);
//        if (clientSocket == INVALID_SOCKET)
//        {
//            int32 errCod = ::WSAGetLastError();
//            cout << "Accept ErrorCode : " << errCod << endl;
//            return 0;
//        }*/
//        //// 손님 입장
//        //char ipAddress[16];
//        //::inet_ntop(AF_INET, &clientAddr.sin_addr, ipAddress, sizeof(ipAddress));
//        //cout << "Client Connected! Client IP = " << ipAddress << endl;
//        this_thread::sleep_for(1s);
//
//        char recvBuffer[1000];
//
//        // UDP
//        // 1:1 연결이 아니라 1 : 다 연결 가능 
//        // listener 가 없고 ServerSocket으로 나한테 정보를 보낸 것을 Recv한다
//
//        int32 recvLen = ::recvfrom(serverSocket, recvBuffer, sizeof(recvBuffer), 0,(SOCKADDR*)&clientAddr,&addrLen);
//
//        if (recvLen <= 0)
//        {
//            int32 errCode = ::WSAGetLastError();
//            cout << "Recv ErrorCode " << endl;
//            return 0;
//        }
//
//        cout << "Recv Data : " << recvBuffer << endl;
//        cout << "Recv Len : " << recvLen;
//
//        char sendBuffer[100] = "Hellp Client I'm Server";
//        int32 sendCode = ::sendto(serverSocket, sendBuffer, sizeof(sendBuffer), 0, (SOCKADDR*)&clientAddr, sizeof(clientAddr));
//        if (sendCode == SOCKET_ERROR)
//        {
//            int32 errorCode = ::WSAGetLastError();
//            cout << "Send ErrorCode : " << errorCode << endl;
//            return 0;
//        }
//      
//
//        // 6. 윈속 종료
//    }
//        ::WSACleanup();
//
//        return 0;
//}

// 동기 vs 비동기
// 블록킹 vs 논블록킹
// 단일스레드 vs 멀티스레드


// 블록킹 함수
// 수신할 데이터가 도착할떄까찌 대기 상태( 데이터가 도착하지 않는다면 영원히 대기상태
// 작업이 완전히 끝날때 대기 상태에서 탈출 
// -> 블로킹 대응 방법
// -> TCP : 수신하는 소켓의 수신버퍼가 가득찰 경우 데이터를 송신하는 소켓의 송신파트도 블로킹에 빠짐  (블로킹에 빠져도 연결이 끊기지않음)
// -> UDP : 수신하다 버퍼가 가득 찼을 경우 송신측에서 무시하고 데이터를 보냄, 수신 버퍼는 가득 차서 못 들어가므로 이를 버림 

// 논블록킹 함수
// 작업이 완료될 떄 까지 대기하는 것이 아니라, 작업 요청을 보낸 다음 다른 작업 실행가능 ? 

// 휴대폰
// TCP: 연결지향형 소켓, 연결된 대상 외에 다른 대상과는 통신 불가능, 
//  -> 연결지향형 소켓은 데이터를 보내고 중간중간 확인작업, 안정적으로 데이터를 보낼수있음 UDP에 비해 속도가 느림 
//  -> 1. 전송순서 보장, 2. 신뢰성 보장 3. 분실위험 적다.
//  신뢰성보장: 전송되면 전송이 안된거를 알수있음
//  -> 단점 : 경계가 없다
// -> 경계가없다 

// 메일 
//  UDP : 비연결지향형 소켓 
//  -> 데이터를 보내고 난 후에 확인작업을 하지 않아서 데이터가 다 수신 됬는지 확인 불가능 , 속도는 빠르지만 데이터 소실 가능성 있음 
// 신뢰성 보장안됨 : 전송이 제대로 이루워져있는지 알수없음 일단 정송 

// 샌드 버프

// 리시브 버프 clientAddr


