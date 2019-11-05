#pragma once


namespace data_structures {
	template <typename T>
	class Element {
	private:
		Element<T>* next;
		T dana;
	public:
		
		Element(T dana, Element<T>* next = nullptr) : next(next), dana(dana) {}

		Element<T>* getNext() const { return next; }
		void setNext(Element<T>* next) { this->next = next; }
		T& operator*() { return dana; }
	};

	template <typename T>
	class List {
	private:
		Element<T>* _head;
		Element<T>* _tail;
		int _count;
	public:
		List() : _head(nullptr), _tail(nullptr), _count(0) {}
		Element<T>* head() const {
			return _head;
		}
		Element<T>* tail() const { 
			return _tail;
		}
		int count() const { 
			return _count;
		}
		
		void add(const T& nowaDana) {
			Element<T>* nowyElement = new Element<T>(nowaDana);
			if (_head == nullptr) {
				_head = nowyElement;
				_tail = nowyElement;
			}
			else {
				_tail->setNext(nowyElement);
				_tail = nowyElement;
			}
			++_count;
		}

		List<T>& operator=(const List<T>& ref) {
			if (this == &ref)
				return;
			while (_head != nullptr) {
				Element<T>* pomocniczy = _head->getNext();
				delete _head;
				_head = pomocniczy;
			}
			_tail = nullptr;
			_count = 0;
			Element<T>* temp;
			temp = ref._head;
			while (temp != nullptr) {
				this->add(**temp);
				temp = temp->getNext;
			}
		}

		List(const List<T>& oryginal) {
			Element<T>* oryginalNext;
			oryginalNext = oryginal._head;
			while (oryginalNext != nullptr) {
				this->add(**oryginalNext);
				oryginalNext = oryginalNext->getNext();
			}
		}

		~List() {
			while (_head != nullptr) {
				Element<T>* tempHead = _head->getNext();
				delete _head;
				_head = tempHead;
				--_count;
			}
			_tail = nullptr;
			
		};
	};
}