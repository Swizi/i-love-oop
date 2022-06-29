#include "CStringList.h"

CStringList::CStringList()
	: m_head(std::make_shared<CNode>(CNode("")))
	, m_tail(m_head)
	, m_size(0)
{
    m_head->SetIsFictitious(true);
    m_head->SetNext(m_head);
    m_head->SetPrev(m_head);
}

CStringList::CStringList(const CStringList& other)
    :CStringList()
{
    std::for_each(other.cbegin(), other.cend(), [&](const CNode& el)
    {
            this->InsertToEnd(el.GetValue());
    });
}

CStringList::CStringList(CStringList&& other) noexcept
    : m_head(other.GetHead() ? other.GetHead()->GetPrev() : other.GetHead())
    , m_tail(other.GetTail())
    , m_size(other.GetSize())
{
    other.SetHead(nullptr);
    other.SetTail(nullptr);
    other.SetSize(0);
}

CStringList& CStringList::operator=(const CStringList& other)
{
    *this = CStringList(other);

    return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{
    m_head = other.GetHead()->GetPrev();
    m_tail = other.GetTail();
    m_size = other.GetSize();
    other.SetHead(nullptr);
    other.SetTail(nullptr);
    other.SetSize(0);
    
    return *this;
}

CStringList::CStringList(std::initializer_list<std::string> initVector)
    :CStringList()
{
    std::for_each(initVector.begin(), initVector.end(), [&](const std::string& el)
    {
            this->InsertToEnd(el);
    });
}

void CStringList::InsertToBegin(const std::string& str)
{
    if (m_head == nullptr)
    {
        *this = CStringList();
    }
    CNode newNode = CNode(str);
    NodePtr newNodePtr = std::make_shared<CNode>(newNode);
    if (m_head == m_tail)
    {
        m_tail = newNodePtr;
    }
    (*newNodePtr).SetPrev(m_head);
    (*newNodePtr).SetNext(m_head->GetNext());
    (*m_head->GetNext()).SetPrev(newNodePtr);
    (*m_head).SetNext(newNodePtr);
    m_size++;
}

void CStringList::InsertToEnd(const std::string& str)
{
    if (m_head == nullptr)
    {
        *this = CStringList();
    }
    CNode newNode = CNode(str);
    NodePtr newNodePtr = std::make_shared<CNode>(newNode);
    (*newNodePtr).SetNext(m_head);
    (*m_head).SetPrev(newNodePtr);
    (*newNodePtr).SetPrev(m_tail);
    (*m_tail).SetNext(newNodePtr);
    m_tail = newNodePtr;
    m_size++;
}

size_t CStringList::GetSize() const
{
    return m_size;
}

bool CStringList::IsEmpty() const
{
    return m_size == 0;
}

void CStringList::Clear()
{
    while (m_size != 0)
    {
        m_head = (*m_head).GetNext();
        m_size--;
    }
}

void CStringList::Update(CStringListIterator& it, const std::string& str)
{
    if (it == nullptr)
    {
        throw std::out_of_range("Iterator is not pointing to any element");
    }
    if (it == m_head)
    {
        throw std::logic_error("Can not update end of list");
    }
    it->SetValue(str);
}

void CStringList::Delete(CStringListIterator& it)
{
    if (it == nullptr)
    {
        throw std::out_of_range("Iterator is not pointing to any element");
    }
    if (it == m_head)
    {
        throw std::logic_error("Can not delete end of list");
    }
    m_size--;
    it->GetPrev()->SetNext(it->GetNext());
    it->GetNext()->SetPrev(it->GetPrev());
}

NodePtr CStringList::GetHead() const
{
    return m_head != nullptr ? m_head->GetNext() : m_head;
}

NodePtr CStringList::GetTail() const
{
    return m_tail;
}

void CStringList::SetHead(const NodePtr head)
{
    m_head = head;
}

void CStringList::SetTail(const NodePtr tail)
{
    m_tail = tail;
}

void CStringList::SetSize(const size_t size)
{
    m_size = size;
}

// CStringListIterator

CStringListIterator CStringList::begin() const
{
    if (m_head == nullptr)
    {
        return m_head;
    }

    return m_head.get()->GetNext();
}

CStringListIterator CStringList::end() const
{
    if (m_head == nullptr)
    {
        throw m_head;
    }

    return m_head.get();
}

std::reverse_iterator<CStringListIterator> CStringList::rbegin() const
{
    return std::make_reverse_iterator(end());
}

std::reverse_iterator<CStringListIterator> CStringList::rend() const
{
    return std::make_reverse_iterator(begin());
}

// CStringListConstIterator

CStringListConstIterator CStringList::cbegin() const
{
    if (m_head == nullptr)
    {
        return m_head;
    }

    return m_head.get()->GetNext();
}
CStringListConstIterator CStringList::cend() const
{
    if (m_head == nullptr)
    {
        return m_head;
    }

    return m_head.get();
}

std::reverse_iterator<CStringListConstIterator> CStringList::crbegin() const
{
    return std::make_reverse_iterator(cend());
}

std::reverse_iterator<CStringListConstIterator> CStringList::crend() const
{
    return std::make_reverse_iterator(cbegin());
}