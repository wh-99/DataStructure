#pragma once

template <typename T>
class Queue {
    private:
        struct Node {
            T data = { };

            Node* next = { };
        };

    public:
        Queue(const Queue<T>&) = delete;
        Queue(Queue<T>&&) noexcept = delete;

        Queue<T>& operator=(const Queue<T>&) = delete;
        Queue<T>& operator=(Queue<T>&&) noexcept = delete;

        Queue();
        ~Queue() noexcept;

        bool operator==(const Queue<T>& _other) const noexcept;
        bool operator!=(const Queue<T>& _other) const noexcept;

        operator bool() const noexcept;

        void enqueue(const T& _data);
        void dequeue();
        void clear();

        T& front();     // not safe

        unsigned int size() const noexcept;
        bool isEmpty() const noexcept;

    private:
        Node* makeNewNode(const T& _data, Node* _next = { }) const;

    private:
        Node* mHead = { };
        Node* mTail = { };

        unsigned int mSize = { };
};

template<typename T> typename Queue<T>::Node* Queue<T>::makeNewNode(const T& _data, typename Queue<T>::Node* _next) const {
    typename Queue<T>::Node* newNode = new Node;
    newNode->data = _data;
    newNode->next = _next;

    return newNode;
}

template<typename T> Queue<T>::Queue() { }
template<typename T> Queue<T>::~Queue() noexcept { clear(); }

template<typename T> bool Queue<T>::operator==(const Queue<T>& _other) const noexcept { return this == &_other; }
template<typename T> bool Queue<T>::operator!=(const Queue<T>& _other) const noexcept { return this != &_other; }

template<typename T> Queue<T>::operator bool() const noexcept { return mSize > 0; }

template<typename T> void Queue<T>::enqueue(const T& _data) {
    typename Queue<T>::Node* newNode = makeNewNode(_data);

    if (mHead)
        mTail->next = newNode;

    else
        mHead = newNode;

    mTail = newNode;
    ++mSize;
}
template<typename T> void Queue<T>::dequeue() {
    if (mSize) {
        typename Queue<T>::Node* nextNode = mHead->next;

        if (mHead == mTail)
            mTail = nextNode;

        delete mHead;
        mHead = nextNode;

        --mSize;
    }
}
template<typename T> void Queue<T>::clear() {
    while (mSize)
        dequeue();
}

template<typename T> T& Queue<T>::front() { return mHead->data; }

template<typename T> unsigned int Queue<T>::size() const noexcept { return mSize; }
template<typename T> bool Queue<T>::isEmpty() const noexcept { return mSize == 0; }

