# Autonomous-Trash-Gathering-Car
 CIJE Hackathon 2024 1st Place - Car that detects and gathers green trash bins

## The challenge
- Build an autonomous car that can gather mini green trash bins by itself

## Features
- Self-driving
- Garbage-locating
- Garbage-gathering

## Tools Used
- Arduino IDE
- HuskyLens

## How to Use
Plug in the battery... the car will do the rest  

## How it works
- Autonomous Object Detection: Uses a HuskyLens AI camera in color recognition mode to continuously scan the environment and identify designated trash by its assigned ID (ID 1).
- Autonomous Navigation: Rotates in place while searching for the target. Once detected, the car uses the object's horizontal center position in the camera's field of view to determine whether to turn left, turn right, or drive straight toward it.
- Motor Control & Tracking: Uses an Arduino and motor driver to independently control two DC motors, adjusting their direction and movement timing to steer the car toward the detected object and pursue it.



## Results
CIJE Hackathon 2024 - Gathered the most garbage bins and won 1st place
