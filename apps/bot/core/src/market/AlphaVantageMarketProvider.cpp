#include "AlphaVantageMarketProvider.h"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <boost/beast/version.hpp>


namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
namespace ssl = net::ssl;       // from <boost/asio/ssl.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using json = nlohmann::json;    // for convenience

void AlphaVantageMarketProvider::fetch() {
    try {
        // https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=IBM&interval=5min&apikey=demo
        // The host and target for the HTTP request
        std::string host = "www.alphavantage.co";
        std::string port = "443";
        std::string target = "/query";
        std::string query_params = "?function=TIME_SERIES_INTRADAY&symbol=IBM&interval=5min&apikey=demo";
        int version = 11; // HTTP 1.1

        // Set up an I/O context
        net::io_context ioContext;
        ssl::context sslContext(ssl::context::tlsv12_client);
        sslContext.set_default_verify_paths(); // Load system default CA certs

        // Resolve the domain name to an IP address
        tcp::resolver resolver(ioContext);
        // Create an SSL stream connected to the socket
        beast::ssl_stream<beast::tcp_stream> sslStream(ioContext, sslContext);

        // Resolve the domain and connect
        auto const results = resolver.resolve(host, port);
        beast::get_lowest_layer(sslStream).connect(results);


        // Perform SSL handshake
        sslStream.handshake(ssl::stream_base::client);

        // Set up an HTTP GET request message
        http::request<http::string_body> httpRequest{http::verb::get, target + query_params, version};
        httpRequest.set(http::field::host, host);
        httpRequest.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Send the HTTP request to the remote host
        http::write(sslStream, httpRequest);

        // Declare a container to hold the response
        beast::flat_buffer buffer;
        http::response<http::dynamic_body> httpResponse;

        // Receive the HTTP response
        http::read(sslStream, buffer, httpResponse);

        // Convert the response body to a string
        std::string body = beast::buffers_to_string(httpResponse.body().data());

        // Output the raw JSON response
        std::cout << "Raw JSON Response: " << body << std::endl;

        // Parse the JSON response
        try {
            json jsonResponse = json::parse(body);

            //// Example: Access some values from the JSON
            //if (jsonResponse.contains("title")) {
            //    std::string title = jsonResponse["title"];
            //    std::cout << "Title: " << title << std::endl;
            //}
            //if (jsonResponse.contains("completed")) {
            //    bool completed = jsonResponse["completed"];
            //    std::cout << "Completed: " << std::boolalpha << completed << std::endl;
            //}
        } catch (json::parse_error& jsonParseError) {
            std::cerr << "JSON Parsing Error: " << jsonParseError.what() << std::endl;
        }

        // Gracefully close the socket
        beast::error_code errorCode;
        sslStream.shutdown(errorCode);
        if (errorCode && errorCode != beast::errc::not_connected) {
            throw beast::system_error{errorCode};
        }
    } catch (std::exception const& exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
    }
}

std::unique_ptr<PriceData>
AlphaVantageMarketProvider::getCurrentPriceData(const std::string& asset) {
    fetch();
    return std::unique_ptr<PriceData>();
}
