package Optimization;




import static tech.tablesaw.api.QueryHelper.column;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import DataClass.Location;
import DataClass.Node;
import DataClass.SuperArea;
import tech.tablesaw.api.Table;
import tech.tablesaw.table.TemporaryView;
import tech.tablesaw.table.ViewGroup;

import java.io.BufferedReader;
import java.io.BufferedWriter;  
import java.io.File;  
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;  
import java.io.IOException;  
 


public class Hello {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		
	 
		 
		 
		    try {  
		    	
		      File csv = new File("C://Users//Administrator//Desktop//Day 15//NCupper15.2.0.csv"); // CSV数据文件 
		      if(!csv.exists()){
		    	  csv.createNewFile();
		      }
		 
		      BufferedReader reader = new BufferedReader(new FileReader(csv));//换成你的文件名   
	           String s= reader.readLine();//第一行信息，为标题信息，不用,如果需要，注释掉   
	           BufferedWriter bw = new BufferedWriter(new FileWriter(csv, true)); // 附加 
	           
	           if(s==null){
	        	   bw.write("\"李四\"" + "," + "\"1988\"" + "," + "\"1992\"");
	        	   bw.newLine();  
	           }
		      
		     
		     
		      // 添加新的数据行 
		      bw.write("\"李四\"" + "," + "\"1988\"" + "," + "\"1992\"");  
		      bw.newLine();  
		      bw.close();  
		 
		    } catch (FileNotFoundException e) {  
		      // File对象的创建过程中的异常捕获 
		      e.printStackTrace();  
		    } catch (IOException e) {  
		      // BufferedWriter在关闭对象捕捉异常 
		      e.printStackTrace();  
		    }  
		  }  
		
		
	
	
	
	
	
	
	
	
	
	
	
	
		


	
	
	public void  readSubfromRealdata( String fileLocation){
		
		String sheetname="tweet0";
	
			
			
			File f=new File(fileLocation);

			XSSFWorkbook workbook=null;
			FileInputStream filein=null;
			
			
				try {
					filein=new FileInputStream(f);
					workbook = new XSSFWorkbook(filein);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				
				XSSFSheet worksheet= workbook.getSheet(sheetname);
			
		int lastRowNum=worksheet.getLastRowNum();
		int hourcount= (int) worksheet.getRow(lastRowNum-1).getCell(0).getNumericCellValue();
			
			
		
		int hourIndex=this.findColumnIndex(worksheet.getRow(0), "Hour");		
		int superIndex= this.findColumnIndex(worksheet.getRow(0), "Super Area");
		int areaweightIndex=this.findColumnIndex(worksheet.getRow(0), "Area Weight");		
		int demandIndex= this.findColumnIndex(worksheet.getRow(0), "Demand");
		int centersIndex=this.findColumnIndex(worksheet.getRow(0), "Centers");		
		int nodeweightIndex= this.findColumnIndex(worksheet.getRow(0), "Node Weight"); 
		int latiIndex=this.findColumnIndex(worksheet.getRow(0), "Location.x");		
		int lontiIndex= this.findColumnIndex(worksheet.getRow(0), "Location.y");
		int rvalueIndex= this.findColumnIndex(worksheet.getRow(0), "R values");
			
		int j=1;

		while(j<=lastRowNum){
							
				int supernow=(int) worksheet.getRow(j).getCell(superIndex).getNumericCellValue();  // super index
				int hour =(int) worksheet.getRow(j).getCell(hourIndex).getNumericCellValue();
				int dvalue=(int) worksheet.getRow(j).getCell(demandIndex).getNumericCellValue();
				double superweight= worksheet.getRow(j).getCell(areaweightIndex).getNumericCellValue();
				System.out.println(supernow);
				
					j++;
									
		}
		
	
		
		
		
		
		
		
		
		
		
			
			
		}

	
	
public  int findColumnIndex(Row row, String cellContent){
    /*
     *  This is the method to find the row number
     */

    int columnNum = 0; 
Iterator<Cell> it =row.cellIterator();
Cell cell;
        while(it.hasNext()) {
        	cell=it.next();
//System.out.println("the cell value is"+cell.getRichStringCellValue().getString ().trim());
            

                if(cell.getStringCellValue().trim().equals(cellContent)){

                	columnNum =cell.getColumnIndex();
                        return columnNum;  
                }
            }
           
    return columnNum;
}




}
