#pragma once

template <typename T>
class List {
    private:
        struct Node {
            T data = { };

            Node* next = { };
            Node* prev = { };
        };

    public:
        class Iterator {
            public:
                Iterator();
                ~Iterator() noexcept;

                Iterator(Node* _target);

                T& operator*() const;       // not safe
                Iterator& operator++();     // prefix

                operator bool() const;

            private:
                Node* target = { };
        };

    public:
        List();
        ~List() noexcept;

        List(const List<T>& _other);
        List(List<T>&& _other) noexcept;

        List<T>& operator=(const List<T>& _other);
        List<T>& operator=(List<T>&& _other) noexcept;

        T& operator[](const unsigned int& _idx) const;      // not safe

        operator bool() const noexcept;

        void push_front(const T& _data);
        void push_back(const T& _data);
        void insert(const T& _data, const unsigned int& _idx);

        void pop_front();
        void pop_back();
        void remove_idx(const unsigned int& _idx);
        void remove_data(const T& _data);
        void clear();

        unsigned int size() const noexcept;
        bool isEmpty() const noexcept;

        T& front() const;           // not safe
        T& back() const;            // not safe

        Iterator begin() const;     // not safe
        Iterator end() const;       // not safe

    private:
        Node* makeNewNode(const T& _data, Node* _prev = { }, Node* _next = { }) const;
        Node* findIdx(const unsigned int& _idx) const;

    private:
        Node* mHead = { };
        Node* mTail = { };

        unsigned int mSize = { };
};

template <typename T> List<T>::Iterator::Iterator() { }
template <typename T> List<T>::Iterator::~Iterator() noexcept { }

template <typename T> List<T>::Iterator::Iterator(typename List<T>::Node* _target)
    : target{_target} { }

template <typename T> T& List<T>::Iterator::operator*() const { return target->data; }
template <typename T> typename List<T>::Iterator& List<T>::Iterator::operator++() {
    if (target)
        target = target->next;

    return *this;
}

template <typename T> List<T>::Iterator::operator bool() const { return target; }


template<typename T> typename List<T>::Node* List<T>::makeNewNode(const T& _data, typename List<T>::Node* _prev, typename List<T>::Node* _next) const {
    typename List<T>::Node* newNode = new Node;
    newNode->data = _data;
    newNode->prev = _prev;
    newNode->next = _next;

    return newNode;
}
template<typename T> typename List<T>::Node* List<T>::findIdx(const unsigned int& _idx) const {
    typename List<T>::Node* target = mHead;
    unsigned int steps = _idx;

    if (_idx < (mSize / 2)) {
        for (unsigned int i = 0; i < steps; ++i)
            target = target->next;
    }
    else {
        target = mTail;
        steps = mSize - _idx - 1;

        for (unsigned int i = 0; i < steps; ++i)
            target = target->prev;
    }

    return target;
}

template<typename T> List<T>::List() { }
template<typename T> List<T>::~List() noexcept { clear(); }

template <typename T> List<T>::List(const List<T>& _other) { *this = _other; }
template <typename T> List<T>::List(List<T>&& _other) noexcept { *this = std::move(_other); }

template <typename T> List<T>& List<T>::operator=(const List<T>& _other) {
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
template <typename T> List<T>& List<T>::operator=(List<T>&& _other) noexcept {
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

template <typename T> T& List<T>::operator[](const unsigned int& _idx) const { return findIdx(_idx)->data; }

template <typename T> List<T>::operator bool() const noexcept { return mSize; }

template<typename T> void List<T>::push_front(const T& _data) {
    typename List<T>::Node* newNode = makeNewNode(_data, { }, mHead);

    if (mSize)
        mHead->prev = newNode;

    else
        mTail = newNode;

    mHead = newNode;
    ++mSize;
}
template<typename T> void List<T>::push_back(const T& _data) {
    typename List<T>::Node* newNode = makeNewNode(_data, mTail, { });

    if (mSize)
        mTail->next = newNode;

    else
        mHead = newNode;

    mTail = newNode;
    ++mSize;
}
template<typename T> void List<T>::insert(const T& _data, const unsigned int& _idx) {
    if (0 < _idx && _idx < mSize - 1) {
        typename List<T>::Node* targetPrev = findIdx(_idx);
        typename List<T>::Node* targetNext = targetPrev->next;
        typename List<T>::Node* target = makeNewNode(_data, targetPrev, targetNext);

        targetPrev->next = target;
        targetNext->prev = target;

        ++mSize;
    }

    else if (_idx == 0)
        push_front(_data);

    else if (_idx == mSize || _idx == mSize - 1)
        push_back(_data);
}

template<typename T> void List<T>::pop_front() {
    if (mSize) {
        typename List<T>::Node* next = mHead->next;

        if (next)
            next->prev = { };

        else
            mTail = { };

        delete mHead;
        mHead = next;
        --mSize;
    }
}
template<typename T> void List<T>::pop_back() {
    if (mSize) {
        typename List<T>::Node* prev = mTail->prev;

        if (prev)
            prev->next = { };

        else
            mHead = { };

        delete mTail;
        mTail = prev;
        --mSize;
    }
}
template<typename T> void List<T>::remove_idx(const unsigned int& _idx) {
    if (mSize) {
        if (0 < _idx && _idx < mSize - 1) {
            typename List<T>::Node* target = findIdx(_idx);
            typename List<T>::Node* targetPrev = target->prev;
            typename List<T>::Node* targetNext = target->next;

            targetPrev->next = targetNext;
            targetNext->prev = targetPrev;

            delete target;
            --mSize;
        }

        else if (_idx == 0)
            pop_front();

        else if (_idx == mSize - 1)
            pop_back();
    }
}
template<typename T> void List<T>::remove_data(const T& _data) {
    typename List<T>::Node* target = [&_data](typename List<T>::Node* _head) {
        typename List<T>::Node* current = _head;

        while (current) {
            if (current->data == _data)
                break;

            current = current->next;
        }

        return current;
    } (mHead);

    if (target) {
        if (target == mHead)
            pop_front();

        else if (target == mTail)
            pop_back();

        else {
            typename List<T>::Node* targetPrev = target->prev;
            typename List<T>::Node* targetNext = target->next;

            if (targetPrev)
                targetPrev->next = targetNext;
            if (targetNext)
                targetNext->prev = targetPrev;

            delete target;
            --mSize;
        }
    }
}
template<typename T> void List<T>::clear() {
    while (mSize)
        pop_front();
}

template<typename T> unsigned int List<T>::size() const noexcept { return mSize; }
template<typename T> bool List<T>::isEmpty() const noexcept { return mSize == 0; }

template <typename T> T& List<T>::front() const { return mHead->data; }
template <typename T> T& List<T>::back() const { return mTail->data; }

template <typename T> typename List<T>::Iterator List<T>::begin() const { return Iterator(mHead); }
template <typename T> typename List<T>::Iterator List<T>::end() const { return Iterator(); }