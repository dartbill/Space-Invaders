__BILLIE_DARTNELL_s5005667__

__Introduction__
This game looks at creating a simple topdown 2D shooter game, similar to space invaders. To make this game, I used qt creator, the NGL library and OpenGL. This report details my research and implementation of this game and what I could do in the future to improve it.

__Research__
![Space Invaders](/Images/spaceinvaders.png)
(What 40 years of 'Space Invaders' says about the 1970s – and today, 2020)

For my research it was important that I looked at how Space Invaders worked to find out the key elements of the game. From my research I found that Space Invaders is a fixed shooter in which the player controls a ship at the bottom of the screen that fires at aliens that move from side to side as they move down the screen. (Space Invaders, 2020). These were the key points from the game that I intended to replicate. However in the original game there were also protective bunkers in front of the player which were gradually destroyed by blasts from the player or the aliens (Space Invaders, 2020).

Vector arrays were a key part of my game, I chose them as they were dynamic, they have the ability to automatically resize itself when an element is added or removed (Array of Vectors in C++ STL - GeeksforGeeks, 2020). This was important so that I could condense all the invaders into a single array that I could resize as the game went on, so it was important I researched into them further. Vector arrays have a function that allows the user to add as many elements as they wanted to the array so that there was no set limit, .push_back(), this meant if I wanted to change the amount of invaders in my game it was easy to do, as well as adding different levels in the future if I wanted to. Another aspect of vector arrays is the ability to erase the element during runtime using .erase() this meant that I could use this to control how many invaders were in the array at any one time however using a range based loop didn’t work (Remove elements from a vector inside a loop in C++ - Techie Delight, 2020) this article explains that using the erase() method on the vector whilst in a loop invalidates the iterator and that a manual for loop would be needed to work around this.


__Implementation__

To start my game, I first needed to set up a camera. To do this I used a struct with two ngl::Mat4 elements, view and project,  I could then, in NGLScene, declare the view and project which could then be passed into my draw functions. 

Within my draw functions I took the project and view and used it to render the elements by setting the transformation and then multiplying it by the product of the view and project. and using that for the uniform shader. For the invaders I used the default troll from the NGL library and looped the x,y values to create three rows and incremented by 2 so that the invaders wouldn’t touch the gap created added difficulty when trying to hit the invaders, with the player I used an obj file from turbo squid (Viper Obj) which I used a VAO to load it in. For the bullets I chose to use OpenGL’s in built GLPoint, this meant I could control the size of the bullet and as it’s stored in a dynamic array like the invaders it also has the potential to allow more than one bullet on the screen at any one time.

![Viper model](/Images/viper.png)

An important aspect of the game is the timer. The bullet needed to move faster than the invaders to make it possible to win, this meant I needed two timers, by using two timer ID's I could separate the two and have them run at different speeds.

My next step was to add controls to the player, for this I used QT Creator's key press event and a switch statement to see which key was pressed. When the left or right arrow key was pressed it  added to a integer variable which was passed into the player move function which would move the spaceship accordingly, iIalso added an if statement here to check whether the player was going out of bounds and stopped them if so. Within the switch statement it also checked to see if the spacebar was pressed and if pressed would reset the bullets position and I used a bool to see whether or not to draw the bullet, this is changed in the space bar switch case if it needs to be drawn or not.
To move the invaders, I looped over the array and had them go just down with the timer at first however I wanted them to move side to side before going down like in the orginal game. Although I didn’t get the movement I wanted, I managed to get the invaders to move to the side before going down diagonally, to do this I checked to see if the invaders x position was odd or even and moving them accordingly. This still made the game more challenging than if I had left at them going straight down.

In order for the player to win or lose I needed to add collision detection. Since it was a top down game I only needed to use the x and y coordinates and I decided to use integers for the positions to make it simpler for the collision detection. To check if a bullet had hit an invader, I passed the bullets position into the invader collision function which then, using if statements, checked to see if the bullet’s x and y equalled the specific invaders position and if so, returned true so that it was known to erase that invader from the array and to stop drawing the bullet. I used the same function to check if the invaders had hit the player, i just passed the player’s coordinates in instead. 

Finally I needed to add a win or lose aspect to the game, to do this I check to see if the player has killed all the invaders by checking the size of the invader array, if it equals 0 the player has won and the game displays “You Won!”, I also added a score to the game, whereby one alien equals one point. If the Invaders either hit the player or the bottom of the screen, they stop moving and “Game Over” is displayed. To stop the game automatically starting when you run it I added in a bool that turns to true when the space bar is pressed, which starts the invaders movement

![Start Screen](/Images/spaceinvadersmine.png)

__Conclusion__
In conclusion, I am happy with the game I have created, the collision detection works well and even though the players are simple it looks good. To improve this game I would add protective bunkers and get the invaders to fire back, I could also add more levels for when the player kills all the invaders.


__References__

En.wikipedia.org. 2020. Space Invaders. [online] Available at: <https://en.wikipedia.org/wiki/Space_Invaders>.

GeeksforGeeks. 2020. Array Of Vectors In C++ STL - Geeksforgeeks. [online] Available at: <https://www.geeksforgeeks.org/array-of-vectors-in-c-stl/>.

Techie Delight. 2020. Remove Elements From A Vector Inside A Loop In C++ - Techie Delight. [online] Available at: <https://www.techiedelight.com/remove-elements-vector-inside-loop-cpp/>.

The Conversation. 2020. What 40 Years Of 'Space Invaders' Says About The 1970S – And Today. [online] Available at: <https://theconversation.com/what-40-years-of-space-invaders-says-about-the-1970s-and-today-97518>

Viper Obj file https://www.turbosquid.com/FullPreview/Index.cfm/ID/612994
