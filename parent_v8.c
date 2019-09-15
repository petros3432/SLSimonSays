//////////////////////////////////////////////////////////////////////////////////////////////////////
//This code is responsible for the proper running of the game.
//The game is the classic "Simon Says" in which the user should press the correct buttons
//of a color sequence which has been displayed. If a user's choices are correct, then a random
//color choice is added to the sequence and the user should press again the new color-sequence
//
//It is meant to run through 8 physical in-world prims on SECOND LIFE together with the files
//[["CONNECTOR_v4.c","STARTRESET.c","RED_v4.c","GREEN_v4.c", "BLUE_v4.c", "YELLOW_v4.c", "INFO_v1.c", "HARD_RESET.c"]]
//and also 1 html page "http://siwonsimon.000webhostapp.com/siwonsimon.html" and 1 PHP file "sl.php"
//both uploaded on a server
//In-world prim could be any built object with scripting privileges
//Not every Second Life in-world destination permits scripting and/or building
//
//It runs automatically with a message from "CONNECTOR_v4".
//It processes the INPUT DATA of our choice through "CONNECTOR_v4" and
//it generates a new sequence using the pseudo-random function "llFrand".
//The generated sequence is being sent to each individual prim with the proper color
//so each prim could flash and indicate the color-sequence to user
//
//This particular game is meant to be played outside Second Life using only a web-browser.
//That's because is being used a two-way communication between the processive power
//(Second Life Server) and user through an HTTP connection.
//However the game is totally playable and within the Second Life world Viewer because
//all the wanted sequences,choices that the user is doing and even score and in-game messages, are 
//displayed on in-world prims.
//
//The only drawback is that a web-browser is still needed for
//proper "selecting" and "making" of choices, but with this pack of code implementing
//four physical in-game prims as buttons or even using the existing colored prims as 
//custom buttons who interact with touch_start() event, is pretty simple. 
//
//Nevertheless, this game's main purpose
//is to demonstrate the different steps and tools that are needed so a simple
//communication between a Second Life Server, and a homemade Server is possible and also
//how the gaming-streaming can be achieved.
//Property of PETROS SALEPIS
//////////////////////////////////////////////////////////////////////////////////////////////////////

integer START_handler = FALSE;

list colors = [ "B", "R", "Y", "G"];//The 4 different color choices R for RED, G for GREEN, B  for BLUE, Y  for YELLOW

integer listenHandle_a;//Handler for listening
integer waitingForInput = FALSE;//Flag which indicates if the game should wait for input from user or not
integer current_step = 0;//Step of the color-sequence that we currently are

integer min = 0;//Integers that are used for random selecetion between 4 colors
integer max = 3;//'0' equals to "B",'1' equals to "R",'2' equals to "Y",'3' equals to "G"

list pattern;//Pattern of colors
string input;

integer length;//Length of the pattern of colors


//This function calculates and 
//"SHOUTS" the wanted pattern both to "CONNECTOR_v4" and to then PHP file, and also to the four colored prims
pattern_SHOUT( integer LETSGO )
{
	if(START_handler == TRUE){
		integer a;
		integer n1 = min+ (integer)(llFrand(max - min + 1)); //Pseudo-Random choice of a number between 0 and 3
		string new_item = llList2String(colors,n1);//Correspondence between the random number and the list of available colors
		pattern = (pattern=[]) + pattern + new_item;//New random color is being added to the existing color pattern
		llShout(-5154789, (string)pattern);//Sending the current pattern(with the addition of the new item) to "CONNECTOR_v4"
		//and from there to the PHP file
		length = llGetListLength(pattern);//Length of the color pattern
		for(a = 0; a < length; ++a)
		{
			if (llList2String(pattern, a) != ""){
			llShout(-5243212, llList2String(pattern, a));//Sending each individual color from the pattern list to the 4 colored prims
			llSleep(1.0);//Small time delay of 1s for proper flashing of each colored prim
			}
		}
		waitingForInput = TRUE;//The calculation and communication of the color pattern are completed so a user input now is required
	}
}



//This function gets user's choice of colors(each one at a time) and checks if the user's choice corresponds to
//the generated color-pattern. The CORRECT message however is being displayed only when all the correct colors has been
//selected
pattern_INPUT( integer HOPGO )
{
	if(START_handler == TRUE){
		llShout(-5243212, input);//Sends the user's input to the 4 colored prims for visual indication of the pressed button
		integer end = llGetListLength(pattern);//Length of color pattern
		if (input == llList2String(pattern, current_step))//Checking if our choice is correct
		{
			current_step++;
			if ( current_step == end )//If our choice is correct and is also the last one, a message indicates that the whole
			//pattern has been selected
			{
                llSay(0, "CORRECT");//Displaying the "CORRECT" message
                waitingForInput = FALSE;//Idling flags and handlers for the start of the next pattern
				current_step = 0;
				llSleep(1.5);
				pattern_SHOUT ( TRUE );
                
			}
		}
		else{//If one user's choice is wrong then the game immediately stops, shows score, idles and resets
			llSay(0, "WRONG" +"\nGAME OVER");
			llSleep(0.5);
			string score = (string)(length - 1);//string score = (string)current_step;//Calculation of final score
			llShout(-5154789,"O");//Sending to PHP the information that the game is OVER
			llSay(0, "YOUR SCORE WAS : " + score);//Displaying the user's score
			llResetScript();
		}
	}
}

default
{
    state_entry(){
		list pattern = [];
		listenHandle_a = llListen(-5243210, "", "", "");
    }
	//Immediately starts to listen for user's data so the colored prims can indicate the sequence
    listen(integer channel, string name, key id, string message){
		//Listens to "CONNECTOR_v4" for user's choice and also to START button 
        if (channel == -5243210){
			if (message == "START"){
                //llSetColor(llList2Vector(colors, 1), ALL_SIDES);
                START_handler = TRUE;
				if (waitingForInput == FALSE)
					pattern_SHOUT( TRUE );
            }
			if ((message == "RESET")||(message == "HARD_RESET")){
				llShout(-5154789,"O");
				llResetScript();
			}				
            if (message == "GREEN"){//Checking the message which is pressed
                //llSetColor(llList2Vector(colors, 1), ALL_SIDES);
                input = "G";
				if (waitingForInput == FALSE)
					pattern_SHOUT( TRUE );//Whatever color is pressed, it is used an indicator that the generation of
					//color pattern should start. This excludes the usage of a START BUTTON and makes the scripting
					//more simple
					//In the HTML page a "START BUTTON" is being displayed but it assigns to the default color
					//"RED" and not to a specific "START BUTTON" message
				else
					pattern_INPUT( TRUE );//Sets off the pattern_INPUT function so a colored prim can flash
            }
            if (message == "BLUE"){
                //llSetColor(llList2Vector(colors, 1), ALL_SIDES);
                input = "B";
                if (waitingForInput == FALSE)
					pattern_SHOUT( TRUE );
				else
					pattern_INPUT( TRUE );
            }
            if (message == "RED"){
                //llSetColor(llList2Vector(colors, 1), ALL_SIDES);
                input = "R";
                if (waitingForInput == FALSE)
					pattern_SHOUT( TRUE );
				else
					pattern_INPUT( TRUE );
            }
            if (message == "YELLOW"){
                //llSetColor(llList2Vector(colors, 1), ALL_SIDES);
                input = "Y";
				if (waitingForInput == FALSE)
					pattern_SHOUT( TRUE );
				else
				pattern_INPUT( TRUE );
            }
        }
    }
}