/******************************************************************************
 * Comms.cpp
 * Source file for Comms.hpp
 * Represents the comms scene, when the player interacts with a terminal.
 * Impliments the handleInput, start, render, and end functions of the comms scene
******************************************************************************/

#include "scenes/comms.hpp"
#include "menu/MenuItem.hpp"
#include "globals.hpp"
#include "fonts.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;

// Predefine functions
void sendMsg(globals& data);
void updEntered(std::string newVal);
void updResponce(globals& data, std::string newVal);

// Keep file variables isolated to this file
namespace {
	// Resume Game
	MenuItem resumeBtn(
		"Exit Console",
		100, 500,
		TEKTUR,
		[](globals& data, RenderWindow& window){ data.curScene = "game"; }  
	);

	// Submit message
	MenuItem sendBtn(
		"Send",
		340, 500,
		TEKTUR,
		[](globals& data, RenderWindow& window){ sendMsg(data); }  
	);
	
	Text enteredTxt(GLYPHS, "", 60);
	Text responceTxt(GLYPHS, "", 60);
	
	// Glyph input guides
	std::vector<MenuItem> keys;
	
	std::string glyphs = "abcdefhiklmnopstwxy";
	
	std::string entered = "";
	std::string responce = "";
	
	// Messages the player can send paired with responces
	const std::unordered_map<std::string, std::string> getResponce = {
		{"ymw", "xma"}, // You are what -> I am alien
		{"yma", "nn"}, // You are alien -> Not untrue
		{"ymna", "xma"}, // You are not alien -> I am alien
		{"ynma", "xma"}, // You not are alien -> I am alien
		{"xmw", "ymna"}, // I am what -> You are not alien
		{"xma", "ymna"}, // I am alien -> You are not alien
		{"xmna", "nn"}, // I am not alien -> Not untrue
		{"xnma", "nn"}, // I not am alien -> Not untrue
		{"bmw", "bmb"}, // Box is what -> Box is box
		{"bmow", "bmobt"}, // Box is owned by what -> Box is owned by box storage
		{"chx", "cmh"}, // Computer helped me -> Computer is helpful
		{"xsc", "yscsx"}, // I speak to computer -> You speak to computer speak to me
		{"xsy", "yscsx"}, // I speak to you -> You speak to computer speak to me
		{"ysx", "xscsy"}, // You speak to me -> I speak to computer speak to you
		{"ysc", "xscsy"}, // You speak to computer -> I speak to computer speak to you
		{"cma", "cnma"}, // Computer is alien -> Computer not is alien
		{"cmb", "cnmb"}, // Computer is box -> Computer not is box
		{"cmy", "xscnmx"}, // Computer is you -> I speak to computer not is me
		{"bma", "bnma"}, // Box is alien -> Box not is alien
		{"bmc", "bnmc"}, // Box is computer -> Box not is computer
		{"bmy", "bnmx"}, // Box is you -> Box not is me
		{"ysk", "xsl"}, // You speak nonsense -> No - I speak language
		{"ysl", "nn"}, // You speak language -> Not untrue
		{"xsk", "ysl"}, // I speak nonsense -> No - You speak language
		{"xsl", "nn"}, // I speak language -> Not untrue
		{"dme", "dmf"}, // Door is closed -> Door is open
		{"yhx", "cnhyixhy"} // You help me -> If computer does not help you then I help you
	};
	
	// Phrase said to recieve help and win the game
	const std::string recieveHelp = "cnhx"; // Computer not help me
}

void sendMsg(globals& data)
{
	// If the message is the one to recieve help
	if (entered == recieveHelp)
	{
		data.curScene = "congrats";
	}
	else
	{
		// If the message has a responce, display it
		try
		{
			updResponce(data, getResponce.at(entered));
		}

		// Otherwise, say "You speak what?"
		catch(const std::exception& e)
		{
			updResponce(data, "ysw");
		}
	}
	
	// Clear entered string
	updEntered("");
}

void updEntered(std::string newVal)
{
	entered = newVal;
	enteredTxt.setString(entered);
}

void updResponce(globals& data, std::string newVal)
{
	responce = newVal;
	responceTxt.setString(responce);
	responceTxt.setPosition({data.windowSize.x - responceTxt.getGlobalBounds().size.x - 20, 20});
}

Scene comms(
	// Input Handler
	[](globals& data, RenderWindow& window, const Event& event)
	{
		if (const auto* btnEvent = event.getIf<Event::MouseButtonPressed>()) {
			// Run button callbacks on press
			if (
				resumeBtn.box.getGlobalBounds().contains(
					static_cast<Vector2f>(btnEvent -> position)
				)
			)
				resumeBtn.callback(data, window);
			
			if (
				sendBtn.box.getGlobalBounds().contains(
					static_cast<Vector2f>(btnEvent -> position)
				)
			)
				sendBtn.callback(data, window);
			
			for (auto& btn: keys)
			{
				if (
					btn.box.getGlobalBounds().contains(
						static_cast<Vector2f>(btnEvent -> position)
					)
				)
					btn.callback(data, window);
			}
		}
	},

	// Scene enter
	[](globals& data, RenderWindow& window)
	{
		// Create glyph input keys
		int x = 25, y = 300;
		for (char l: glyphs)
		{
			keys.emplace_back(
				std::string(1, l),
				x, y,
				GLYPHS,
				[l](globals& data, RenderWindow& window){ updEntered(entered + l); },
				true
			);
			
			x += 60;
			if (x >= data.windowSize.x - 60)
			{
				y += 90;
				x = 25;
			}
		}

		// Position and style text
		enteredTxt.setPosition({20, 80});
		enteredTxt.setFillColor(Color(0, 255, 0));
		
		responceTxt.setFillColor(Color(0, 255, 0));
	},

	// Renderer
	[](globals& data, RenderWindow& window)
	{
		auto mouse = static_cast<Vector2f>(Mouse::getPosition(window));

		window.draw(enteredTxt);
		window.draw(responceTxt);
		
		for (auto& btn: keys)
		{
			if (btn.box.getGlobalBounds().contains(mouse))
				btn.box.setFillColor(Color(100, 100, 100));
			else
				btn.box.setFillColor(Color(70, 70, 70));
			window.draw(btn.box);
			window.draw(btn.label);
		}
		
		// Mouse hover for Resume button
		if (resumeBtn.box.getGlobalBounds().contains(mouse))
			resumeBtn.box.setFillColor(Color(100, 100, 100));
		else
			resumeBtn.box.setFillColor(Color(70, 70, 70));
		
		window.draw(resumeBtn.box);
		window.draw(resumeBtn.label);

		// Mouse hover for Send button
		if (sendBtn.box.getGlobalBounds().contains(mouse))
			sendBtn.box.setFillColor(Color(100, 100, 100));
		else
			sendBtn.box.setFillColor(Color(70, 70, 70));
		
		window.draw(sendBtn.box);
		window.draw(sendBtn.label);
	},

	// Scene exit
	[](globals& data, RenderWindow& window)
	{
		// No cleanup needed
	}
);