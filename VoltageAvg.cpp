/**
* @author Rhys Bryant <code@voltprojects.com>
* basic library for calculating a moving average of a given voltage
* if you can see an issue or better way please report a bug
* @copyright Rhys Bryant <code@voltprojects.com>
*
* === Legal Jargen  ===
* This code is provided "AS IS" without warranty of any kind.
*   In no event shall the author be held liable for any damages arising from the
*   use of this code.
* @licence LGPL
* this notice MUST not be removed
*/

#define VoltageAvg_CPP 1
#ifndef VoltageAvg_H
#include "VoltageAvg.h"
#endif

class VoltageAvg {
private:
    unsigned int samples[16];
    int sampleCount;
    int last;
    static float refVoltage;
    float voltageDiff;
	static unsigned long lastUpdate;//only update every x ms
public:
    float v;
    int pinNum;//the pin number to work on
    static void setRefVoltage(float v_) {
        refVoltage=v_;
    }
	static float getRefVoltage(){
		return refVoltage;
	}
	/**
	* this calculates the voltage Devider value.
	* based on the values of 2 resistors see http://en.wikipedia.org/wiki/Voltage_divider
	**/
	void setDeviderDiff(unsigned long r1,unsigned long r2){
		voltageDiff=((refVoltage*(r1+r2)/r2)/1023);
	}
	/**
	* set the voltage voltageDiff value
	**/
	void setDiff(float value){
		voltageDiff=value;
	}
	/**
	* adds an analog value to the samples array for later converting to a voltage based on the value of voltageDiff
	* @param voltage the value from a call to analogread()
	**/
    void addReading(int voltage) {
		//Serial.println(voltage);
        last=voltage;
		//move all the samples along by 1 to make room for the new value
        if(sampleCount>=15) {
            for(int i=1; i<=sampleCount; i++) {
                samples[i-1]=samples[i];

            }
            sampleCount=15;

            samples[sampleCount]=voltage;
        }

        else {//we have not reached the max number of samples then just add the value to the end
            samples[sampleCount]=voltage;
            sampleCount++;

        }
    }
	/**
	* calculates the average value based on the array of samples and returns it
	**/
    double calcAvg() {
        unsigned int total=0;
        double tmp=0.0;
       //count the values of each sample to get the total value
        for(int i=0; i<sampleCount; i++) {
            //Serial.print(samples[i]);
            //Serial.print(",");
            total+=samples[i];
        }
        //Serial.print("}");
        tmp=((total+.0)/(sampleCount+.0));
        //Serial.println("\n");
		//Serial.println(total);
        return tmp;
    }
	/**
	* adds the value from a call to analogRead(pinNum) to the samples array and recalculates the average.
	* will only recalculate if the time diffence beteewn the last check and now is >UPDATE_DELAY
	* @return true if the average value has changed
	**/
    bool update() {
		//updating delay
		unsigned long m=millis();
		if(m-lastUpdate<UPDATE_DELAY)
			return false;
		else
			lastUpdate=m;
	
        addReading(analogRead(pinNum));
        float tmp=0;

        tmp=voltageDiff*calcAvg();

        if(tmp!=v) {// && (tmp-v>0.01 || v-tmp>0.01)
            v=tmp;

            return true;
        }
        else
            return false;
    }
};