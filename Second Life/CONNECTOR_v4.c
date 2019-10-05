//////////////////////////////////////////////////////////////////////////////////////////////////////
//This code is responsible for the proper running of the game.
//The game is the classic "Simon Says" in which the user should press the correct buttons
//of a color sequence which has been displayed. If a user's choices are correct, then a random
//color choice is added to the sequence and the user should press again the new color-sequence
//
//It is meant to run through 8 physical in-world prims on SECOND LIFE together with the files
//[["parent_v8.c","STARTRESET.c","RED_v4.c","GREEN_v4.c", "BLUE_v4.c", "YELLOW_v4.c", "INFO_v1.c", "HARD_RESET.c"]]
//and also 1 html page "http://siwonsimon.000webhostapp.com/siwonsimon.html" and 1 PHP file "sl.php"
//both uploaded on a server.
//
//In-world prim could be any built object with scripting privileges
//Not every Second Life in-world destination permits scripting and/or building
//This code enables the HTTP connection between the LS server and our devices
//It also communicates to the main computing code of the game "parent_v8" 
//to receive and sent the data of the game
//This code is meant to be implemented into a separate in-world prim which 
//communicates with "parent_v8",
//"RED_v4","GREEN_v4", "BLUE_v4", "YELLOW_v4", "STARTRESET", "HARD_RESET" 
//using llSay() and llShout() functions and listen handles
//
//It uses URL_REQUEST for HTTP communication using Linden Server (Second Life's) and the functions
//llHTTPRequest() for sending data to a php file in a server 
//"http://siwonsimon.000webhostapp.com/sl.php?test="
//Property of PETROS SALEPIS
//////////////////////////////////////////////////////////////////////////////////////////////////////


//In world web-page header
string header="<body style='background-color:white;font-size:15pt;'>";
//Two different variables for listening to two seperate channels
integer listenHandle_a;
integer listenHandle_b;
//Get the help of the external page to express the key on the smartphone mobile homepage.
//The question mark character "?" is crucial so we can approach our page which we will be adapted to the HTTP request
string baseurl="http://siwonsimon.000webhostapp.com/siwonsimon.html?";
//string baseurl="http://siwonsimon.000webhostapp.com/siwonsimon_debugging.html?"; //For debugging purposes. 
string url;
string PHP_URL;
integer URLRELEASED;
string PHP_DATA;
//The color black for the in-game prim
vector BLACK =  <0.0, 0.0, 0.0>;

default
{	
	//The script is reset if the connector-prim has changed
	on_rez(integer start_param)
    {
        llResetScript();
    }
	//Main statement runs instantly
	state_entry()
    {
		//Listening to two different channels
		listenHandle_a = llListen(-5243210, "", "", "");//channel "--5243210" for communicating with the STARTRESET BUTTON and also HARD_RESET
		listenHandle_b = llListen(-5154789, "", "", "");//channel "-5154789" for gaining data from "parent_v8"
        llRequestURL();//Requisting URL for HTTP communication
		llSay(0, url);
		llSetColor(BLACK, ALL_SIDES);//Setting the black color to the in-game prim of "CONNECTOR_v4"
		URLRELEASED = FALSE;
    }
    listen(integer channel, string name, key id, string message){//Listening Function
        if (channel == -5243210){//Communication with the HARD_RESET BUTTON
			if (message == "HARD_RESET"){
				llSay(0, "URL RELEASED");
				llSleep(2);
				llReleaseURL(url);//If we press the HARD_RESET BUTTON the URL of our HTTP communication will be released
				llSleep(2);//Small time delay for proper message announcement to user
				llSay(0, "GAME HARD RESETED");
				URLRELEASED=TRUE;
			}
		}
		//Communication with "parent_v8" for gaining the wanted sequence of colors
		if (channel == -5154789){
			PHP_URL= "http://siwonsimon.000webhostapp.com/sl.php?test=";
			PHP_DATA= PHP_URL + message;//Color sequence is a string in the variable "message"(e.g. "RRYBG")
			//R stands for RED, G stands for GREEN, B stands for BLUE, Y stands for YELLOW, O stands for GAME OVER
			llHTTPRequest(PHP_DATA,[],"");//Sending the wanted sequence into a php file 
			//in which is been proccessed and saved to a TXT file
		}
	}				
    // Touch an object
    touch_start(integer num)
    {
        // Take the homepage address.
		if(URLRELEASED == TRUE){
			llRequestURL();//Requisting URL for HTTP communication
			URLRELEASED = FALSE;
		}
		llSay(0, url);
    }
    
    // If a homepage server request or a URL request comes in
    http_request(key id, string method, string body)
    {
        // If the request is an address
        if (method == URL_REQUEST_GRANTED)
        {
            // Show your new homepage address in chat window.
            url=body;
            //llOwnerSay("URL: " + url);
        }
        // When a GET request arrives
        else if (method == "GET")
        {
			//Data from our answer is contained in the HTTP header of our page
			//HTML page generates a new window(invisible window) in which's header, our answer it's written
            string result = llGetHTTPHeader(id,"x-query-string");//Data from our answer is being kept in the variable "result"
            llSetContentType(id, CONTENT_TYPE_HTML);
            //The first interaction with the object "CONNECTOR_v4" prints a custom QR code for easy navigation to the proper URL
			//QR code generator is being called through a specific url of its page + baseurl + url
			if(result=="")
				//Proper URL is our baseurl plus the url which is generated from the "llRequestURL()"
				//baseurl+url navigates to the window of our custom HTML page which is built for this specific HTTP communication ONLY
				//If the URL is released then the wanted HTML page will be changed but it will be generated automatically again
                llHTTPResponse(id,200,header + 
                    "<br/>Take a QR code with your smartphone.<br/>
                    <img src='https://api.qrserver.com/v1/create-qr-code/?data=" + baseurl + url + "'/>");

            if(result=="mode")//Checking for unwanted mode errors
                llHTTPResponse(id,200,header + " <div style='width:100px;height:20px;background-color:yellow;border:1px solid blue;'>R</div>");
            if(result=="RED")//If our choice is "RED", the word "RED" is sent to "parent_v8"
               llSay(-5243210,"RED");
            if(result=="BLUE")//If our choice is "BLUE", the word "BLUE" is sent to "parent_v8"
               llSay(-5243210,"BLUE");  
			if(result=="GREEN")//If our choice is "GREEN", the word "GREEN" is sent to "parent_v8"
               llSay(-5243210,"GREEN");
			if(result=="YELLOW")//If our choice is "YELLOW", the word "RYELLOW" is sent to "parent_v8"
               llSay(-5243210,"YELLOW");
			if(result=="START")//If we want to start the game and pressed "START", the word "START" is sent to "parent_v8"
               llSay(-5243210,"START");
        }
    }
}
