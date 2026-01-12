# **Autonomous Claw Gripping Mechanism**

## Introduction
The original intention behind this project was to design and develop a drone mechanism that was capable of autonomously going to a location, detecting an object using Computer Vision, and then using sensors (ultrasonic sensors and limit switches) to sense proximity to the object and how well gripped the object is. Because of timeline constraints and project requirements, my partner, Rayyan, and I pivoted. We focused on developing the claw mechanism and will continue the project outside of the class when time permits. This GitHub goes over our design process, objectives, and progress for the claw gripping mechanism. 

## Concept
Utilizing the PLTW curriculum, the mechanism was analyzed through a state machine-like perspective. A flowchart was developed to describe what the claw was designed to do. This visulization was useful in keeping a scope of the project consistent, and also serves as a coding flowchart for what the code should reflect. 

## Part Selection
### Sensors
An ultrasonic sensor was necessary to sense the distance from the claw gripping mechanism to the object. The [Elegoo HC-SR04](https://us.elegoo.com/products/elegoo-ultrasonic-sensor-kit?srsltid=AfmBOopR5ByhwLNMcnsA_8Amvfx4RrA7DNE-4UT02PolGaRuG4Qwy_L2) was chosen because it is inexpensive but does the job, and works well with most microcontrollers such as Arduinos and ESP32s

To detect the object, a couple of options could be pursued. A force sensor could be embedded into the prong of the claw. A limit switch could also be embedded into the prong of the claw. Ultimately, the final decision was to go with a limit switch-like system where a mini pushbutton switch would cause the claw prong to stop via GPIO pins and a pull-up circuit. 

### Motor
A motor was necessary to drive the claw mechanism. Using gears mitigating having multiple motors to drive the two prongs. A stepper, servo, or continuous servo motor would suffice. In the selection process, it was pivotal to have a claw with high torque. In the end, the [DS3235SG Servo Motor](https://www.amazon.com/ZOSKAY-Coreless-Digital-Stainless-arduino/dp/B07SBYZ4G5?th=1) was selected because of its high reliability, control angle, and sufficient grip strength. 

### Microcontroller
A microcontroller was necessary to process sensors, handle inputs, and exert outputs. Because of the price-constraints relating to the project, our options were narrowed down to an Arduino Uno R3 and the ESP32 S3 Dev board. In the drone, it would be important to have a WiFi and Bluetooth system to communicate commands from the ground station to the drone. Due to the [ESP32 S3](https://lonelybinary.com/en-us/products/s3?variant=43784065712285) having Bluetooth capabilities, it was selected for the claw gripping mechanism. 

### CAD Model

### Claw Mechanism
The claw mechanism uses double-helical gears, known for their superior load capacity and high efficiency, to drive the claw prongs. Liam Sagi and I collaborated on the claw mechanism, as both of our projects required a claw gripping mechanism. 

📦 **STL (3D Preview Available):**  
[Original Full Assembly](CAD/Original_Full_Assembly.stl)

However, our mechanisms differed in housing a system that would be able to detect when an object was fully gripped. I made modifications to the CAD file and created housings for mini pushbuttons to be housed.
