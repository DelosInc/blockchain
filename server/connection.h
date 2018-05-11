#pragma once

#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <boost/asio.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>

class Connection
{
public:

	Connection(boost::asio::io_context& io_context)
		: socket(io_context) {

	}

	boost::asio::ip::tcp::socket& getSocket() {
		return socket;
	}

	template <typename T, typename Handler>
	void asyncWrite(const T& t, Handler handler)
	{
		std::ostringstream archiveStream;
		boost::archive::text_oarchive archive(archiveStream);
		archive << t;
		outboundData = archiveStream.str();
		std::ostringstream headerStream;
		headerStream << std::setw(8) << std::hex << outboundData.size();
		if (!headerStream || headerStream.str().size() != 8) {
			boost::system::error_code error(boost::asio::error::invalid_argument);
			boost::asio::post(socket.get_executor(), boost::bind(handler, error));
			return;
		}
		outboundHeader = headerStream.str();
		std::vector<boost::asio::const_buffer> buffers;
		buffers.push_back(boost::asio::buffer(outboundHeader));
		buffers.push_back(boost::asio::buffer(outboundData));
		boost::asio::async_write(socket, buffers, handler);
	}

	template <typename T, typename Handler>
	void asyncRead(T& t, Handler handler) {
		void (Connection::*f)(const boost::system::error_code&, T&, boost::tuple<Handler>) = &Connection::handleReadHeader<T, Handler>;
		boost::asio::async_read(socket, boost::asio::buffer(inboundHeader), boost::bind(f, this, boost::asio::placeholders::error, boost::ref(t), boost::make_tuple(handler)));
	}

	template <typename T, typename Handler>
	void handleReadHeader(const boost::system::error_code& e, T& t, boost::tuple<Handler> handler) {
		if (e) {
			boost::get<0>(handler)(e);
		}
		else {
			std::istringstream is(std::string(inboundHeader, 8));
			std::size_t inboundDataSize = 0;
			if (!(is >> std::hex >> inboundDataSize)) {
				boost::system::error_code error(boost::asio::error::invalid_argument);
				boost::get<0>(handler)(error);
				return;
			}
			inboundData.resize(inboundDataSize);
			void (Connection::*f)(const boost::system::error_code&, T&, boost::tuple<Handler>) = &Connection::handleReadData<T, Handler>;
			boost::asio::async_read(socket, boost::asio::buffer(inboundData), boost::bind(f, this, boost::asio::placeholders::error, boost::ref(t), handler));
		}
	}

	template <typename T, typename Handler>
	void handleReadData(const boost::system::error_code& e, T& t, boost::tuple<Handler> handler)
	{
		if (e) {
			boost::get<0>(handler)(e);
		}
		else {
			try {
				std::string archiveData(&inboundData[0], inboundData.size());
				std::istringstream archiveStream(archiveData);
				boost::archive::text_iarchive archive(archiveStream);
				archive >> t;
			}
			catch (std::exception& e) {
				(void)e;
				boost::system::error_code error(boost::asio::error::invalid_argument);
				boost::get<0>(handler)(error);
				return;
			}
			boost::get<0>(handler)(e);
		}
	}

private:
	boost::asio::ip::tcp::socket socket;
	std::string outboundHeader;
	std::string outboundData;
	char inboundHeader[8];
	std::vector<char> inboundData;
};

