package Optimization;

import java.util.ArrayList;

import DataClass.Location;
import DataClass.SuperArea;
import Manager.DataGeneration;

public class MainMethod {

	
	public static void main(String args[]){
	
	int CH_count;
	double equity=0.0;
	int capacity;
	int days=24;
	
	int supercount=8;
	int rbase=40;
	int fulCa=300;
	
	DataGeneration up=new DataGeneration();
	ArrayList<SuperArea[]> supers_days=new ArrayList<SuperArea[]>() ;
	
	 String filename="C:\\Users\\nihao\\NC Rest\\Zgeneral\\NC data\\Realdata8.xlsx";
	 String eventFile= "C:\\Users\\nihao\\NC Rest\\Zgeneral\\NC data\\Hurricane_locations8.csv";
	 String f="C:\\Users\\nihao\\NC Rest\\Zgeneral\\NC data\\supers_days8.csv";
	
	
	 // only for one day's data
	ArrayList<Location[]>  event=up.getEvenLocationDaysFromExcelFile(eventFile);
    supers_days=up.generateSubfromRealdata(rbase, supercount,filename, event.get(0) );  // this is only for day8
	
	
//.out.println("done with super"+  supers_days.get(0).length);
//supers_days=up.readSubfromRealdataTable(f);
	
     for(int k=0;k<supers_days.size();k++){
    		System.out.println("supers size"+supers_days.get(k).length );
    	}
	
	
	}	
	
	
	
	
}
