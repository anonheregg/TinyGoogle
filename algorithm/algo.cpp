#include<iostream>
#include<bits/stdc++.h>
//#include "search.h"
#include "index.h"
#include<string>
#include<ctime>
#include<algorithm>
using namespace std;
//THIS IS TO CAPITALISE THE SEARCH QUERY
string capitalise(string str){
  transform(str.begin(),str.end(),
  str.begin(),[](unsigned char c){
    return toupper(c);
  });
  return str;
}
//THIS PART WILL RANK THE CONTENT IN THE SEGMENT AND GIVES THE FINAL APPROPRIATE CONTENTS
vector<string> finaloutput(vector<string> seg ,vector<string> ranwor){
  vector<string> goldenout;
  map<string,vector<string>> midbox;
  //SORTING THE RANWORDS!
  sort(ranwor.begin(),ranwor.end(),[](string a,string b){
    return a.size()>b.size();
  });
  //THIS WILL CREATE THE BOXED MAP WITH THE KEY WE HAVE FOUND!
  //HERE IT SHOULD PICK THE  ARTICLES RANDOMLY AND SEND IT TO THE MAIN THE FUNCTION(FOR FLEXIBLE/VARIETY SEARCH!)
  for(const auto& xs:ranwor){
    srand(time(NULL));
    vector<string> cache={};
    int random_nu=rand()%seg.size();
    for(int xc=0;xc<0;xc++){
      string xse=seg[xc];
      if(xse.find(xs)!=string::npos){
        cache.push_back(xse);
        
      }  //THIS PART GENEARTE A RANDOM NUMBER TO MAKE THE DATABASE(INTERNET.TXT) SIMILAR TO INTERNET
      }
    for(int xce=random_nu;xce<seg.size()-1;xce++){
      string xse=seg[xce];
      if(xse.find(xs)!=string::npos){
        cache.push_back(xse);
    }
    
  }
  midbox[xs]=cache;
  }
  int fc=0;
  int l=0;
  while(fc<4&&l<10){
    l+=1;
    for(const auto& x:ranwor){
      if(midbox[x].size()!=0){
        if(find(goldenout.begin(),goldenout.end(),midbox[x][0])==goldenout.end()){
            goldenout.push_back(midbox[x][0]);
            midbox[x].erase(midbox[x].begin()+0);
        }
      }
      
    }
    fc=goldenout.size();
  }
  return goldenout;

}
//THIS PART OF THE CODE TAKES THE INPUT OF THE INDEx AND RESULTS THE ARTICLES IN THAT WHOLE PART!
vector<string> scrollbot(string sccr){

    vector<string> li1={"COVID","CHICKENPOX","DMK"};
    map<string,vector<string>> z1=bot1(li1);
    //THIS PART IS FOR TWO KIND KEYWORD!
    vector<vector<string>> li2={{"COVID","CHICKENPOX"},{"COVID","DMK"},{"CHICKENPOX","DMK"}};
    map<string,vector<string>> z2=bot2(li2);
    //THIS PART IS FOR THREE KIND KEYWORD!
    vector<vector<string>> li3={{"COVID","CHICKENPOX","DMK"}};
    map<string,vector<string>> z3=bot3(li3);
    vector<string> x3=z3["COVID_CHICKENPOX_DMK"];
    //MERGING ALL INTO A SINGLE INDEX FINALLY
    map<string,vector<string>> final_index;
    for(const auto& corp:z1){
        final_index.insert(corp);
    }
    for(const auto& corp:z2){
        final_index.insert(corp);    
    }
    for(const auto& corp:z3){
        final_index.insert(corp);
    }
    vector<vector<string>> finalkeys={{"COVID"},{"CHICKENPOX"},{"DMK"},{"COVID","CHICKENPOX"},
    {"COVID","DMK"},{"CHICKENPOX","DMK"},{"COVID","CHICKENPOX","DMK"}}; 
    if(sccr=="ERROR"){
    vector<string> xxxcache={"YOUR SEARCH IS INVALID///CHECK SPELLING!"};
    return xxxcache;
    }
    else{
    return final_index[sccr];
    }
    
}
//THIS PART OF CODE WILL DETERMINE THE SEGMENT OF A PARTICULAR STRING ITS IN!(like covid,dmk,chickenpox)
string segment(string s){
  
      if(s.find("COVID")!=string::npos && s.find("CHICKENPOX")!=string::npos){
                if(s.find("DMK")!=string::npos){
                  return "COVID_CHICKENPOX_DMK";
                }
                else{
                  return "COVID_CHICKENPOX";
                }
      }
      if(s.find("CHICKENPOX")!=string::npos && s.find("DMK")!=string::npos){
         if(s.find("COVID")!=string::npos){
                  return "COVID_CHICKENPOX_DMK";
                }
                else{
                  return "CHICKENPOX_DMK";
                }
      }
      if(s.find("COVID")!=string::npos && s.find("DMK")!=string::npos){
         if(s.find("CHICKENPOX")!=string::npos){
                  return "COVID_CHICKENPOX_DMK";
                }
                else{
                  return "COVID_DMK";
                }
      }
      if(s.find("COVID")!=string::npos){
        return "COVID";
      }
      if(s.find("CHICKENPOX")!=string::npos){
        return "CHICKENPOX";
      }
      if(s.find("DMK")!=string::npos){
        return "DMK";
      }
      else{
        return "ERROR";
      }
}
//THE MAIN IMPLEMENTATION OF THE ALGORITHM(EVERYTHING ASSEMBELED HERE)
int main(){
    cout<<"\n";
    cout<<"   CHECK SPELLING PROPERLY"<<"\n";
    cout<<"ASK ABOUT COVID,CHICKENPOX,POLITICS"<<endl;
    cout<<"      \n     \n  ";
    string search,mid;
    vector<string> key;
    cout<<"SEARCH WEB:";
    //algo starts
    vector<string> avoid={
    "I","CORONA",
    "TO","THE","IS","A",
    "AN","?","AND","HAVE","HAD","HIS","HER",
    "IS","THAT","THIS","WHY","WHAT","WHO","HOW","WHERE"};
    getline(cin,search);
    search=capitalise(search);
    //HERE WE ARE REMOVING THE ? IN THE SEARCH QUERY
    if(search[search.length()-1]=='?'){
      search.erase(search.length()-1,1);
    }

    vector<string> found_seg=scrollbot(segment(search));
    /*for(const auto&xx:found_seg){
      cout<<"**"<<xx<<endl;
    }*/
    stringstream ss(search);
    vector<string> rankingword;
    string word;
    while(ss>>word){
        if(find(avoid.begin(),avoid.end(),word)==avoid.end()){
          rankingword.push_back(word);
        }
    }
    if(found_seg[0]=="YOUR SEARCH IS INVALID///CHECK SPELLING!"){
      cout<<"PLEASE INCLUDE KEYS LIKE COVID,CHICKENPOX AND DMK TO HELP US FIND YOU THE RELATED ARTICLE!";
    }
    else{
    for(const auto& xx:finaloutput(found_seg,rankingword)){
      cout<<xx<<endl;
    }
    }
    return 0;
}
