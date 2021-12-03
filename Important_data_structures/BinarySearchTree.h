/*
	This is template implementation of the Binary search tree (BST). BST is a container with the following conditions:
		1) Every subtree is a BST.
		2) The values of the left sub-tree are structly less then its root value.
		3) The values of the right sub-tree are greater or equal to its root value.

	Complexity:
		Space: average O(n), worst O(n)
		Search: avg O(log n), worst O(n)
		Insert: avg O(log n), worst O(n)
		Delete: avg O(log n), worst O(n)
*/

#include <memory>

namespace Trees
{
template <class KeyType, class ValueType>
class BinarySearchTree
{
public:
//	Classes and structures
	struct Element
	{
	public:
	//	Constructors/destructor
	/*
			Element constructor
			Params: key, value
	*/
		Element(const KeyType& key_, const ValueType& value_) : key(key_), value(value_)
		{
		}
	/*
			Assignment operator
			Params: object to assign
			Return: Element
	*/
		Element& operator=(const Element& other)
		{
			if (this != &other)
			{
				key = other.key;
				value = other.value;
			}
			return *this;
		}

	//	Members
		const KeyType key;
		ValueType value;
	};
	
//	Constructors/destructor
/*
		BinarySearchTree constructor
		Params: parent
*/
	BinarySearchTree() : root(nullptr)
	{
	}

/*		
		BinarySearchTree destructor
*/
	~BinarySearchTree()
	{
		destroy(root);
	}

//	Methods
/*
		Inserts an element to the tree
		Params: element to insert
		Return: none
*/
	void insert(const KeyType& key, const ValueType& value)
	{
		insert_to_tree(key, value, root);
	}

/*
		Looks for the element with the specified key.
		Params: key, current tree node
		Return: node ptr
*/
	Element* find(const KeyType& key) const
	{
		return find_in_tree(key, root);
	}

/*
		Removes the element with the specified key
		Params: key of the element to remove
		Return: none
*/
	void remove(const KeyType& key)
	{
		remove_from_tree(key, root);
	}

/*
		Traverses a tree in the increase order and applies functor to each element
		Params: functor
		Return: none
*/
	template <typename FunctorType>
	void traverse(const FunctorType& functor)
	{
		traverse_tree(functor, root);
	}

private:
//	Classes
//		Node type
	struct Node
	{
	//	Constructors/destructor
	/*
			Node constructor
			Params: key, value, parent
	*/
		Node(const KeyType& key, const ValueType& value, Node* parent_ = nullptr)
			: element(Element(key, value)), parent(parent_), left(nullptr), right(nullptr)
		{
		}

	//	Methods
	/*
			Gets the most left elemet
			Params: none
			Return: pointer to the most left element
	*/
		Node* most_left(void)
		{
			if (left == nullptr)
				return this;
			return left->most_left();
		}

	/*
			Sets all the node's connections to the null pointer
			Params: none
			Return: none
	*/
		void clear(void)
		{
			parent = nullptr;
			left = nullptr;
			right = nullptr;
		}

	//	Members
	//		Element
		Element element;
	//		Parent
		Node* parent;
	//		Left child
		Node* left;
	//		Right child
		Node* right;
	};

//	Methods
/*
		Inserts an element to the tree
		Params: element to insert, tree node
		Return: none
*/
	void insert_to_tree(const KeyType& key, const ValueType& value, Node*& node)
	{
		if (node == nullptr)
		{
			node = new Node(key, value, nullptr);
			return;
		}
		if (key < node->element.key)
		{
			if (node->left == nullptr)
				node->left = new Node(key, value, node);
			else
				insert_to_tree(key, value, node->left);
		}
		else 
			if (node->element.key < key)
			{
				if (node->right == nullptr)
					node->right = new Node(key, value, node);
				else
					insert_to_tree(key, value, node->right);
			}
			else
			{
				node->element.value = value;
				return;
			}
	}

/*
		Looks for the element with the specified key.
		Params: key, current tree node
		Return: node ptr
*/
	Element* find_in_tree(const KeyType& key, Node* const& node) const
	{
		if (node == nullptr)
			return nullptr;

		if (key < node->element.key)
			return find_in_tree(key, node->left);
		else
		{
			if (node->element.key < key)
				return find_in_tree(key, node->right);
			else
				return &node->element;
		}
	}

/*
		Removes the element with the specified key
		Params: key of the element to remove, current tree node
		Return: none
*/
	void remove_from_tree(const KeyType& key, Node*const& node)
	{
		if (node == nullptr)
			return;
		if (key < node->element.key)
			remove_from_tree(key, node->left);
		else
		{
			if (node->element.key < key)
				remove_from_tree(key, node->right);
			else
			{
				auto* child_to_reset = node->parent == nullptr ? nullptr : // If there's no parent, we don't need to reset child (because there are no any)
					(node->element.key < node->parent->element.key ? &node->parent->left : &node->parent->right);
				if (node->left == nullptr && node->right == nullptr)
				{
					if (node->parent == nullptr)
						root = nullptr;
					else
					{
						*child_to_reset = nullptr;
						node->clear();
					}
				}
				else if (node->left == nullptr || node->right == nullptr)
				{
					auto& new_child = node->left != nullptr ? node->left : node->right;
					if (node->parent = nullptr)
						root = new_child;
					else
						*child_to_reset = new_child;
					new_child->parent = node->parent;
					node->clear();
				}
				else
				{
					auto most_left_in_right_subtree = node->right->most_left();
					most_left_in_right_subtree->left = node->left;
					node->left->parent = most_left_in_right_subtree;
					most_left_in_right_subtree->parent = node->parent;

					node->clear();
					delete node;

					if (child_to_reset != nullptr)
						*child_to_reset = most_left_in_right_subtree;
				}
			}
		}
	}

/*
		Traverses a tree in the increase order and applies functor to each element
		Params: functor, node
		Return: none
*/
	template <typename FunctorType>
	void traverse_tree(const FunctorType& functor, Node*& node)
	{
		if (node == nullptr)
			return;
		traverse_tree(functor, node->left);
		functor(node->element.key, node->element.value);
		traverse_tree(functor, node->right);
	}

/*
		Destroys the tree recursively
		Params: node
		Return: none
*/
	void destroy(Node* node)
	{
		if (node != nullptr)
		{
			destroy(node->left);
			destroy(node->right);
			delete node;
		}
	}

//	Members
//		Root node
	Node* root;
};
}