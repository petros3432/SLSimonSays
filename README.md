# SLSimonSays Project
## Instruction Manual
This package of objects and scripts provides the classic game Simon Says but with a twist...
You have the opportunity to interact with the main tablet of the board game and play solely in-world of Second Life.

However the special feature that this package contains is the fact that you can play through any web browser you want, even on a smart-phone. 
This project uses the HTML page ***http://siwonsimon.000webhostapp.com/siwonsimon.html***, and also the PHP file ***http://siwonsimon.000webhostapp.com/sl.php*** which creates
also a TXT file. All code of these files and also all scripts that are used in this project in Second Life are available for free 
in this github page ***https://github.com/petros3432/SLSimonSays***.

## GAME RULES

Simon Says is a simple yet entertaining game that test player's concentration and memory.

**Rules are Simple**
- The game displays one random color sequence
- User should click all the colors of the sequence in the correct order.
- If user's guess is right then the old color sequence is displayed again but a new color entry is added to its end.
- This way the game becomes much harder even after a few rounds.
- When the user makes a wrong guess of a color then the game's round ends and the score of the user is being displayed.
- Score corresponds to the highest number of colors of a sequence that the user has pressed correctly in the entire round.

## COMPONENTS

**1 In-world in Second Life tablet over which every other button is installed.**
>CONTAINS
- 1 script "parent_v8" which is the oparational brain of the game

**4 colored square buttons (RED, GREEN, BLUE, YELLOW) that flash ( brighten up )**
>EACH ONE CONTAINS
- 1 dedicated script (There are 4 in total ) which operates each button, indicates its color and communicates with "parent" 

**1 STARTRESET button with double texture face. It shows "START" text and also "RESET" when it 's been pressed.**
This reset affects only the parent and doesn't release the generated URL (soft reset).
>CONTAINS
- 1 script "STARTRESET" which communicates with "parent" indicating when the game should begin and when should reset.
- 2 custom made textures with "START" and "RESET" on them.

**1 COMMUNICATOR triangle button which communicates with parent and also sends and receives data from the HTTP communication through the 
generated URL. It generates the first URL and generates a new one with pressing it, only when the former has been released.**
>CONTAINS
- 1 script "COMMUNICATOR" which communicates with parent and HARD RESET button

**1 HARD RESET rectangular button which resets the script of the parent and ALSO releases the generated URL ( hard reset ).**
>CONTAINS
- 1 script "HARDRESET" that sends a message to "COMMUNICATOR" and also parent when pressed

**1 INFO cylindrical button which doesn't communicate with any other component of the project. It is displayed with an "i" symbol on top of it.**
>CONTAINS
- 1 script "INFO" that provides useful informatin about the project and a "how to use it" guide.
- 1 custom made texture with "i" on it.

## INSTALLATION
The object that represents the project of Simon Says exists in Second Life Marketplacei in this link . It is off-charge and contains both the physical objects in-Second Life and the wanted scripts. The scripts also exist in this GitHub repository and can be used freely. The scripts that are being used are the following:
- parent_v8.c
- CONNECTOR_V4.C
- RED_v4.c
- GREEN_v4.c
- BLUE_v4.c
- YELLOW_v4.c
- STARTRESET_v2.c
- HARD_RESET.c
- INFO_v1.c

These scripts exist both in GitHub and in the object from the Marketplace.
If you desire to use them without downloading the object from Second Life's Marketplace, then you have to copy the scripts and paste them each one to their one object. Additionaly, in script STARTRESET.c you have to delete these lines
```
string texture1 = "STARTimg";
string texture2 = "RESETimg";
llSetTexture(texture1, 1);
llSetTexture(texture2, 1);
llSetTexture(texture2, 1);
```
**OR**
Import the images START.png and RESET.png into the object that would contain STARTRESET_v2.c script, as textures. You can add the images 
to use them as textures by paying 10L$ ( Second Life's standard price for uploading ) or free to use them ***only temporarily***.
To add the textures in the inventory of object, simply Right-click on object>Edit>Content>Drag & Drop the textures from your inventory to the folder Contains of the object.
These apply also for the script INFO_v1.c where the lines 
```
string texture1 = "INFOimg";
llSetTexture(texture1, 0);
```
should be removed
**OR** 
You can do the previous steps for adding the image INFO.png as a texture to the object which contains the script INFO_v1.c.

## HOW TO USE

### In-world Second Life


- First of all paste the Linked object in-world. Instantly the object will communicate with you through chat and will provide a URL.

***IF YOU WANT TO JUST PLAY THE BOARD GAME EXCLUSIVELY  in SECOND LIFE then proceed to ignore this URL. You won't have to deal with it again in the future except if you delete the object and then paste it again.***


- After that, proceed to click the START button. Immediately a color sequence will be displayed through the 4 squared colored buttons. The colors of the buttons are: RED, GREEN, BLUE and YELLOW. When a button has to display a color of the wanted sequence it would flash(it will get brighter) indicating the wanted color sequence. An example of color sequence is this

```
GREEN, BLUE, BLUE, RED 
```
If user's guess of the color sequence is correct then the color sequence can be modified like this

```
GREEN, BLUE, BLUE, RED, GREEN
```

- Then, the user has to import his guess of the displayed color sequence. In-world Second Life this is possible with touching the correct color buttons in the correct order. When the user touches the last color button of his guessed color sequence, if it's correct the next color sequence will start automatically. Meanwhile, the game will communicate with the user through chat informing him that his guess was indeed correct, displaying the "CORRECT" message.

- If user did a mistake throughout his answer, the game will instantly stop, it would be GAME OVER and a proper message will be displayed through chat.

- To start again the game all user has to do is to press again the START button and a new round of game will initialize.
    
- During a round of the game, user has the ability to reset( soft reset actually ) the game and idle it. This is the equivalent of a GAME OVER. It can be achieved while pressing the RESET button that is visible when the START button has been pressed.

- When the user ends his gameplay, it is advised to hard reset the game so any generated URLs can be released. Even though this type of gameplay doesn't use the system's ability for two-way communication through dynamic generated URLs, the object generates automatically, one and only URL at the very beginning of its life, when someone pastes it in-world. The significance of releasing URLs is further analyzed in the WARNING sector, further down the text. This hard reset can be achieved by pressing the rectangular beige button at the lower right corner of the in-game tablet.

### Web Browser

- First of all paste the Linked object in-world. Instantly the object will communicate with you through chat and will provide a URL.

- Click the URL that is being displayed in chat. It should look something like this

```
e.g http://sim10186.agni.lindenlab.com:12043/cap/469d084a-e1ab-2e35-6e6d-95c3d6f464b0 
```
It will open a window in Second Life with a QR code.
#### Smartphone Web Browser

- Scan the QR code with your smartphone's camera. It should open a window of your default Web Browser with a simple interface of a START button and 4 colored buttons The basic rules of the game are the same with the in-game gameplay.

- A colored sequence will be generated in Second Life and it will be sent through URL, to the opened window. There, the 4 buttons will flash accordingly and the user should press the buttons in the correct order.

- If the user presses a wrong button then the game is finished, GAME OVER will be displayed and also the final score will be visible.

- To initialize a new game all the user has to do is to press START GAME into the smartphone Web Browser. Note that with this feature the smartphone can be used not only with the utility of a controller that goes with the second life, but also totally independently.

- In this state the smartphone can be operating wherever the user desires to if only it utilizes with a stable internet connection.

- The generated URL and also the generated QR code can be copied and shared to whomever the user wants but only one user can be operating the game at a time.


#### Any other kind of Web Browser

- Copy the generated URL in Second Life. The URL looks like this 
```
e.g http://sim10186.agni.lindenlab.com:12043/cap/469d084a-e1ab-2e35-6e6d-95c3d6f464b0
```
- The desired Web Browser should be opened.
       
- Navigate to this page **http://siwonsimon.000webhostapp.com/siwonsimon.html?**

- Paste the generated URL after the question mark of the above link and press enter. It should look something like this 
```
e.g http://siwonsimon.000webhostapp.com/siwonsimon.html?http://sim10186.agni.lindenlab.com:12043/cap/469d084a-e1ab-2e35-6e6d-95c3d6f464b0
```
- To initialize a new game all the user has to do is to press START GAME into Web Browser. Note that with this feature the smarthphone can be used not only with the utility of a controller that goes with the second life, but also totally independently.

- In this state the web browser can be operating wherever the user desires to if only it utilizes with a stable internet connection.

- The generated URL can be copied and shared to whomever the user wants but only one user can be operating the game at a time.

- The Second Life script should be operating the whole time.

- When the user wants to terminate the game AND the URL, it is advised to release the operating URL using HARD RESET. This will release the URL and the former communication with every browser won't be operational.

- To generate a new URL the user has to press the triangle button( Δ ) at the bottom-center of the tablet in Second Life. This will generate a new URL and it will display it through in-game chat, like before. From there, the previous steps in sectors of **Smartphone Web Browser** and  **Any other kind of Web Browser** are applicable.


## IMPORTANT

### URL RELEASING

  It is advised that URLs should be released before a new one is generated or after the terminal of gameplay time. That's because URLs tend to exist even after
the game is closed and the object has been deleted. They also possess a physical space in the memory of a destination in Second Life. That means that if 
an in world destination has a capacity of 1000 prims( type of object in Second Life ) then it could be filled with 1000 URLs and its owner would not be able
to build or script anything. This can result to banning users from certain areas, if they don't own the land.
  Second Life has foresighted this problem and has implemented an auto-URL-releaser. However, this releaser doesn't work instantly and doesn't have perfect
perfomance.

### SCRIPTING AND BUILDING IN SECOND LIFE

  If you don't own land or don't rend land in Second Life, you can open, modify and copy this project in a destination in Second Life that 
scripting and building are permitted.

### USE OF PRODUCT

Copyright (c) 2011-2017 GitHub Inc.
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*PROPERTY OF PETROS SALEPIS*
