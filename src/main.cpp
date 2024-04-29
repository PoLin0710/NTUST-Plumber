/***********************************************************************
 * File: main.cpp
 * Author:
 *		B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *		B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *		B11215008 ¬x§B¿o (n590762743@gmail.com)
 *		B11215012 Henry Liu (rov20031214@gmail.com)
 * Create Date: 2024-04-07
 * Editor:
 *		B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *		B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *		B11215008 ¬x§B¿o (n590762743@gmail.com)
 *		B11215012 Henry Liu (rov20031214@gmail.com)
 * Update Date: 2024-04-30
 * Description: This file contains the main function for the server application.
***********************************************************************/

#include "main.h"

int main()
{
	// Set up URI for the server
	uri_builder uri(U("http://localhost:34568"));
	auto addr = uri.to_uri().to_string();
	http_listener listener(addr);

	// Set up request handlers
	listener.support(methods::OPTIONS, handle_options);

	// Set up a listener to handle POST requests
	listener.support(methods::POST, [=](http_request request) {
		// Extract the path from the request URI
		auto path = request.relative_uri().path();

		// Check the path and call the corresponding handler function
		if (path == U("/start")) {
			// Call the handle_start function for the "/start" path
			handle_start(request);
		}
		else if (path == U("/move")) {
			// Call the handle_move function for the "/move" path
			handle_move(request);
		}
		else if (path == U("/turn"))
		{
			// Call the handle_turn function for the "/turn" path
			handle_turn(request);
		}
		else {
			// Handle unrecognized request paths
			// Prepare a response indicating the request path is not recognized
			http_response response(status_codes::BadRequest);
			json::value response_data;
			response_data[U("message")] = json::value::string(U("Request path not recognized"));
			response.set_body(response_data);
			response.headers().add(U("Access-Control-Allow-Origin"), U("*")); // Ensure this line is added for error handling as well

			// Send the response
			request.reply(response);
		}
		});

	try {
		// Start listening for requests
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
