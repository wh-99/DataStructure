#pragma once

template <typename T>
class Stack {
    private:
        struct Node {
            T data = { };

            Node* prev = { };
        };

    public:
        Stack(const Stack<T>&) = delete;
        Stack(Stack<T>&&) noexcept = delete;

        Stack<T>& operator=(const Stack<T>&) = delete;
        Stack<T>& operator=(Stack<T>&&) noexcept = delete;

        Stack();
        ~Stack() noexcept;

        bool operator==(const Stack<T>& _other) const noexcept;
        bool operator!=(const Stack<T>& _other) const noexcept;

        operator bool() const noexcept;

        void push(const T& _data);
        void pop();
        void clear();

        T& top() const;     // not safe

        unsigned int size() const noexcept;
        bool isEmpty() const noexcept;

    private:
        Node* makeNewNode(const T& _data, Node* _prev = { }) const;

    private:
        Node* mTail = { };

        unsigned int mSize = { };
};

template<typename T> typename Stack<T>::Node* Stack<T>::makeNewNode(const T& _data, typename Stack<T>::Node* _prev) const {
    typename Stack<T>::Node* newNode = new Node;
    newNode->data = _data;
    newNode->prev = _prev;

    return newNode;
}

template<typename T> Stack<T>::Stack() { }
template<typename T> Stack<T>::~Stack() noexcept { clear(); }

template<typename T> bool Stack<T>::operator==(const Stack<T>& _other) const noexcept { return this == &_other; }
template<typename T> bool Stack<T>::operator!=(const Stack<T>& _other) const noexcept { return this != &_other; }

template<typename T> Stack<T>::operator bool() const noexcept { return mSize > 0; }

template<typename T> void Stack<T>::push(const T& _data) {
    typename Stack<T>::Node* newNode = makeNewNode(_data, mTail);

    mTail = newNode;
    ++mSize;
}
template<typename T> void Stack<T>::pop() {
    if (mSize) {
        typename Stack<T>::Node* prevNode = mTail->prev;

        delete mTail;
        mTail = prevNode;

        --mSize;
    }
}
template<typename T> void Stack<T>::clear() {
    while (mSize)
        pop();
}

template<typename T> T& Stack<T>::top() const { return mTail->data; }

template<typename T> unsigned int Stack<T>::size() const noexcept { return mSize; }
template<typename T> bool Stack<T>::isEmpty() const noexcept { return mSize == 0; }

