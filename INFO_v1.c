//////////////////////////////////////////////////////////////////////////////////////////////////////
//This code is NOT responsible for the proper running of the game.
//You can exclude this script and the bulding of the equvelant button
//However it displays crucial information for the understanding of the game and the 
//different utilites it provides, so the use of this is script is recommended.
//
//The game is the classic "Simon Says" in which the user should press the correct buttons
//of a color sequence which has been displayed. If a user's choices are correct, then a random
//color choice is added to the sequence and the user should press again the new color-sequence
//
//This script uses llDialog() functions to display in a unique window information about the game
//It also provides several buttons for smooth navigation throughout the information panel
//
//Property of PETROS SALEPIS
//////////////////////////////////////////////////////////////////////////////////////////////////////

//Public Variables
string texture1 = "INFOimg";//Texture of the object. Texture file should be added in the inventory of the object in sub-folded "Contents"
list MENU1 = [];//This list contains the buttons that are being displayed each time
list MENU2 = [];
integer listener;
integer MENU_CHANNEL = 1000;
//Separate function Dialog instead llDialog so we can remove the different listeners each time and burden further the Second Life world
Dialog(key id,string tempMessage, list menu)
{
    llListenRemove(listener);//Remove old listener
    listener = llListen(MENU_CHANNEL, "", NULL_KEY, "");//Initialise the new one
    llDialog(id, tempMessage, menu, MENU_CHANNEL);
}
default
{
    on_rez(integer num)
    {
        //Reset Sripts when object has changed
        llResetScript();
    }
    state_entry()
    {
		vector COLOR_WHITE = <1.0, 1.0, 1.0>;//Color and opaqueness of the floating object
		float  OPAQUE      = 0.6;
        llSetText("Info", COLOR_WHITE, OPAQUE);//Floating text which provoke user to press the Info button
		llSetTexture(texture1, 0);
    }

    touch_start(integer total_number)
    {
		llSetText("", ZERO_VECTOR, 0);//Remove the floating text
        MENU1 = [];
        MENU1 = ["How to Play"];//One button only which displays "How to Play" text
        MENU2 = [];
        MENU2 = ["Back","Second Life", "Web Browser"];//Three buttons
        Dialog(llDetectedKey(0),"\n Welcome \n This is the classic game \"Simon Says\" \n\n\nBy Petros Salepis @ petros.1822@gmail.com\n\nIMPORTANT\nDon't forget to reset the game when you stop playing so the generated URL can be released.\nYou can do so by clicking the \"HARD RESET\" button that is placed on bottom left corner.\nTop \"RESET\" buttons is being displayed after you press the \"START\" button and is responsible only for In-game reset of the color sequence.", MENU1);
    }
    listen(integer channel, string name, key id, string message) 
    {
        if (channel == MENU_CHANNEL)
        {
            llListenRemove(listener);  
            if (message == "How to Play")
            {
				Dialog(id,"You can play either in Second Life or using a web-browser. \nIn both situations second life's script-package should be operating constantly.", MENU2);
            }
            else if (message == "Back")
            {
                Dialog(id,"\n Welcome \n This is the classic game \"Simon Says\" \n\n\nBy Petros Salepis @ petros.1822@gmail.com\n\nIMPORTANT\nDon't forget to reset the game when you stop playing so the generated URL can be released.\nYou can do so by clicking the \"HARD RESET\" button that is placed on bottom left corner.\nTop \"RESET\" buttons is being displayed after you press the \"START\" button and is responsible only for In-game reset of the color sequence.", MENU1);
            }
            else if (message == "Second Life")
            {
                Dialog(id,"Playing Simon Says in Second Life is very easy. \nYou simply press the \"START\" button and a colored button will blink. \nThen, you have to press the correct button.\nAfter that, a sequence of colored buttons will blink etc. \nAs long as you press the correct buttons you will advance in the game. \nThe game ends when you press a wrong button.", MENU1);            
            }
           else if (message == "Web Browser")
            {
                Dialog(id,"You can play Simon Says using a Web Browser. \nSimply press \"START\" button and press the link that is being displayed in chat. \nThen you can scan the generated QR code with your phone and play online. \nYou can also copy the generated link and paste it after '?' character in this link \nhttps://siwonsimon.000webhostapp.com/siwonsimon.html? \nIf you want to read again the produced URL, all you have to do is to press the triangle button in the bottom of the prim.", MENU1);
            }
        }
	}
}