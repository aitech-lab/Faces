#pragma once
	
class Properties
{	
public:
	Properties(float _fStartingScale=0.6f, float _fScalingFactor=1.2f, int _nScales=12);
	~Properties();
	Properties(Properties &prop);

	Properties& operator=(Properties& prop);

	int findClosestScale(float scale);

	float fStartingScale;
	float fScalingFactor;
	int nScales;
	
	float *allScales;
};	