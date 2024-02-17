#pragma once

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
		void deleteAtCurrent();

		bool isEmpty();
		bool moveNext();
		bool movePrevious();

		void moveToFirst();
		void moveToLast();
		void clear();

		T getCurrent();

	private:
		Node<T>* mHeadNode;
		Node<T>* mTailNode;
		Node<T>* mCurrentNode;
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
		if (isEmpty())
		{
			Node<T>* newNode = new Node<T>();

			newNode->mData = data;
			mHeadNode = newNode;
			mTailNode = newNode;
			mCurrentNode = mHeadNode;

			return;
		}

		Node<T>* newNode = new Node<T>();
		
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

	}

	template<typename T>
	inline void LinkedList<T>::deleteAtCurrent()
	{
		if (isEmpty()) return;


		if (mCurrentNode->mPrevNode != nullptr)
		{
			mCurrentNode->mPrevNode->mNextNode = mCurrentNode->mNextNode;
		}
		else
		{
			mHeadNode = mCurrentNode->mNextNode;
		}

		if (mCurrentNode->mNextNode != nullptr)
		{
			mCurrentNode->mNextNode->mPrevNode = mCurrentNode->mPrevNode;
		}
		else
		{
			mTailNode = mCurrentNode->mNextNode;
		}

		Node<T>* deleteNode = mCurrentNode;
		mCurrentNode = mCurrentNode->mNextNode;

		delete deleteNode;
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

