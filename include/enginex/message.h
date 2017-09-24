#pragma once
#include <string>
#include <vector>
#include <enginex/utils.h>


namespace enginex{

class Message
{
public:
	using HeaderValues = std::vector<std::string>;
public:
	/// Get the HTTP version string
	/**
	* @return The version string for this parser
	*/
	std::string const & GetVersion() const {
		return version;
	}

	/// Set HTTP parser Version
	/**
	* Input should be in format: HTTP/x.y where x and y are positive integers.
	* @todo Does this method need any validation?
	*
	* @param [in] version The value to set the HTTP version to.
	*/
	void SetVersion(std::string const & value) {
		version = value;
	}

	/// Get the value of an HTTP header
	/**
	* @todo Make this method case insensitive.
	*
	* @param [in] key The name/key of the header to get.
	* @return The value associated with the given HTTP header key.
	*/
	std::string const & GetHeader(std::string const & key) const;
	HeaderValues  GetHeaders(std::string const & key) const;
	CiMap const & GetHeaders()const;
	/// Set a value for an HTTP header, replacing an existing value
	/**
	* This method will set the value of the HTTP header `key` with the
	* indicated value. If a header with the name `key` already exists, `val`
	* will replace the existing value.
	*
	* @todo Make this method case insensitive.
	* @todo Should there be any restrictions on which keys are allowed?
	* @todo Exception free varient
	*
	* @see AppendHeader
	*
	* @param [in] key The name/key of the header to append to.
	* @param [in] val The value to append.
	*/
	void SetHeader(std::string const & key, std::string const & val);
	/// Append a value to an existing HTTP header
	/**
	* This method will set the value of the HTTP header `key` with the
	* indicated value. If a header with the name `key` already exists, `val`
	* will be appended to the existing value.
	*
	* @todo Make this method case insensitive.
	* @todo Should there be any restrictions on which keys are allowed?
	* @todo Exception free varient
	*
	* @see ReplaceHeader
	*
	* @param [in] key The name/key of the header to append to.
	* @param [in] val The value to append.
	*/
	void AppendHeader(std::string const & key, std::string const & val);


	/// Remove a header from the parser
	/**
	* Removes the header entirely from the parser. This is different than
	* setting the value of the header to blank.
	*
	* @todo Make this method case insensitive.
	*
	* @param [in] key The name/key of the header to remove.
	*/
	void RemoveHeader(std::string const & key);

	/// Get HTTP body
	/**
	* Gets the body of the HTTP object
	*
	* @return The body of the HTTP message.
	*/
	std::string const & GetBody() const {
		return body;
	}

	/// Set body content
	/**
	* Set the body content of the HTTP response to the parameter string. Note
	* set_body will also set the Content-Length HTTP header to the appropriate
	* value. If you want the Content-Length header to be something else, do so
	* via replace_header("Content-Length") after calling set_body()
	*
	* @param value String data to include as the body content.
	*/
	void SetBody(std::string const & value) {
		body = value;
	}
	void SetBody(std::string && value) {
		body = value;
	}


	std::string version;
	std::string body;
	CiMap headers;
};

}//namespace enginex 
