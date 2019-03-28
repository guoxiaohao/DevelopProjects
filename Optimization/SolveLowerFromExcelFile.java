/**
 * 
 */
package Optimization;

import static tech.tablesaw.api.QueryHelper.column;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;

import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;


import DataClass.LowerSolutions;

import DataClass.SuperArea;
import Manager.DataGeneration;

import Manager.Lower_level_model;
import Manager.ResultstoExcel;
import tech.tablesaw.api.Table;


/**
 * @author bairongw
 *
 */
public class SolveLowerFromExcelFile {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		SolveLowerFromExcelFile sf=new SolveLowerFromExcelFile();
		
		
		int daynumber=11;
		String daynum="NC"+String.format("%02d", daynumber);
		int superCount=8;
		String folder="C://Users//Administrator//Desktop//Day "+daynumber+"//";
		
		
		//for(int k=7;k<10;k++){
		int k=0; //7,8,9
		String daystr=daynumber+"."+k;
		String excelstr="NCupperReal"+daystr; 
		String upperfileLocation=folder+excelstr+".csv"; //SCupperReal10.7
		System.out.print(upperfileLocation);
		int[] capIndex={2};//2,3,5,10,20,50,150   3 150
		
		
		
		for(int i=0;i<capIndex.length;i++){
		
		String lowerfileLocation=folder+"NCLower"+daystr+"."+capIndex[i]+".0.xlsx";
		 String f=folder+"supers_days_"+daynumber+".csv"; 
		
		sf.solveLowerbyReadingCSV(capIndex[i], daynum, superCount, upperfileLocation, lowerfileLocation,f); 
		
		}
		}

	//}

	
	
	
	
	
	
	
	
	
	
	public void solveLowerbyReadingCSV(int capIndex,String daynum, int superCount,String upperfileLocation, String lowerfileLocation, String supers_days_file ){
	
		DataGeneration up=new DataGeneration(); 
		ResultstoExcel res=new ResultstoExcel();
		
		ArrayList<SuperArea []> supers_days=up.readSubfromRealdataTable(supers_days_file);
		Lower_level_model lm=new Lower_level_model();
	
	
		String lowerfileLocation0=lowerfileLocation;
	Table datatable=null;
	try {
		datatable= Table.read().csv(upperfileLocation );
	} catch (IOException e) {
			e.printStackTrace();
	}
	
	int[] Xindex=new int[superCount]; 
	int[] Yindex=new int[superCount];
		
	int solutionIndex=datatable.columnIndex("solutionIndex");
	int hourIndex=datatable.columnIndex("hour");		
	int capacityIndex=datatable.columnIndex( "capacity");
	
	for(int i=0;i<superCount;i++){
		String x="x"+(i+1);
		String y="y"+(i+1);
		//System.out.println(x+" "+y);
		
		Xindex[i]=datatable.columnIndex(x );
		Yindex[i]=datatable.columnIndex(y);
		
		//System.out.println(Xindex[i]+"y"+Yindex[i]);
	}
	
							
	ArrayList< LowerSolutions> lowers=new ArrayList< LowerSolutions>();
	
	

	
	
	//ViewGroup h=datatable.groupBy("capacity");
	
	//System.out.println("capacity number:"+h.size());
	
	
	//Table captable=h.get(capIndex).asTable() ;
	System.out.println("capIndex:"+capIndex);
	 Table captable= datatable. selectWhere(   datatable.shortColumn("capacity").isEqualTo(capIndex));
	int k=0;
	int m=0;
System.out.println(captable.rowCount());
	for(int p=0;p<captable.rowCount();p++){
		
		String solutionIndexStr=captable.get(p, solutionIndex);
		int hour =Integer.valueOf(captable.get(p, hourIndex)) ;
		int capacity= Integer.valueOf(captable.get(p, capacityIndex)) ;
		
		for(int i=0;i<superCount;i++){
			
			
			int xvalue= Integer.valueOf(captable.get(p, Xindex[i]));
			
			if(xvalue>0){
				int yvalue= Integer.valueOf(captable.get(p, Xindex[i]));
			
			ArrayList< LowerSolutions> lower=lm.solveMe( supers_days.get(hour)[i], xvalue, capacity, yvalue,solutionIndexStr  );
           // System.out.println("x"+(i+1)+"value is"+xvalue+ "y"+(i+1)+"value is"+yvalue+ "lower size is:"+lower.size());   
			
			lowers.addAll(lower);
			}
			
			if(lowers.size()>=500){
				k++;
				res.lower2excel(lowerfileLocation, lowers, daynum);
				lowers.clear();
			}
			
			
			
			if(k>=20){
				k=0;
				int index=lowerfileLocation0.indexOf(".xlsx");
				String str=lowerfileLocation0.substring(index-1, index); 
				
				String filestr=lowerfileLocation0.substring(0, index-1)+m+".xlsx"; 
				System.out.println("file Str"+str+"m:"+filestr);
				m++;
				lowerfileLocation=filestr;
				
			}
			
			
			
			
		}
		
		
	}
	
	
	

	if(lowers.size()>0){
		res.lower2excel(lowerfileLocation, lowers, daynum);
		
	}
	
	
		
		
	}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
