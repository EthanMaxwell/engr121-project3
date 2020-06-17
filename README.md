ENGR101 Project 3 Plan

# Team Name: Group 1

# Team Members &amp; contact info:

Suveesthiga Sathiyaseelan

Katuta Mwila

Jaedan Ringrose Perez

Ethan Maxwell

# Communication tool:

- Facebook
- Email
- Zoom

# Roles:

Suveesthiga Sathiyaseelan - Project Manager, in charge on insuring that group log is updated regularly, and meeting are created and attended.

Ethan Maxwell – Lead coder, I we spearhead the coding operation for the team, making sure that code gets written and functioning.

Jaedan Ringrose Perez – Assistant coder and assistant project manager.

Katuta Mwila - Assistant project manager and assistant coder.

Github: [https://github.com/EthanMaxwell/engr121-project3](https://github.com/EthanMaxwell/engr121-project3)

# Instructions on Installing and geting the Program running in Windows:

1. Install MinGW compiler and SFML from the following link: 
   https://www.sfml-dev.org/download/sfml/2.5.1/
      - Make sure the that your MinGW and SMFL are the same version
        <img width="708" alt="2020-06-12 (2)" src="https://user-images.githubusercontent.com/66412829/84852323-a3610a80-b0b0-11ea-842e-799edee89310.png">
      - Download SFML installer --> GCC 7,3,0 MinGW (SEH) - 64-bit
      - If you don't have MinGW compiler --> MinGW Builds 7.3.0 (64-bit) download it from this website, link is in the orange box   
 2. Save both of them somewhere in you file explorer, it would be easy if you save it in the Window directory.
      - Create folder SFML and save the installed SFML in there    
 3. Download AVC Win10.zip, extract and save that to a folder
 4. Make a makefile for both robot and server and save them in their respective AVC_robot and AVC_server folder
    <img width="564" alt="2020-06-17 (17)" src="https://user-images.githubusercontent.com/66412829/84867972-12019080-b0d0-11ea-8f78-51461100c416.png">
      - The above example is for robot, so for server just change everywhere that says "robot" to "server3"
      - Change the Include and Lib directory to where ever you saved your SMFL. NOTE - if you saved it in window directory under                 folder "SFML" you don't need to change the directory
      - If you are running C++ in Geany, then go to Build --> Set Build Commands and instead of make enter mingw32-make
        <img width="362" alt="2020-06-17 (19)" src="https://user-images.githubusercontent.com/66412829/84869282-eed7e080-b0d1-11ea-86ac-f60e05461232.png">    
 5. Go to bin folder in the SFML and copy everything in that folder and paste it to both AVC_Robot and AVC_server folder
 6. Download the file "**NEED to ADD NAME**" from this GitHub repository and save it in AVC_Robot folder and rename it robot.cpp (if         it wasn't already name that) and replace any file with that name.
 7. Now you should be able to run the core program. In Geany: 
      - Open server3.cpp and its makefile
      - Open robot.cpp and it's makefile
       For both these go Build --> Make then execute
 8. If you want to change the program to run other program:
      - AVC_server Folder --> open config.txt --> change where it says "core.txt" to "completion.txt" or "challenge.txt" to run the             other program


# PLAN

| Objectives | Due date | Item due | Tasks |
| --- | --- | --- | --- |
| Start the project | 4 June | Planning of how the project is | Gather as a group to complete AVC planAs a group tests all installations. Help to install SFML on all team computers if they are having problems. Each group member should get started on keeping a log what they are doing (such as getting the program started). This allows us to start the process of tracking how the progress is coming along. |
| Core and completion | 11 June | Core and completion code | Write code so robot can follow a line so it can complete the core.Write Extend the code for the robot so that it can also do the completion maze as well. Ethan will be in charge the coding primarily, and that progress is being made to reach our deadline. Jaedan and Katatu will assist with coding and debugging it to see if robot is &quot;flawless&quot; at achieving the goal. Alongside, making sure that code is written well and easy to follow.Suvee in charge of the report and planning of meetings. Ensuring that people are doing what they are supposed to, and we are an effective team.We will all ensure we keep in communication with each other. We need at hold least weekly meeting with each other so that we can together and discuss progress. This should be done on the 11 June (or earlier if progress is good). |
| Challenge | 18 June | Challenge code | Get Challenge Code completedEthan will oversee writing a detailed procedure to ensure our program can be easily downloaded and run by anyone. Other members will need to test these instructions to ensure they are of a high quality.This second week should go a lot like the previous one did. So, we plan on everything running the same. Suvee is in charge of overseeing that the noncoding related aspects progress smoothly and Ethan is in charge of overseeing the coding related aspects.Record all the discussions regarding the Challenge code and have a meeting near the end of this week to ensure already to handed in our code. |
| Project codeGroup Log | 19 June | Core, Completion, Challenge all turned in. | Ethan will do a final run through and make sure everything is working as it supposed to be. |
