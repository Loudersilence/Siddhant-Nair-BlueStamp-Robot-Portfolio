# 3 Joint Robotic Arm

Replace this text with a brief description (2-3 sentences) of your project. This description should draw the reader in and make them interested in what you've built. You can include what the biggest challenges, takeaways, and triumphs from completing the project were. As you complete your portfolio, remember your audience is less familiar than you are with all that your project entails!

You should comment out all portions of your portfolio that you have not completed yet, as well as any instructions:
```HTML 
<!--- This is an HTML comment in Markdown -->
<!--- Anything between these symbols will not render on the published site -->
```

| **Engineer** | **School** | **Area of Interest** | **Grade** |
|:--:|:--:|:--:|:--:|
| Siddhant N | Mission San Jose High school | Mechanical Engineering | Incoming Senior

**Replace the BlueStamp logo below with an image of yourself and your completed project. Follow the guide [here](https://tomcam.github.io/least-github-pages/adding-images-github-pages-site.html) if you need help.**

![Headstone Image](logo.svg)
  
# Final Milestone

**Don't forget to replace the text below with the embedding for your milestone video. Go to Youtube, click Share -> Embed, and copy and paste the code to replace what's below.**

<iframe width="560" height="315" src="https://www.youtube.com/embed/F7M7imOVGug" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

For your final milestone, explain the outcome of your project. Key details to include are:
- What you've accomplished since your previous milestone
- What your biggest challenges and triumphs were at BSE
- A summary of key topics you learned about
- What you hope to learn in the future after everything you've learned at BSE



# Second Milestone

**Don't forget to replace the text below with the embedding for your milestone video. Go to Youtube, click Share -> Embed, and copy and paste the code to replace what's below.**

<iframe width="560" height="315" src="https://www.youtube.com/embed/y3VAmNlER5Y" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>


For my second milestone, I implemented a Raspberry Pi and a Pi camera into my project. I added the Pi and the Pi camera so that the claw can have the ability to identify specific objects and pick up specific items. So far I have established the serial communication between the Arduino Nano and the Raspberry Pi. I have also been able to get the Pi camera and object recognition working using the coco library to be able to identify a few different items.


## Challenges
- Struggling to get the Arduino IDE to work on the raspberry pi. To solve the issue, I did some research, and with the help of my instructor Katie, I figured out that I had the wrong version of the IDE. I had the linux 32arm and instantly switched to the Linux 64arm.
- Downloading the open CV for object detection. I was not able to download the libjasper package required for object detection because it wasn't recognized or wasn't available on the latest OS of the Raspberry Pi (bullseye). To fix this, I flashed my micro SD to an older buster, specifically the one released in May of 2021. This seemed to fix my problem I was able to get object detection working.

## Steps towards final milestone
- To bring this robot together, I plan on integrating the Raspberry Pi and the camera into the arm so that they can work together to complete certain tasks like recognizing and picking up a specific object when instructed.
- I may also add a rubber sleeve to the claws to be able to grip items better

# First Milestone

**Don't forget to replace the text below with the embedding for your milestone video. Go to Youtube, click Share -> Embed, and copy and paste the code to replace what's below.**

<iframe width="1083" height="609" src="https://www.youtube.com/embed/9bqB15PK2Zs?list=PLe-u_DjFx7eticgHvdNBMS-CTTohSGwUM" title="Siddhant N  First Milestone" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
  
- The project I have chosen is the 3 joint robot arm which uses a total of 4 servos. The arm can pick up and drop small lightweight objects. The arm can move objects from one place to another using the servo which rotates the bottom platform with the help of a large bearing- So far I have made the base model of the robotic arm which is controlled using two joysticks connected to an Arduino Nano that instructs the servos on the arm as per the input from the joysticks.	 
## Challenges
- The flimsy base piece broke and was later replaced.
- One of the servos stopped functioning because it was burnt out 
- The big bearing for the platform was too rough for the small MG90s servo to push around. I fixed this issue by using basic bicycle chain lubricant which worked perfectly and made the bearing smooth enough for the servo to move the arm around.
## Further improvements
- For the claw to pick up a variety of differently shaped items, I plan on adding another servo to the arm that rotates the claw so it can better position itself to pick up different items.
- I also plan on connecting a Rasberry Pi and a Pi camera to the robot arm for color and object detection so the arm can recognize objects around it and hopefully be commanded to pick up specific objects.
  
# Schematics 
Here's where you'll put images of your schematics. [Tinkercad](https://www.tinkercad.com/blog/official-guide-to-tinkercad-circuits) and [Fritzing](https://fritzing.org/learning/) are both great resoruces to create professional schematic diagrams, though BSE recommends Tinkercad becuase it can be done easily and for free in the browser. 

# Code
Here's where you'll put your code. The syntax below places it into a block of code. Follow the guide [here]([url](https://www.markdownguide.org/extended-syntax/)) to learn how to customize it to your project needs. 

```c++
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello World!");
}

void loop() {
  // put your main code here, to run repeatedly:

}
```

# Bill of Materials
Here's where you'll list the parts in your project. To add more rows, just copy and paste the example rows below.
Don't forget to place the link of where to buy each component inside the quotation marks in the corresponding row after href =. Follow the guide [here]([url](https://www.markdownguide.org/extended-syntax/)) to learn how to customize this to your project needs. 

| **Part** | **Note** | **Price** | **Link** |
|:--:|:--:|:--:|:--:|
| 3 Joint Robotic Arm| Used as the base model for the robotic arm | $50 | <a href="https://www.amazon.com/LK-COKOINO-Compliment-Engineering-Technology/dp/B081FG1JQ1"> Link </a> |
| Servo Shield | Replace orginal shield to use 9v batteries | $10.99 | <a href="https://a.co/d/gEROH1a"> Link </a> |
| 9V batteries | Used to power the robotic arm | $8.99 | <a href="https://a.co/d/fZLAYWA"> Link </a> |
| Screwdriver Kit | Used to assemble the robotic arm | $7.99 | <a href="https://www.amazon.com/Small-Screwdriver-Set-Mini-Magnetic/dp/B08RYXKJW9/"> Link </a> |
| Raspberry Pi 4B | Used connect the pi camera to the arm and for object recognition | $105 | <a href="https://a.co/d/0bOvawIx"> Link </a> |
| Pi camera | used for object recognition | $10 | <a href="https://a.co/d/0j8dtRFs"> Link </a> |
| 9V Barrel Jack | Used to connect the 9V battery to the servo shield | $5.99 | <a href="https://a.co/d/hVp96Vq"> Link </a> |
| 9V Barrel Jack | Used to connect the 9V battery to the servo shield | $5.99 | <a href="https://a.co/d/hVp96Vq"> Link </a> |


# Other Resources/Examples
One of the best parts about Github is that you can view how other people set up their own work. Here are some past BSE portfolios that are awesome examples. You can view how they set up their portfolio, and you can view their index.md files to understand how they implemented different portfolio components.
- [Example 1](https://trashytuber.github.io/YimingJiaBlueStamp/)
- [Example 2](https://sviatil0.github.io/Sviatoslav_BSE/)
- [Example 3](https://arneshkumar.github.io/arneshbluestamp/)

To watch the BSE tutorial on how to create a portfolio, click here.
