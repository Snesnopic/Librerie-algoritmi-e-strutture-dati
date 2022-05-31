namespace lasd
{

/* ************************************************************************** */
	template<typename Data>
	bool BinaryTree<Data>::Node::operator==(const Node& n) const noexcept
	{
		if (dato != n.dato)
			return false;
		if (HasLeftChild() && n.HasLeftChild())
		{
			if (LeftChild().operator!=(n.LeftChild()))
			{
				return false;
			}
		}
		if (HasRightChild() && n.HasRightChild())
		{
			if (RightChild().operator!=(n.RightChild()))
				return false;
		}
		return true;
	}

	template<typename Data>
	bool BinaryTree<Data>::Node::operator!=(const Node& n) const noexcept
	{
		return !(*this == n);
	}

	template<typename Data>
	bool BinaryTree<Data>::operator==(const BinaryTree& bt) const noexcept
	{
		if (size == 0 && 0 == bt.size)
			return true;
		if (size == bt.size)
			return Root() == bt.Root();
		return false;
	}

	template<typename Data>
	bool BinaryTree<Data>::operator!=(const BinaryTree& bt) const noexcept
	{
		return !(*this == bt);
	}

	template<typename Data>
	void BinaryTree<Data>::Map(MapFunctor f, void *par)  // Override MappableContainer member
	{
		if (size != 0)
			MapPreOrder(f, par, &Root());
	}

	template<typename Data>
	void BinaryTree<Data>::Fold(FoldFunctor f, const void *par, void *acc) const  // Override FoldableContainer member
	{
		if (size != 0)
			FoldPreOrder(f, par, acc, &Root());
	}

	template<typename Data>
	void BinaryTree<Data>::MapPreOrder(MapFunctor f, void *par)  // Override PreOrderMappableContainer member
	{
		if (size != 0)
			MapPreOrder(f, par, &Root());
	}

	template<typename Data>
	void BinaryTree<Data>::FoldPreOrder(FoldFunctor f, const void *par, void *acc) const  // Override PreOrderFoldableContainer member
	{
		if (size != 0)
			FoldPreOrder(f, par, acc, &Root());
	}

	template<typename Data>
	void BinaryTree<Data>::MapPostOrder(MapFunctor f, void *par) // Override PostOrderMappableContainer member
	{
		if (size != 0)
			MapPostOrder(f, par, &Root());
	}

	template<typename Data>
	void BinaryTree<Data>::FoldPostOrder(FoldFunctor f, const void *par, void *acc) const // Override PostOrderFoldableContainer member
	{
		if (size != 0)
			FoldPostOrder(f, par, acc, &Root());
	}

	template<typename Data>
	void BinaryTree<Data>::MapInOrder(MapFunctor f, void *par) // Override InOrderMappableContainer member
	{
		if (size != 0)
			MapInOrder(f, par, &Root());
	}

	template<typename Data>
	void BinaryTree<Data>::FoldInOrder(FoldFunctor f, const void *par, void *acc) const // Override InOrderFoldableContainer member
	{
		if (size != 0)
			FoldInOrder(f, par, acc, &Root());
	}

	template<typename Data>
	void BinaryTree<Data>::MapBreadth(MapFunctor f, void *par) // Override BreadthMappableContainer member
	{
		if (size != 0)
		{
			QueueLst<Node *> queue{};
			queue.Enqueue(&Root());
			Node *n;
			while (!queue.Empty())
			{
				n = queue.Head();
				f(n->dato, par);
				queue.Dequeue();
				if (n->HasLeftChild())
					queue.Enqueue(&n->LeftChild());
				if (n->HasRightChild())
					queue.Enqueue(&n->RightChild());
			}
		}
	}

	template<typename Data>
	void BinaryTree<Data>::FoldBreadth(FoldFunctor f, const void *par, void *acc) const  // Override BreadthFoldableContainer member
	{
		if (size != 0)
		{
			QueueLst<Node *> queue{};
			queue.Enqueue(&Root());
			Node *n;
			while (!queue.Empty())
			{
				n = queue.Head();
				f(n->dato, par, acc);
				queue.Dequeue();
				if (n->HasLeftChild())
					queue.Enqueue(&n->LeftChild());
				if (n->HasRightChild())
					queue.Enqueue(&n->RightChild());
			}
		}
	}

	template<typename Data>
	void BinaryTree<Data>::MapPreOrder(MapFunctor f, void *par, Node *n) // Accessory function executing from one node of the tree
	{
		f(n->dato, par);
		if (n->HasLeftChild())
			MapPreOrder(f, par, &n->LeftChild());
		if (n->HasRightChild())
			MapPreOrder(f, par, &n->RightChild());
	}

	template<typename Data>
	void BinaryTree<Data>::FoldPreOrder(FoldFunctor f, const void *par, void *acc, Node *n) const // Accessory function executing from one node of the tree
	{
		f(n->dato, par, acc);
		if (n->HasLeftChild())
			FoldPreOrder(f, par, acc, &n->LeftChild());
		if (n->HasRightChild())
			FoldPreOrder(f, par, acc, &n->RightChild());
	}

	template<typename Data>
	void BinaryTree<Data>::MapPostOrder(MapFunctor f, void *par, Node *n) // Accessory function executing from one node of the tree
	{
		if (n->HasLeftChild())
			MapPostOrder(f, par, &n->LeftChild());
		if (n->HasRightChild())
			MapPostOrder(f, par, &n->RightChild());
		f(n->dato, par);
	}

	template<typename Data>
	void BinaryTree<Data>::FoldPostOrder(FoldFunctor f, const void *par, void *acc, Node *n) const // Accessory function executing from one node of the tree
	{
		if (n->HasLeftChild())
			FoldPostOrder(f, par, acc, &n->LeftChild());
		if (n->HasRightChild())
			FoldPostOrder(f, par, acc, &n->RightChild());
		f(n->dato, par, acc);
	}

	template<typename Data>
	void BinaryTree<Data>::MapInOrder(MapFunctor f, void *par, Node *n) // Accessory function executing from one node of the tree
	{
		if (n->HasLeftChild())
			MapInOrder(f, par, &n->LeftChild());
		f(n->dato, par);
		if (n->HasRightChild())
			MapInOrder(f, par, &n->RightChild());
	}

	template<typename Data>
	void BinaryTree<Data>::FoldInOrder(FoldFunctor f, const void *par, void *acc, Node *n) const // Accessory function executing from one node of the tree
	{
		if (n->HasLeftChild())
			FoldInOrder(f, par, acc, &n->LeftChild());
		f(n->dato, par, acc);
		if (n->HasRightChild())
			FoldInOrder(f, par, acc, &n->RightChild());
	}

	/* ************************************************************************ */

	// Copy constructor
	template<typename Data>
	BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator& poi)
	{
		curr = poi.curr;
		stack = poi.stack;
		treePtr = poi.treePtr;
	}

	// Move constructor
	template<typename Data>
	BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator&& poi) noexcept
	{
		std::swap(curr, poi.curr);
		std::swap(stack, poi.stack);
		std::swap(treePtr, poi.treePtr);
	}

	/* ************************************************************************ */

	// Destructor
	template<typename Data>
	BTPreOrderIterator<Data>::~BTPreOrderIterator()
	{
		stack.Clear();
	}

	/* ************************************************************************ */

	// Copy assignment
	template<typename Data>
	BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator& poi)
	{
		if (this != &poi)
		{
			curr = poi.curr;
			stack = poi.stack;
			treePtr = poi.treePtr;
		}
		return *this;
	}

	// Move assignment
	template<typename Data>
	BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator&& poi) noexcept
	{
		if (this != &poi)
		{
			std::swap(curr, poi.curr);
			std::swap(stack, poi.stack);
			std::swap(treePtr, poi.treePtr);
		}
		return *this;
	}

	/* ************************************************************************ */

	// Comparison operators
	template<typename Data>
	bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator& poi) const noexcept
	{
		return curr == poi.curr;
	}

	template<typename Data>
	bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator& poi) const noexcept
	{
		return !(*this == poi);
	}

	/* ************************************************************************ */

	// Specific member functions (inherited from Iterator)
	template<typename Data>
	Data& BTPreOrderIterator<Data>::operator*() const  // (throw std::out_of_range when terminated)
	{
		if (Terminated())
			throw std::out_of_range("Out of range!");
		return curr->dato;
	}

	template<typename Data>
	bool BTPreOrderIterator<Data>::Terminated() const noexcept  // (should not throw exceptions)
	{
		return curr == nullptr;
	}

	template<typename Data>
	BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt) // An iterator over a given binary tree
	{
		if (!bt.Empty())
			curr = &bt.Root();
		treePtr = &bt;
	}

	template<typename Data>
	BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++()  // (throw std::out_of_range when terminated)
	{
		if (Terminated())
			throw std::out_of_range("Out of range!");
		if (curr->HasRightChild())
			stack.Push(&curr->RightChild());
		if (curr->HasLeftChild())
			curr = &curr->LeftChild();
		else
		{
			if (!stack.Empty())
				curr = stack.TopNPop();
			else
				curr = nullptr;
		}
		return *this;
	}

	template<typename Data>
	void BTPreOrderIterator<Data>::Reset() noexcept  // (should not throw exceptions)
	{
		if (treePtr != nullptr)
			curr = &treePtr->Root();
		stack.Clear();
	}

	/* ************************************************************************ */
	template<typename Data>
	struct BinaryTree<Data>::Node *BTPostOrderIterator<Data>::minLeaf(struct BinaryTree<Data>::Node *n)
	{
		struct BinaryTree<Data>::Node *tmp = n;
		stack.Push(tmp);
		if (tmp->HasLeftChild())
		{
			return minLeaf(&tmp->LeftChild());
		}
		else
		{
			return stack.TopNPop();
		}
	}

	// Copy constructor
	template<typename Data>
	BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& poi)
	{
		curr = poi.curr;
		stack = poi.stack;
		treePtr = poi.treePtr;
	}

	// Move constructor
	template<typename Data>
	BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& poi) noexcept
	{
		std::swap(curr, poi.curr);
		std::swap(stack, poi.stack);
		std::swap(treePtr, poi.treePtr);
	}

	/* ************************************************************************ */

	// Destructor
	template<typename Data>
	BTPostOrderIterator<Data>::~BTPostOrderIterator()
	{
		stack.Clear();
	}

	/* ************************************************************************ */

	// Copy assignment
	template<typename Data>
	BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& poi)
	{
		if (this != &poi)
		{
			curr = poi.curr;
			stack = poi.stack;
			treePtr = poi.treePtr;
		}
		return *this;
	}

	// Move assignment
	template<typename Data>
	BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& poi) noexcept
	{
		if (this != &poi)
		{
			std::swap(curr, poi.curr);
			std::swap(stack, poi.stack);
			std::swap(treePtr, poi.treePtr);
		}
		return *this;
	}

	/* ************************************************************************ */

	// Comparison operators
	template<typename Data>
	bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& poi) const noexcept
	{
		if (curr == poi.curr && stack == poi.stack && treePtr == poi.treePtr)
			return true;
		else
			return false;
	}

	template<typename Data>
	bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& poi) const noexcept
	{
		return !(*this == poi);
	}

	/* ************************************************************************ */

	// Specific member functions (inherited from Iterator)
	template<typename Data>
	Data& BTPostOrderIterator<Data>::operator*() const // (throw std::out_of_range when terminated)
	{
		if (Terminated())
			throw std::out_of_range("Out of range!");
		return curr->dato;
	}

	template<typename Data>
	bool BTPostOrderIterator<Data>::Terminated() const noexcept // (should not throw exceptions)
	{
		return curr == nullptr;
	}

	/* ************************************************************************ */

	// Specific member functions (inherited from ForwardIterator)
	template<typename Data>
	BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt) // An iterator over a given binary tree
	{
		treePtr = &bt;
		if (!bt.Empty())
			curr = minLeaf(&bt.Root());
	}

	template<typename Data>
	BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() // (throw std::out_of_range when terminated)
	{
		if (Terminated())
			throw std::out_of_range("Out of range!");
		if (stack.Empty())
			curr = nullptr;
		else
		{
			if (stack.Top()->HasRightChild() && curr == &(stack.Top()->RightChild()))
				curr = stack.TopNPop();
			else
			{
				if (stack.Top()->HasLeftChild() && curr == &(stack.Top()->LeftChild()))
				{
					if (!stack.Top()->HasRightChild())
						curr = stack.TopNPop();
					else
						curr = minLeaf(&(stack.Top()->RightChild()));
				}
			}
		}
		return *this;
	}

	template<typename Data>
	void BTPostOrderIterator<Data>::Reset() noexcept // (should not throw exceptions)
	{
		stack.Clear();
		if (treePtr != nullptr)
			curr = minLeaf(&treePtr->Root());
	}

	/* ************************************************************************ */


	// Copy constructor
	template<typename Data>
	BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator& ii)
	{
		curr = ii.curr;
		stack = ii.stack;
		treePtr = ii.treePtr;
	}

	// Move constructor
	template<typename Data>
	BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator&& ii) noexcept
	{
		std::swap(curr, ii.curr);
		std::swap(stack, ii.stack);
		std::swap(treePtr, ii.treePtr);
	}

	// Destructor
	template<typename Data>
	BTInOrderIterator<Data>::~BTInOrderIterator()
	{
		stack.Clear();
	}

	// Copy assignment
	template<typename Data>
	BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator& ii)
	{
		if (this != &ii)
		{
			curr = ii.curr;
			stack = ii.stack;
			treePtr = ii.treePtr;
		}
		return *this;
	}

	// Move assignment
	template<typename Data>
	BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator&& ii) noexcept
	{
		if (this != &ii)
		{
			std::swap(curr, ii.curr);
			std::swap(stack, ii.stack);
			std::swap(treePtr, ii.treePtr);
		}
		return *this;
	}

	// Comparison operators
	template<typename Data>
	bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator& ii) const noexcept
	{
		if (curr == ii.curr && stack == ii.stack && treePtr == ii.treePtr)
			return true;
		else
			return false;
	}

	template<typename Data>
	bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator& ii) const noexcept
	{
		return !(*this == ii);
	}

	template<typename Data>
	struct BinaryTree<Data>::Node *BTInOrderIterator<Data>::Min(struct BinaryTree<Data>::Node *n)
	{
		struct BinaryTree<Data>::Node *tmp = n;
		if (tmp->HasLeftChild())
		{
			stack.Push(tmp);
			tmp = Min(&tmp->LeftChild());
		}
		return tmp;
	}

	template<typename Data>
	BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt) // An iterator over a given binary tree
	{
		treePtr = &bt;
		if (!bt.Empty())
			curr = Min(&bt.Root());
	}

	// Specific member functions (inherited from Iterator)
	template<typename Data>
	Data& BTInOrderIterator<Data>::operator*() const // (throw std::out_of_range when terminated)
	{
		if (Terminated())
			throw std::out_of_range("Out of range!");
		return curr->dato;
	}

	template<typename Data>
	bool BTInOrderIterator<Data>::Terminated() const noexcept // (should not throw exceptions)
	{
		return curr == nullptr;
	}

	template<typename Data>
	BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++()  // (throw std::out_of_range when terminated)
	{
		if (Terminated())
			throw std::out_of_range("Out of range!");
		if (curr->HasRightChild())
		{
			if (!stack.Empty() && curr == stack.Top())
				stack.Pop();
			else
				curr = Min(&curr->RightChild());
		}
		else
		{
			if (stack.Empty())
				curr = nullptr;
			else
				curr = stack.TopNPop();
		}
		return *this;
	}

	// Specific member functions (inherited from ResettableIterator)
	template<typename Data>
	void BTInOrderIterator<Data>::Reset() noexcept // (should not throw exceptions)
	{
		stack.Clear();
		if (treePtr != nullptr)
			curr = Min(&treePtr->Root());
	}

/* ************************************************************************ */
	template<typename Data>
	BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt) // An iterator over a given binary tree
	{
		if (!bt.Empty())
			curr = &bt.Root();
		treePtr = &bt;
	}

	// Copy constructor
	template<typename Data>
	BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator& bi)
	{
		treePtr = bi.treePtr;
		curr = bi.curr;
		que = bi.que;
	}

	// Move constructor
	template<typename Data>
	BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator&& bi) noexcept
	{
		std::swap(treePtr, bi.treePtr);
		std::swap(curr, bi.curr);
		std::swap(que, bi.que);
	}

/* ************************************************************************ */

// Destructor
	template<typename Data>
	BTBreadthIterator<Data>::~BTBreadthIterator()
	{
		que.Clear();
	}

/* ************************************************************************ */

// Copy assignment
	template<typename Data>
	BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator& bi)
	{
		if (this != &bi)
		{
			treePtr = bi.treePtr;
			curr = bi.curr;
			que = bi.que;
		}
		return *this;
	}

// Move assignment
	template<typename Data>
	BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator&& bi) noexcept
	{
		if (this != &bi)
		{
			std::swap(treePtr, bi.treePtr);
			std::swap(curr, bi.curr);
			std::swap(que, bi.que);
		}
		return *this;
	}

/* ************************************************************************ */

// Comparison operators
	template<typename Data>
	bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator& bi) const noexcept
	{
		if (treePtr == bi.treePtr && curr == bi.curr && que == bi.que)
			return true;
		else
			return false;
	}

	template<typename Data>
	bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator& bi) const noexcept
	{
		return !(*this == bi);
	}

/* ************************************************************************ */

	// Specific member functions (inherited from Iterator)

	template<typename Data>
	Data& BTBreadthIterator<Data>::operator*() const // (throw std::out_of_range when terminated)
	{
		if (Terminated())
			throw std::out_of_range("Out of range!");
		else
			return curr->dato;
	}

	template<typename Data>
	bool BTBreadthIterator<Data>::Terminated() const noexcept // (should not throw exceptions)
	{
		return curr == nullptr;
	}

	template<typename Data>
	BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++()  // (throw std::out_of_range when terminated)
	{
		if (Terminated())
			throw std::out_of_range("Out of range!");
		if (curr->HasLeftChild())
			que.Enqueue(&curr->LeftChild());
		if (curr->HasRightChild())
			que.Enqueue(&curr->RightChild());
		if (!que.Empty())
			curr = que.HeadNDequeue();
		else
			curr = nullptr;
		return *this;
	}

	//Specific member functions (inherited from ResettableIterator)
	template<typename Data>
	void BTBreadthIterator<Data>::Reset() noexcept // (should not throw exceptions)
	{
		if (treePtr != nullptr)
			curr = &treePtr->Root();
		que.Clear();
	}
}
