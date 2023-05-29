#pragma once

template <typename T>
class Deque {
    private:
        struct Node {
            T data = { };

            Node* prev = { };
            Node* next = { };
        };

    public:
        class Iterator {
            public:
                Iterator();
                ~Iterator() noexcept;

                Iterator(Node* _target) noexcept;

                T& operator*() const;               // not safe
                Iterator& operator++() noexcept;    // prefix

                operator bool() const noexcept;

            private:
                Node* target = { };
        };

    public:
        Deque();
        ~Deque() noexcept;

        Deque(const Deque<T>& _other);
        Deque(Deque<T>&& _other) noexcept;

        Deque<T>& operator=(const Deque<T>& _other);
        Deque<T>& operator=(Deque<T>&& _other) noexcept;

        bool operator==(const Deque<T>& _other) const noexcept;
        bool operator!=(const Deque<T>& _other) const noexcept;

        Deque<T>& operator+=(const Deque<T>& _other);

        operator bool() const noexcept;

        void push_front(const T& _data);
        void push_back(const T& _data);

        void pop_front();
        void pop_back();
        void clear();

        T& front() const;           // not safe
        T& back() const;            // not safe

        Iterator begin() const noexcept;
        Iterator end() const noexcept;

        unsigned int size() const noexcept;
        bool isEmpty() const noexcept;

    private:
        Node* makeNewNode(const T& _data, Node* _prev = { }, Node* _next = { }) const;

    private:
        Node* mHead = { };
        Node* mTail = { };

        unsigned int mSize = { };
};

template <typename T> Deque<T>::Iterator::Iterator() { }
template <typename T> Deque<T>::Iterator::~Iterator() noexcept { }

template <typename T> Deque<T>::Iterator::Iterator(typename Deque<T>::Node* _target) noexcept
    : target{_target} { }

template <typename T> T& Deque<T>::Iterator::operator*() const { return target->data; }
template <typename T> typename Deque<T>::Iterator& Deque<T>::Iterator::operator++() noexcept {
    if (target)
        target = target->next;

    return *this;
}

template <typename T> Deque<T>::Iterator::operator bool() const noexcept { return (target ? true : false); }


template <typename T> typename Deque<T>::Node* Deque<T>::makeNewNode(const T& _data, typename Deque<T>::Node* _prev, typename Deque<T>::Node* _next) const {
    typename Deque<T>::Node* newNode = new Node;
    newNode->data = _data;
    newNode->prev = _prev;
    newNode->next = _next;

    return newNode;
}

template <typename T> Deque<T>::Deque() { }
template <typename T> Deque<T>::~Deque() noexcept { clear(); }

template <typename T> Deque<T>::Deque(const Deque<T>& _other) { *this = _other; }
template <typename T> Deque<T>::Deque(Deque<T>&& _other) noexcept { *this = std::move(_other); }

template <typename T> Deque<T>& Deque<T>::operator=(const Deque<T>& _other) {
    if (this != &_other) {
        clear();

        auto it = _other.begin();
        while (it) {
            push_back(*it);

            ++it;
        }
    }

    return *this;
}
template <typename T> Deque<T>& Deque<T>::operator=(Deque<T>&& _other) noexcept {
    if (this != &_other) {
        clear();

        mSize = _other.mSize;
        mHead = _other.mHead;
        mTail = _other.mTail;

        _other.mSize = { };
        _other.mHead = { };
        _other.mTail = { };
    }

    return *this;
}

template <typename T> bool Deque<T>::operator==(const Deque<T>& _other) const noexcept { return this == &_other; }
template <typename T> bool Deque<T>::operator!=(const Deque<T>& _other) const noexcept { return this != &_other; }

template <typename T> Deque<T>& Deque<T>::operator+=(const Deque<T>& _other) {
    if (this != &_other) {
        auto it = _other.begin();

        while (it) {
            push_back(*it);

            ++it;
        }
    }

    return *this;
}

template <typename T> Deque<T>::operator bool() const noexcept { return mSize > 0; }

template <typename T> void Deque<T>::push_front(const T& _data) {
    typename Deque<T>::Node* newNode = makeNewNode(_data, { }, mHead);

    if (mSize)
        mHead->prev = newNode;

    else
        mTail = newNode;

    mHead = newNode;
    ++mSize;
}
template <typename T> void Deque<T>::push_back(const T& _data) {
    typename Deque<T>::Node* newNode = makeNewNode(_data, mTail);

    if (mSize)
        mTail->next = newNode;

    else
        mHead = newNode;

    mTail = newNode;
    ++mSize;
}

template <typename T> void Deque<T>::pop_front() {
    if (mSize) {
        typename Deque<T>::Node* next = mHead->next;

        if (next)
            next->prev = { };

        else
            mTail = { };

        delete mHead;
        mHead = next;
        --mSize;
    }
}
template <typename T> void Deque<T>::pop_back() {
    if (mSize) {
        typename Deque<T>::Node* prev = mTail->prev;

        if (prev)
            prev->next = { };

        else
            mHead = { };

        delete mTail;
        mTail = prev;
        --mSize;
    }
}
template <typename T> void Deque<T>::clear() {
    while (mSize)
        pop_front();
}

template <typename T> T& Deque<T>::front() const { return mHead->data; }
template <typename T> T& Deque<T>::back() const { return mTail->data; }

template <typename T> typename Deque<T>::Iterator Deque<T>::begin() const noexcept { return Iterator(mHead); }
template <typename T> typename Deque<T>::Iterator Deque<T>::end() const noexcept { return Iterator(); }

template <typename T> unsigned int Deque<T>::size() const noexcept { return mSize; }
template <typename T> bool Deque<T>::isEmpty() const noexcept { return mSize == 0; }