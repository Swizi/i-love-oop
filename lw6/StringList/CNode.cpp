#include "CNode.h"

CNode::CNode()
	: m_prev(nullptr)
	, m_next(nullptr)
	, m_value("")
	, m_isFictitious(false)
{
}

CNode::CNode(const std::string& str)
	: m_prev(nullptr)
	, m_next(nullptr)
	, m_value(str)
	, m_isFictitious(false)
{
}

NodePtr CNode::GetNext() const
{
	return m_next;
}

NodePtr CNode::GetPrev() const
{
	return m_prev;
}

std::string CNode::GetValue() const
{
	return m_value;
}

bool CNode::GetIsFictitious() const
{
	return m_isFictitious;
}

void CNode::SetNext(const NodePtr& ptr)
{
	m_next = ptr;
}

void CNode::SetPrev(const NodePtr& ptr)
{
	m_prev = ptr;
}

void CNode::SetValue(const std::string& str)
{
	m_value = str;
}

void CNode::SetIsFictitious(const bool& isFictitious)
{
	m_isFictitious = isFictitious;
}

bool operator==(const CNode& leftOperand, const CNode& rightOperand)
{
	return leftOperand.GetValue() == rightOperand.GetValue();
}

// !=
bool operator!=(const CNode& leftOperand, const CNode& rightOperand)
{
	return leftOperand.GetValue() != rightOperand.GetValue();
}

// <
bool operator<(const CNode& leftOperand, const CNode& rightOperand)
{
	return leftOperand.GetValue() < rightOperand.GetValue();
}

// <=
bool operator<=(const CNode& leftOperand, const CNode& rightOperand)
{
	return leftOperand.GetValue() <= rightOperand.GetValue();
}

// >
bool operator>(const CNode& leftOperand, const CNode& rightOperand)
{
	return leftOperand.GetValue() > rightOperand.GetValue();
}

// >=
bool operator>=(const CNode& leftOperand, const CNode& rightOperand)
{
	return leftOperand.GetValue() >= rightOperand.GetValue();
}