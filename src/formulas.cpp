#include <iostream>
#include <cmath>
using namespace std;
namespace Formula
{
	namespace Temperature
	{
		float ctof(const float temp)
		{
			return (1.8*temp)+32;
		}
		
		float ftoc(const float temp)
		{
			return (5.0/9.0)*(temp-32);
		}
	}
	
	namespace Alcohol
	{
		float ABV(const float OG, const float FG)
		{
			return (OG-FG) * 131;
		}
		
		// ABW is approximately 4/5 ABV
		float ABW(const float OG, const float FG)
		{
			return ABV(OG,FG) * 0.8;
		}
		
		/*
			Returns correction value for a 59F calibrated hydrometer at temperature f_temp
			
			equation found by performing a 3rd order polnomial fit on data from "Handbook of Chemistry and Physics (CRC)"
			in numpy
		*/
		float hydrometerCorrectionValue(const float f_temp)
		{
			return (1.3135066 - (0.13267572*f_temp) + (2.0578021e-3*(f_temp*f_temp)) - (2.6276568e-6*(f_temp*f_temp*f_temp)))*10e-3;
		}
		
		/*
			
		*/
		float hydrometerAdjustment(const float SG, const float f_temp)
		{
			return SG + hydrometerCorrectionValue(f_temp);
		}
	}
									
	namespace Color
	{
		static const string srmToRGBTable[] = {"F3F993","F5F75C","F6F513","EAE615","E0D01B",
												"D5BC26","CDAA37","C1963C","BE8C3A","BE823A",
												"C17A37","BF7138","BC6733","B26033","A85839",
												"985336","8D4C32","7C452D","6B3A1E","5D341A",
												"4E2A0C","4A2727","361F1B","261716","231716",
												"19100F","16100F","120D0C","100B0A","050B0A"};
								
		string srmToRGB(const float srm)
		{
			if(srm <= 30)
			{
				if(srm >= 1)
					return srmToRGBTable[(int)(srm)-1];
				return "000000";
			}
			return "FFFFFF";
		}
		
		float srmToEBC(const float srm)
		{
			return srm * 1.97;
		}
		
		float ebcToSRM(const float ebc)
		{
			return ebc * 0.508;
		}
		
	}
}


int main(int argc, char** argv)
{
	float og, sg;
	og = 1.051;
	sg = 1.011;
	cout << "OG: " << og << "   SG: " << sg << endl;
cout << "ABV: " << Formula::Alcohol::ABV(og,sg) << endl;
cout << "ABW: " << Formula::Alcohol::ABW(og,sg) << endl;
cout << "ftoc: " << Formula::Temperature::ftoc(32) << "  ctof: " << Formula::Temperature::ctof(0) << endl;
cout << "hydrometer adjust 1.051 at 77F: " << Formula::Alcohol::hydrometerAdjustment(1.051, 59) << endl;
cout << "hydrometer adjust 1.051 at 77F: " << Formula::Alcohol::hydrometerAdjustment(1.051, 77) << endl;
cout << "SRM 1.1 to RGB: " << Formula::Color::srmToRGB(1.1) << " SRM 29.8 to RGB: " << Formula::Color::srmToRGB(29.8) << endl;
cout << "SRM 0.1 to RGB: " << Formula::Color::srmToRGB(0.1) << " SRM 38 to RGB: " << Formula::Color::srmToRGB(38) << endl;
return 0;
}
