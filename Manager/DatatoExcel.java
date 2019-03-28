/**
 * 
 */
package Manager;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;

import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.xssf.usermodel.XSSFRow;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import DataClass.Location;
import DataClass.Node;
import DataClass.SuperArea;



/**
 * @author bairongw
 * this class is to write all the generate data to excel, including super area data and sub area data
 */
public class DatatoExcel {

	
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}
	
	
public void superday2excel(String fileLocation, ArrayList<SuperArea[]> superArea  ){
			
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
		
		
		
		ArrayList<String> labels=new ArrayList<String>();
		
	labels.add("Hour");
	labels.add("Super Area");
	labels.add("Area Weight");
	labels.add("Demand");
	labels.add("Centers"); // this is an String contains every 
	labels.add("Node Weight");
	labels.add("Location.x");
	labels.add("Location.y");
	labels.add("R values");
		
		FileOutputStream fileout=null;
		
		
		
		
		this.addCellForSuperDayData(superArea, workbook, labels);
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
	


public  void addLabelForRealData ( XSSFSheet sheet, ArrayList<String> labels)	{ 
	
	XSSFRow row=sheet.createRow(0);
	for(int k=0;k<labels.size();k++){
		row.createCell(k).setCellValue(labels.get(k));
	}
	
	
}	


public void addCellForSuperDayData(ArrayList<SuperArea[]> sups,XSSFWorkbook myexcel, ArrayList<String> labels) {
	//solutions is an array of the solution class, the size is the number of solutions
		// define the x variable, the number of CHs in each sub-area within each super area in each day
	
			int tracedRow=0;
int sheetNum=myexcel.getNumberOfSheets();
XSSFSheet mysheet=null;
//System.out.println("the sheet num is "+sheetNum);
if(sheetNum==0){
	 mysheet=myexcel.createSheet("tweet"+sheetNum);
	
	 addLabelForRealData(mysheet,labels);
	 tracedRow=mysheet.getLastRowNum();
	// System.out.println("we create a new sheet tweet0"+"and the last row number is"+tracedRow+"and the first row number is"+mysheet.getFirstRowNum());
}
if(sheetNum>=1){
	
	myexcel.setSheetName( sheetNum-1, "tweet0");
	mysheet=myexcel.getSheetAt(sheetNum-1);
	tracedRow=mysheet.getLastRowNum();
	//System.out.println("the number of tracedrow is, we get the last sheet "+tracedRow);
}


int sz=sups.size();
//System.out.println("all hour length is"+sz);
tracedRow=tracedRow+1;
	
     for (int i=0;i<sz;i++) {
    	 SuperArea[] s=sups.get(i);  // for the hour i
    	// System.out.println("super area day"+i);
          for(int j=0;j<s.length;j++ ){
        	          	  
    	SuperArea sp=s[j];
    	//System.out.println("j value"+j);
    	     ArrayList<Node>  nodes=   s[j].getNodes();
    	     int nodesize=nodes.size();
	 		Location[] m=sp.getCenters();
	 		String centerstr=""+m[0].x+","+ m[0].y+";";
	 		for(int k=1;k<m.length;k++){
	 			centerstr=centerstr+m[k].x+","+ m[k].y+";";
	 				
	 		}
	 		
	 		if(nodesize==0){
	 			 XSSFRow row=mysheet.createRow(tracedRow++);
	 			row.createCell(0,1).setCellValue(sp.getHour());
				row.createCell(1,1).setCellValue(sp.getIndex() );
				row.createCell(2,1).setCellValue(sp.getWeight());
				row.createCell(3,1).setCellValue(sp.getDemand());
				row.createCell(4,1).setCellValue(centerstr);
	 		}else{
    	 
    	 for(int r=0;r<nodesize;r++){
    	 
    	 XSSFRow row=mysheet.createRow(tracedRow++);
    	 
    	 Node node=nodes.get(r);
    	 
    	 int[] rvalue=node.getRvalues();
    	 String rvaluestr=rvalue[0]+"";
    	 for(int k=1;k<rvalue.length;k++){
	 		rvaluestr= rvaluestr+","+rvalue[k];
	 				
	 		}
    	 
    	
  			row.createCell(0,1).setCellValue(sp.getHour());
			row.createCell(1,1).setCellValue(sp.getIndex() );
			row.createCell(2,1).setCellValue(sp.getWeight());
			row.createCell(3,1).setCellValue(sp.getDemand());
			row.createCell(4,1).setCellValue(centerstr);
			row.createCell(5,1).setCellValue(node.getWeight());
			row.createCell(6,1).setCellValue(node.getLocation().x);
			row.createCell(7,1).setCellValue(node.getLocation().y);
			row.createCell(8,1).setCellValue(rvaluestr);
	
}
	 		}
    	 
    	 
    	 
    	 
}
     
     
}


	
	
	
	
	
	
	
	
	
	
	
	
	
	
}	

	
	

}
