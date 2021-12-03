#include "Exception.h"

namespace Trees
{
template <class KeyType, class ValueType>
class AVLTree
{
public:
//	Classes and structures
//		Element type
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
	AVLTree() : root(nullptr)
	{
	}

/*		
		BinarySearchTree destructor
*/
	~AVLTree()
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

/*
		Traverses a tree in the increase order and applies functor to each element, const version
		Params: functor
		Return: none
*/
	template <typename FunctorType>
	void traverse(const FunctorType& functor) const 
	{
		traverse_tree(functor, root);
	}

private:
//	Node struct forward declaration
	struct Node;
//	Types
	typedef std::unique_ptr<Node> NodePtr;
	struct Node
	{
	//	Constructors/destructor
	/*
			Node constructor
			Params: key, value, parent
	*/
		Node(const KeyType& key, const ValueType& value, Node* parent_ = nullptr)
			: element(Element(key, value)), parent(parent_), left(nullptr), right(nullptr), height(0), balance_score(0)
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
			Recounts the balance and the height of the current node subtree
			Params: none
			Reutrn: none
	*/
		void recount_height_and_balance(void)
		{
			int height_right = right == nullptr ? -1 : right->height;
			int height_left = left == nullptr ? -1 : left->height;
			height = (height_right > height_left ? height_right : height_left) + 1;
			balance_score = height_right - height_left;
		}

	/*
			Rotates the subtree from left to right
			Params: none
			Return: none
	*/
		void right_turn(void)
		{
		//	If the left subtree has the positive balance (right-heavy), make the left turn for Y
			if (left->balance_score > 0)
				left->left_turn();

			Node* Y = left;
			Node* Yl = Y->left;
			Node* Yr = Y->right;

			Node** child_to_replace = (parent == nullptr ? nullptr : (parent->left == this ? &parent->left : &parent->right));

			Y->parent = parent;
			parent = Y;
			left = Yr;
			Y->right = this;
			if (child_to_replace != nullptr)
				*child_to_replace = Y;
		}

	/*
			Rotates the subtree from right to left
			Params: none
			Return: none
	*/
		void left_turn(void)
		{
		//	If the right subtree has the negative balance (left-heavy), make the right turn for Y
			if (right->balance_score < 0)
				right->right_turn();

			Node* Y = right;
			Node* Yl = Y->left;
			Node* Yr = Y->right;

			Node* child_to_replace = (parent->left == this ? parent->left : parent->right);

			Y->parent = parent;
			parent = Y;
			right = Yl;
			Y->left = this;
			child_to_replace = Y;
		}
		
	/*
			Balances the current subtree
			Params: none
			Return: none
	*/
		void balance(void)
		{
			recount_height_and_balance();
			if (abs(balance_score) <= 1) // Subtree is nearly balanced
				return;
			if (balance_score < 0)
			{
				right_turn();
				recount_height_and_balance();
			}
			else
			{
				left_turn();
				recount_height_and_balance();
			}
			parent->recount_height_and_balance();
		}

	/*
			Find the root of the tree
			Params: none
			Return: root
	*/
		Node* find_root(void)
		{
			if (parent == nullptr)
				return this;
			return parent->find_root();
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
	//		Subtree height
		int height;
	//		Subtree balance
		int balance_score;
	};

//	Methods
/*
		Execute the tree balancing
		Params: node to balance
		Return: none
*/
	void balance(Node* node)
	{
		node->balance();
		if (root->parent != nullptr)
			root = root->find_root();
	}

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
			balance(node);
		}
		else 
			if (node->element.key < key)
			{
				if (node->right == nullptr)
					node->right = new Node(key, value, node);
				else
					insert_to_tree(key, value, node->right);
				balance(node);
			}
			else
			{
				node->element.value = value;
				return;
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
		{
			remove_from_tree(key, node->left);
			balance(node);
		}
		else
		{
			if (node->element.key < key)
			{
				remove_from_tree(key, node->right);
				balance(node);
			}
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

					balance(most_left_in_right_subtree);
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
		Traverses a tree in the increase order and applies functor to each element, const version
		Params: functor, node
		Return: none
*/
	template <typename FunctorType>
	void traverse_tree(const FunctorType& functor, Node*& node) const
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

//	Memebrs
//		Root node
	Node* root;
};

}
