#pragma once
#include "CStringListIterator.h"
#include "CStringListConstIterator.h"

class CStringList
{
public:
    CStringList();
    CStringList(std::initializer_list<std::string> initVector);
    CStringList(const CStringList& other);
    CStringList(CStringList&& other) noexcept;

    void InsertToBegin(const std::string& str);
    void InsertToEnd(const std::string& str);
    bool IsEmpty() const;
    void Clear();
    void Update(CStringListIterator& it, const std::string& str);
    void Delete(CStringListIterator& it);

    CStringList& operator=(const CStringList& other);
    CStringList& operator=(CStringList&& other) noexcept;

    NodePtr GetHead() const;
    NodePtr GetTail() const;
    size_t GetSize() const;

    void SetHead(const NodePtr head);
    void SetTail(const NodePtr tail);
    void SetSize(const size_t size);

    // CStringListIterator
    CStringListIterator begin() const;
    CStringListIterator end() const;
    std::reverse_iterator<CStringListIterator> rbegin() const;
    std::reverse_iterator<CStringListIterator> rend() const;

    // CStringListConstIterator
    CStringListConstIterator cbegin() const;
    CStringListConstIterator cend() const;
    std::reverse_iterator<CStringListConstIterator> crbegin() const;
    std::reverse_iterator<CStringListConstIterator> crend() const;
private:
    NodePtr m_head; // Fictious head
    NodePtr m_tail;
    size_t m_size;
};