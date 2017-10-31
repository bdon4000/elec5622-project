#ifndef ALLSERIALHANDING_H
#define ALLSERIALHANDING_H
extern volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
extern volatile int Signal;                // holds the incoming raw data
extern volatile int IBI;             // int that holds the time interval between beats! Must be seeded!
extern volatile int Signal;
extern void serialOutput();
extern void serialOutputWhenBeatHappens();
extern void Pulse_Init();
extern void Pulse_Allot();
extern void PulseSensor_SD_Write();

#endif
