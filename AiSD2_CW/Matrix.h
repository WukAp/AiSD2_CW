#pragma once
#include "List.h"

//List<List<T>>

template<class T>
class Matrix {
	class Node {
	private:
		List<T> data;
		Node* next, * prev;
	public:

		Node(List<T> data) {
			this->data = data;
			next = nullptr;
			prev = nullptr;
		}
		~Node() {
			next = nullptr;
			prev = nullptr;
		}

		Node() : next(nullptr), prev(nullptr) {};

		void set_data(List<T>& data) {
			this->data = data;
		}

		List<T>& get_data() {
			return data;
		}

		Node* get_next() {
			return next;
		}

		Node* get_prev() {
			return prev;
		}

		void set_next(Node* temp) {
			next = temp;
		}

		void set_prev(Node* temp) {
			prev = temp;
		}
	};

	Node* head, * tail;

	Node* get_node(size_t index)
	{
		if (isEmpty() || (index > get_size() - 1))
		{
			throw out_of_range("Invalid argument");
		}
		else if (index == get_size() - 1)
			return tail;
		else if (index == 0)
			return head;
		else
		{
			Node* temp = head;
			while ((temp) && (index--))
			{
				temp = temp->get_next();
			}
			return temp;
		}
	}
public:
	Matrix() : head(nullptr), tail(nullptr) {}

	Matrix(const Matrix<T>& list) {
		head = nullptr;
		tail = nullptr;
		Node* temp = list.head;
		while (temp) {
			push_back(temp->get_data());
			temp = temp->get_next();
		}
	}

	~Matrix()
	{
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
		head = nullptr;
	}

	void set(size_t index, List<T> data)
	{
		Node* temp;
		temp = get_node(index);
		temp->set_data(data);
	}

	void push_back(List<T>& data)
	{
		Node* temp = new Node;
		temp->set_data(data);

		if (head)
		{
			temp->set_prev(tail);
			tail->set_next(temp);
			tail = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}

	void push_front(List<T> data)
	{
		Node* temp = new Node;
		temp->set_data(data);
		if (head)
		{
			temp->set_next(head);
			head->set_prev(temp);
			head = temp;
		}
		else
		{
			head = temp;
			tail = head;
		}
	}

	void push_back(Matrix<bool> scnd_list)
	{
		Node* temp = scnd_list.head;
		size_t size = scnd_list.get_size();
		while ((temp) && (size--))
		{
			push_back(temp->get_data());
			temp = temp->get_next();
		}
	}

	void push_front(Matrix& scnd_list)
	{
		Node* temp = scnd_list.tail;
		size_t n = scnd_list.get_size();
		while ((temp) && (n--))
		{
			push_front(temp->get_data());
			temp = temp->get_prev();
		}
	}

	void insert(size_t index, List<T> data)
	{
		Node* temp;
		temp = get_node(index);
		if (temp == head)
			push_front(data);
		else
		{
			Node* newel = new Node;
			newel->set_data(data);
			temp->get_prev()->set_next(newel);
			newel->set_prev(temp->get_prev());
			newel->set_next(temp);
			temp->set_prev(newel);
		}
	}

	void pop_back()
	{
		if (head != tail)
		{
			Node* temp = tail;
			tail = tail->get_prev();
			tail->set_next(nullptr);
			delete temp;
		}

		else if (!isEmpty())
		{
			Node* temp = tail;
			tail = head = nullptr;
			delete temp;
		}
		else
			throw out_of_range("The list is empty");
	}

	void pop_front()
	{
		if (head != tail)
		{
			Node* temp = head;
			head = head->get_next();
			head->set_prev(nullptr);
			delete temp;
		}
		else if (!isEmpty())
		{
			Node* temp = head;
			head = tail = nullptr;
			delete temp;
		}
		else
			throw out_of_range("The list is empty");
	}

	void remove(List<T> data) {
		Node* temp = head;
		while (temp && temp->get_data() != data)
			temp = temp->get_next();
		if (!temp)
			throw out_of_range("Invalid argument");
		if (temp == head)
			pop_front();
		else if (temp == tail)
			pop_back();
		else
		{
			temp->get_prev()->set_next(temp->get_next());
			temp->get_next()->set_prev(temp->get_prev());
			delete temp;
		}
	}

	List<T>& at(size_t index) {
		Node* temp;
		temp = get_node(index);
		return temp->get_data();
	}

	void remove(size_t index) {
		Node* temp;
		temp = get_node(index);
		if (temp == head)
			pop_front();
		else if (temp == tail)
			pop_back();
		else
		{
			temp->get_prev()->set_next(temp->get_next());
			temp->get_next()->set_prev(temp->get_prev());
			delete temp;
		}
	}

	size_t get_size() {
		Node* temp = head;
		size_t length = 0;
		while (temp)
		{
			length++;
			temp = temp->get_next();
		}
		return length;
	}

	void print()	{
		Node* temp = head;
		while (temp) {
			temp->get_data().print();
			temp = temp->get_next();
		}
			std::cout << std::endl;
	}

	void clear() {
		while (head)
		{
			tail = head->get_next();
			delete head;
			head = tail;
		}
	}

	bool isEmpty() {
		if (!head)
			return true;
		else
			return false;
	}
};
