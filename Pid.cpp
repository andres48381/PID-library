#include "Pid.h"
/**
* @brief Class constructor. Init Ctes.
* @param propGain Cte Kp
* @param derGain Cte Kd
* @param intGain Cte Ki
* @param deadband_ Dead zone 
*/
Pid::Pid( double propGain /*= 1.0*/, double derGain /*= 1.0*/, double intGain /*= 1.0*/, double deadband /*= 0.0 */ )
	: propGain_( propGain ), derGain_( derGain ), intGain_( intGain ), deadband_( deadband )
{
}
/**
* @brief calculate de new error value
* @param curError actual error value
* @param deltaTime cycle tyme
* @return new error value
*/
double Pid::calc( double curError, double deltaTime /*= 0.001 */ )
{
	if(deltaTime > 0.0 /*&& (curError>deadband_)*/) {
		
		m_delta_Time = deltaTime;

		integral_ = integral_ + curError * m_delta_Time;
		double d = (curError - lastError_) / m_delta_Time;
		result = propGain_*curError+ intGain_*integral_ + derGain_*d;
		lastError_ = curError;
	}
	else
	{
		printf( "deltaTime can't be 0\n" );
	}

	return result;
}
/**
* @brief Get integrated error
* @param value Cte actual error value
* @param deltaTime cycle tyme
* @return derivated error
*/
double Pid::derivative( double value, double deltaTime /*= -1*/, double absTime /*= -1*/)
{
	double timeDiff = 0; 

	if( deltaTime == -1 ) {
		timeDiff = absTime - lastDerAbsTime_;
	} else if( absTime == -1 ) {
		timeDiff = deltaTime;
	} else {
		printf( "Either a deltaTime or an absTime argument must be supplied\n" );
	}
	if( timeDiff == 0 ) {
		printf( "Time Difference Cannot Be Zero, Exiting Deravative Calculation\n" );
	}

	double ret = (value - lastDerValue_) / timeDiff;

	lastDerAbsTime_ = absTime;
	lastDerValue_ = value;

	return ret;
}
/**
* @brief Get integrated error
* @param value Cte actual error value
* @param deltaTime cycle tyme
* @return integrated error
*/
double Pid::integral( double value, double deltaTime /*= -1*/, double absTime /*= -1*/, bool reset /*= false */ )
{
	double timeDiff = 0; 

	if( reset ) {
		intValueCarry_ = 0;
		return 0;
	}

	if( deltaTime == -1 ) {
		timeDiff = absTime - lastIntAbsTime_;
	} else if( absTime == -1 ) {
		timeDiff = deltaTime;
	} else {
		printf( "Either a deltaTime or an absTime argument must be supplied\n" );
	}

	if( timeDiff == 0 ) {
		printf( "Time Difference Cannot Be Zero, Exiting Integral Calculation\n" );
	}

	double ret = (0.5 * (timeDiff * (value - lastIntValue_))) + (lastIntValue_ * timeDiff) + intValueCarry_;
	intValueCarry_ = ret;
	lastIntAbsTime_ = absTime;
	lastIntValue_ = value;
	if( timeDiff == 0 ) {
		printf( "Time Difference Cannot Be Zero, Exiting Integral Calculation\n" );
	}

	return ret;
}
