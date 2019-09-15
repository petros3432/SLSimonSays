//////////////////////////////////////////////////////////////////////////////////////////////////////
//This code is responsible for the proper running of the game.
//The game is the classic "Simon Says" in which the user should press the correct buttons
//of a color sequence which has been displayed. If a user's choices are correct, then a random
//color choice is added to the sequence and the user should press again the new color-sequence
//
//It is meant to run through 8 physical in-world prims on SECOND LIFE together with the files
//[["parent_v8.c","CONNECTOR_v4.c","RED_v4.c","GREEN_v4.c", "BLUE_v4.c", "YELLOW_v4.c", "INFO_v1.c","HARD_RESET.c"]]
//and also 1 html page "http://siwonsimon.000webhostapp.com/siwonsimon.html" and 1 PHP file "sl.php"
//both uploaded on a server.
//
//This script is responsible for initialise the game and starting the display of the sequence of colors
//It changes its texture accordinly to if the game has started already or not
//One texture displays the custom made "START" text and the other the "RESET" text
//
//In-world prim could be any built object with scripting privileges
//Not every Second Life in-world destination permits scripting and/or building
//This code is meant to be implemented in an in-world prim so it can be thouched in-world
//and send a message for RESET of the script
//
//It is pretty accountable that a url should be released 
//every time that the in-world activity has ended
//because even though an automated "url releaser" exists, 
//it is surely not perfect and urls in every destination
//take a physical seat out of a limited number, exactly like other objects
//Not releasing urls could eliminate available places 
//for building and scripting and could make you be banned
//Property of PETROS SALEPIS
//////////////////////////////////////////////////////////////////////////////////////////////////////



string texture1 = "STARTimg";//Texture of the object. Texture file should be added in the inventory of the object in sub-folded "Contents"
string texture2 = "RESETimg";//Two different textures for the "START" and "RESET" image which is being displayed as a texture
integer listenHandle_a;
integer listenHandle_b;
integer counter;//Counter is used to record how many times user has been pressed the STARTRESET button
integer stateofSTART;//State variable which indicates whether START button has been pressed either from URL or in-world in Second Life
default
{ 
    state_entry()
    {
		listenHandle_a = llListen(-5154789, "", "", "");
		listenHandle_b = llListen(-5243210, "", "", "");
		vector COLOR_WHITE = <1.0, 1.0, 1.0>;//Color and opaqueness of the floating object
		float  OPAQUE      = 1.0;
		stateofSTART = 0;//Initialising the state to 0 so the START hasn't been pressed neither from URL nor in Second Life
		llSetText("PRESS START \n \n ", COLOR_WHITE, OPAQUE);//Floating text which provoke user to press the START button
        llSetTexture(texture1, 1);//Change the texture of only the front side
    }
	listen(integer channel, string name, key id, string message){//Listening Function
        if (channel == -5154789){//Communication with parent so the button can know when to change from "RESET" texture to "START"
			if(message == "O"){
				llResetScript();//The change of texture to the initial state of displaying "START" is being achieved with reseting the script
			}
		}
		if (channel == -5243210){//Communication with CONNECTOR so the button knows if START button has been pressed from the URL
			if(message == "START"){
				llSetTexture(texture2, 1);
				llSetText("", ZERO_VECTOR, 0);
				stateofSTART = 1;//If START has been pressed from URL then the state changes to 1 indicating that the button has to change to RESET state
			}
			if(message == "HARD_RESET"){
				llResetScript();
			}
		}
	}
	touch_start(integer num)
    {
		if(stateofSTART == 0){
			llSay(-5243210, "START");//Sending to parent to start the game and display the color sequence
			llSetText("", ZERO_VECTOR, 0);    
			llSetTexture(texture2, 1);
			stateofSTART = 1;
		}
		else if(stateofSTART == 1){//But because some users could press the reset button continuesly, fool-proof design has been implemented
			llSay(-5243210, "RESET");//Inform only the parent for reseting script and not for releasing URL
			llResetScript();//Reset also button's script so the counter can initialise
		}
    }	
}
