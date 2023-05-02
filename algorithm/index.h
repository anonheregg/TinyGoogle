#ifndef INDEX_H
#define INDEX_H
#include<bits/stdc++.h>
using namespace std;
//THIS IS SIMILAR TO THE GOOGLE BOTS THAT SURF THE WHOLE INTERNET!
//HERE THE 3 BOTS SEGREGATED THE WHOLE INTERNET TXTS AS POSSIBLE COMBINATIONS
map<string,vector<string>> bot1(vector<string> lis){
    map<string,vector<string>> index1;
    for(const auto& kw:lis){
        vector<string> midc1;
        ifstream infile("internet.txt");
        string line1;
        while(getline(infile,line1)){
            if(line1.find(kw)!=string::npos){
                midc1.push_back(line1);

            }
        }
        index1[kw]=midc1;
    }
    return index1;
}
/*vector<vector<string>> li2={{"COVID","CHICKENPOX"},{"COVID","DMK"}
,{"CHICKENPOX","DMK"}};*/
map<string,vector<string>> bot2(vector<vector<string>> lis){
    map<string,vector<string>> index2;
    for(const auto& kw:lis){
        vector<string> midc2;
        ifstream infile("internet.txt");
        string line2;
        while(getline(infile,line2)){
            if(line2.find(kw[0])!=string::npos && line2.find(kw[1])!=string::npos){
                midc2.push_back(line2);

            }
        }
        index2[kw[0]+"_"+kw[1]]=midc2;
    }
    return index2;
}
map<string,vector<string>> bot3(vector<vector<string>> lis){
    map<string,vector<string>> index3;
    for(const auto& kw:lis){
        vector<string>midc3;
        ifstream infile("internet.txt");
        string line3;
        while(getline(infile,line3)){
            if(line3.find(kw[0])!=string::npos && line3.find(kw[1])!=string::npos){
                if(line3.find(kw[2])!=string::npos){
                midc3.push_back(line3);
                }

            }
            index3[kw[0]+"_"+kw[1]+"_"+kw[2]]=midc3;
    }
    return index3;
}
}


#endif