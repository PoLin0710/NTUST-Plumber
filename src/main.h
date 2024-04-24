#ifndef _MAIN_H_
#define _MAIN_H_

#include "Game.h"
#include "cpprestsdk/Release/include/cpprest/json.h"
#include "cpprestsdk/Release/include/cpprest/http_listener.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

Game game;

void handle_options(http_request request) {
	http_response response(status_codes::OK);
	response.headers().add(U("Allow"), U("GET, POST, OPTIONS"));
	response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
	response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, OPTIONS"));
	response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
	request.reply(response);
}

void handle_start(http_request request) {
	request.extract_json().then([=](json::value request_json) {
		//get josn info
		utility::string_t text = request_json[U("mode")].as_string();
		int M = request_json[U("M")].as_integer();
		int N = request_json[U("N")].as_integer();

		//output to cmd
		std::wcout << U("SetMode") << text << std::endl;
		std::wcout << U("M") << M << std::endl;
		std::wcout << U("N") << N << std::endl;

		//call game function
		game.setMode(text[0]);
		game.start(M, N);

		json::value response_data;
		response_data[U("M")] = json::value::number(game.getBoardSize()[0]);
		response_data[U("N")] = json::value::number(game.getBoardSize()[1]);
		response_data[U("PIPES")] = json::value::array(game.getStatu().size());
		response_data[U("begin")] = json::value::number(game.getStartEnd()[0]);
		response_data[U("end")] = json::value::number(game.getStartEnd()[1]);
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
		http_response response(status_codes::OK);
		response.set_body(response_data);
		response.headers().add(U("Access-Control-Allow-Origin"), U("*")); // Ensure this line is added
		request.reply(response);

		}).wait();
}

void handle_move(http_request request) {
	request.extract_json().then([=](json::value request_json) {
		//get josn info
		utility::string_t text = request_json[U("move")].as_string();

		//output to cmd
		std::wcout << U("move") << text << std::endl;

		//call game function
		game.keyUpdate(text[0]);
		game.update();

		json::value response_data;
		response_data[U("playerX")] = json::value::number(game.getPlayer()[0]);
		response_data[U("playerY")] = json::value::number(game.getPlayer()[1]);
		http_response response(status_codes::OK);
		response.set_body(response_data);
		response.headers().add(U("Access-Control-Allow-Origin"), U("*")); // Ensure this line is added
		request.reply(response);

		}).wait();
}

void handle_turn(http_request request) {
	request.extract_json().then([=](json::value request_json) {
		//get josn info
		utility::string_t text = request_json[U("turn")].as_string();

		//output to cmd
		std::wcout << U("turn") << text << std::endl;

		//call game function
		game.keyUpdate(text[0]);
		game.update();

		json::value response_data;
		response_data[U("M")] = json::value::number(game.getBoardSize()[0]);
		response_data[U("N")] = json::value::number(game.getBoardSize()[1]);
		response_data[U("PIPES")] = json::value::array(game.getStatu().size());

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

		http_response response(status_codes::OK);
		response.set_body(response_data);
		response.headers().add(U("Access-Control-Allow-Origin"), U("*")); // Ensure this line is added
		request.reply(response);

		}).wait();
}


#endif // !_MAIN_H_
