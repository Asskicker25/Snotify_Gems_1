#pragma once

#include "SmartArray.h"

namespace Containers
{
	template <typename T>
	class Node
	{
	public:
		Node* mPrevNode = nullptr;
		Node* mNextNode = nullptr;
		
		T mData;
	};

	template <typename T>
	class LinkedList
	{
	public:
		LinkedList();
		~LinkedList();

		void insertBeforeCurrent(T data);
		void updateCurrent(T data);
		void deleteAtCurrent();

		bool isEmpty();
		bool moveNext();
		bool movePrevious();
		bool deleteElement(T element);

		void deleteNode(Node<T>* node);
		void moveToFirst();
		void moveToLast();
		void clear();

		inline unsigned int getSize() { return mSize; }
		inline Node<T>* getCurrentNode() { return mCurrentNode; }
		inline void setCurrentNode(Node<T>* node) { mCurrentNode = node; }
		
		T getCurrent();

	private:

		Node<T>* mHeadNode;
		Node<T>* mTailNode;
		Node<T>* mCurrentNode;

		unsigned int mSize = 0; 

	};

	template<typename T>
	inline LinkedList<T>::LinkedList()
	{
		mHeadNode = nullptr;
		mTailNode = nullptr;
		mCurrentNode = nullptr;
	}

	template<typename T>
	inline LinkedList<T>::~LinkedList()
	{
		clear();
	}

	template<typename T>
	inline void LinkedList<T>::insertBeforeCurrent(T data)
	{
		Node<T>* newNode;

		if (isEmpty())
		{
			newNode = new Node<T>();

			newNode->mData = data;
			mHeadNode = newNode;
			mTailNode = newNode;
			mCurrentNode = mHeadNode;

			mSize++;
			return;
		}

		newNode = new Node<T>();
		
		newNode->mData = data;
		newNode->mNextNode = mCurrentNode;
		newNode->mPrevNode = mCurrentNode->mPrevNode;

		mCurrentNode->mPrevNode = newNode;
		mCurrentNode = newNode;

		if(mCurrentNode->mPrevNode == nullptr)
		{
			mHeadNode = mCurrentNode;
		}


		//Only needed if we have insertAfterCurrent
		/*if (mCurrentNode->mNextNode == nullptr)
		{
			mTailNode = mCurrentNode;
		}*/

		mSize++;
	}

	template<typename T>
	inline void LinkedList<T>::updateCurrent(T data)
	{
		mCurrentNode->mData = data;
	}

	template<typename T>
	inline void LinkedList<T>::deleteAtCurrent()
	{
		if (isEmpty()) return;

		Node<T>* nodeToDelete = mCurrentNode;
		mCurrentNode = nodeToDelete->mNextNode;

		deleteNode(nodeToDelete);
	}

	template<typename T>
	inline bool LinkedList<T>::deleteElement(T element)
	{
		Node<T>* tempNode = mCurrentNode;

		moveToFirst();

		do
		{
			if (getCurrent() == element)
			{
				deleteNode(mCurrentNode);

				mCurrentNode = tempNode;
				return true;
			}

		} while (moveNext());

		return false;
	}

	template<typename T>
	inline void LinkedList<T>::deleteNode(Node<T>* node)
	{
		if (node->mPrevNode != nullptr)
		{
			node->mPrevNode->mNextNode = node->mNextNode;
		}
		else
		{
			mHeadNode = node->mNextNode;
		}

		if (node->mNextNode != nullptr)
		{
			node->mNextNode->mPrevNode = node->mPrevNode;
		}
		else
		{
			mTailNode = node->mPrevNode;
		}

		delete node;

		mSize--;
	}

	template<typename T>
	inline bool LinkedList<T>::isEmpty()
	{
		return mHeadNode == nullptr;
	}

	template<typename T>
	inline bool LinkedList<T>::moveNext()
	{
		if (mCurrentNode == nullptr) return false;

		if (mCurrentNode->mNextNode != nullptr)
		{
			mCurrentNode = mCurrentNode->mNextNode;
			return true;
		}

		return false;
	}

	template<typename T>
	inline bool LinkedList<T>::movePrevious()
	{
		if (mCurrentNode == nullptr) return false;

		if (mCurrentNode->mPrevNode != nullptr)
		{
			mCurrentNode = mCurrentNode->mPrevNode;
			return true;
		}

		return false;
	}

	

	template<typename T>
	inline void LinkedList<T>::moveToFirst()
	{
		mCurrentNode = mHeadNode;
	}

	template<typename T>
	inline void LinkedList<T>::moveToLast()
	{
		mCurrentNode = mTailNode;
	}

	template<typename T>
	inline void LinkedList<T>::clear()
	{
		Node<T>* current = mHeadNode;

		while (current != nullptr)
		{
			Node<T>* next = current->mNextNode;
			delete current;
			current = next;
		}

		mHeadNode = nullptr;
		mTailNode = nullptr;
		mCurrentNode = nullptr;
	}

	template<typename T>
	inline T LinkedList<T>::getCurrent()
	{
		return mCurrentNode->mData;
	}



}

