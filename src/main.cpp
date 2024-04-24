#include "main.h"

int main()
{


	uri_builder uri(U("http://localhost:34568"));
	auto addr = uri.to_uri().to_string();
	http_listener listener(addr);

	listener.support(methods::OPTIONS, handle_options);

	listener.support(methods::POST, [=](http_request request) {
		auto path = request.relative_uri().path();
		if (path == U("/start")) {
			handle_start(request);
		}
		else if (path == U("/move")) {
			handle_move(request);
		}
		else if (path == U("/turn"))
		{
			handle_turn(request);
		}
		else {
			http_response response(status_codes::BadRequest);
			json::value response_data;
			response_data[U("message")] = json::value::string(U("Request path not recognized"));
			response.set_body(response_data);
			response.headers().add(U("Access-Control-Allow-Origin"), U("*")); // Ensure this line is added for error handling as well
			request.reply(response);
		}
		});

	try {
		listener.open().wait();
		std::wcout << U("Server is listening at: ") << addr << std::endl;
		std::string line;
		std::getline(std::cin, line); // Wait for user to close the program
		listener.close().wait();
	}
	catch (const std::exception& e) {
		std::cerr << "An error occurred: " << e.what() << std::endl;
	}

	return 0;


}
