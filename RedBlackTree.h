#pragma once
#pragma once
#include<iostream>
using namespace std;


enum Color
{
	RED,
	BLACK
};

template<class K, class V >
class RBNode
{
public:
	typedef RBNode<K, V>Node;

	Node* _left;
	Node* _right;
	Node* _parent;
	Color _color;
	pair<K, V>_kv;
public:
	RBNode(pair<K, V>kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _color(RED)
	{}
	
};


//������
template<class K,class V>
class _iterator
{
public:
	typedef RBNode<K, V> Node;
public:
	Node* _node;
public:
	_iterator(Node*node)
	{
		_node = node;
	}
	_iterator(const _iterator& it)
	{
		_node = it._node;
	}
	Node* LeftMost(Node* node)
	{
		if (node == nullptr)
			return nullptr;
		while (node->_left)
		{
			node = node->_left;
		}
		return node;
	}
	Node* RightMost(Node*root)
	{
		while (root->_right)
		{
			root = root->_right;
		}
		return root;
	}

	_iterator<K, V> operator++()
	{
		if (_node->_right != nullptr)
		{
			_node = LeftMost(_node->_right);
			return *this;
		}
		Node* parent = _node->_parent;
		if (_node->_parent == nullptr)
			return _iterator<K, V>(nullptr);
		while (parent)
		{
			if (parent->_left == _node)
			{
				_node = parent;
				return *this;
			}
			else
			{
				_node = parent;
				parent = parent->_parent;
			}
		}

		_node = nullptr;
		return _iterator<K,V>(nullptr);
	}
	K &operator*()
	{
		if (_node == nullptr)
			printf("��ָ��");
		return _node->_kv.first;
	}
	pair<K, V>operator->()
	{
		return _node->_kv;
	}
	bool operator!=(_iterator it)
	{
		return _node != it._node;
	}
	bool operator==(_iterator it)
	{
		return _node == it._node;
	}



};




template<class K, class V, class Compare>
class RBTree
{
public:
	typedef RBNode<K, V> Node;
private:
	Node* _root = nullptr;
public:
	typedef _iterator<K, K> Iterator;



	//���캯��
	RBTree()
		:_root(nullptr)
	{}



	//��������
	void _Destory(Node* root)
	{
		if (root == nullptr)
			return;
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}
	~RBTree()
	{
		_Destory(_root);
	}


	//�������캯��
	Node* _Copy(Node* root)
	{
		if (root == nullptr)
			return nullptr;
		Node* left = _Copy(root->_left);
		Node* right = _Copy(root->_right);
		Node* newnode = new Node;
		newnode->_left = left;
		newnode->_right = right;
		newnode->_color = root->_color;
		newnode->_kv = root->_kv;
		return newnode;

	}
	RBTree(const Node& t)
	{
		_Copy(&t);
	}


	//��ֵ
	RBTree<K, V, Compare>operator=(RBTree<K, V, Compare>t)
	{
		swap(_root, t._root);
		return *this;
	}



	//������

	Node* LeftMost(Node*root)
	{
		if (_root == nullptr)
			return nullptr;
		while (root->_left)
		{
			root = root->_left;
		}
		return root;
	}
	Iterator _begin()
	{

		return Iterator(LeftMost(_root));
	}
	Iterator _end()
	{
		return Iterator(nullptr);
	}
	
	

	//����

	void RotateL(Node* cur)
	{
		Node* parent = cur->_parent;
		Node* curL = cur->_left;
		Node* gradpa = parent->_parent;
		if (gradpa && gradpa->_left == parent)
			gradpa->_left = cur;
		if (gradpa && gradpa->_right == parent)
			gradpa->_right = cur;
		if (gradpa == nullptr)
			_root = cur;
		parent->_right = cur->_left;
		parent->_parent = cur;
		cur->_parent = gradpa;
		cur->_left = parent;
		if (gradpa == nullptr)
			_root = cur;

	}

	//����
	void RotateR(Node* cur)
	{
		Node* parent = cur->_parent;
		Node* curR = cur->_right;
		Node* gradpa = parent->_parent;
		if (gradpa && gradpa->_left == parent)
			gradpa->_left = cur;
		if (gradpa && gradpa->_right == parent)
			gradpa->_right = cur;
		parent->_left = curR;
		parent->_parent = cur;
		cur->_right = parent;
		cur->_parent = gradpa;
		if (gradpa == nullptr)
			_root = cur;
	}



	//����
	pair<_iterator<K,V>,bool> Insert(pair<K, V>kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_color = BLACK;

			return make_pair(_iterator<K,V>(_root),true);
		}
		Node* cur = _root;
		//�ҵ�Ҫ�����λ��
		Node* parent = nullptr;
		Compare comfun;
		while (cur)
		{
			if (comfun( kv.first, cur->_kv.first))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (comfun(cur->_kv.first , kv.first))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return make_pair(cur, false);
			}
		}

		cur = new Node(kv);
		//��������
		_iterator<K, V>it(cur);
		Node* gradpa = nullptr;
		Node* uncle = nullptr;
		cur->_parent = parent;


		//�жϵ�������˫��
		if (comfun(parent->_kv.first , kv.first))
		{
			//�²���ڵ�λ����߻����ұ�
			//�½ڵ�������
			parent->_left = cur;
			//parent�����Ǹ��ڵ�
			if (parent->_color == BLACK)
				return make_pair(it, true);
			//parentһ���Ǻ�ɫ����һ���и��ڵ�
			gradpa = parent->_parent;
			//�ж�uncle��parent˭����ڵ�˭���ҽڵ�
			if (parent == gradpa->_left)
				uncle = gradpa->_right;
			else
				uncle = gradpa->_left;
		}
		else
		{
			//�½ڵ�����ұ�
			parent->_right = cur;
			if (parent->_color == BLACK)
				return make_pair(it, true);
			gradpa = parent->_parent;
			if (parent == gradpa->_left)
				uncle = gradpa->_right;
			else
				uncle = gradpa->_left;
		}

		while (cur)
		{
			if (parent->_color == BLACK)
			{
				break;
			}
			else
			{
				//���½ڵ���ɫ
				if (uncle && uncle->_color == RED)
				{
					uncle->_color = parent->_color = BLACK;
					gradpa->_color = RED;
					cur = gradpa;
					parent = cur->_parent;

					if (parent == nullptr || parent->_color == BLACK)
						break;

					gradpa = parent->_parent;
					if (parent->_right == cur)
						uncle = gradpa->_left;
					else
						uncle = gradpa->_right;
				}
				//��ת
				else
				{
					if (cur == parent->_left)
					{
						if (parent == gradpa->_left)
						{
							RotateR(parent);
							gradpa->_color = RED;
							parent->_color = BLACK;
							break;

						}
						else
						{
							RotateR(cur);
							RotateL(cur);
							cur->_color = BLACK;
							gradpa->_color = RED;
							break;
						}
					}
					else
					{
						if (parent == gradpa->_right)
						{
							RotateL(parent);
							gradpa->_color = RED;
							parent->_color = BLACK;
							break;

						}
						else
						{
							RotateL(cur);
							RotateR(cur);
							cur->_color = BLACK;
							gradpa->_color = RED;
							break;
						}
					}
				}
			}
		}
		_root->_color = BLACK;
		return make_pair(it, true);
	}
	//�������
	void _Inorder(Node* root)
	{
		if (root == nullptr)
			return;
		_Inorder(root->_left);
		cout << root->_kv.first << " " << root->_color << " ";
		_Inorder(root->_right);
	}
	void Inorder()
	{
		_Inorder(_root);
	}

};

