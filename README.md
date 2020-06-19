# Instructions on Installing and getting the Program running in Windows 10:
This is assuming you have MinGW previously installed. If you don&#39;t have [MinGW](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-posix/seh/x86_64-7.3.0-release-posix-seh-rt_v5-rev0.7z/download) and [Geany](https://download.geany.org/geany-1.36_setup.exe) installed, you will need to set up them first. You can download them for windows by clicking their names.

1. Download SFML from the following link
   https://www.sfml-dev.org/download/sfml/2.5.1/
      - Download the SMFL for the version of MinGW that you have.
      - How to check MinGW version
            - Go to powershell
            - in the commandline type "g++ --version"
      - If your MinGW compiler version is same as one of the SFML version in the website download that SFML installer.
      
        <img width="708" alt="2020-06-12 (2)" src="https://user-images.githubusercontent.com/66412829/84852323-a3610a80-b0b0-11ea-842e-799edee89310.png">
      - If you don't have the correct version or don't have MinGW compiler --> MinGW Builds 7.3.0 (64-bit) download it from this website, link is in the orange box. You will need to set up MinGW first.
      
**Setting up MinGW Compiler**

      - Extract the MinGW compiler and save it in computer
      - If you have trouble extracting it:
            - Download BreeZip from your Microsoft Store.
            - Open the installed MinGW compiler folder in BreeZip adn extract it
      - In the MinGW find the bin folder and copy the path of that directory
      - Then in your computer go to system --> Advanced system settings --> Environment variables --> Under system variable select Path
        and click Edit --> New --> paste your copied directory of the path of bin folder in MinGW into it.
      - Check if the MinGW compiler is installed:
            - Open Window Powershell --> type in g++ --> if you see message "fatal error: no input files" then you are good.
      - Now you should be able to run C++ language in any platform that accomodate it
      - Now you can go ahead and download the same version of SFML.
      
 2. Save your SMFL folder.
      - After you have downloaded it you will need to extract it, to do this you can right click the downloaded zip folder and select "extract all" and pick where you want to save the SFML folder.
      - Pick somewhere in your file explorer where you can find it again.
 3. Download AVC_Win10.zip, extract and save that to a folder.
      - You can easily download it by [clicking this link](https://ecs.wgtn.ac.nz/foswiki/pub/Courses/ENGR101_2020T1/Project3/AVC_Win10.zip).
      - To extract it you can right click the downloaded zip folder and select "extract all" and pick where you want the AVC_Win10 folder to be saved.
 4. Edit the makefile that is in "AVC_robot" and "AVC_server" folders.
      - To do this first open up the file "makefile" in the "AVC_server" folder in the "AVC_Win10" folder that you previously downloaded and extracted. You can do this using Geany (right click file and choose "Open with Geany").
      - The first line of the file should be "DIR = C:\\\SFML", we need to replace "C:\\\SFML" with where your SFML folder is.
      - To do this you need to find where you saved your SFML folder in file explorer and open that folder. Make sure the folders in the folder you're in are "bin", "doc", "examples" and so on, otherwise your not in the correct location.  
      - Then right click on the file address along the top (it should be something like "> This PC > Windows(C:) > SFML", but can vary greatly depending on where you saved your SFML folder) and select "Copy address".
      - Paste your newly copied address in to replace "C:\\\SFML" in the first line of the "makefile" you opened and save it.
      - Within the "AVC_robot" folder also within the "AVC_Win10" folder you will find another file called "makefile". Open this file as well and paste the file address of your SFML folder over "C:\\\SFML" as well, just like you just did for the first "makefile".
  5. Setup "**robot.cpp**" from this GitHub repository.
      - Select "robot.cpp" from this GitHub repository (it's probably just above this) and select it so you are looking at the code.
      - Select ALL the code for "robot.cpp" and nothing more, then copy it.
      - With Geany open "robot.cpp" in the "AVC_robot" folder and delete all the code there so you can paste in the code you just copied.
 6. Now you need to make the executable files for the robot and server3
      - To do this first open "server3.cpp" in the "AVC_server" folder using Geany.
      - Add a space anywhere in the document (such as the end of the first line) and then delete the space you just added (this marks the file as changed so you can remake it).
      - Then from along the top select "Build" and then "Make" from the dropdown menu. This should make the file compile successfully if all previous instructions were followed correctly.
      - Repeat what you did for "server3.cpp" on "robot.cpp" in the "AVC_robot" folder. To do this open it in Geany and just select "Build" then "Make" like before.
      - After you make each of these it should say "compilation completed successfully" in the box at the bottom of Geany. If it instead says "Compilation failed" you either entered the file address wrong or more likely you have the wrong version of SFML, so go back and select a different version of SFML and try that.
 7. Now you should be able to make the program run.
      - Make sure you have "server3.cpp" and "robot.cpp" open in Geany.
      - Go to "server3.cpp" and press the execute option above the code, or you could just push f5 of your keyboard. This should bring up the robot unmoving on a green environment. If anything pops up warning you about running the program make sure you tell it that you trust the file and you want it to run (you can trust our program).
      - Switch back to your Geany window and execute "robot.cpp" the same way as well (you may need to push execute twice to make it run).
      - The program is now running so switch over back to the window that showed the robot on the green environment and watch it get to the flag!
      - To run the program again just repeat this step. Note: before you can run the program again you must shut ALL windows that popped up when the program was run.
 7. If you want to change it so the robot does a different course:
      - AVC_server Folder --> open config.txt --> change where it says "core.txt" on the first line to "completion.txt" or "challenge.txt" to run the different course.


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



# PLAN

| Objectives | Due date | Item due | Tasks |
| --- | --- | --- | --- |
| Start the project | 4 June | Planning of how the project is | Gather as a group to complete AVC planAs a group tests all installations. Help to install SFML on all team computers if they are having problems. Each group member should get started on keeping a log what they are doing (such as getting the program started). This allows us to start the process of tracking how the progress is coming along. |
| Core and completion | 11 June | Core and completion code | Write code so robot can follow a line so it can complete the core.Write Extend the code for the robot so that it can also do the completion maze as well. Ethan will be in charge the coding primarily, and that progress is being made to reach our deadline. Jaedan and Katatu will assist with coding and debugging it to see if robot is &quot;flawless&quot; at achieving the goal. Alongside, making sure that code is written well and easy to follow.Suvee in charge of the report and planning of meetings. Ensuring that people are doing what they are supposed to, and we are an effective team.We will all ensure we keep in communication with each other. We need at hold least weekly meeting with each other so that we can together and discuss progress. This should be done on the 11 June (or earlier if progress is good). |
| Challenge | 18 June | Challenge code | Get Challenge Code completedEthan will oversee writing a detailed procedure to ensure our program can be easily downloaded and run by anyone. Other members will need to test these instructions to ensure they are of a high quality.This second week should go a lot like the previous one did. So, we plan on everything running the same. Suvee is in charge of overseeing that the noncoding related aspects progress smoothly and Ethan is in charge of overseeing the coding related aspects.Record all the discussions regarding the Challenge code and have a meeting near the end of this week to ensure already to handed in our code. |
| Project codeGroup Log | 19 June | Core, Completion, Challenge all turned in. | Ethan will do a final run through and make sure everything is working as it supposed to be. |
