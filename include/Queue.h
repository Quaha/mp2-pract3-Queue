#pragma once

template <typename QueueType> class Queue {
private:

	QueueType* data = nullptr;
	int front_ptr = 0;
	int end_ptr = 0;

	int sz = 0;
	int capacity = 1;

	void destruct(Queue* queue) {
		delete[] queue->data;
	}

	void construct(Queue* queue) {
		queue->data = new QueueType[1]();
		front_ptr = 0;
		end_ptr = 0;
		sz = 0;
		capacity = 1;
	}

public:

	Queue() {
		construct(this);
	}

	~Queue() {
		destruct(this);
	}

	Queue(const Queue& other) {

		this->front_ptr = other.front_ptr;
		this->end_ptr = other.end_ptr;

		this->sz = other.sz;
		this->capacity = other.capacity;

		this->data = new QueueType[capacity]();
		if (front_ptr <= end_ptr) {
			for (int i = front_ptr; i < end_ptr; ++i) {
				this->data[i] = other.data[i];
			}
		}
		else {
			for (int i = front_ptr; i < capacity; ++i) {
				this->data[i] = other.data[i];
			}
			for (int i = 0; i < end_ptr; ++i) {
				this->data[i] = other.data[i];
			}
		}
	}

	Queue(Queue&& other) {
		this->front_ptr = other.front_ptr;
		this->end_ptr = other.end_ptr;

		this->sz = other.sz;
		this->capacity = other.capacity;

		this->data = other.data;

		construct(&other);
	}

	Queue& operator=(const Queue& other) {
		if (this == &other) return *this;

		destruct(this);

		this->front_ptr = other.front_ptr;
		this->end_ptr = other.end_ptr;

		this->sz = other.sz;
		this->capacity = other.capacity;

		this->data = new QueueType[capacity]();
		if (front_ptr <= end_ptr) {
			for (int i = front_ptr; i < end_ptr; ++i) {
				this->data[i] = other.data[i];
			}
		}
		else {
			for (int i = front_ptr; i < capacity; ++i) {
				this->data[i] = other.data[i];
			}
			for (int i = 0; i < end_ptr; ++i) {
				this->data[i] = other.data[i];
			}
		}

		return *this;
	}

	Queue& operator=(Queue&& other) {
		if (this == &other) return *this;

		destruct(this);

		this->front_ptr = other.front_ptr;
		this->end_ptr = other.end_ptr;

		this->sz = other.sz;
		this->capacity = other.capacity;

		this->data = other.data;

		construct(&other);

		return *this;
	}

	void push(const QueueType& value) {
		data[end_ptr] = value;
		++sz;

		if (sz == capacity) {
			capacity *= 2;
			QueueType* new_data = new QueueType[capacity]();
			
			for (int i = 0, p = front_ptr; i < sz; i++, front_ptr++, front_ptr %= sz) {
				new_data[i] = data[p];
			}

			front_ptr = 0;
			end_ptr = sz;

			delete[] data;
			data = new_data;
		}
	}

	void pop() {
		if (empty()) {
			throw std::out_of_range("It is forbidden to use the method .pop_back() on an empty queue!");
		}
		front_ptr++;
		if (front_ptr == capacity) {
			front_ptr = 0;
		}
	}

	QueueType front() const {
		if (empty()) {
			throw std::out_of_range("It is forbidden to use the method .back() on an empty queue!");
		}
		return data[front_ptr];
	}

	size_t size() const {
		return sz;
	}

	bool empty() const {
		return sz == 0;
	}

	void clear() {
		destruct(this);
		construct(this);
	}
};