#include "CHttpUrl.h"

// Default constants

const Protocol DEFAULT_PROTOCOL = Protocol::HTTP;
const unsigned short DEFAULT_PORT = 80;
const std::map<const Protocol, const unsigned short> defaultPorts =
{
	{Protocol::HTTP, 80},
	{Protocol::HTTPS, 443}
};
const std::string DEFAULT_DOCUMENT = "/index.html";
const unsigned short MIN_AVAILABLE_PORT = 10;
const unsigned short MAX_AVAILABLE_PORT = 65535;

// Regexps

// TODO: URL = Protocol + Domain + ...
// Url
const boost::regex urlRegexp("(?:(?:(?:http[s]?):)?\\/\\/)(?:(?!(?:10|127)(?:\\.\\d{1,3}){3})(?!(?:169\\.254|192\\.168)(?:\\.\\d{1,3}){2})(?!172\\.(?:1[6-9]|2\\d|3[0-1])(?:\\.\\d{1,3}){2})(?:[1-9]\\d?|1\\d\\d|2[01]\\d|22[0-3])(?:\\.(?:1?\\d{1,2}|2[0-4]\\d|25[0-5])){2}(?:\\.(?:[1-9]\\d?|1\\d\\d|2[0-4]\\d|25[0-4]))|(?:(?:[a-z0-9\\u00a1-\\uffff][a-z0-9\\u00a1-\\uffff_-]{0,62})?[a-z0-9\\u00a1-\\uffff]\\.)+(?:[a-z\\u00a1-\\uffff]{2,}\\.?))(?:[/?#]\\S*)?(?:[/?#]\\S*)?", boost::regex_constants::ECMAScript);
// Protocols
const boost::regex protocolRegexp("(?:(?:(?:http[s]?):)?\\/\\/)", boost::regex_constants::ECMAScript);
// Domain
const boost::regex domainRegexp("(?:(?!(?:10|127)(?:\\.\\d{1,3}){3})(?!(?:169\\.254|192\\.168)(?:\\.\\d{1,3}){2})(?!172\\.(?:1[6-9]|2\\d|3[0-1])(?:\\.\\d{1,3}){2})(?:[1-9]\\d?|1\\d\\d|2[01]\\d|22[0-3])(?:\\.(?:1?\\d{1,2}|2[0-4]\\d|25[0-5])){2}(?:\\.(?:[1-9]\\d?|1\\d\\d|2[0-4]\\d|25[0-4]))|(?:(?:[a-z0-9\\u00a1-\\uffff][a-z0-9\\u00a1-\\uffff_-]{0,62})?[a-z0-9\\u00a1-\\uffff]\\.)+(?:[a-z\\u00a1-\\uffff]{2,}\\.?))", boost::regex_constants::ECMAScript);
const boost::regex protocolDomainRegexp("(?:(?:(?:http[s]?):)?\\/\\/)(?:(?!(?:10|127)(?:\\.\\d{1,3}){3})(?!(?:169\\.254|192\\.168)(?:\\.\\d{1,3}){2})(?!172\\.(?:1[6-9]|2\\d|3[0-1])(?:\\.\\d{1,3}){2})(?:[1-9]\\d?|1\\d\\d|2[01]\\d|22[0-3])(?:\\.(?:1?\\d{1,2}|2[0-4]\\d|25[0-5])){2}(?:\\.(?:[1-9]\\d?|1\\d\\d|2[0-4]\\d|25[0-4]))|(?:(?:[a-z0-9\\u00a1-\\uffff][a-z0-9\\u00a1-\\uffff_-]{0,62})?[a-z0-9\\u00a1-\\uffff]\\.)+(?:[a-z\\u00a1-\\uffff]{2,}\\.?))", boost::regex_constants::ECMAScript);
// Port
const boost::regex portRegexp("(?::-?\\d{1,5})", boost::regex_constants::ECMAScript);
const boost::regex protocolDomainPortRegexp("(?:(?:(?:http[s]?):)?\\/\\/)(?:(?!(?:10|127)(?:\\.\\d{1,3}){3})(?!(?:169\\.254|192\\.168)(?:\\.\\d{1,3}){2})(?!172\\.(?:1[6-9]|2\\d|3[0-1])(?:\\.\\d{1,3}){2})(?:[1-9]\\d?|1\\d\\d|2[01]\\d|22[0-3])(?:\\.(?:1?\\d{1,2}|2[0-4]\\d|25[0-5])){2}(?:\\.(?:[1-9]\\d?|1\\d\\d|2[0-4]\\d|25[0-4]))|(?:(?:[a-z0-9\\u00a1-\\uffff][a-z0-9\\u00a1-\\uffff_-]{0,62})?[a-z0-9\\u00a1-\\uffff]\\.)+(?:[a-z\\u00a1-\\uffff]{2,}\\.?))(?::\\d{2,5})?", boost::regex_constants::ECMAScript);
// Document
const boost::regex documentRegexp("(?:[/][a-z0-9@/\\-._~!$&'()*+,;=:@%]*)", boost::regex_constants::ECMAScript);


std::string ParseDocument(const std::string& url)
{
	std::string document = DEFAULT_DOCUMENT;
	boost::smatch documentSm;
	boost::smatch protocolDomainPortSm;

	boost::regex_search(url, protocolDomainPortSm, protocolDomainPortRegexp);
	const std::string strBeforeDocument = std::string(protocolDomainPortSm[0].first, protocolDomainPortSm[0].second);
	const std::string strAfterPort = protocolDomainPortSm.suffix();
	const bool isDocumentExists = boost::regex_search(strAfterPort, documentSm, documentRegexp);
	if (!isDocumentExists)
	{
		return document;
	}
	if (documentSm.size() > 1)
	{
		throw CUrlParsingError("Number of documents in url should be equals to one");
	}
	if (documentSm.size() == 1)
	{
		document = std::string(documentSm[0].first, documentSm[0].second);
	}
	if (document == "/")
	{
		document = DEFAULT_DOCUMENT;
	}

	return document;
}

unsigned short ParsePort(const std::string& url, Protocol protocol)
{
	unsigned short port = defaultPorts.count(protocol) ? defaultPorts.at(protocol) : DEFAULT_PORT;
	boost::smatch portSm;

	const bool isPortExists = boost::regex_search(url, portSm, portRegexp);
	if (!isPortExists)
	{
		return port;
	}
	if (portSm.size() > 1)
	{
		throw CUrlParsingError("Number of ports in url should be equals to one");
	}
	// TODO: portSm.size() == 1 не нужен
	if (portSm.size() == 1)
	{
		const std::string portStr = std::string(portSm[0].first+1, portSm[0].second);
		if (portStr.size() != 0)
		{
			// TODO: обрабатывать исключение stoi
			const int portNum = std::stoi(portStr.c_str());
			if (portNum < 0)
			{
				throw CUrlParsingError("Port can not be negative");
			}
			if (portNum < MIN_AVAILABLE_PORT)
			{
				throw CUrlParsingError("Port should be greater than 9");
			}
			if (portNum > MAX_AVAILABLE_PORT)
			{
				throw CUrlParsingError("Port can not be greater than 65535");
			}
			port = portNum;
		}
	}

	return port;
}

std::string ParseDomain(const std::string& url)
{
	std::string domain = "";
	boost::smatch domainSm;
	boost::smatch portSm;

	const bool isDomainExists = boost::regex_search(url, domainSm, domainRegexp);
	if (!isDomainExists)
	{
		throw CUrlParsingError("Domain is incorrect");
	}
	if (domainSm.size() > 1)
	{
		throw CUrlParsingError("Number of domains in url should be equals to one");
	}
	std::string str = std::string(domainSm[0].first, domainSm[0].second);
	// TODO: вынести offset в функцию
	size_t offset = 0;
	if (boost::regex_search(str, portSm, portRegexp))
	{
		offset = std::string(portSm[0].first, portSm[0].second).size();
	}
	domain = std::string(str.begin(), str.end() - offset);

	return domain;
}

Protocol ParseProtocol(const std::string& url)
{
	Protocol protocol = DEFAULT_PROTOCOL;
	boost::smatch protocolSm;
	boost::smatch httpProtocolSm;
	bool isProtocolExists = boost::regex_search(url, protocolSm, protocolRegexp);
	if (!isProtocolExists)
	{
		throw CUrlParsingError("Protocol is incorrect");
	}
	// if !isProtocolExists -> return
	if (isProtocolExists)
	{
		// protocolSm.size() != 1 -> throw
		if (protocolSm.size() == 1)
		{
			if (std::string(protocolSm[0].first, protocolSm[0].second) != "http://" && std::string(protocolSm[0].first, protocolSm[0].second) != "https://")
			{
				throw CUrlParsingError("Incorrect protocol name");
			}
			if (std::string(protocolSm[0].first, protocolSm[0].second) == "https://")
			{
				protocol = Protocol::HTTPS;
			}
		}
		else
		{
			throw CUrlParsingError("Number of protocols in url must be equals to one");
		}
	}

	return protocol;
}

bool IsDomainValid(const std::string& domain)
{
	boost::smatch domainSm;
	
	return boost::regex_match(domain, domainSm, domainRegexp);
}

bool IsDocumentValid(const std::string& document)
{
	std::string documentStr;
	if (document == "")
	{
		return true;
	}
	if (document[0] != '/')
	{
		documentStr = "/";
	}
	documentStr.append(document);
	boost::smatch documentSm;

	return boost::regex_match(documentStr, documentSm, documentRegexp);
}

bool IsProtocolValid(const Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
	case Protocol::HTTPS:
		return true;
	default:
		return false;
	}
}
CHttpUrl::CHttpUrl(std::string const& url)
	: m_protocol(ParseProtocol(lower(url)))
	, m_domain(ParseDomain(lower(url)))
	, m_port(ParsePort(lower(url), m_protocol))
	, m_document(ParseDocument(lower(url)))
{
	boost::smatch urlSm;
	if (!boost::regex_search(url, urlSm, urlRegexp))
	{
		throw CUrlParsingError("Incorrect order of url members");
	}
}

CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol)
{
	if (!IsProtocolValid(protocol))
	{
		throw std::invalid_argument("Protocol is invalid");
	}
	if (!IsDomainValid(domain))
	{
		throw std::invalid_argument("Domain is invalid");
	}
	if (!IsDocumentValid(document))
	{
		throw std::invalid_argument("Document is invalid");
	}

	m_protocol = protocol;
	m_domain = domain;
	m_port = defaultPorts.at(protocol);
	if (document == "/" || document == "")
	{
		m_document = DEFAULT_DOCUMENT;
	}
	else
	{
		if (document[0] != '/')
		{
			m_document = "/";
		}
		m_document.append(document);
	}
}

CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port) :
	CHttpUrl(domain, document, protocol)
{
	m_port = port;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

std::string CHttpUrl::GetURL() const
{
	std::string url;

	// Protocol
	switch (m_protocol)
	{
	case Protocol::HTTP:
		url.append("http://");
		break;
	case Protocol::HTTPS:
		url.append("https://");
		break;
	default:
		url.append("http://");
		break;
	}
	// Domain
	url.append(m_domain);
	// Port
	if (m_port != defaultPorts.at(Protocol::HTTP) && m_port != defaultPorts.at(Protocol::HTTPS))
	{
		url.append(":");
		url.append(std::to_string(m_port));
	}
	// Document
	url.append(m_document);

	return url;
}