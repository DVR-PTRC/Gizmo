# Gizmo
Code for Gizmo project - Group 8

Code Brief:

Control two groups of modular mechanisms to make music with harmonicas and piezo electric sensors.

•	Harmonica group: there are three identical mechanisms each made by a linear motion system that move and play a harmonica using a pulley and belt arrange, each driven by a stepper motor. For the air supply and control each module have a 3d printed valve driven by a micro servo.

•	Fingers group: there are four identical mechanisms each made by a mechanical finger, made by a three linkage system driven by a servo motor that moves to touch a piezo electric to trigger a signal that is processed by a computer to make a note or a percussion sample.

Code requirements:

•	Drive 2 or more steppers motors at the same time.
•	Drive 7 servo motors at the same time.
•	Store one or more songs in musical notation with its tempo for each note.
•	Play each modular mechanism by checking the tempo (time between execution).
•	Check the state of the piezo electric sensor to send a serial message to a computer to play sample sounds.
•	Do all other requirements at the same time, based on time and sensors events routine without using delay function.

Code description:

The code work as an event base routine so the program in every loop will drive all the actuators at the same time (servo motors and steppers motors), review the state of the sensors (piezo electrics) and check the time to play the instruments. For this Project we decide to use object oriented programing because we have modular mechanisms so if the amount of modules changes, the code will easily adapt to it. To drive the stepper motor, we used a library that can handle multiple steppers at time, using timers instead of delay to not interfere with the program routine. Finally, to store the music we used a two-dimensional array, storing in the first column the note to be played and its tempo in the second column, so each time that the program plays a note it reads the next row. 




