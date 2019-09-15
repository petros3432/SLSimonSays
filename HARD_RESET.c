//////////////////////////////////////////////////////////////////////////////////////////////////////
//This code is responsible for the proper running of the game.
//The game is the classic "Simon Says" in which the user should press the correct buttons
//of a color sequence which has been displayed. If a user's choices are correct, then a random
//color choice is added to the sequence and the user should press again the new color-sequence
//
//It is meant to run through 8 physical in-world prims on SECOND LIFE together with the files
//[["CONNECTOR_v4.c","STARTRESET.c","RED_v4.c","GREEN_v4.c", "parent_v8.c", "YELLOW_v4.c", "INFO_v1.c", "BLUE_v4.c"]]
//and also 1 html page "http://siwonsimon.000webhostapp.com/siwonsimon.html" and 1 PHP file "sl.php"
//both uploaded on a server.
//
//In-world prim could be any built object with scripting privileges
//Not every Second Life in-world destination permits scripting and/or building
//This code is meant to be implemented in an in-world prim so it can be thouched in-world
//and send a message for RESET of the script and URL's
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



//Physical color of the in-world prim
vector GREY = <0.667, 0.667, 0.667>;


default
{ 
    state_entry()
    {
        llSetColor(GREY, ALL_SIDES);
    }
	touch_start(integer num)
    {
        // RESET everything.Both CONNECTOR_v4 and parent_v8.
        llSay(-5243210, "HARD_RESET");	
    }
}
