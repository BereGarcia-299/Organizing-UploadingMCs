#include <assert.h>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <tgmath.h>
#include <iostream>
#include <TChain.h>
#include <TLegend.h>
#include "TTree.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TRandom3.h"
#include <TAttMarker.h>
#include <TCanvas.h>
#include <TPaveText.h>
#include "TLorentzVector.h"
#include "TPaveLabel.h"
#include <vector>
#include <fstream>
#include "TGraph.h"
#include "TMultiGraph.h"
#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
#include <string>
#include <map>
#include <iterator>



//-------Variables--------//
//--------Typedefs--------//
typedef std::map<std::string, std::string> Create_Map;					//-----Create Type For Maps
typedef std::map<std::string, std::string>::iterator itr;				//-----Create Type For Iterators


//------------------------------------------------------------------------//
//------------------------------------------------------------------------//
//------------------------Initializing Maps-------------------------------//
//------------------------------------------------------------------------//
//------------------------------------------------------------------------//



//------These Maps Will ONLY Contain The 'KEY'/Name Of File & 'ELEMENT'/It The Path To It 

Create_Map pp_50_70GeV;													//-----Creating Map For 50-70 GeV pp mC Files
Create_Map* PointMap_1 = &pp_50_70GeV;									//-----Creating Pointer For This Map

Create_Map pp_70_140GeV;												//-----Creating Map For 70-140 GeV pp mC Files
Create_Map* PointMap_2 = &pp_70_140GeV;									//-----Creating Pointer For This Map

Create_Map pp_140_280GeV;												//-----Creating Map For 140-280 GeV pp mC Files
Create_Map* PointMap_3 = &pp_140_280GeV;								//-----Creating Pointer For This Map

Create_Map pp_280_500GeV;												//-----Creating Map For 280-500 GeV pp mC Files
Create_Map* PointMap_4 = &pp_280_500GeV;								//-----Creating Pointer For This Map



//------These Maps Will ONLY Contain THE 'KEY'/Name Of File & 'ELEMENT'/Name Of The Tree 
//------These Will Contain Thist Information For Every Different pT Range

Create_Map pp_5070_treename;											
Create_Map* PointM_TreeName_1 = &pp_5070_treename;

Create_Map pp_70140_treename;
Create_Map* PointM_TreeName_2 = &pp_70140_treename;

Create_Map pp_140280_treename;
Create_Map* PointM_TreeName_3 = &pp_140280_treename;

Create_Map pp_280500_treename;
Create_Map* PointM_TreeName_4 = &pp_280500_treename;


//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//------This Function Will Put The Text Information Into a Map-------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

void TextFile_Map(std::string pass_text,std::map<std::string, std::string> *point_map,std::map<std::string, std::string> *point_tree){
	
	cout << endl;
	cout << "I will Read Your Text File and Take The Information To Place It Into A Map" << endl;
	cout << endl;


	string temp_variable;

	ifstream myFile (pass_text);

	while (getline (myFile,temp_variable)){ 
		
		if(temp_variable.size() == 0) {continue;}											//------Skip Line If It's Empty
		
		if(temp_variable.find(",")){														//------If A ',' Is Found Go Execute The Following Code 		
			int index_txt = temp_variable.find(",") + 1;  										//------Index of where we found our first ',' + 1 
			int last_index_txt = temp_variable.find(".root");
			
			int index_tree = temp_variable.find(".root") + 1;

			//------Storing Element 
			point_map->insert(pair<std::string,std::string>(temp_variable.substr(0,temp_variable.find(",")),temp_variable.substr(index_txt,last_index_txt)));
			point_tree->insert(pair<std::string,std::string>(temp_variable.substr(0,temp_variable.find(",")),temp_variable.substr(index_tree,temp_variable.size())));
		}

    } 

}

//---------------------------------------------------------------//
//---------------------------------------------------------------//
//------This Function Will Print Out What is Inside My Map-------//
//---------------------------------------------------------------//
//---------------------------------------------------------------//
void Print_Map(std::map<std::string, std::string> *point_map){

		itr itr_temp;

		for (itr_temp = point_map->begin(); itr_temp != point_map->end(); ++itr_temp) { 
        cout << '\t' << "This is the KEY: " << itr_temp->first 
        << '\t' << "This is your ELEMENT:  " << itr_temp->second << '\n'; 
    }

}




int Read_Files(){

	//-------List Of My Text Files W/ Diffirent pT Ranges---------//
	std::string pT_5070GeV_txt = "/Users/berenicegarcia/Desktop/ATLAS/mc_v006/5070GeV_pp.txt";
	std::string pT_70140GeV_txt = "/Users/berenicegarcia/Desktop/ATLAS/mc_v006/70140GeV_pp.txt";
	std::string pT_140280GeV_txt = "/Users/berenicegarcia/Desktop/ATLAS/mc_v006/140280GeV_pp.txt";
	std::string pT_280500GeV_txt = "/Users/berenicegarcia/Desktop/ATLAS/mc_v006/280500GeV_pp.txt";




	
	TextFile_Map(pT_5070GeV_txt,PointMap_1,PointM_TreeName_1);				//------Inserting Text File For 50-70 GeV & Creating A Map For It
    Print_Map(PointMap_1);													//------Printing What Is In Your Map


    TextFile_Map(pT_70140GeV_txt,PointMap_2,PointM_TreeName_2);				//------Inserting Text File For 70-140 GeV & Creating A Map For It
    Print_Map(PointMap_2);													//------Printing What Is In Your Map

    TextFile_Map(pT_140280GeV_txt,PointMap_3,PointM_TreeName_3);			//------Inserting Text File For 140-280 GeV & Creating A Map For It
    Print_Map(PointMap_3);													//------Printing What Is In Your Map

    TextFile_Map(pT_280500GeV_txt,PointMap_4,PointMap_4);					//------Inserting Text File For 280-500 GeV & Creating A Map For It
    Print_Map(PointMap_4);													//------Printing What Is In Your Map

    

   
	

	return 0;
}
