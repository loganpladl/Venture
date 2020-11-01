#pragma once

namespace Venture {
	template <class T>
	class CircularQueue {
	private:
		static const int MAX_ELEMENTS = 256;
		static T queue[MAX_ELEMENTS];
		static int head, tail;
	public:
		static int Enqueue(T event);
		static T Dequeue();
	};
}