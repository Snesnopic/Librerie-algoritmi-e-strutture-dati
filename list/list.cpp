#include "../vector/vector.hpp"
namespace lasd
{

/* ************************************************************************** */
	//Node methods
	//Node Data copy constructor
	template<typename Data>
	List<Data>::Node::Node(const Data& d) : dato(d){}


	//Node Data move constructor
	template<typename Data>
	List<Data>::Node::Node(Data&& d) noexcept
	{
		std::swap(dato, d);
	}

	//Node Node copy constructor
	template<typename Data>
	List<Data>::Node::Node(const Node& n) : dato(n.dato), next(n.next){}

	//Node Node move constructor
	template<typename Data>
	List<Data>::Node::Node(Node&& n) noexcept
	{
		std::swap(dato, n.dato);
		std::swap(next, n.next);
	}

	//Node destructor
	template<typename Data>
	List<Data>::Node::~Node()
	{
		delete next;
	}

	//Node operators
	//Equal comparison
	template<typename Data>
	bool List<Data>::Node::operator==(const Node& n) const noexcept
	{
		if (dato == n.dato)                              //se i dati sono uguali...
		{
			if (next == nullptr && n.next == nullptr)    //e entrambi non hanno un prossimo...
			{
				return true;
			}
			if (next != nullptr && n.next != nullptr)    //o hanno un prossimo...
			{
				if (*next == *n.next)                    //ed è lo stesso...
					return true;
			}
		}
		return false;
	}

	//Not equal comparison
	template<typename Data>
	bool List<Data>::Node::operator!=(const Node& n) const noexcept
	{
		return !(*this == n);
	}

	//List functions
	//Destructor
	template<typename Data>
	List<Data>::~List()
	{
		delete head;
	}

	//LinearContainer constructor
	template<typename Data>
	List<Data>::List(const LinearContainer<Data>& lc)
	{
		if (!lc.Empty())
		{
			head = new Node(lc[0]);
			Node *tmp = head;
			for (std::size_t i = 1; i < lc.Size(); ++i)
			{
				tmp->next = new Node(lc[i]);
				tmp = tmp->next;
			}
		}
		size = lc.Size();
	}

	//Copy constructor
	template<typename Data>
	List<Data>::List(const List& l)
	{
		size = l.size;
		if (l.head != nullptr)
		{
			head = new Node(l.head->dato);
			Node *tmp1 = head;
			Node *tmp2 = l.head->next;
			while (tmp2 != nullptr)
			{
				tmp1->next = new Node(tmp2->dato);
				tmp1 = tmp1->next;
				tmp2 = tmp2->next;
			}
			tmp1->next = nullptr;
		}

	}

	//Move constructor
	template<typename Data>
	List<Data>::List(List&& l) noexcept
	{
		if (l.head != nullptr)
		{
			std::swap(head, l.head);
			std::swap(size, l.size);
		}
	}

	//Clear
	template<typename Data>
	void List<Data>::Clear()
	{
		delete head;
		head = nullptr;
		size = 0;
	}

	//Front
	template<typename Data>
	Data& List<Data>::Front() const
	{
		if (size == 0)
			throw std::length_error("Index out of bounds!");
		return head->dato;
	}

//Back
	template<typename Data>
	Data& List<Data>::Back() const
	{
		if (size == 0)
			throw std::length_error("Index out of bounds!");
		return operator[](size - 1);
	}

	template<typename Data>
	bool List<Data>::Insert(const Data& d) // Copy of the value
	{
		if (FoldableContainer<Data>::Exists(d))
			return false;
		InsertAtFront(d);
		return true;
	}

	template<typename Data>
	bool List<Data>::Insert(Data&& d) noexcept // Move of the value
	{
		if (FoldableContainer<Data>::Exists(d))
			return false;
		InsertAtFront(std::move(d));
		return true;
	}

	template<typename Data>
	bool List<Data>::Remove(const Data& d) // Override DictionaryContainer member
	{
		Node *temp = head;
		Node *prev = nullptr;
		if (temp != nullptr && temp->dato == d)
		{
			head = temp->next; // Changed head
			temp->next = nullptr;
			delete temp;            // free old head
			size--;
			return true;
		}
		while (temp != nullptr && temp->dato != d)
		{
			prev = temp;
			temp = temp->next;
		}
		if (temp == nullptr)
			return false;
		prev->next = temp->next;
		temp->next = nullptr;
		delete temp;
		size--;
		return true;
	}

//Copy assignment
	template<typename Data>
	List<Data>& List<Data>::operator=(const List& l)
	{
		if (this != &l)
		{
			if (l.head != nullptr)
			{
				Clear();
				head = new Node(l.head->dato);
				Node *tmp1 = head;
				Node *tmp2 = l.head->next;
				while (tmp2 != nullptr)
				{
					tmp1->next = new Node(tmp2->dato);
					tmp1 = tmp1->next;
					tmp2 = tmp2->next;
				}
				tmp1->next = nullptr;
			}
			size = l.size;
		}
		return *this;
	}

//Move assignment
	template<typename Data>
	List<Data>& List<Data>::operator=(List&& l) noexcept
	{
		if (this != &l)
		{
			std::swap(size, l.size);
			std::swap(head, l.head);
		}
		return *this;
	}

//Random operator
	template<typename Data>
	Data& List<Data>::operator[](const std::size_t index) const
	{
		if (size == 0 || index >= size)
			throw std::out_of_range("Index out of bounds!");
		Node *tmp = head;
		for (std::size_t i = 0; i < index; ++i)
		{
			tmp = tmp->next;
		}
		return tmp->dato;
	}

//Equal comparison operator
	template<typename Data>
	bool List<Data>::operator==(const List& l) const noexcept
	{
		if (size != l.size)
			return false;
		Node *tmp = head;
		Node *tmp2 = l.head;
		while (tmp != nullptr)
		{
			if (tmp->dato != tmp2->dato)
				return false;
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
		return true;
	}

//Not equal comparison operator
	template<typename Data>
	bool List<Data>::operator!=(const List& l) const noexcept
	{
		return !(*this == l);
	}

//Insert At Front copy
	template<typename Data>
	void List<Data>::InsertAtFront(const Data& d) noexcept
	{
		Node *n = new Node(d);
		n->next = head;
		head = n;
		size++;
	}

//Insert At Front move
	template<typename Data>
	void List<Data>::InsertAtFront(Data&& d) noexcept
	{
		Node *n = new Node(std::move(d));
		n->next = head;
		head = n;
		size++;
	}

//Remove From Front
	template<typename Data>
	void List<Data>::RemoveFromFront()
	{
		if (size == 0)
			throw std::length_error("Lenght error!");
		Node *tmp = head;
		head = head->next;
		tmp->next = nullptr;
		delete tmp;
		size--;
	}

//Front And Remove (rimuovi un elemento e restituiscilo)
	template<typename Data>
	Data& List<Data>::FrontNRemove()
	{
		if (size == 0)
			throw std::length_error("Lenght error!");
		Data& ref = *(new Data(head->dato));
		RemoveFromFront();
		return ref;
	}

//Insert At Back copy
	template<typename Data>
	void List<Data>::InsertAtBack(const Data& d) noexcept
	{
		Node *n = new Node(d);
		n->next = nullptr;
		if (head == nullptr)
		{
			head = n;
		}
		else
		{
			Node *tmp = head;
			while (tmp->next != nullptr)
				tmp = tmp->next;
			tmp->next = n;
		}
		size++;
	}

//Insert At Back move
	template<typename Data>
	void List<Data>::InsertAtBack(Data&& d) noexcept
	{
		Node *n = new Node(std::move(d));
		n->next = nullptr;
		if (head == nullptr)
			head = n;
		else
		{
			Node *tmp = head;
			while (tmp->next != nullptr)
				tmp = tmp->next;
			tmp->next = n;
		}
		size++;
	}

	template<typename Data>
	std::size_t List<Data>::GetIndexOf(Data& d) const
	{
		Node *tmp = head;
		for (std::size_t i = 0; i < size; ++i)
		{
			if (d == tmp->dato)
				return i;
			tmp = tmp->next;
		}
		throw std::exception(d + " doesn't exist in the container!");
	}

	template<typename Data>
	List<Data>::operator std::vector<Data>() const
	{
		Vector<Data> v(*this);
		std::vector<Data> newv(v);
		return newv;
	}

	template<typename Data>
	void List<Data>::Sort() noexcept
	{
		Vector<Data> v(*this);
		v.Sort();
		List<Data> l(v);
		*this = std::move(l);
	}

	template<typename Data>
	void List<Data>::SortAscending() noexcept
	{
		Sort();
	}

	template<typename Data>
	void List<Data>::SortDescending() noexcept
	{
		Vector<Data> v(*this);
		v.SortDescending();
		List<Data> l(v);
		*this = std::move(l);
	}

//Map functions
//Map
	template<typename Data>
	void List<Data>::Map(MapFunctor f, void *par)
	{
		MapPreOrder(f, par, head);
	}

//MapPreOrder
	template<typename Data>
	void List<Data>::MapPreOrder(MapFunctor f, void *par)
	{
		if (head != nullptr)
			MapPreOrder(f, par, head);
	}

//MapPreOrder ricorsiva
	template<typename Data>
	void List<Data>::MapPreOrder(MapFunctor f, void *par, Node *n)
	{
		while (n != nullptr)
		{
			f(n->dato, par);
			n = n->next;
		}
	}

//MapPostOrder
	template<typename Data>
	void List<Data>::MapPostOrder(MapFunctor f, void *par)
	{
		if (head != nullptr)
			MapPostOrder(f, par, head);
	}

//MapPostOrder ricorsiva
	template<typename Data>
	void List<Data>::MapPostOrder(MapFunctor f, void *par, Node *n)
	{
		if (n->next != nullptr)
			MapPostOrder(f, par, n->next);
		f(n->dato, par);
	}

//Fold functions
//Fold
	template<typename Data>
	void List<Data>::Fold(FoldFunctor f, const void *par, void *acc) const
	{
		FoldPreOrder(f, par, acc, head);
	}

//FoldPreOrder
	template<typename Data>
	void List<Data>::FoldPreOrder(FoldFunctor f, const void *par, void *acc) const
	{
		if (head != nullptr)
			FoldPreOrder(f, par, acc, head);
	}

//FoldPreOrder ricorsiva
	template<typename Data>
	void List<Data>::FoldPreOrder(FoldFunctor f, const void *par, void *acc, Node *n) const
	{
		while (n != nullptr)
		{
			f(n->dato, par, acc);
			n = n->next;
		}
	}

//FoldPostOrder
	template<typename Data>
	void List<Data>::FoldPostOrder(FoldFunctor f, const void *par, void *acc) const
	{
		if (head != nullptr)
			FoldPostOrder(f, par, acc, head);
	}

//FoldPostOrder ricorsiva
	template<typename Data>
	void List<Data>::FoldPostOrder(FoldFunctor f, const void *par, void *acc, Node *n) const
	{
		if (n->next != nullptr)
			FoldPostOrder(f, par, acc, n->next);
		f(n->dato, par, acc);
	}
/* ************************************************************************** */
}
