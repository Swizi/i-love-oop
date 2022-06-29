#pragma once
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../CStringList.h"

SCENARIO("User has ability to create list")
{
	WHEN("User creates list")
	{
		CStringList list;

		THEN("List should be empty")
		{
			REQUIRE(list.GetSize() == 0);
			REQUIRE(list.IsEmpty() == true);
		}
	}
}

SCENARIO("User has ability to add items to list")
{
	WHEN("User adds to begin one item")
	{
		CStringList list;

		list.InsertToBegin("i like js");

		THEN("List should contain one element")
		{
			REQUIRE(list.GetSize() == 1);
			REQUIRE(list.IsEmpty() == false);
		}
	}

	WHEN("User adds to end one item")
	{
		CStringList list;

		list.InsertToEnd("i like js");

		THEN("List should contain one element")
		{
			REQUIRE(list.GetSize() == 1);
			REQUIRE(list.IsEmpty() == false);
		}
	}

	WHEN("User adds to begin and to end one element at a time")
	{
		CStringList list;

		list.InsertToBegin("i don't like js");
		list.InsertToEnd("i like js");

		THEN("List should contain two elements")
		{
			REQUIRE(list.GetSize() == 2);
			REQUIRE(list.IsEmpty() == false);
		}
	}

	WHEN("User adds to begin two elements")
	{
		CStringList list;

		list.InsertToBegin("i don't like js");
		list.InsertToBegin("i like js");

		THEN("List should contain two elements")
		{
			REQUIRE(list.GetSize() == 2);
			REQUIRE(list.IsEmpty() == false);
		}
	}

	WHEN("User adds to end two elements")
	{
		CStringList list;

		list.InsertToEnd("i don't like js");
		list.InsertToEnd("i like js");

		THEN("List should contain two elements")
		{
			REQUIRE(list.GetSize() == 2);
			REQUIRE(list.IsEmpty() == false);
		}
	}
}

SCENARIO("User has ability to get size of list")
{
	WHEN("User gets size of empty list")
	{
		CStringList emptyList;

		THEN("Result should be 0")
		{
			REQUIRE(emptyList.GetSize() == 0);
		}
	}

	WHEN("User gets size of not 1-list")
	{
		CStringList list;

		list.InsertToBegin("i like js");

		THEN("Result should should 1")
		{
			REQUIRE(list.GetSize() == 1);
		}
	}
}

SCENARIO("User has ability to check whether list is empty")
{
	WHEN("List is empty")
	{
		CStringList emptyList;

		THEN("Result should be true")
		{
			REQUIRE(emptyList.IsEmpty() == true);
		}
	}

	WHEN("List is not empty")
	{
		CStringList list;
		list.InsertToBegin("i like js");

		THEN("Result should be false")
		{
			REQUIRE(list.IsEmpty() == false);
		}
	}
}

SCENARIO("User has ability to clear list")
{
	WHEN("User clears empty list")
	{
		CStringList emptyList;

		emptyList.Clear();

		THEN("List should be empty")
		{
			REQUIRE(emptyList.GetSize() == 0);
			REQUIRE(emptyList.IsEmpty() == true);
		}
	}

	WHEN("User clears not empty list")
	{
		CStringList list;
		list.InsertToBegin("i like js");

		list.Clear();

		THEN("List should be empty")
		{
			REQUIRE(list.GetSize() == 0);
			REQUIRE(list.IsEmpty() == true);
		}
	}
}

SCENARIO("User has ability to add items to random index")
{
	WHEN("User updates first element in empty list")
	{
		CStringList list;

		CStringListIterator it = CStringListIterator(list.GetHead());

		THEN("Exception should be returned")
		{
			REQUIRE_THROWS(list.Update(it, "1"));
		}
	}

	WHEN("User updates first element")
	{
		CStringList list;
		list.InsertToBegin("i like js");
		CStringListIterator it = CStringListIterator(list.GetHead());

		list.Update(it, "i don't like js");

		THEN("First element should be updated")
		{
			REQUIRE(list.GetHead()->GetValue() == "i don't like js");
		}
	}

	WHEN("User updates second element")
	{
		CStringList list;
		list.InsertToBegin("1");
		list.InsertToBegin("2");
		list.InsertToBegin("3");
		CStringListIterator it = CStringListIterator(list.GetHead());
		it++;

		list.Update(it, "i don't like js");

		THEN("Second element should be updated")
		{
			REQUIRE(list.GetHead()->GetNext()->GetValue() == "i don't like js");
		}
	}

	WHEN("User updates last element")
	{
		CStringList list;
		list.InsertToBegin("1");
		list.InsertToBegin("2");
		CStringListIterator it = CStringListIterator(list.GetTail());

		list.Update(it, "i don't like js");

		THEN("First element should be updated")
		{
			REQUIRE(list.GetTail()->GetValue() == "i don't like js");
		}
	}
}

SCENARIO("User has ability to delete items in random indexes")
{
	WHEN("User delets first element in empty list")
	{
		CStringList list;
		CStringListIterator it = CStringListIterator(list.GetHead());

		THEN("Exception should be returned")
		{
			REQUIRE_THROWS(list.Delete(it));
		}
	}

	WHEN("User delets first element in 1-list")
	{
		CStringList list;
		list.InsertToBegin("i like js");
		CStringListIterator it = CStringListIterator(list.GetHead());

		list.Delete(it);

		THEN("List should be empty")
		{
			REQUIRE(list.GetSize() == 0);
			REQUIRE(list.IsEmpty() == true);
		}
	}

	WHEN("User delets first element in 2-list")
	{
		CStringList list;
		list.InsertToBegin("i like js");
		list.InsertToBegin("i like js");
		CStringListIterator it = CStringListIterator(list.GetHead());

		list.Delete(it);

		THEN("List should be 1-list")
		{
			REQUIRE(list.GetSize() == 1);
			REQUIRE(list.IsEmpty() == false);
		}
	}
}

SCENARIO("User has ability to use iterators from begin, end methods")
{
	WHEN("User uses begin method on 1-list")
	{
		CStringList list;
		list.InsertToBegin("i like js");
		auto it = list.begin();

		THEN("Iterator must point to first element")
		{
			REQUIRE(it->GetValue() == "i like js");
		}
	}

	WHEN("User uses begin method on 2-list with incremention")
	{
		CStringList list;
		list.InsertToBegin("2");
		list.InsertToBegin("1");
		auto it = list.begin();
		it++;

		THEN("Iterator must point to second element")
		{
			REQUIRE(it->GetValue() == "2");
		}
	}

	WHEN("User uses end method on 1-list")
	{
		CStringList list;
		list.InsertToBegin("i like js");
		auto it = list.end();

		THEN("Iterator should not be pointed to first element")
		{
			REQUIRE(it->GetValue() != "i like js");
		}
	}

	WHEN("User tries to change element with begin method")
	{
		CStringList list;
		list.InsertToBegin("i like js");
		auto it = list.begin();
		it[0] = CNode("i don't like js");

		THEN("Iterator should change value of first element")
		{
			REQUIRE(list.GetHead()->GetValue() == "i don't like js");
		}
	}

	WHEN("User tries to go beyond the boundaries of the list")
	{
		CStringList list;
		list.InsertToBegin("i like js");
		auto it = list.begin();
		
		THEN("Exception should be returned")
		{
			it++;
			REQUIRE_THROWS(it++);
		}

		THEN("Exception should be returned")
		{
			REQUIRE_THROWS(it--);
		}

		THEN("Exception should not be returned")
		{
			REQUIRE(it[2] == *list.GetHead().get());
		}
	}
}

SCENARIO("User has ability to use iterators with stl algorithms")
{
	WHEN("Use for_each function from stl with string's list to compose all elements")
	{
		std::ostringstream oss;
		CStringList list;
		list.InsertToEnd("1");
		list.InsertToEnd("2");
		list.InsertToEnd("3");

		std::for_each(list.begin(), list.end(), [&](CNode& el)
		{
			oss << el.GetValue();
		});

		THEN("String should contain all elements of list in direct order")
		{
			REQUIRE(oss.str() == "123");
		}
	}
}

SCENARIO("User has ability to use iterators with range-based for")
{
	WHEN("Use range-based for on list to compose all to one stream")
	{
		std::ostringstream oss;
		CStringList list;
		list.InsertToEnd("1");
		list.InsertToEnd("2");
		list.InsertToEnd("3");

		for (const auto& el : list)
		{
			oss << el.GetValue();
		}

		THEN("Stream should contain all elements from list")
		{
			REQUIRE(oss.str() == "123");
		}
	}

	WHEN("Use range-based for on empty list")
	{
		std::ostringstream oss;
		CStringList list;

		for (const auto& el : list)
		{
			oss << el.GetValue();
		}

		THEN("Stream should be empty")
		{
			REQUIRE(oss.str() == "");
		}
	}

}

SCENARIO("User has ability to use reverse iterators")
{
	WHEN("Use for_each function from stl with string's list to compose all elements")
	{
		std::ostringstream oss;
		CStringList list;
		list.InsertToEnd("1");
		list.InsertToEnd("2");
		list.InsertToEnd("3");

		std::for_each(list.rbegin(), list.rend(), [&](CNode& el)
			{
				oss << el.GetValue();
			});

		THEN("String should contain all elements of list in direct order")
		{
			REQUIRE(oss.str() == "321");
		}
	}
}

SCENARIO("User has ability to use move constructor and move assignment operator")
{
	GIVEN("Move constructor")
	{
		WHEN("Move exactly from constructor")
		{
			CStringList list(std::move(CStringList({"1", "2"})));

			THEN("List should contain list from moved list")
			{
				REQUIRE(list.GetSize() == 2);
				REQUIRE(list.GetHead()->GetValue() == "1");
				REQUIRE(list.GetTail()->GetValue() == "2");
			}
		}

		WHEN("Move from variable")
		{
			CStringList sourceList({ "i love JS!" });
			CStringList receiveList(std::move(sourceList));

			THEN("Receive list should contain value and source list should contain no value")
			{
				REQUIRE(sourceList.GetSize() == 0);
				REQUIRE(receiveList.GetSize() == 1);
			}
		}

		WHEN("Move empty list")
		{
			CStringList list(std::move(CStringList()));

			THEN("List should be empty")
			{
				REQUIRE(list.GetSize() == 0);
			}
		}
	}

	GIVEN("Move assignment operation")
	{
		WHEN("Move from variable")
		{
			CStringList sourceList({ "i love JS!" });
			CStringList receiveList({ "js is shit" });

			receiveList = std::move(sourceList);

			THEN("Receive list should contain value and source list should contain no value")
			{
				REQUIRE(sourceList.GetSize() == 0);
				REQUIRE(receiveList.GetSize() == 1);
			}
		}

		WHEN("Move empty list")
		{
			CStringList sourceList;
			CStringList receiveList({ "js is shit" });

			receiveList = std::move(sourceList);

			THEN("Receive list should contain no value and source list should contain no value")
			{
				REQUIRE(sourceList.GetSize() == 0);
				REQUIRE(receiveList.GetSize() == 0);
			}
		}
	}
}

SCENARIO("User has ability to use copy constructor")
{
	WHEN("User creates filled list through copying")
	{
		CStringList sourceList{ "1", "2", "3" };
		CStringList hostList = sourceList;

		THEN("List's data should be equals to copied data")
		{
			REQUIRE(hostList.GetHead()->GetValue() == "1");
			REQUIRE(hostList.GetHead()->GetNext()->GetValue() == "2");
			REQUIRE(hostList.GetTail()->GetValue() == "3");
		}

		THEN("List's data should be equals to copied data's length")
		{
			REQUIRE(hostList.GetSize() == 3);
		}
	}

	WHEN("User creates empty list through copying")
	{
		CStringList sourceList;
		CStringList hostList = sourceList;

		THEN("List's data should be equals to copied data's length")
		{
			REQUIRE(hostList.GetSize() == 0);
		}
	}
}