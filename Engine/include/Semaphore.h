#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>

namespace Venture {
	class Semaphore {
	private:
		int m_count;
		std::mutex m_mutex;
		std::condition_variable m_cv;

	public:
		explicit Semaphore(int initialCount) {
			m_count = initialCount;
		}

		~Semaphore() {

		}

		void Wait() {
			std::unique_lock<std::mutex> lock(m_mutex);

			// Put thread to sleep while m_count is 0
			m_cv.wait(lock, [&] {return m_count != 0; });

			--m_count;
			lock.unlock();
		}

		void Signal() {
			std::unique_lock<std::mutex> lock(m_mutex);	
			++m_count;
			lock.unlock();

			// Signal to wake up a thread if the count was zero
			// Signal after unlocking because otherwise the waking thread would immediately block again
			if (m_count == 1) {
				m_cv.notify_one();
			}
		}
	};
}