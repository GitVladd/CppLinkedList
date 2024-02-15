#pragma once

template <typename T>
class DList {
	Node* front_;
	Node* back_;
public:

	struct Node {
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr)
		{
			data_ = data;
			next_ = next;
			prev_ = prev;
		};
	};

	class const_iterator {
		friend class DList;
	protected:
		//const DList* list_;
		Node* curr_;
		const_iterator(Node* curr) //, const DList* list
		{
			curr_ = curr;
			//list_ = list;
		}
	public:
		const_iterator()
		{
			//list_ = nullptr;
			curr_ = nullptr;
		}
		const_iterator operator++() const
		{
			curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}
		const_iterator& operator--() const
		{
			if (curr_)
			{
				curr_ = curr_->prev_;
			}
			/*else
			{
				if (list_)
				{
					curr_ = list->last_
				}
			}*/
			return this;
		}
		const_iterator operator--(int)
		{
			const_iterator old = *this;
			if (curr_)
			{
				curr_ = curr_->prev_;
			}
			return old;
		}

		const T& operator*() const
		{
			return curr_->data_;
		}
		bool operator==(const_iterator it2) const
		{
			bool toReturn = false;
			if (curr_ == it2.curr_) //list_ == it2.list_ && 
			{
				toReturn = true;
			}

			return toReturn;
		}
		bool operator!=(const_iterator it2) const
		{
			bool toReturn = false;
			if (curr_ != it2.curr_) //list_ != it2.list_ && 
			{
				toReturn = true;
			}

			return toReturn;
		}
	};

	class iterator : public const_iterator {
		friend class DList;

		iterator(Node* curr) : const_iterator(curr) {} //iterator(Node* curr, DList* list) : const_iterator(curr, list) {}

	public:
		iterator() :const_iterator() {}
		iterator operator++()
		{
			this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int)
		{
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}
		iterator operator--()
		{
			if (this->curr_)
			{
				this->curr_ = this->curr_->prev_;
			}
			/*else
			{
				if (this->list_)
				{
					this->curr_ = this->list->last_
				}
			}*/
			return this;
		}
		iterator operator--(int)
		{
			Node* old = *this;
			if (this->curr_)
			{
				this->curr_ = this->curr_->prev_;
			}
			/*else
			{
				if (this->list_)
				{
					this->curr_ = this->list->last_;
				}
			}*/
			return old;
		}
		const T& operator*()const
		{
			return curr_->data_;
		};
		T& operator*()
		{
			return curr_->data_;
		}
		bool operator==(iterator it2) const
		{
			bool toReturn = false;
			if (curr_ == it2.curr_) //list_ == it2.list_ && 
			{
				toReturn = true;
			}

			return toReturn;
		}
		bool operator!=(iterator it2) const
		{
			bool toReturn = false;
			if (curr_ != it2.curr_) //list_ != it2.list_ && 
			{
				toReturn = true;
			}

			return toReturn;
		}

	};

	DList()
	{
		front_ = nullptr;
		back_ = nullptr;
	}
	iterator insert(iterator it, const T& data)
	{
		Node newNode(data, it->curr_, it->curr_->prev_);
		if (it->curr_->prev_ != nullptr)
		{
			it->curr_->prev_->next_ = &newNode;
		}

		it->curr_->prev_ = &newNode;

		return iterator(newNode);
	}
	iterator begin()
	{
		return iterator(front_);
	}
	iterator end()
	{
		return iterator(); //or iterator(Node( NULL, nullptr, back_))
	}
	const_iterator cbegin() const
	{
		return const_iterator(front_);
	}
	const_iterator cend() const
	{
		return const_iterator();
	}
	iterator erase(iterator it)
	{
		iterator toReturn(it->curr_->next_);

		it->curr_->next_->prev_ = it->curr_->prev_;
		it->curr_->prev_->next_ = it->curr_->next_;
		delete it->curr_;

		return toReturn;
	}
	/////////////////////

	void sort(iterator first, iterator last)
	{
		if (first != last)
		{
			for (DList<T>::iterator it = first; it != --last; it++)
			{
				for (DList<T>::iterator itNext = ++it; itNext != last; itNext++)
				{
					if (*it > *itNext)
					{
						itNext->curr_->next_->prev_ = it->curr_;
						it->curr_->prev_->next_ = itNext->curr_;

						itNext->curr_->prev_ = it->curr_->prev_;

						it->curr_->next_ = itNext->curr_->next_;

						itNext->curr_->next_ = it->curr_; ///////

						it->curr_->prev_ = itNext->curr_;

					}
				}

			}
		}

	}

	iterator search(const T& data)
	{
		for (DList<T>::iterator it(front_); it != this->end(); ++it)
		{
			if (*it == data)
			{
				return it;
			}
		}

		return this->end();
	}
	const_iterator search(const T& data) const
	{
		for (DList<T>::const_iterator it(this->front_); it != this->cend(); ++it)
		{
			if (*it == data)
			{
				return it;
			}
		}

		return this->end();
	}
	bool empty() const
	{
		if (this->front_ == nullptr)
			return true;
		return false;
	}
	int size() const
	{
		int toReturn = 0;
		if (front_ != nullptr)
		{
			DList<T>::const_iterator it(front_);
			while (it != this->cend();)
			{
				++toReturn;
				++it;
			}
		}

		return toReturn;
	}
	~DList()
	{
		if (front_ != nullptr)
		{
			while (front_->next_ != nullptr)
			{
				Node* p = front_->next_;
				delete front_;
				front_ = p;
			}
			delete front_;
		}
	}
	DList(const DList& other)
	{
		this->front_ = other->front_;
		this->back_ = other->back_;
	}
	DList& operator=(const DList& other)
	{

		//deallocate current DList
		if (front_ != nullptr)
		{
			while (front_->next_ != nullptr)
			{
				Node* p = front_->next_;
				delete front_;
				front_ = p;
			}
			delete front_;
		}

		//new front and back
		this->front_ = other->front_;
		this->back_ = other->back_;
	}
	DList(DList&& other)
	{
		this->front_ = other->front_;
		this->back_ = other->back_;

		other->front_ = nullptr;
		other->back_ = nullptr;
	}
	DList& operator=(DList&& other)
	{
		this->front_ = other->front_;
		this->back_ = other->back_;

		other->front_ = nullptr;
		other->back_ = nullptr;
	}


};

