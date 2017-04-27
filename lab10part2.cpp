//============================================================================
//Author      : Aaron Neidlinger,
// Description : Lab 7 -> Lab 6 converted into vectors
//============================================================================

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<vector>
#include <algorithm>
#include <iterator>

using namespace std;

class Signal{
	private:
		//private data
		double maximumValue;
        double max;
		double average;
		//private functions
		double getAverage();
		double getMax();
	public:
		//constructors
		double length;
		vector<double> data;
		Signal();
		Signal(int)throw(const char *);
		Signal(const char*);
                ~Signal();      //destructor
		//public functions
		void operator+(double);
		void operator*(double);
		void center(Signal*);
		void normalize(Signal*);
		void statistics();
		void saveSignal(char*);
                void sigInfo();
};

//available constructors
Signal::Signal(){
	length = 0;
	maximumValue = 0;
	max = 0;
	average = 0;
	
}

Signal::Signal(int fileNum)throw(const char *){

	int i,size;
        double value;
	char fileName[50] = "";	//strings

	sprintf(fileName, "Raw_data_%02d.txt", fileNum);

	ifstream fileIn(fileName);
        if(fileIn.fail()){
            throw "That file could not be found!";
        }
        
        fileIn >> length >> maximumValue;
        
        size = (int)length;
         
       while(fileIn >> value){
            data.push_back(value);
        }
}

Signal::Signal(const char* fileName){
	int i,size;
        double value;

	ifstream fileIn(fileName);
        if(fileIn.fail()){
            cout << "That file could not be found!" << endl;
            exit(0);
        }
        
        fileIn >> length >> maximumValue;
        
        size = (int)length;
       
        while(fileIn >> value){
            data.push_back(value);
        }
}

Signal::~Signal(){

}

void Signal::saveSignal(char* fileName){
    int i;
//max value correct - must call statistics
    //statistics();

    //creates or opens a file of specified fileName
    ofstream fileOut;
    fileOut.open(fileName);

    vector<double> b =data ;
                 for(int i = 0; i < length; i++){
                            cout<< "temp333:  " << b[i] << endl;
                        }   
    
    //fills the file with data
    fileOut << length << " " << max << endl;
    for(i = 0; i < length; i++){
	fileOut << data[i] << endl;
    }
}

void Signal::sigInfo(){
    //auto runs statistics to get necessary info
    statistics();
    //prints out acquired info
    cout << "Length of data set: " << length << endl;
    cout << "Current maximum value: " << max << endl;
    cout << "Current average of the signal: " << average << endl;
    
}

//void Signal::offset(double off){
void Signal::operator+(double off){
	 int i;
         //offsets the data by off amount
        for(i = 0; i < length; i++){
	     data[i] = (double)data[i] + off;
	 }
}

//void Signal::scale(double scal){
void Signal::operator*(double scal){
	 int i;
         //scales the data by scal amount
	 for(i = 0; i < length; i++){
	    data[i] = (double)data[i] * scal;

	 }
}

double Signal::getAverage(){
	int i;
	double sum = 0;
	double avg = 0;

        //sums all the data
	for(i=0; i < length; i++){
	    sum = sum + data[i];
	}
      //divide by size for average
	avg = sum / length;

	return avg;
}

double Signal::getMax(){
	int i;
	double max = 0;

        //sorts data for largest present value
	for(i=0; i < length; i++){
	   if(max < data[i])
	        max = data[i];
	}

	return max;
}

void Signal::center(Signal* signal){
    //auto calls statistics to make sure average is populated
    statistics();
    //offsets data by its average to center it
    //offset(average);
	signal->operator+(average);
}

void Signal::normalize(Signal* signal){
    //scales data by the inverse of its largest possible value to center it
	//scale((1.0/maximumValue));
	signal->operator*((1.0/maximumValue));
}

void Signal::statistics(){
    //uses functions to get the average and max values;
    average = getAverage();
    max = getMax();
}

Signal operator+(const Signal &sig1, const Signal &sig2) throw(const char *){
    Signal sigSum;
        
    vector<double> signal1;
    signal1.insert(signal1.end(),sig1.data.begin(),sig1.data.end());

    vector<double> signal2;
    signal2.insert(signal2.end(),sig2.data.begin(),sig2.data.end());
	
	if(signal2.size() != signal1.size())
		throw "The signal vectors of two different sizes can not be summed!";

    vector<double> sum;

	if(sig1.length == sig2.length){
        for(int i = 0; i < sig1.length; i++){
            sum.push_back(signal1[i] + signal2[i]);
        }
          
        sigSum.data = sum;  
        sigSum.statistics();
        sigSum.length = sig1.length;
	}

	return sigSum;
}

int main(int argc, char* argv[]){
    int myNum,fileNum = 0;
    int choice = -1;
    double scal,off,hold;
    string input,fileNumber,fileName,fileName1,fileName2,select = "";
    char newFileName[50] = "";
    Signal *signal1;

    //will not run if command line arguments are present
    if(argc <= 2){
        while(true){
            //displays file loading options
        cout << "Please Select a menu option from below: " << endl;
        cout << "1. Load Default Signal" << endl;
        cout << "2. Load Signal File Using File Number" << endl;
        cout << "3. Load Signal File Using Full File Name" << endl;
		cout << "4. Sum Two Signal Files Into One Signal Object" << endl;
        cout << "5. Quit Without Loading a File" << endl;
        cout << "> ";
        
        //gets the user input
        getline(cin,input);
        cout << endl;
        //uses bit shifting to safely convert to an integer
        stringstream myStream(input);
        if(myStream >> myNum)
            break;
        else
            cout << "That input was not valid, please input a valid number" << endl;            
        }
        
        if(myNum == 1){
            //calls the default constructor
            signal1 = new Signal;
        }else
        if(myNum == 2){
			try{
            //offers the user the ability to enter the file number
            cout << "Please input a valid file number: ";
            //safely takes user input and converts to integer
            while(true){
                getline(cin,fileNumber);
                stringstream numStream(fileNumber);
                if(numStream >> fileNum)
                    break;
                cout << "That input was not valid, please input a valid number" << endl;
                }
                
            //calls a parametric constructor
            signal1 = new Signal(fileNum);
			}catch(const char * s){
				cout << s << endl;
				return -6;
			}
        }else
        if(myNum == 3){
            //offers the user the ability to enter the file name
            cout << "Please input a valid file name: ";
            //gets user input
            getline(cin,fileName);
            //converts string to constant character pointer
            const char* name = fileName.c_str();
            //calls a parametric constructor
            signal1 = new Signal(name);
        }else if(myNum == 4){
            //offers the user the ability to enter the file name
            cout << "Please input a valid file name for signal 1: ";
            //gets user input
            getline(cin,fileName1);
            //converts string to constant character pointer
            const char* name1 = fileName1.c_str();
			
            cout << "Please input a valid file name for signal 2: ";
            //gets user input
            getline(cin,fileName2);
            //converts string to constant character pointer
            const char* name2 = fileName2.c_str();
			
			Signal signal2(name1);
            Signal signal3(name2);
            Signal signal4;
			
			try{
				signal4 = operator+(signal2,signal3);
				signal1 = &signal4;	
			}catch(const char * s){
				cout << s << endl;
				return -5;
			}
		}
			/*
			//saving for this operation only works here due to a dangling pointer problem we have yet to figure out
			cout << endl << "File name for saving in if statment" << endl;
                cin >> newFileName;
            signal1->saveSignal(newFileName);
			return -1;
        }else
            return 1;
*/
		try{
        while(choice != 0){
			
			if(signal1->data[0] < 0){
				throw (-1);
			}
            //displays operations that the user can perform on the data
            cout << "Please Select an Option From Below:" << endl;
            cout << "0. Quit this program" <<endl;
            cout << "1. Offset Current Data" << endl;
            cout << "2. Scale Current Data" << endl;
            cout << "3. Center the Current Data" << endl;
            cout << "4. Normalize the Current Data" << endl;
            cout << "5. Get the Statistics of the Current Data" << endl;
            cout << "6. Display Info on the Current Data" << endl;
            cout << "7. Save the Current Data" << endl;
            cout << "> ";

			cin >> choice;
			cin.ignore();
            cout << endl;
        		  //gets user input and converts to 
				  /*
            while(true){
                //cin.ignore();
                fflush(stdin);
                getline(cin,select);
                cout << endl;
                stringstream numStream(select);
                if(numStream >> choice)
                    break;
                cout << "That input was not valid, please select a valid option" << endl;
            }
            */
            //handles various input cases
			if(signal1->data.empty()){
				throw "The signal vector was empty!";
			}
            switch(choice){
                case 1:
                    cout << "What offset value would you like to use?" << endl << "> ";
                    cin >> off;
                    cin.ignore();
                    cout << endl;
                    signal1->operator+(off);	//note why its like this
                    cout << "The data has now been offset!" << endl;
                    break;
                    
                case 2:
                    cout <<"What scalar value would you like to use?" << endl << "> ";
                    cin >> scal;
                    cin.ignore();
                    cout << endl;
                    signal1->operator*(scal);
                    cout << "The data has now been scaled!" << endl;
                    break;
                    
                case 3:
                    signal1->center(signal1);
                    cout << "The data has now been centered!" << endl;
                    break;
                    
                case 4:
                    signal1->normalize(signal1);
                    cout << "The data has now been normalized!" << endl;   
                    
                case 5:
                    signal1->statistics();
                    cout << "The data has had it's statistics calculated!" << endl;
                    break;
                    
                case 6:
                    signal1->sigInfo();
                    break;
                    
                case 7:
                    cout << "Please enter a name for the save file." << endl << "This should included the file extension and will overwrite an existing file if necessary" << endl << "> ";
                    cin >> newFileName;

                    for(int i = 0; i< signal1->length;i++)
                    cout << "Data[x]: " << signal1->data[i] << endl;
                    cin.ignore();
                    signal1->saveSignal(newFileName);
                    break;
                default:
                    return 0;
                    break;
            }
        }
                    
    }catch(const int s){
		cout << "The signal vector is corrupted! Program will now terminate" << endl;
		return -1;
	}
	catch(const char * s){
            cout << s << endl;
            return -3;
        }
	catch(...){
            cout << "An error was thrown! ";
            return -2;
        }
	}

    return 0;
}