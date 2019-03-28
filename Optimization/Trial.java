package Optimization;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import static tech.tablesaw.api.QueryHelper.column;


import DataClass.Location;
import DataClass.Node;
import DataClass.SuperArea;
import DataClass.UpperSolutions;
import Manager.DataGeneration;




public class Trial {

	public static void main(String[] args) {
		DataGeneration up=new DataGeneration();
		
	
	
	
	 int supercount=8;
		int rbase=40;
	 
		ArrayList<SuperArea[]> supers_days=new ArrayList<SuperArea[]>() ;
			
	 String filename="/user/bairongw/Coverage/Realdata.xlsx";
	 String eventFile= "/user/bairongw/Coverage/Hurricane_locations2.csv";
	 
	
	
	 // only for one day's data
	 ArrayList<Location[]>  event=up.getEvenLocationDaysFromExcelFile(eventFile);
	 
	supers_days=up.generateSubfromRealdata(rbase, supercount,filename, event.get(0) ); 
	 
	
	}

	
	

	
	
}
