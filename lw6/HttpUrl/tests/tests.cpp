#pragma once
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../CHttpUrl.h"

SCENARIO("User has ability to create urls with protocol")
{
	WHEN("User creates url without protocol")
	{
		THEN("Exception should be returned")
		{
			REQUIRE_THROWS(CHttpUrl("google.com"));
		}
	}

	WHEN("User creates url with http protocol")
	{
		CHttpUrl url = CHttpUrl("http://google.com");

		THEN("Http protocol should be applied")
		{
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
		}
	}

	WHEN("User creates url with https protocol")
	{
		CHttpUrl url = CHttpUrl("https://google.com");

		THEN("Https protocol should be applied")
		{
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
	}

	WHEN("User creates url with wrong protocol name")
	{
		THEN("Exception should be returned")
		{
			REQUIRE_THROWS(CHttpUrl("ftp://google.com"));
		}
	}

	WHEN("User creates url with wrong protocol delimiter")
	{
		THEN("Exception should be returned")
		{
			REQUIRE_THROWS(CHttpUrl("http:\google.com"));
			REQUIRE_THROWS(CHttpUrl("http:/google.com"));
			REQUIRE_THROWS(CHttpUrl("http:google.com"));
		}
	}
}

SCENARIO("User has ability to create urls with domain")
{
	WHEN("User creates url with domain")
	{
		CHttpUrl url = CHttpUrl("http://google.com");

		THEN("Domain should contain domain name")
		{
			REQUIRE(url.GetDomain() == "google.com");
		}
	}

	WHEN("User creates url with ip")
	{
		CHttpUrl url = CHttpUrl("http://128.0.0.1:80");

		THEN("Domain should containt domain name")
		{
			REQUIRE(url.GetDomain() == "128.0.0.1");
		}
	}

	WHEN("User creates url with domain and port")
	{
		CHttpUrl url = CHttpUrl("http://google.com:80/index.html");

		THEN("Domain should containt domain name")
		{
			REQUIRE(url.GetDomain() == "google.com");
		}
	}

	WHEN("User creates url with unicode domain")
	{
		CHttpUrl url = CHttpUrl("http://✪df.ws/123");

		THEN("Domain should contain unicode symbols")
		{
			REQUIRE(url.GetDomain() == "✪df.ws");
		}
	}

	WHEN("User creates url that contains only digits")
	{
		CHttpUrl url = CHttpUrl("http://1337.net");

		THEN("Domain should be successfully saved")
		{
			REQUIRE(url.GetDomain() == "1337.net");
		}
	}

	WHEN("User creates url with domain, that contains hyphen")
	{
		CHttpUrl url = CHttpUrl("http://a.b-c.de");

		THEN("Domain should be successfully saved")
		{
			REQUIRE(url.GetDomain() == "a.b-c.de");
		}
	}

	WHEN("User creates url without domain")
	{
		THEN("Exception should be returned")
		{
			REQUIRE_THROWS(CHttpUrl("http://"));
		}
	}

	WHEN("User creates url with domain, that contains hyphen at the start")
	{
		THEN("Exception should be returned")
		{
			REQUIRE_THROWS(CHttpUrl("http://-error-.invalid/"));
		}
	}

	WHEN("User creates url with domain, that contains incorrect ip-address")
	{
		THEN("Exception should be returned")
		{
			REQUIRE_THROWS(CHttpUrl("http://0.0.0.0"));
		}
	}

	WHEN("User creates url with incorrect TLD")
	{
		THEN("Exception should be returned")
		{
			REQUIRE_THROWS(CHttpUrl("http://g.c"));
		}
	}
}

SCENARIO("User has ability to create urls with port")
{
	WHEN("User creates url without port")
	{
		CHttpUrl url = CHttpUrl("http://google.com");

		THEN("Port should be equals to default port")
		{
			REQUIRE(url.GetPort() == 80);
		}
	}

	WHEN("User creates url with default port")
	{
		CHttpUrl url = CHttpUrl("http://google.com:80");

		THEN("Port should be equals to default port")
		{
			REQUIRE(url.GetPort() == 80);
		}
	}

	WHEN("User creates url with specific port(123)")
	{
		CHttpUrl url = CHttpUrl("http://google.com:123");

		THEN("Exception should be returned")
		{
			REQUIRE(url.GetPort() == 123);
		}
	}

	WHEN("User creates url with port, greater than available(65535)")
	{
		THEN("Exception should be returned")
		{
			REQUIRE_THROWS(CHttpUrl("http://google.com:65536"));
		}
	}

	WHEN("User creates url with port, less than 10")
	{
		THEN("Exception should be returned")
		{
			REQUIRE_THROWS(CHttpUrl("http://google.com:6"));
		}
	}

	WHEN("User creates url with negative port")
	{
		THEN("Exception should be returned")
		{
			REQUIRE_THROWS(CHttpUrl("http://google.com:-80"));
		}
	}
}

SCENARIO("User has ability to create urls with document")
{
	WHEN("User creates url with default document")
	{
		CHttpUrl url = CHttpUrl("http://google.com/index.html");

		THEN("Document should be default")
		{
			REQUIRE(url.GetDocument() == "/index.html");
		}
	}

	WHEN("User creates url with nested document")
	{
		CHttpUrl url = CHttpUrl("http://google.com/catalog/cart.html");

		THEN("Document should contain absolute path")
		{
			REQUIRE(url.GetDocument() == "/catalog/cart.html");
		}
	}

	WHEN("User creates url without document")
	{
		CHttpUrl url1 = CHttpUrl("http://google.com/");
		CHttpUrl url2 = CHttpUrl("http://google.com");

		THEN("Document should be default")
		{
			REQUIRE(url1.GetDocument() == "/index.html");
			REQUIRE(url2.GetDocument() == "/index.html");
		}
	}

	WHEN("User creates url with / at the end")
	{
		CHttpUrl url = CHttpUrl("http://foo.com/blah_blah/");

		THEN("Document should be successfully saved")
		{
			REQUIRE(url.GetDocument() == "/blah_blah/");
		}
	}

	WHEN("User creates url with brackets")
	{
		CHttpUrl url = CHttpUrl("http://foo.com/blah_blah_(wikipedia)");

		THEN("Document should be successfully saved")
		{
			REQUIRE(url.GetDocument() == "/blah_blah_(wikipedia)");
		}
	}

	WHEN("User creates url with document with query string")
	{
		CHttpUrl url = CHttpUrl("http://google.com?q=how%20to%20make%20programm");

		THEN("Document should not contain query string")
		{
			REQUIRE(url.GetDocument() == "/index.html");
		}
	}

	WHEN("User creates url with document with id")
	{
		CHttpUrl url = CHttpUrl("http://google.com#block1");

		THEN("Document should not contain id")
		{
			REQUIRE(url.GetDocument() == "/index.html");
		}
	}

	WHEN("User creates url with document with id and query string")
	{
		CHttpUrl url = CHttpUrl("http://google.com/search.html?q=vkontakte&utm_source=yandex#block1");

		THEN("Document should not contain id and query string")
		{
			REQUIRE(url.GetDocument() == "/search.html");
		}
	}
}

SCENARIO("User has ability to get string view of url after creation")
{
	WHEN("Get url of created url")
	{
		CHttpUrl url = CHttpUrl("http://google.com:80/catalog/cart.html");

		THEN("Data should be equals to source data")
		{
			REQUIRE(url.GetURL() == "http://google.com/catalog/cart.html");
		}
	}
}

SCENARIO("User has ability to create urls with specific parameters")
{
	WHEN("User creates url with specific parameter")
	{
		CHttpUrl url1 = CHttpUrl("vk.com", "");
		CHttpUrl url2 = CHttpUrl("vk.com", "feed", Protocol::HTTPS);
		CHttpUrl url3 = CHttpUrl("vk.com", "/feed", Protocol::HTTP);
		CHttpUrl url4 = CHttpUrl("vk.com", "/feed", Protocol::HTTP, 80);
		CHttpUrl url5 = CHttpUrl("vk.com", "/feed", Protocol::HTTPS, 443);

		THEN("Url should be successfully created")
		{
			REQUIRE(url1.GetURL() == "http://vk.com/index.html");
			REQUIRE(url2.GetURL() == "https://vk.com/feed");
			REQUIRE(url3.GetURL() == "http://vk.com/feed");
			REQUIRE(url4.GetURL() == "http://vk.com/feed");
			REQUIRE(url5.GetURL() == "https://vk.com/feed");
		}
	}
}

// TODO: Добавить некорректные тесты