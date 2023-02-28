#pragma once
#include <stdio.h>
class Pid
{
public:
	Pid( double propGain = 1.0, double derGain = 1.0, double intGain = 1.0, double deadband = 0.0 );

	double calc( double curError, double deltaTime = 0.001 );

	void setPropGain( double val ) { propGain_ = val; }
	void setDerGain( double val ) { derGain_ = val; }
	void setIntGain( double val ) { intGain_ = val; }
	void setDeadband( double val ) { deadband_ = val; }
	double propGain() { return propGain_; }
	double derGain() { return derGain_; }
	double intGain() { return intGain_; }
	double deadband() { return deadband_; }
	void setIntegError(double integral) { integral_ = integral; } 
    void ResetError() { lastError_=0 ; }
private:
	double propGain_;
	double derGain_;
	double intGain_;
	double deadband_;

	double lastDerValue_ = 0;
	double lastDerAbsTime_ = 0;

	double lastIntValue_ = 0;
	double lastIntAbsTime_ = 0;
	double intValueCarry_ = 0;

	double lastError_ = 0;
	double integral_ = 0;

	double m_delta_Time = 0;
	double result = 0;

	double derivative( double value, double deltaTime = -1, double absTime = -1);
	double integral( double value, double deltaTime = -1, double absTime = -1, bool reset = false );
};
