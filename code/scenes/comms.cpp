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
		{"ymw", "n xma"}, // You are what -> No - I am alien
		{"yma", "nn"}, // You are alien -> Not untrue
		{"ymna", "n xma"}, // You are not alien -> No - I am alien
		{"ynma", "n xma"}, // You not are alien -> No - I am alien
		{"xmw", "ymna"}, // I am what -> You are not alien
		{"xma", "n ymna"}, // I am alien -> No - You are not alien
		{"xmna", "nn"}, // I am not alien -> Not untrue
		{"xnma", "nn"}, // I not am alien -> Not untrue
		{"bmw", "bmb"}, // Box is what -> Box is box
		{"bmow", "bmobt"}, // Box is owned by what -> Box is owned by box storage
		{"chx", "cmh"}, // Computer helped me -> Computer is helpful
		{"cmh", "nn"}, // Computer is helpful -> Not untrue
		{"xsc", "nn ysc csx"}, // I speak to computer -> Not untrue - You speak to computer - Computer speaks to me
		{"xsy", "nn ysc csx"}, // I speak to you -> Not untrue - You speak to computer - Computer speaks to me
		{"ysx", "nn xsc csy"}, // You speak to me -> Not untrue - I speak to computer - Computer speaks to you
		{"ysc", "nn xsc csy"}, // You speak to computer -> Not untrue - I speak to computer - Computer speaks to you
		{"cma", "n cnma"}, // Computer is alien -> No - Computer not is alien
		{"cmb", "n cnmb"}, // Computer is box -> No - Computer not is box
		{"cmy", "n xsc cnmx"}, // Computer is you -> No - I speak to computer - Computer not is me
		{"bma", "n bnma"}, // Box is alien -> No - Box not is alien
		{"bmc", "n bnmc"}, // Box is computer -> No - Box not is computer
		{"bmy", "n bnmx"}, // Box is you -> No - Box not is me
		{"ysk", "n xsl"}, // You speak nonsense -> No - I speak language
		{"ysw", "xsl"}, // You speak what -> I speak language
		{"ysl", "nn"}, // You speak language -> Not untrue
		{"xsk", "n ysl"}, // I speak nonsense -> No - You speak language
		{"xsl", "nn"}, // I speak language -> Not untrue
		{"dme", "n dmf"}, // Door is closed -> No - Door is open
		{"yhx", "cnhyixhy"}, // You help me -> If computer does not help you then I help you
		{"d", "dmf ncidme"}, // Door -> Doors are open. Without computer, doors are closed.
		{"c", "cha ahc"}, // Computer -> Computers help us, we help computers
		{"b", "bnha apb"}, // Box -> Box not help us, we push boxes
		{"t", "wt"}, // Room -> Which room?
		{"s", "s ysx xsy asa"}, // Speech? -> Speech. You speak to me, I speak to you, aliens speak to each other.
		{"h", "h ah bnh"}, // Help? -> Help. Aliens help. Boxes do not help.
		{"e", "e de aed ced"}, // Close -> Close. Doors close. Aliens close doors. Computers close doors.
		{"f", "f df afd cfd"}, // Open -> Open. Doors open. Aliens open doors. Computers open doors.
		{"ct", "ctiafc"}, // Computer room -> With computer room, we access computers
		{"ht", "htiaha"}, // Help room -> With help room, we help each other
		{"bt", "bnha acbt apb"}, // Box room -> Box not help us - We close box room - We push boxes
		{"st", "stniynsx"}, // Speech room -> Without speech room, you could not speak to me
		{"at", "atmh"} // Alien room -> Alien room is helpful.
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
	responceTxt.setPosition({data.windowSize.x - responceTxt.getGlobalBounds().size.x - 30, 20});
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
		keys = {};
		
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