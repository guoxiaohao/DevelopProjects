/**
 * 
 */
package Optimization;

import java.text.DecimalFormat;
import java.util.ArrayList;


import DataClass.*;

import Manager.*;

/**
 * @author bairongw
 *
 */
public class MainForModelsRealData {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	
			// TODO Auto-generated method stub
			
			Upper_level_model model=new Upper_level_model();
		
			int CH_count;
			double equity=0.0;
			int capacity;
			int days=24;
			
			
			int rbase=40;
			int fulCa=300;
			
			DataGeneration up=new DataGeneration();
		//	DatatoExcel de=new DatatoExcel();
		// ArrayList<Integer> factors= model.findFactors(fulCa);
			
		 ArrayList<UpperSolutions> solutions=new ArrayList<UpperSolutions>(); 
			ArrayList<SuperArea[]> supers_days=new ArrayList<SuperArea[]>() ;
				
		 //String filename="C:\\Users\\nihao\\NC Rest\\Zgeneral\\NC data\\Realdata10.xlsx";
		// String eventFile= "C:\\Users\\nihao\\NC Rest\\Zgeneral\\NC data\\Hurricane_locations13.csv";
		 String f="C:\\Users\\Administrator\\Desktop\\Day 16\\supers_days_16.csv";
		
		
		 // only for one day's data
		//ArrayList<Location[]>  event=up.getEvenLocationDaysFromExcelFile(eventFile);
		 
 //supers_days=up.generateSubfromRealdata(rbase, supercount,filename, event.get(0) );  // this is only for day8
	
		
	//.out.println("done with super"+  supers_days.get(0).length);
supers_days=up.readSubfromRealdataTable(f);
for(int k=0;k<supers_days.size();k++){
	System.out.println("supers size"+supers_days.get(k).length );
}
//	supers_days=up.generateSubfromSimulation(6, 6, 2, 3, 1.5, 24, eventDemand, eventLocation);
			ResultstoExcel res= new ResultstoExcel();
		//Lower_level_model lm=new Lower_level_model();	
			
	//		String lowerpath="C://Users//nihao//Dropbox//Twitter Coverage//UpperResults//NC//NClowerFollow15.4.xlsx";
			
			int daynum=16;
			int e=4;
			equity=Double.valueOf(String.format("%.2f", 0.1*e ));
			
			int[] us={ 24,12,8,6,4,3,2,1 }; // 24,12,8,6,4,3,2,1
			
			 
			int[] CHs={15};// 150,100,60,30,15,6,2
			//String upperpath="C://Users//Administrator//Desktop//Day "+daynum+"//NCupper"+daynum+"."+e+".xlsx";
			String upperpath="C://Users//Administrator//Desktop//Day "+daynum+"//NCupper"+daynum+"."+e+".csv";
					
				for(int j=0;j<CHs.length;j++){  //factors.size()-1
				
				CH_count=CHs[j];
				capacity=fulCa/CH_count;
				
				
				//int u=0;
				for(int k=0;k<us.length;k++){
					
					solutions=	model.solveMe(supers_days, CH_count, equity, days, capacity,us[k],rbase);	
				System.out.println("u value is"+us[k]+" the size is"+solutions.size());
				//res.upper2excel(upperpath,solutions,daynum);
				res.upper2CSV(upperpath, solutions);
				}
				
				}
			
		
			
			}
			
			
		
	}


/*
 			for(int s=0;s<sz ;s++){
					ArrayList< LowerSolutions> lowers=new ArrayList<LowerSolutions>();
					
					//ArrayList< LowerSolutions> lowers2=new ArrayList<LowerSolutions>();
				for(int d=0;d<24;d++){
					ArrayList<Integer> xs=solutions.get(s).getX().get(d);
					ArrayList<Integer> ys=solutions.get(s).getY().get(d);
					String solutionIndex=solutions.get(s).getDaySolutionIndex().get(d);
					 for(int t=0;t<supercount;t++){
						// System.out.println("super"+t);
						 int xv=xs.get(t);
						 int demand= (int) ((int) ys.get(t));
						 if(xv>0){
							ArrayList< LowerSolutions> lower=lm.solveMe( supers_days.get(d)[t], xv, capacity, demand,solutionIndex  );
							
							lowers.addAll(lower);
						 }
					 }
				}
				
		//	res.lower2excel(lowerpath, lowers, daynum);   
		System.out.println("writing to loweer"+lowers.size());
				}


*/

