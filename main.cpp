#include <iostream>
#include <fstream>
#include <sstream> /*   for split into words */
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv){
	
	string fileName; 
	bool flag = false;
	bool mFlag = false;
	bool cFlag = false;
	bool bFlag = false; 

	if (argv[1] == 0 ){
		cout << "NO FILES" << endl; 
		return -1; 
	}
	else if (argv[1] !=0)
	{
		fileName = argv[1];
		flag = true;
		
		for (int i= 2; i <argc; i++){
				if (strcmp(argv[i], "-b") == 0 ){
						bFlag = true;
				}
				else if (strcmp(argv[i], "-c") == 0 ){
						cFlag = true;
				}
				else if (strcmp(argv[i], "-m") == 0 ){
						mFlag = true;
				}
				else {
					cout << argv[i]<<endl;
					cout << "UNRECOGNIZED FLAG"<<endl;
					return -1; 
				}
		}
	}
	
	string line,longLine;
	vector <string> color; 
	vector <int> count;
	int longestWord = 0; 
	int i = 0; 
	int longestLine = 0 ;
	int highestCount = 0; 
	int lineCount = 0;
	string longWord = "";
	ifstream infile(argv[1]);
	
	if (!infile.is_open()){
		cout <<"Error opening file"<<endl;
		return -1; 
	} 
	/*cout <<"Hello World"<<endl;*/
	else {
		while (!infile.eof()){
			getline (infile, line);
			/*cout << line <<" : " << line.length()<<endl;*/
			
			
			int lineLength = line.length();
			/*cout <<line<<" : "<< lineLength<<endl; */
			if (longestLine < lineLength){
				longestLine = lineLength; 
				longLine = line; 
				lineCount= 1; 
			}
			else if (longestLine == lineLength){
				lineCount +=1; 
			}
			istringstream ss(line); 

			do {
				string word; 
				ss >> word;
				if (word != " "){
					int length = word.length();
					if (length > longestWord){
						longestWord = length; 
						color.clear();
						color.push_back (word);
						longWord = word; 
						/*count[10] = {1,0,0,0,0,0,0,0,0,0};*/
						count.clear();
						count.push_back(1);
						highestCount = 1; 
					}
					else if (length  == longestWord){
						if (find(color.begin(),color.end(),word) == color.end()){
							color.push_back (word); 
							count.push_back(1);
							
						}
						else if (find(color.begin(),color.end(),word) != color.end()){
					
							int index = std::find(color.begin(), color.end(), word) - color.begin();
							int temp = count[index];
							/*count[index] = temp+1;*/
							color.erase(std::remove(color.begin(), color.end(), word), color.end());
							color.push_back(word);
							count.erase(count.begin()+temp);
							count.push_back(temp+1);
							if (highestCount < temp+1)
								highestCount = temp+1 ; 
						}
					}
					/*cout << word<< " : "<< length << endl;*/
				}
			}while (ss); 	

		}
		/*cout <<cFlag <<" "<<bFlag<<" "<<mFlag<<endl;*/
		for (int j = (color.size()-1 ); j >= 0 ; j--){
			if (mFlag){
				if (cFlag){
					int index = std::find(count.begin(), count.end(), highestCount) - count.begin();
					cout << color[index]<<"("<<highestCount<<")";
					break;
				}
				
				else{
					cout << longWord ; 
					break; 
				}
			}
			else if (cFlag){
				cout << color[j]<<"("<<count[j]<<")";
				if (j-1 >= 0 )
					cout << ", ";			
			}
			else if (flag){
				cout << color[j];
					if (j-1 >= 0 )
						cout << ", ";
			}
		}
		if (cFlag){
		cout <<endl <<longestLine<<"("<<lineCount<<")"<<endl;
		}
		else {	cout <<endl <<longestLine <<endl;}
	
	}
	return 0;
}