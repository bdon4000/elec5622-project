#ifndef INTERRUPT_H
#define INTERRUPT_H
extern volatile int rate[10];                    // array to hold last ten IBI values
extern volatile unsigned long sampleCounter;          // used to determine pulse timing
extern volatile unsigned long lastBeatTime;           // used to find IBI
extern volatile int P;                      // used to find peak in pulse wave, seeded
extern volatile int T;                     // used to find trough in pulse wave, seeded
extern volatile int thresh;                // used to find instant moment of heart beat, seeded
extern volatile int amp;                   // used to hold amplitude of pulse waveform, seeded
extern volatile boolean firstBeat;        // used to seed rate array so we startup with reasonable BPM
extern volatile boolean secondBeat;      // used to seed rate array so we startup with reasonable BPM
//  Variables
extern int pulsePin;                 // Pulse Sensor purple wire connected to analog pin 0
extern int blinkPin;                // pin to blink led at each beat
extern int fadePin;                  // pin to do fancy classy fading blink at each beat
extern int fadeRate;                 // used to fade LED on with PWM on fadePin

// Volatile Variables, used in the interrupt service routine!

extern volatile boolean Pulse;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
extern volatile boolean QS ;        // becomes true when Arduoino finds a beat.
extern void interruptSetup();

#endif

