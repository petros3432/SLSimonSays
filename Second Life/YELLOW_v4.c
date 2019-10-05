//////////////////////////////////////////////////////////////////////////////////////////////////////
//This code is responsible for the proper running of the game.
//The game is the classic "Simon Says" in which the user should press the correct buttons
//of a color sequence which has been displayed. If α user's choices are correct, then a random
//color choice is added to the sequence and the user should press again the new color-sequence
//
//It is meant to run through 8 physical in-world prims on SECOND LIFE together with the files
//[["CONNECTOR_v4.c","STARTRESET.c","RED_v4.c","GREEN_v4.c", "parent_v8.c", "BLUE_v4.c", "INFO_v1.c", "HARD_RESET.c"]]
//and also 1 html page "http://siwonsimon.000webhostapp.com/siwonsimon.html" and 1 PHP file "sl.php"
//both uploaded on a server
//
//In-world prim could be any built object with scripting privileges
//Not every Second Life in-world destination permits scripting and/or building
//This code is meant to be implemented in an in-world prim so it can interact with the user 
//through script "parent_v8". The sole purpose of this script is to change its color 
//(pseudo-indicating a short flash) into a brighter version of the default dark color, 
//whenever a color pattern should be displayed or whenever the user selects 
//this color through HTTP communication.
//Property of PETROS SALEPIS
//////////////////////////////////////////////////////////////////////////////////////////////////////

integer listenHandle_a;
//This scripts uses timer() function for a timed flash of 0.5s
float toff_unit = 0.5;
//Both DARK and BRIGHT colors
vector YELLOW_DARK =  <0.8, 0.6, 0.0>;
vector YELLOW_BRIGHT = <1.0, 1.0, 0.0>;


default
{ 
    state_entry()
    {
        llSetColor(YELLOW_DARK, ALL_SIDES);
        listenHandle_a = llListen(-5243212, "", "", "");
       
    }
	//Listen to "parent_v8"
    listen(integer channel, string name, key id, string message){
        if (channel == -5243212){
            if (message == "Y"){
                //This would change the color of the prim forever and not temporarily
                //llSetColor(llList2Vector(colors, 1), ALL_SIDES);
				//So we call another state where the prim changes color only 
				//for toff_unit = 0.5 seconds
                state YELLOW_BUTTON;
            }
        }
    }
	touch_start(integer num){		
		llSay(-5243210,"YELLOW");
		llResetScript();
	}
}
state YELLOW_BUTTON
{
    state_entry()
    {
        llSetColor(YELLOW_BRIGHT, ALL_SIDES);
        llSetTimerEvent(toff_unit); 
			
    }
    timer() { state default; } 
} 
