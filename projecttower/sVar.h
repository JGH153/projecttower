#pragma once
#include "string"


/*

sVar verson 1.2

*/

struct sVar
{
	//supports:
	//(i)nt, (f)loat, (c)har, (s)tring
	char currentType;

	//force same memory pos to save memory:
	union{
		int tInt;
		char tChar;
		float tFloat;
	};
	//a string can't be in an union:
	std::string tString;

	sVar(){
		currentType = 'i'; //default as 0 int
		tInt = 0;
		tString = "";
	}

	//convert whatever this instance contains to a int and return it:
	int thisToInt(){
		switch (currentType)
		{
			case 'c': return int(tChar);							break;
			case 'i': return tInt;									break;
			case 'f': return int(tFloat);							break;
			case 's': return atoi(tString.c_str());					break;
			default: return tInt;									break;
		}
	}
	float thisToFloat(){
		switch (currentType)
		{
			case 'c': return float(tChar);							break;
			case 'i': return float(tInt);							break;
			case 'f': return (tFloat);								break;
			case 's': return atof(tString.c_str());					break;
			default: return tFloat;									break;
		}
	}
	char thisToChar(){
		switch (currentType)
		{
			case 'c': return tChar;									break;
			case 'i': return char(tInt);							break;
			case 'f': return char(int(tFloat));						break;
				//retuns the first char in the string
			case 's': return tString[0];							break;
			default:  return tChar;									break;
		}
	}
	std::string thisToString(){
		
		switch (currentType)
		{
			case 'c': return std::to_string(tChar);						break;
			case 'i': return std::to_string(tInt);						break;
			case 'f': return std::to_string(tFloat);					break;
			case 's': return tString;									break;
			default: return tString;									break;
		}
	}
	

	void  operator ++ (){
		switch (currentType)
		{
			case 'c': tChar = char(int(tChar) + 1);					break;
			case 'i': tInt += 1;									break;
			case 'f': tFloat += 1.f;								break;
			
		}
	}
	void  operator -- (){
		switch (currentType)
		{
			case 'c': tChar = char(int(tChar) - 1);					break;
			case 'i': tInt -= 1;									break;
			case 'f': tFloat -= 1.f;								break;
			
		}
	}


	//set this class/array value to something:
	void  operator = (int number){
		currentType = 'i';
		tInt = number;
	}
	void  operator = (char number){
		currentType = 'c';
		tChar = number;
	}
	void  operator = (float number){
		currentType = 'f';
		tFloat = number;
	}
	void  operator = (std::string text){
		currentType = 's';
		tString = text;
	}

	//kalles når en ny utgave lages direkte
	sVar(int number){
		currentType = 'i';
		tInt = number;
	}
	sVar(char number){
		currentType = 'c';
		tChar = number;
	}
	sVar(float number){
		currentType = 'f';
		tFloat = number;
	}
	sVar(std::string text){
		currentType = 's';
		tString = text;
	}


	//kalles hver gang denne klassen prøves og legges sammen med en int i rekken først: this + int
	int operator+ (int tall2){
		return thisToInt() + tall2;
	}
	float operator+ (float tall2){
		return thisToFloat() + tall2 + 500; //500 ?
	}
	char operator+ (char char2){
		return char(thisToInt()+int(char2));
	}
	
	//kalles hver gang klassen blir bedt om å retunere en int, ala typecasting to int
	operator int(){
		return thisToInt();
	}
	operator float(){
		return thisToFloat();
	}
	operator char(){
		return thisToChar();
	}
	operator std::string(){
		return thisToString();
	}


	

	//for hver type av sammenligning mellom to sVar av typen (this < sVar):
	bool operator<(sVar typeTwo){

		switch (currentType){
			case 'c': return (tChar < (char)typeTwo);							break;
			case 'i': return (tInt < (int)typeTwo);								break;
			case 'f': return (tFloat < (float)typeTwo);							break;
			case 's': return (tString < (std::string)typeTwo);						break;
		}
		return false;

	}
	bool operator>(sVar typeTwo){

		switch (currentType){
			case 'c': return (tChar > (char)typeTwo);							break;
			case 'i': return (tInt > (int)typeTwo);								break;
			case 'f': return (tFloat > (float)typeTwo);							break;
			case 's': return (tString > (std::string)typeTwo);					break;
		}
		return false;

	}
	bool operator>=(sVar typeTwo){

		switch (currentType){
			case 'c': return (tChar >= (char)typeTwo);							break;
			case 'i': return (tInt >= (int)typeTwo);							break;
			case 'f': return (tFloat >= (float)typeTwo);						break;
			case 's': return (tString >= (std::string)typeTwo);					break;
		}
		return false;

	}
	bool operator<=(sVar typeTwo){

		switch (currentType){
			case 'c': return (tChar >= (char)typeTwo);							break;
			case 'i': return (tInt >= (int)typeTwo);							break;
			case 'f': return (tFloat >= (float)typeTwo);						break;
			case 's': return (tString >= (std::string)typeTwo);					break;
		}
		return false;

	}
	bool operator==(sVar typeTwo){

		switch (currentType){
			case 'c': return (tChar == (char)typeTwo);							break;
			case 'i': return (tInt == (int)typeTwo);							break;
			case 'f': return (tFloat == (float)typeTwo);						break;
			case 's': return (tString == (std::string)typeTwo);					break;
		}
		return false;

	}
	bool operator!=(sVar typeTwo){

		switch (currentType){
			case 'c': return (tChar != (char)typeTwo);							break;
			case 'i': return (tInt != (int)typeTwo);							break;
			case 'f': return (tFloat != (float)typeTwo);						break;
			case 's': return (tString != (std::string)typeTwo);					break;
		}
		return false;

	}

	// += operator
	void operator += (int data2){
		switch (currentType){
			case 'c': tChar += data2;							break;
			case 'i': tInt  += data2;							break;
			case 'f': tFloat += data2;							break;
		}
	}
	void operator += (float data2){
		switch (currentType){
			case 'c': tChar += (int)data2;						break;
			case 'i': tInt  += (int)data2;						break;
			case 'f': tFloat += data2;							break;
		}
	}
	void operator += (char data2){
		switch (currentType){
			case 'i': tInt  += (int)data2;						break;
			case 'f': tFloat += (float)data2;					break;
			case 's': tString += data2;							break;
		}
	}
	void operator += (std::string data2){
		switch (currentType){
			case 'i': tInt  += atoi(data2.c_str());;			break;
			case 'f': tFloat += atof(data2.c_str());;			break;
			case 's': tString += data2;							break;
		}
	}

	// -= operator
	void operator -= (int data2){
		switch (currentType){
			case 'c': tChar -= data2;							break;
			case 'i': tInt  -= data2;							break;
			case 'f': tFloat -= data2;							break;
		}
	}
	void operator -= (float data2){
		switch (currentType){
			case 'c': tChar -= (int)data2;						break;
			case 'i': tInt  -= (int)data2;						break;
			case 'f': tFloat -= data2;							break;
		}
	}
	void operator -= (char data2){
		switch (currentType){
			case 'i': tInt  -= (int)data2;						break;
			case 'f': tFloat -= (float)data2;					break;
		}
	}
	void operator -= (std::string data2){
		switch (currentType){
			case 'i': tInt  -= atoi(data2.c_str());;			break;
			case 'f': tFloat -= atof(data2.c_str());;			break;
		}
	}

	char getCurrentType(){

		return currentType;

	}

	//swaps two sVar elements safely without loss of data
	void swap(sVar *sVarToSwapTo){

		//temp store this sVar
		sVar temp_sVar;
		switch (currentType){
			case 'c': temp_sVar = tChar;						break;
			case 'i': temp_sVar = tInt;							break;
			case 'f': temp_sVar = tFloat;						break;
			case 's': temp_sVar = tString;						break;
		}

		//overwrite this with the new one
		switch (sVarToSwapTo->getCurrentType()){
			case 'c': tChar = *sVarToSwapTo;					break;
			case 'i': tInt = *sVarToSwapTo;						break;
			case 'f': tFloat = *sVarToSwapTo;					break;
			case 's': tString = (std::string)*sVarToSwapTo;		break;
		}

		//set the sVarToSwapTo to be what this was
		*sVarToSwapTo = temp_sVar;
		

	}



};