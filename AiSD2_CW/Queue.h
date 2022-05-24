#include <stdexcept>
#include <cstdio>

using namespace std;

template <class T>
class Node {
private:
	Node* next;

	T data;

public:
	Node() {
		next = nullptr;
	}
	explicit Node(const T value) {
		next = nullptr;
		data = value;
	}
	~Node() {
		next = nullptr;
	}
	/*
	 * funcs allow you set new value to queue_el object properties
	 */
	void set_next(Node* const next_el) {
		next = next_el;
	};
	void set_data(T new_data) {
		data = new_data;
	};

	/*
	 * funcs allow you get value of queue_el object properties
	 */
	Node* get_next() {
		return next;
	};
	T get_data() {
		return data;
	};

	/*
	 * funcs set next/prev properties value to 'nullptr'
	 */
	void clr_next() {
		delete this;
		next = nullptr;
	};
};

template <class T>
class Queue {
private:
	Node<T>* front;
	Node<T>* back;
	Node<T>* temp;

	size_t queue_size;

public:
	Queue() {
		front = nullptr;
		back = nullptr;
		temp = nullptr;
		queue_size = 0;
	}

	~Queue() {
		while (queue_size != 0) {
			this->takeTop();
		}
		front = nullptr;
		back = nullptr;
		temp = nullptr;
		queue_size = 0;
	}

	Node<T>* get_front() {
		return front;
	}

	Node<T>* get_back() {
		return back;
	}

	/*
	 * func adds element to queue
	 */
	void push(T data) {
		temp = new Node<T>(data);
		if (queue_size == 0) {
			front = temp;
			back = temp;
			temp = nullptr;
			queue_size++;
			return;
		}
		back->set_next(temp);
		back = back->get_next();

		temp = nullptr;
		queue_size++;
	}

	/*
	 * func removes element from queue and returns its value
	 */
	T takeTop() {
		if (queue_size == 0) {
			throw std::out_of_range("The queue is empty");
		}
		T front_data;
		front_data = front->get_data();
		if (queue_size == 1) {
			front = nullptr;
			back = nullptr;
			temp = nullptr;
			queue_size = 0;
			return front_data;
		}
		temp = front;
		front = front->get_next();
		temp->clr_next();

		temp = nullptr;
		queue_size--;
		return front_data;
	};

	/*
	 * func returns value of first queue element
	 */
	T getTop() {
		if (queue_size == 0) {
			throw  std::out_of_range("The queue is empty");
		}
		return front->get_data();
	}

	/*
	 * func returns queue size
	 */
	size_t get_size() {
		return queue_size;
	}

};


