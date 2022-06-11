# DC-Motor-PID-Control-System

   I connected DC motor to Arduino and motor driver and examined encoder motor output-A and output-B rising edges on oscilloscope to get motor's position information. When I control without PID, motor had resonance, it generated vibration. So, , I created PID control algorithm and determined PID tuning parameters value which are Kp, Ki, Kd on Matlab. Finally, test results were as expected. Motor didn’t have resonance or vibration.
