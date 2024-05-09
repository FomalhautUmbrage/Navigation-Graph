#pragma once

template<typename T>
class PriorityQueue
{
private:
	class Node
	{
	public:
		T data;
		Node* next;
		Node(T d) {
			next = nullptr;
			data = d;
		}
	};
private:
	Node* head;

public:
	PriorityQueue()
	{
		head = nullptr;
	}

	~PriorityQueue()
	{
		Node* t = head;
		while (head != nullptr)
		{
			t = head;
			head = head->next;
			delete t;
		}
	}

	void push(T data)
	{
		Node* n = new Node(data);
		if (head == nullptr)
		{
			head = n;
		}
		else
		{
			if (head->data < data)
			{
				n->next = head;
				head = n;
			}
			else
			{
				Node* t = head, * up = head;
				while (t != nullptr && data < t->data)
				{
					up = t;
					t = t->next;
				}
				n->next = t;
				if (t == up) {
					head = n;
				}
				else {
					up->next = n;
				}
				
				
			}
		}
	}

	T top()
	{
		T t;
		if (head != nullptr)
			return head->data;
		else
			return t;
	}

	void pop()
	{
		if (head != nullptr) {
			Node* t = head;
			head = head->next;
			delete t;
		}
	}

	bool empty()
	{
		return head == nullptr;
	}


};

