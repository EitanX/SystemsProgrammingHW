#pragma once

#include "Task.h"
#include <stdexcept>

namespace mtm {
    // -----------------------
    // SortedList
    // -----------------------
    template<typename T>
    class SortedList {
    public:
        class ConstIterator;

        SortedList() = default;
        SortedList(const SortedList& list);
        ~SortedList();
        SortedList& operator=(const SortedList& list);
        SortedList& insert(const T& task);
        SortedList& remove(const ConstIterator& iter);
        int length() const;
        const ConstIterator begin() const;
        const ConstIterator end() const;
        template<typename Condition>
        SortedList filter(Condition functor) const;
        template<typename Operation>
        SortedList apply(Operation functor) const;

    private:
        class Node;

        Node* headNode = nullptr;
        int size = 0;

        //-----Our Functions
        void linkTwoNodes(Node* prevNode, Node* nextNode);
        Node* buildNodes(const SortedList& list);
        void removeSpecificNode(Node* node);
    };

    // -----------------------
    //ConstIterator
    // -----------------------
    template<typename T>
    class SortedList<T>::ConstIterator {
        const Node* pointingAtNode = nullptr;

        friend class SortedList;

        ConstIterator(const Node* node);

    public:
        ConstIterator() = default;
        ConstIterator(const ConstIterator& iter) = default;
        ~ConstIterator() = default;
        ConstIterator& operator=(const ConstIterator& iter);
        const T& operator*() const;
        void operator++();
        bool operator!=(const ConstIterator& iter) const;
    };

    // -----------------------
    // Node
    // -----------------------
    template<typename T>
    class SortedList<T>::Node {
    public:
        T data;
        Node* prevNode = nullptr;
        Node* nextNode = nullptr;
        //---Constructors---
        Node(const T& data);
    };

    //---------------------------------------------------------------------------------------------
    //---------------------------------------Implementations---------------------------------------
    //---------------------------------------------------------------------------------------------
    // -----------------------
    // My Function
    // -----------------------
    // linkTwoNodes - links two given nodes. used alot throughout the code. made for readability.
    template<typename T>
    void SortedList<T>::linkTwoNodes(Node* prevNode, Node* nextNode) {
        prevNode->nextNode = nextNode;
        nextNode->prevNode = prevNode;
    }
    // buildNodes - creates a copy of a list of nodes, handling errors and deletion accordingly.
    template<typename T>
    typename SortedList<T>::Node* SortedList<T>::buildNodes(const SortedList& list) {
        if (list.headNode == nullptr) {
            return nullptr;
        }
        Node* headOfNodes = new Node(*list.headNode);
        try {
            // running on the given  list and makes copies
            Node* addingNode = list.headNode;
            Node* currNode = headOfNodes;
            while (addingNode->nextNode != nullptr) {
                currNode->nextNode = new Node(*addingNode->nextNode);
                addingNode = addingNode->nextNode;
                currNode = currNode->nextNode;
            }
            return headOfNodes;
        } catch (...) {
            // if caught error, deletes allocated memory and throws error again
            Node* currNode = headOfNodes;
            while (currNode->nextNode != nullptr) {
                currNode = currNode->nextNode;
                delete currNode->prevNode;
            }
            delete currNode;
            throw;
        }
    }
    // removeSpecificNode - logic of removing a specific node in a list.
    template<typename T>
    void SortedList<T>::removeSpecificNode(Node* node) {
        if (node == nullptr) {
            return;
        }
        // cases we remove node from the start
        if(node == this->headNode && node->nextNode == nullptr)
        {
            this->headNode = nullptr;
        }
        else if(node == this->headNode)
        {
            this->headNode = this->headNode->nextNode;
        }
        // case we remove last
        else if (node->nextNode == nullptr) {
            node->prevNode->nextNode = nullptr;
        }
        // case between 2 nodes
        else {
            linkTwoNodes(node->prevNode, node->nextNode);
        }
        delete node;
    }

    // -----------------------
    // Sortedlist Functions
    // -----------------------
    template<typename T>
    SortedList<T>::SortedList(const SortedList& list) : size(list.size) {
        this->headNode = buildNodes(list);
    }
    template<typename T>
    SortedList<T>::~SortedList() {
        Node* currNode = this->headNode;
        while (currNode != nullptr) {
            Node* tempNode = currNode->nextNode;
            delete currNode;
            currNode = tempNode;
        }
    }
    template<typename T>
    SortedList<T>& SortedList<T>::operator=(const SortedList& list) {
        if (this == &list) {
            return *this;
        }

        // init the list with newNodes, using buildNodes()
        Node* newListHead = buildNodes(list);

        // if copy creation successful - delete all Nodes and Tasks inside them
        Node* currNode = this->headNode;
        while (currNode != nullptr) {
            Node* temp = currNode->nextNode;
            delete currNode;
            currNode = temp;
        }

        // set the new ADDRES and VALUE
        this->headNode = newListHead;
        this->size = list.size;
        return *this;
    }
    template<typename T>
    SortedList<T>& SortedList<T>::insert(const T& task) {
        // here finding currNode that is smaller than the newNode.
        // we insert above currNode. S.T. (newNode->next = currNode)
        Node* newNode = new Node(task);

        // if list is empty
        if (this->headNode == nullptr) {
            this->headNode = newNode;
            this->size = this->size + 1;
            return *this;
        }

        Node* currNode = this->headNode;
        // using operator> of Task
        while (currNode != nullptr && currNode->data > task) {
            if (currNode->nextNode == nullptr)
            {
                // in case we are at the end of the list, insert it in the end
                linkTwoNodes(currNode, newNode);
                this->size = this->size + 1;
                return *this;
            }
            currNode = currNode->nextNode;
        }

        // if we need to insert in the beginning
        if (currNode == this->headNode) {
            this->headNode = newNode;
            linkTwoNodes(newNode, currNode);
        }
        // HERE currNode is pointing at "A".  and we know that INSERTED >= A
        else {
            Node* prevNode = currNode->prevNode;
            linkTwoNodes(prevNode, newNode);
            linkTwoNodes(newNode, currNode);
        }
        this->size = this->size + 1;
        return *this;
    }
    template<typename T>
    SortedList<T>& SortedList<T>::remove(const SortedList::ConstIterator& iter)
    {
        if(iter.pointingAtNode == nullptr)
        {
            return *this;
        }

        // finding the node thats wanted for deletion.
        Node* foundNode = this->headNode;
        while (foundNode != nullptr && foundNode != iter.pointingAtNode) {
            foundNode = foundNode->nextNode;
        }

        // if not found - no change to the list
        if(foundNode == nullptr)
        {
            return *this;
        }

        // if found - removes the node using removeSpecificNode()
        removeSpecificNode(foundNode);

        this->size = this->size - 1;
        return *this;
    }
    template<typename T>
    int SortedList<T>::length() const {
        return this->size;
    }
    template<typename T>
    const typename SortedList<T>::ConstIterator SortedList<T>::begin() const {
        const ConstIterator iter(this->headNode);
        return iter;

    }
    template<typename T>
    const typename SortedList<T>::ConstIterator SortedList<T>::end() const {
        // the default iter c'tor, hold pointingAtNode = nullptr
        // thats used for symbol for the end of the list.
        const ConstIterator iter;
        return iter;
    }
    template<typename T>
    template<typename Condition>
    typename SortedList<T>::SortedList SortedList<T>::filter(Condition functor) const {
        // given a Condition that eash task must pass.
        // run that condition on each node.
        Node* currNode = this->headNode;
        SortedList newList;
        while (currNode != nullptr) {
            if (functor(currNode->data)) {
                // if passed condition, insert the task to the new list
                newList.insert(currNode->data);
            }
            currNode=currNode->nextNode;
        }
        return newList;
    }
    template<typename T>
    template<typename Operation>
    typename SortedList<T>::SortedList SortedList<T>::apply(Operation functor) const {
        // given an Operation that eash task must go through.
        // run that operation on each node.
        Node* currNode = this->headNode;
        SortedList newList;
            while (currNode != nullptr) {
                newList.insert(functor(currNode->data));
                currNode=currNode->nextNode;
            }
        return newList;
    }

    // -----------------------
    // ConstIterator Functions
    // -----------------------
    template<typename T>
    SortedList<T>::ConstIterator::ConstIterator(const Node* node) : pointingAtNode(node) {}
    template<typename T>
    typename SortedList<T>::ConstIterator&
    SortedList<T>::ConstIterator::operator=(const ConstIterator& iter) {
        if (this == &iter) {
            return *this;
        }

        this->pointingAtNode = iter.pointingAtNode;
        return *this;
    }
    template<typename T>
    const T& SortedList<T>::ConstIterator::operator*() const {
        if (this->pointingAtNode == nullptr) {
            // error handling
            throw std::runtime_error("null iterator");
        }
        return this->pointingAtNode->data;
    }
    template<typename T>
    void SortedList<T>::ConstIterator::operator++() {
        if (this->pointingAtNode == nullptr) {
            // error handling
            throw std::out_of_range("you went too far bro!");
        }
        this->pointingAtNode = this->pointingAtNode->nextNode;
    }
    template<typename T>
    bool SortedList<T>::ConstIterator::operator!=(const ConstIterator& iter) const {
        if (this->pointingAtNode != iter.pointingAtNode) {
            return true;
        }
        return false;
    }

    // -----------------------
    // Node Functions
    // -----------------------
    template<typename T>
    SortedList<T>::Node::Node(const T& data) : data(data) {}
}


