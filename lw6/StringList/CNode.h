#pragma once
#include "common_libs.h"

class CNode
{
public:
	using NodePtr = std::shared_ptr<CNode>;

	CNode();
	CNode(const std::string& str);

	NodePtr GetNext() const;
	NodePtr GetPrev() const;
	std::string GetValue() const;
	bool GetIsFictitious() const;

	void SetNext(const NodePtr& ptr);
	void SetPrev(const NodePtr& ptr);
	void SetValue(const std::string& str);
	void SetIsFictitious(const bool& isFictitious);

	// ==
	friend bool operator==(const CNode& leftOperand, const CNode& rightOperand);

	// !=
	friend bool operator!=(const CNode& leftOperand, const CNode& rightOperand);

	// <
	friend bool operator<(const CNode& leftOperand, const CNode& rightOperand);

	// <=
	friend bool operator<=(const CNode& leftOperand, const CNode& rightOperand);

	// >
	friend bool operator>(const CNode& leftOperand, const CNode& rightOperand);

	// >=
	friend bool operator>=(const CNode& leftOperand, const CNode& rightOperand);

private:
	NodePtr m_next;
	NodePtr m_prev;
	std::string m_value;
	bool m_isFictitious;
};

using NodePtr = std::shared_ptr<CNode>;