/**
 * 
 */
package Manager;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.xssf.usermodel.XSSFRow;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import DataClass.Location;
import DataClass.LowerSolutions;
import DataClass.Node;
import DataClass.SuperArea;
import DataClass.UpperSolutions;

/**
 * @author bairongw
 * This class is used to write upper and lower level model results to excel sheets 
 */
public class ResultstoExcel {

	
	
	
public void upper2excel(String fileLocation, ArrayList<UpperSolutions> solutions, int daynum ){
			
		File f=new File(fileLocation);
		XSSFWorkbook workbook=null;
		FileInputStream filein=null;
		
		if(!f.exists()){
			workbook =  new XSSFWorkbook();
		}else{
			try {
				filein=new FileInputStream(f);
				workbook = new XSSFWorkbook(filein);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		
		ArrayList<String> labels= new ArrayList<String> ();
		labels.add("solutionIndex");
		/*labels.add("capacity");
		labels.add("CHs count");
		labels.add("equity");*/
		labels.add("hour");
		//labels.add("day");
		
		labels.add("coverage");
		/*labels.add("u_policy");
		labels.add("total time");*/
		//int areaCount=8; //
		int areaCount=solutions.get(0).X.get(0).size();
		for(int i=1;i<areaCount+1;i++){
			labels.add("x"+i);
		}
		for(int i=1;i<areaCount+1;i++){
			labels.add("y"+i);
		}
		for(int i=1;i<areaCount+1;i++){
			labels.add("d"+i);
		}
	
		
		FileOutputStream fileout=null;
		
		
		
		this.addCellForUpperSolutions(solutions, workbook, labels,daynum);
		try {
			//filein.close();
			fileout=new FileOutputStream(f);
			workbook.write(fileout);
		
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally{
			try {
				fileout.close();
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	
}
	


public  void addLabel ( XSSFSheet sheet, ArrayList<String> labels)	{ 
	
	XSSFRow row=sheet.createRow(0);
	for(int k=0;k<labels.size();k++){
		row.createCell(k).setCellValue(labels.get(k));
	}
	
	
}	


public void addCellForUpperSolutions(ArrayList<UpperSolutions> sups,XSSFWorkbook myexcel, ArrayList<String> labels, int daynum) {
	//solutions is an array of the solution class, the size is the number of solutions
		// define the x variable, the number of CHs in each sub-area within each super area in each day
	
			int tracedRow=0;
int sheetNum=myexcel.getNumberOfSheets();
XSSFSheet mysheet=null;
//System.out.println("the sheet num is "+sheetNum);
if(sheetNum==0){
	 mysheet=myexcel.createSheet("upper"+sheetNum);
	
	 addLabel(mysheet,labels);
	 tracedRow=mysheet.getLastRowNum();
	// System.out.println("we create a new sheet tweet0"+"and the last row number is"+tracedRow+"and the first row number is"+mysheet.getFirstRowNum());
}
if(sheetNum>=1){
	mysheet=myexcel.getSheetAt(sheetNum-1);
	tracedRow=mysheet.getLastRowNum();
	//System.out.println("the number of tracedrow is, we get the last sheet "+tracedRow);
}
int sz=sups.size();
tracedRow=tracedRow+1;
// xvalues size is 6
ArrayList< ArrayList<Integer> > xvalues=new ArrayList< ArrayList<Integer> >();	 
 
 // yvalues size is the number of nodes , y is the decision variable
ArrayList< ArrayList<Integer> > yvalues=new ArrayList<ArrayList<Integer>>();
//	 ArrayList<ArrayList<Double>> wvalues=new ArrayList<ArrayList<Double>>();
// ArrayList<Location> lvalues=new ArrayList<Location>();
 //every node has its r values and each r value is an array
 ArrayList<ArrayList<Integer>> dvalues=new ArrayList<ArrayList<Integer>>();
	
     for (int i=0;i<sz;i++) {
    	 UpperSolutions s=sups.get(i);
        //	double finalValue=s.getValue();
    	
    	
    	/*int sarea=s.getX();
    	int time=s.getTime();*/
    	 
    	
	    	
    	// the allocation of X into different centers
    	 xvalues=s.getX();
    	 yvalues=s.getY();
    	 dvalues=s.getD();
    	 //lvalues=s.getL();
    	// wvalues=s.getW();
    	 
    	// int nodesize=lvalues.size();
    	
    	 ArrayList<String> indexvalues=s.getDaySolutionIndex();
    	 int areas=xvalues.get(0).size(); // the number of sub-centers in each sub-area
    	 int days=xvalues.size(); // number of days in each super solutions
    	 if(tracedRow>100000){
    			mysheet=myexcel.createSheet("tweet"+myexcel.getNumberOfSheets());
    			//System.out.println("we create the nwe sheet when a new sheet is necessary");	
    			addLabel(mysheet, labels);
    				tracedRow=mysheet.getLastRowNum(); 				
		 }
    	 
    	 for(int r=0;r<days;r++){
    		 
    	 XSSFRow row=mysheet.createRow(tracedRow++);
    	
	
			row.createCell(0,1).setCellValue(indexvalues.get(r));
		//	row.createCell(1,1).setCellValue(capacity);
		//	row.createCell(2,1).setCellValue(chcount);
		//	row.createCell(3,1).setCellValue(s.getEquity());
			row.createCell(1,1).setCellValue(r);
		//	row.createCell(5,1).setCellValue(daynum);
			//row.createCell(2,1).setCellValue(daynum);
			row.createCell(2,1).setCellValue(s.getValue());
			//row.createCell(8,0).setCellValue(s.getUpperTime());
			

			//System.out.println("areas:"+areas);
			try {
		for(int area=0;area<areas;area++){
			   
			    row.createCell(3+area,1).setCellValue(xvalues.get(r).get(area));
			  
			    row.createCell(3+areas+area,1).setCellValue(yvalues.get(r).get(area));
			 //   System.out.println("yvalue"+yvalues.get(r).get(area));
			    row.createCell(3+areas*2+area,1).setCellValue(dvalues.get(r).get(area));
			   // System.out.println("dvalue"+dvalues.get(r).get(area));
					
		}
					
    	 }
			catch(Exception e){
				e.printStackTrace();
			}
	

}
}
     
     
}


public void lower2excel(String fileLocation, ArrayList<LowerSolutions> solutions, String daynum){
		
	File f=new File(fileLocation);
	XSSFWorkbook workbook=null;
	FileInputStream filein=null;
	
	if(!f.exists()){
		workbook =  new XSSFWorkbook();
	}else{
		try {
			filein=new FileInputStream(f);
			workbook = new XSSFWorkbook(filein);
			
			
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	ArrayList<String> labels= new ArrayList<String> ();
	labels.add("superIndex");
	labels.add("lowerIndex");
	labels.add("day");
	labels.add("CH_count");
	labels.add("weight");
	labels.add("location.x");
	labels.add("location.y");
	labels.add("super_cover");
	labels.add("lower_cover");
	labels.add("lowercoverage");
	labels.add("total time");
	

	int areaCount= 10;
	for(int i=1;i<areaCount+1;i++){
		labels.add("x"+i);
	}
	for(int i=1;i<areaCount+1;i++){
		labels.add("r"+i);
	}
	for(int i=1;i<areaCount+1;i++){
		labels.add("y"+i);
	}

	
	FileOutputStream fileout=null;
	
	
	
	this.addCellForLowerSolutions(solutions, workbook, labels,areaCount,daynum);
	try {
		//filein.close();
		fileout=new FileOutputStream(f);
		workbook.write(fileout);
	
	} catch (FileNotFoundException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	} catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}finally{
		try {
			fileout.close();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}

	
public void addCellForLowerSolutions(ArrayList<LowerSolutions> lowers,XSSFWorkbook myexcel, ArrayList<String> labels, int lableLen, String daynum) {
	//solutions is an array of the solution class, the size is the number of solutions
		// define the x variable, the number of CHs in each sub-area within each super area in each day
	
			int tracedRow=0;
int sheetNum=myexcel.getNumberOfSheets();
XSSFSheet mysheet=null;
//System.out.println("the sheet num is "+sheetNum);
if(sheetNum==0){
	 mysheet=myexcel.createSheet("lower"+sheetNum);
	
	 addLabel(mysheet,labels);
	 tracedRow=mysheet.getLastRowNum();
	// System.out.println("we create a new sheet tweet0"+"and the last row number is"+tracedRow+"and the first row number is"+mysheet.getFirstRowNum());
}
if(sheetNum>=1){
	mysheet=myexcel.getSheetAt(sheetNum-1);
	tracedRow=mysheet.getLastRowNum();
	//System.out.println("the number of tracedrow is, we get the last sheet "+tracedRow);
}
int sz=lowers.size();
tracedRow=tracedRow+1;
	
     for (int i=0;i<sz;i++) {
    	 LowerSolutions s=lowers.get(i);
    	ArrayList<Node> nodes=s.getNodes();
    	int sub_count=s.getX().length;
    	int nodeSize=nodes.size();
    	 int chcount=s.getCH_count();
    	
     	int[] xvalues=s.getX();	 
    	 int[][] yvalues=s.getY();
    	 if(tracedRow>100000){
    			mysheet=myexcel.createSheet("tweet"+myexcel.getNumberOfSheets());
    			//System.out.println("we create the nwe sheet when a new sheet is necessary");	
    			addLabel(mysheet, labels);
    				tracedRow=mysheet.getLastRowNum(); 				
		 }
    	 
    	 int m=Math.min(1, nodeSize);
    	 
    	 for(int d=0;d<1 ;d++){ //nodeSize
    		 
    	 XSSFRow row=mysheet.createRow(tracedRow++);
    	 row.createCell(0,1).setCellValue(s.getSuperSolutionIndex());
  		row.createCell(1,1).setCellValue(s.getSolutionIndex());
  		row.createCell(2,1).setCellValue(daynum );
			row.createCell(3,1).setCellValue(chcount );
			//System.out.println("super"+s.getSuperSolutionIndex()+ "lower"+s.getSolutionIndex());
			
			if(nodeSize>0){
				row.createCell(4,1).setCellValue( nodes.get(d).getWeight());
				row.createCell(5,1).setCellValue(nodes.get(d).getLocation().x );	
				row.createCell(6,1).setCellValue(nodes.get(d).getLocation().y);
				
				int r[]=nodes.get(d).getRvalues();
				for(int area=0;area<sub_count;area++){	
				 row.createCell(11+lableLen+area,1).setCellValue( r[area]);
				}
			}
			
			row.createCell(7,1).setCellValue(s.getSuperCover());
			row.createCell(8,0).setCellValue(s.getCover() );
			row.createCell(9,0).setCellValue(s.getCoverage() );
			row.createCell(10,0).setCellValue(s.getLowerTime() );

			
			try {
				
			
				
		for(int area=0;area<sub_count;area++){		   
			    row.createCell(11 +area,1).setCellValue( xvalues[area]);			        
			    row.createCell(11+lableLen*2+area,1).setCellValue(yvalues[d][area]);
		}
					
    	 }
			catch(Exception e){
				e.printStackTrace();
			}
	  
			}
    	
    	 
}
     
     
}


public void upper2CSV(String fileLocation, ArrayList<UpperSolutions> solutions ){
	
		 
	
	
	ArrayList<String> labels= new ArrayList<String> ();
	labels.add("solutionIndex");
	/*labels.add("capacity");
	labels.add("CHs count");
	labels.add("equity");*/
	labels.add("hour");
	//labels.add("day");
	
	labels.add("coverage");
	/*labels.add("u_policy");
	labels.add("total time");*/
	//int areaCount=8; //
	int areaCount=solutions.get(0).X.get(0).size();
	for(int i=1;i<areaCount+1;i++){
		labels.add("x"+i);
	}
	for(int i=1;i<areaCount+1;i++){
		labels.add("y"+i);
	}
	for(int i=1;i<areaCount+1;i++){
		labels.add("d"+i);
	}

	
	
		 
		    try {  
		    	
		      File csv = new File(fileLocation); // CSV数据文件 
		      if(!csv.exists()){
		    	  csv.createNewFile();
		      }
		 
		      BufferedReader reader = new BufferedReader(new FileReader(csv));//
	           String headstr= reader.readLine();//第一行信息，为标题信息，不用,如果需要，注释掉   
	           BufferedWriter bw = new BufferedWriter(new FileWriter(csv, true)); // 附加 
	          reader.close();
	           // write headlines for CSV file
	           if(headstr==null){
	        	   for(int i=0;i<labels.size();i++){
	        		   bw.write(labels.get(i)+",");
	        	      	   }
	        	   bw.newLine();  
	           }
		      
		     
		    
		    
		      	
		           for (int i=0;i<solutions.size();i++) {
		          	// the allocation of X into different centers
		          	 
		          
		          	 ArrayList<String> indexvalues=solutions.get(i).getDaySolutionIndex();
		          	
		          	 int days=solutions.get(i).getX().size(); // number of days in each super solutions
		          	
		          	 
		          	 for(int r=0;r<days;r++){
		          		 
		          
		          		 bw.write(indexvalues.get(r) + "," );
		          		 bw.write(r + "," );
		          		 bw.write(solutions.get(i).getValue() + "," );
		      	
		          		bw.write(solutions.get(i).getX().get(r).get(0)+ "," +solutions.get(i).getX().get(r).get(1)+ ","+solutions.get(i).getX().get(r).get(2)+ ","+solutions.get(i).getX().get(r).get(3)+ ","+solutions.get(i).getX().get(r).get(4)+ ","+solutions.get(i).getX().get(r).get(5)+ ","+solutions.get(i).getX().get(r).get(6)+ ","+solutions.get(i).getX().get(r).get(7)+ ",");
		          		bw.write(solutions.get(i).getY().get(r).get(0)+ "," +solutions.get(i).getY().get(r).get(1)+ ","+solutions.get(i).getY().get(r).get(2)+ ","+solutions.get(i).getY().get(r).get(3)+ ","+solutions.get(i).getY().get(r).get(4)+ ","+solutions.get(i).getY().get(r).get(5)+ ","+solutions.get(i).getY().get(r).get(6)+ ","+solutions.get(i).getY().get(r).get(7)+ ",");
		          		bw.write(solutions.get(i).getD().get(r).get(0)+ "," +solutions.get(i).getD().get(r).get(1)+ ","+solutions.get(i).getD().get(r).get(2)+ ","+solutions.get(i).getD().get(r).get(3)+ ","+solutions.get(i).getD().get(r).get(4)+ ","+solutions.get(i).getD().get(r).get(5)+ ","+solutions.get(i).getD().get(r).get(6)+ ","+solutions.get(i).getD().get(r).get(7)+ ",");
		          		
		      		
		      		 bw.newLine();  	   

		      }
		          	 
		      }
		      
		      
		      
		      
		  //    bw.newLine();  
		      bw.close();  
		      
		 
		    } catch (FileNotFoundException e) {  
		      // File对象的创建过程中的异常捕获 
		      e.printStackTrace();  
		    } catch (IOException e) {  
		      // BufferedWriter在关闭对象捕捉异常 
		      e.printStackTrace();  
		    }  
		  }  
		
		
	
	
	
	
}
	
	

