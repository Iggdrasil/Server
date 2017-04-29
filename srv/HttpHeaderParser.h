#pragma once
#include <boost\tuple\tuple.hpp>
#include <boost\logic\tribool.hpp>

struct HttpRequest;

class HttpHeaderParser
{
	boost::tribool consume(HttpRequest& req, char input);

	static bool is_char(int c);

	static bool is_ctl(int c);

	static bool is_tspecial(int c);

	static bool is_digit(int c);

	enum state
	{
		method_start,
		method,
		uri,
		http_version_h,
		http_version_t_1,
		http_version_t_2,
		http_version_p,
		http_version_slash,
		http_version_major_start,
		http_version_major,
		http_version_minor_start,
		http_version_minor,
		expecting_newline_1,
		header_line_start,
		header_lws,
		header_name,
		space_before_header_value,
		header_value,
		expecting_newline_2,
		expecting_newline_3
	} state_;

public:
	HttpHeaderParser();
	~HttpHeaderParser();

	void reset();

	template <typename InputIterator>
	boost::tuple<boost::tribool, InputIterator> parse(HttpRequest& req,
		InputIterator begin, InputIterator end)
	{
		while (begin != end)
		{
			boost::tribool result = consume(req, *begin++);
			if (result || !result)
				return boost::make_tuple(result, begin);
		}
		boost::tribool result = boost::indeterminate;
		return boost::make_tuple(result, begin);
	}

	
};
