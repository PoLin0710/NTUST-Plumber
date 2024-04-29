/***********************************************************************
 * File: main.h
 * Author:
 *		B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *		B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *		B11215008 ¬x§B¿o (n590762743@gmail.com)
 *		B11215012 Henry Liu (rov20031214@gmail.com)
 * Create Date: 2024-04-24
 * Editor:
 *		B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *		B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *		B11215008 ¬x§B¿o (n590762743@gmail.com)
 *		B11215012 Henry Liu (rov20031214@gmail.com)
 * Update Date: 2024-04-30
 * Description: This program serves as the backend for a game, handling HTTP requests
 *				from clients to perform various game-related actions , and JSON data formatting for communication with clients.
***********************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_

#include "Game.h"
#include "cpprest/json.h"
#include "cpprest/http_listener.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

//Declare Game
Game game;

/**
 * Intent: Handles the OPTIONS request by setting appropriate CORS headers.
 * Pre: None.
 * Post: Responds to the OPTIONS request with CORS headers allowing specified methods and headers.
 * \param message The HTTP request object.
 */
void handle_options(http_request message)
{
	http_response rep;

	// Allow CROS configuration
	rep.headers().add(U("Access-Control-Allow-Origin"), U("*"));
	rep.headers().add(U("Access-Control-Request-Method"), U("GET,POST,OPTIONS"));
	rep.headers().add(U("Access-Control-Allow-Credentials"), U("true"));
	rep.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type,Access-Token,x-requested-with,Authorization"));
	rep.set_status_code(status_codes::OK);
	message.reply(rep);
}

/**
 * Intent: Handles the start request by extracting JSON data, setting up the game, and responding with game state information.
 * Pre: The request contains valid JSON data with mode, fileName, M, and N fields.
 * Post: Responds with game state information in JSON format.
 * \param request The HTTP request object.
 */
void handle_start(http_request request) {
	request.extract_json().then([=](json::value request_json) {
		// Get JSON information
		utility::string_t text = request_json[U("mode")].as_string();
		utility::string_t filename = request_json[U("fileName")].as_string();
		int M = request_json[U("M")].as_integer();
		int N = request_json[U("N")].as_integer();

		// Output to command line
		std::wcout << U("SetMode") << text << std::endl;
		std::wcout << U("M") << M << std::endl;
		std::wcout << U("N") << N << std::endl;

		// Call game function
		game.setMode(text[0]);
		game.start(M, N, filename);
		game.update();

		// Prepare response data
		json::value response_data;
		response_data[U("State")] = json::value::boolean(game.getSetSatae());
		response_data[U("M")] = json::value::number(game.getBoardSize()[0]);
		response_data[U("N")] = json::value::number(game.getBoardSize()[1]);
		response_data[U("PIPES")] = json::value::array(game.getStatu().size());
		response_data[U("begin")] = json::value::number(game.getStartEnd()[0]);
		response_data[U("end")] = json::value::number(game.getStartEnd()[1]);
		response_data[U("current_id")] = json::value::number(game.getPlayer());
		response_data[U("win_statu")] = json::value::boolean(game.getWinStatu());

		for (int i = 0; i < game.getStatu().size(); i++)
		{
			json::value result = json::value::object();
			result[U("id")] = json::value::number(game.getStatu()[i].id);
			result[U("type")] = json::value::number(game.getStatu()[i].type);
			result[U("dir")] = json::value::number(game.getStatu()[i].dir);
			result[U("flow")] = json::value::number(game.getStatu()[i].flow);
			result[U("answer")] = json::value::number(game.getStatu()[i].answer);

			response_data[U("PIPES")][i] = result;
		}

		// Send HTTP response
		http_response response(status_codes::OK);
		response.set_body(response_data);
		response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
		request.reply(response);
		}).wait();
}

/**
 * Intent: Handles the move request by extracting JSON data, updating the game state accordingly,
 *		   and responding with updated game state information.
 * Pre: The request contains valid JSON data with the move field indicating the player's move direction.
 * Post: Responds with updated game state information in JSON format.
 * \param request The HTTP request object.
 */
void handle_move(http_request request) {
	request.extract_json().then([=](json::value request_json) {
		// Get JSON information
		utility::string_t text = request_json[U("move")].as_string();

		// Output to command line
		std::wcout << U("move") << text << std::endl;

		// Call game function
		game.keyUpdate(text[0]);
		game.update();

		// Prepare response data
		json::value response_data;
		response_data[U("M")] = json::value::number(game.getBoardSize()[0]);
		response_data[U("N")] = json::value::number(game.getBoardSize()[1]);
		response_data[U("PIPES")] = json::value::array(game.getStatu().size());
		response_data[U("begin")] = json::value::number(game.getStartEnd()[0]);
		response_data[U("end")] = json::value::number(game.getStartEnd()[1]);
		response_data[U("current_id")] = json::value::number(game.getPlayer());
		response_data[U("win_statu")] = json::value::boolean(game.getWinStatu());

		for (int i = 0; i < game.getStatu().size(); i++)
		{
			json::value result = json::value::object();
			result[U("id")] = json::value::number(game.getStatu()[i].id);
			result[U("type")] = json::value::number(game.getStatu()[i].type);
			result[U("dir")] = json::value::number(game.getStatu()[i].dir);
			result[U("flow")] = json::value::number(game.getStatu()[i].flow);
			result[U("answer")] = json::value::number(game.getStatu()[i].answer);

			response_data[U("PIPES")][i] = result;
		}

		// Send HTTP response
		http_response response(status_codes::OK);
		response.set_body(response_data);
		response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
		request.reply(response);
		}).wait();
}

/**
 * Intent: Handles the turn request by extracting JSON data, updating the game state accordingly,
 *		   and responding with updated game state information.
 * Pre: The request contains valid JSON data with the turn field indicating the direction to turn the pipe.
 * Post: Responds with updated game state information in JSON format.
 * \param request The HTTP request object.
 */
void handle_turn(http_request request) {
	request.extract_json().then([=](json::value request_json) {
		// Get JSON information
		utility::string_t text = request_json[U("turn")].as_string();

		// Output to command line
		std::wcout << U("turn") << text << std::endl;

		// Call game function
		game.keyUpdate(text[0]);
		game.update();

		// Prepare response data
		json::value response_data;
		response_data[U("M")] = json::value::number(game.getBoardSize()[0]);
		response_data[U("N")] = json::value::number(game.getBoardSize()[1]);
		response_data[U("PIPES")] = json::value::array(game.getStatu().size());
		response_data[U("begin")] = json::value::number(game.getStartEnd()[0]);
		response_data[U("end")] = json::value::number(game.getStartEnd()[1]);
		response_data[U("current_id")] = json::value::number(game.getPlayer());
		response_data[U("win_statu")] = json::value::boolean(game.getWinStatu());

		for (int i = 0; i < game.getStatu().size(); i++)
		{
			json::value result = json::value::object();
			result[U("id")] = json::value::number(game.getStatu()[i].id);
			result[U("type")] = json::value::number(game.getStatu()[i].type);
			result[U("dir")] = json::value::number(game.getStatu()[i].dir);
			result[U("flow")] = json::value::number(game.getStatu()[i].flow);
			result[U("answer")] = json::value::number(game.getStatu()[i].answer);

			response_data[U("PIPES")][i] = result;
		}

		// Send HTTP response
		http_response response(status_codes::OK);
		response.set_body(response_data);
		response.headers().add(U("Access-Control-Allow-Origin"), U("*")); // Ensure this line is added
		request.reply(response);
		}).wait();
}

#endif // !_MAIN_H_
