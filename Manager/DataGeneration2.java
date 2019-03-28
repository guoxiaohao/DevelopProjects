package Manager;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Random;



import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import DataClass.Location;
import DataClass.Node;
import DataClass.SubArea;
import DataClass.SuperArea;
import java.util.List;
import static tech.tablesaw.api.QueryHelper.column;

import it.unimi.dsi.fastutil.ints.IntIterator;
import it.unimi.dsi.fastutil.ints.IntRBTreeSet;
import it.unimi.dsi.fastutil.objects.Object2DoubleOpenHashMap;
import tech.tablesaw.api.Table;
import tech.tablesaw.columns.Column;
import tech.tablesaw.columns.ColumnReference;
import tech.tablesaw.table.TemporaryView;
import tech.tablesaw.table.ViewGroup;




public class DataGeneration2 {

	// generate location centers for all sub area
	public Location[][] generateCenters(int x, int y){
		
			
	Location centers[][]=new Location[x][y];
		    for (int i=0;i<x;i++){
		    	for( int j=0;j<y;j++){
		    		centers[i][j]=new Location();
		    		centers[i][j].x=i+0.5;  
		          centers[i][j].y=j+0.5;
		          
		         // System.out.println(centers[i][j].x+"and the y value is"+ centers[i][j].y);
		  }

		  }
	
	
	
	
		return centers;
	}
	
	
	public double getDistance(Location l1, Location l2){
		double dis;
		dis=Math.sqrt(Math.pow((l1.x-l2.x), 2)+Math.pow((l1.y-l2.y), 2));
		
		return dis;
	}
	
	
	public ArrayList<Node> generateNodes(int demand, Location originalLocation, Location event_location, int x_length, int y_length){
		
		ArrayList<Node> nodes=new ArrayList<Node>();
		
		for(int i=0; i<demand; i++){
			Node node=new Node();
			Location l=new Location();
		
			l.x= Double.parseDouble(String.format("%.3f",originalLocation.x+  Math.random()*(x_length))); 
			l.y= Double.parseDouble(String.format("%.3f",originalLocation.y+Math.random()*(y_length))); 
			node.setLocation(l);
			
			if(l.x>originalLocation.x+x_length | l.y>originalLocation.y+y_length){
				System.out.println("x abnormal");
				System.out.println("x:"+l.x +" y:"+l.y);
				
			}
			
			
			if(l.x<2){
				
			//	System.out.println("x:"+l.x +" y:"+l.y);
			}
			

			node.setDemand(1);
			double w=Math.exp(-getDistance(l,event_location));
			node.setWeight(w); 
			
			
		nodes.add(node);
			
			
		}
		
		
		
		
		
		return nodes;
		
		
		
	}
	
	
public void setNodeDis( Location[] centers, double dis_thresh, ArrayList<Node> nodes){
		
		
		
		for(int i=0; i<nodes.size(); i++){
			Node node=nodes.get(i);
			
			int r[]=new int[centers.length];
			double d[]=new double[centers.length];
			for(int j=0;j<centers.length;j++){
				
				d[j]=getDistance(centers[j],node.getLocation());
				r[j]=(d[j]>=dis_thresh)?0:1;
				
			}
			
		
			
			
		}
		
		
		
		
		
		
		
	}
	
	// generate the sub-area
	
	public  SubArea[][] generateSubs(int x_lim, int y_lim, Location event, int eventDemand,double rbase){
		SubArea[][] subs=new SubArea[x_lim][y_lim];
		  
		 for(int i=0; i<x_lim;i++ ){
			 for (int j=0; j<y_lim;j++) {
				 subs[i][j]=new SubArea();
				 Location ori=new Location(i,j);
				 	Location l=new Location(i+0.5,j+0.5);
					subs[i][j].setCenters(l);
					
					double w=  Math.exp(-getDistance(l,event))+1/(x_lim*y_lim);
					w=Double.parseDouble(String.format("%.4f", w));
					subs[i][j].setWeight(w);
					// d is the demand
					int d=(int) Math.round(w*eventDemand+ Math.random()*rbase) ; 
					subs[i][j].setDemand(d);
				//	System.out.println("Original node:"+ori.x +", "+ori.y);
					ArrayList<Node> sub_nodes=generateNodes(d,ori,event,1,1);
					
					subs[i][j].setNodes(sub_nodes);
					
						
			}
		}
		
		
		
		return subs;
	}
	

	
	
	public SuperArea[] generateSupers(int x_lim, int y_lim,int x_div, int y_div, SubArea[][] subs, double dis, int hour, String day){
		
		int super_count=(x_lim/x_div)*(y_lim/y_div);
		//System.out.println("super count"+super_count);
		int sub_count=x_lim*y_lim;
		//System.out.println("sub count"+sub_count);
		int center_count_super=sub_count/super_count;
		SuperArea[] sups=new SuperArea[super_count];
		for(int y=0;y<sups.length;y++){
			sups[y]=new SuperArea(center_count_super);
		}
		int[] index=new int[sub_count/super_count];
		
		
		
	
		 for(int k1=0;k1<y_lim;k1++){ 
			 for(int k2=0;k2<x_lim;k2++){
				 
				  int km1= (k1/y_div-k1%y_div/y_div)*y_div+(k2/x_div-k2%y_div/y_div); 
				//System.out.println(km1); 
				  
				  sups[km1].demand+=subs[k2][k1].getDemand();
				  // weight of the super area is the sum of the sub-area weight
				  sups[km1].weight +=subs[k2][k1].getWeight();
				  
				  Location l=new Location( subs[k2][k1].getCenters().x,subs[k2][k1].getCenters().y) ;
				// System.out.println(l.x+","+l.y);
				 sups[km1].Centers[index[km1]++]=l;
				ArrayList<Node> nodet= subs[k2][k1].getNodes();	 
				 sups[km1].getNodes().addAll( nodet );
				 
			 }
			 
			 
		 }
		 
	for(int j=0; j< super_count;j++){
		ArrayList<Node> nodes=sups[j].getNodes();
		for(int i=0; i< nodes.size() ; i++){
			
			Node node=sups[j].getNodes().get(i);
			
			int []  r=new int[6];
			double d[]=new double[6];
			for(int k=0;k<6;k++){
				double dt=getDistance( sups[j].getCenters()[k],node.getLocation());
				d[k]=  Double.parseDouble(String.format("%.4f", dt)) ;
				
				if(d[k]>=dis){
					
					r[k]=0;
				}else{
					r[k]=1;
				}
				
				
			}
			sups[j].getNodes().get(i).setRvalues(r);
			sups[j].getNodes().get(i).setDistance(d);
		
			 sups[j].weight=Double.parseDouble(String.format("%.4f", sups[j].weight));
			sups[j].setHour(hour);
			sups[j].setDay(day);
		}
		
	 
	
		
	}	 
		 
	/*for(int j=0; j< super_count;j++){
		ArrayList<Node> nodes=sups[j].getNodes();
		for(int i=0; i< nodes.size() ; i++){
			
			Node node=sups[j].getNodes().get(i);
			for(int k=0;k<6;k++){
				System.out.println("the d value is"+sups[j].getNodes().get(i).getDistance()[k]+ "the r value is" +sups[j].getNodes().get(i).getrValue()[k]);
				
			}
			
		}
		
		
	}*/
	
		
		
		return sups;
		
	}
	
	
	
public ArrayList<SuperArea[] > generateSubfromSimulation(int x_lim, int y_lim,int x_div, int y_div,  double U, int hourcount, int eventDemand, Location event ){
	ArrayList<SuperArea[] > supers_days=new ArrayList<SuperArea[] >();
	
	for(int i=0;i<hourcount;i++){
		
			SubArea[][] subs=this.generateSubs(x_lim, y_lim, event, eventDemand, U);
		SuperArea[] supers=this.generateSupers(x_lim, y_lim, x_div, y_div, subs, U,i,"8");
		supers_days.add(supers);
		}
		

	return supers_days;
}
	
	
	
	// this method is used to generate just one day's 
 public  ArrayList< SuperArea[]>  generateSubfromRealdata(double rbase, int supcount, String fileLocation , Location[] event ){
		
	String sheetname="tweet0";
	ArrayList< SuperArea[]> supers_days=new ArrayList<SuperArea[]>() ;
	
	
	DatatoExcel de=new DatatoExcel();
		
		
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
		
	int countyIndex= this.findColumnIndex(worksheet.getRow(0), "County");
	int hourIndex=this.findColumnIndex(worksheet.getRow(0), "Hour");
			
	int demandIndex= this.findColumnIndex(worksheet.getRow(0), "Demand");
	int latiIndex=this.findColumnIndex(worksheet.getRow(0), "Latitude");
	int lontiIndex=this.findColumnIndex(worksheet.getRow(0), "Longitude");
	int superIndex=this.findColumnIndex(worksheet.getRow(0), "Super Area");
	int radiusIndex=this.findColumnIndex(worksheet.getRow(0), "Radius");
	
		
	int j=1;

	
	ArrayList<SubArea> subs=new ArrayList<SubArea>();
	int lastsuper=1;
	int lasthour=0;
	
	ArrayList<SuperArea > spa=new ArrayList<SuperArea>();
	
	while(j<=lastRowNum){
		
		SubArea sb=new SubArea();
			
			int supernow=(int) worksheet.getRow(j).getCell(superIndex).getNumericCellValue();
			int hour =(int) worksheet.getRow(j).getCell(hourIndex).getNumericCellValue();
			double la=worksheet.getRow(j).getCell(latiIndex).getNumericCellValue();
			double lg=worksheet.getRow(j).getCell(lontiIndex).getNumericCellValue();
			double radius=worksheet.getRow(j).getCell(radiusIndex).getNumericCellValue();
			int d=(int) worksheet.getRow(j).getCell(demandIndex).getNumericCellValue();
			String name=worksheet.getRow(j).getCell(countyIndex).getStringCellValue();
			
				sb.setSuperName(supernow);
				Location l=new Location(la,lg);
				sb.setCenters(l);
				sb.setDemand(d);
				sb.setHour(hour);
				sb.setName(name);
				sb.setRadius(radius);
				//System.out.println("radius"+radius);
				ArrayList<Node> nodes=new ArrayList<Node>();
				
				//System.out.println("hour"+hour);
				if(d>0 & hour<24){
			 nodes=generateNodesRealData(d,radius, l, event[hour]);
			 sb.setNodes(nodes);
				}
				 //System.out.println("node size"+ nodes.size() +"the demand is"+d);
				
				
				if(supernow==lastsuper){
					subs.add(sb);
				}else{
					
					SuperArea sp=new SuperArea(subs.size());
					ArrayList<Node> spnodes= new ArrayList<Node>();
					int superdemand=0;
					Location[] Centers=new Location[subs.size()];
					for(int k=0;k<subs.size();k++){
						Centers[k]=subs.get(k).getCenters();
						superdemand=superdemand+ subs.get(k).getDemand();	
						//System.out.println("subnode size"+subs.get(k).getNodes().size());
						if(subs.get(k).getNodes()!=null){
						spnodes.addAll(subs.get(k).getNodes());	
						}
					}
					
					int sphour=subs.get(0).getHour();
					if(spnodes.size()>0){
					sp.setNodes(spnodes);
					}
					//System.out.println("spnode size"+spnodes.size());
					sp.setCenters(Centers);
					sp.setHour(sphour);
					
				sp.setIndex(lastsuper);
				sp.setDemand(superdemand);
				
				double weight=0.0;
				for(int k0=0;k0<spnodes.size();k0++){
					
					Node nd=spnodes.get(k0);
					weight=weight+nd.getWeight();
					int sub_count=sp.getCenters().length;
					int[] rd= new int[Centers.length];
					//System.out.println("centers size"+sp.getCenters().length);
					
					for(int t=0; t<sub_count;t++ ){					
						double dis=distance(nd.getLocation().x, nd.getLocation().y,sp.getCenters()[t].x,sp.getCenters()[t].y,"N");
					//	System.out.println("dis value:"+dis);
						int rr=dis>=rbase? 0:1;
				//	System.out.println("distance:"+dis+" "+ rbase+" "+rr);
					
						rd[t]=rr;
						
					}
					spnodes.get(k0).setRvalues(rd);
					
				}
				if(weight>0 &spnodes.size()>0){
                  weight=weight/spnodes.size();
				}
						sp.setWeight(weight);
					spa.add(sp);
					subs=new ArrayList<SubArea>();
					if(j<lastRowNum){
									subs.add(sb);
									}
					lastsuper=supernow;
				}
					
				j++;
								
	}
	int days=spa.size()/supcount;
//	System.out.println("days"+days+"super count"+supcount);
	
	for(int t=0;t<days;t++){
		SuperArea[] s= new SuperArea[supcount];
		supers_days.add(s);
	}
	
	
	//System.out.println(spa.size());
	
	for(int i=0;i<spa.size();i++){
		//System.out.println("spa"+spa.get(i).getIndex() +" "+spa.get(i).getCenters().length);
		
	
	 int supname=spa.get(i).getIndex();
	 int hour=spa.get(i).getHour();
	 supers_days.get(hour)[supname-1]=spa.get(i);
	
	 
	}
	 
	
	
	
	
	
	
	
	de.superday2excel("C:\\Users\\nihao\\SC Rest\\Zgeneral\\SC data\\supers_days.xlsx", supers_days);
	
	
		
		return supers_days;
		
	}



 public  ArrayList< SuperArea[]>  readSubfromRealdata( String fileLocation){
		
	String sheetname="tweet0";
	ArrayList< SuperArea[]> supers_days=new ArrayList<SuperArea[]>() ;
	
		
		
		
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

	
	ArrayList<Node> nodes=new ArrayList<Node>();
	int lastsuper=3;
	int lasthour=0;
	int lastdemand=0;
	double lastweight=0.048862394;
	Location [] lastCenter=null;
	
	ArrayList<SuperArea > spa=new ArrayList<SuperArea>();
	
	while(j<=lastRowNum){
		String centerstr=worksheet.getRow(j).getCell(centersIndex).getStringCellValue();
		String rvaluestr="";
		
	
		 
		Node node=new Node();
	
			
			int supernow=(int) worksheet.getRow(j).getCell(superIndex).getNumericCellValue();  // super index
			int hour =(int) worksheet.getRow(j).getCell(hourIndex).getNumericCellValue();
			int dvalue=(int) worksheet.getRow(j).getCell(demandIndex).getNumericCellValue();
			double superweight= worksheet.getRow(j).getCell(areaweightIndex).getNumericCellValue();
			
			
			if(dvalue>0){
				double wvalue=(int) worksheet.getRow(j).getCell(nodeweightIndex).getNumericCellValue();
				node.setWeight(wvalue);
				double la=worksheet.getRow(j).getCell(latiIndex).getNumericCellValue();
				double lg=worksheet.getRow(j).getCell(lontiIndex).getNumericCellValue();



				Location l=new Location(la,lg);
				node.setLocation(l);

					
				rvaluestr=worksheet.getRow(j).getCell(rvalueIndex).getStringCellValue();
					
					String[] rstr=rvaluestr.split(",") ;
									int[] r=new int[rstr.length];
					
					
					for(int k=0;k<rstr.length;k++){
						r[k]=Integer.valueOf(rstr[k]);
										}
					
					node.setRvalues(r);

			}
				if(supernow==lastsuper){
					if(dvalue>0){
					nodes.add(node);
					}
					
				}else{
					
					String[] cstr=centerstr.split(";");
					Location [] center=new Location [cstr.length];
					
					for(int k=0;k<cstr.length;k++){
						String s[]=cstr[k].split(",");
						double lavalue=Double.valueOf(s[0]) ;				
						double lnvalue=Double.valueOf(s[1]) ;			
						center[k]=new Location(lavalue,lnvalue);
					}
					
					SuperArea sp=new SuperArea(center.length);
					
					sp.setCenters(lastCenter);
					sp.setNodes(nodes);
					sp.setWeight(lastweight); 
					sp.setCenters(lastCenter);
					sp.setHour(lasthour);
					sp.setIndex(lastsuper);
				    sp.setDemand(lastdemand);
						
					spa.add(sp);
					nodes=new ArrayList<Node>();
					
					if(j<lastRowNum){
						lasthour=hour;
						lastdemand=dvalue;
						lastCenter=center;
						lastweight=superweight;
						
						if(dvalue>0){
									nodes.add(node);
						}
									}
					lastsuper=supernow;
				}
					
				j++;
								
	}
	
	int supercount=spa.size()/(hourcount); 
	
	//System.out.println("supercount"+supercount+"super count"+spa.size() );
	
	for(int t=0;t<hourcount+1;t++){
		SuperArea[] s= new SuperArea[supercount];
		supers_days.add(s);
	}
	
	
	//System.out.println(spa.size());
	
	for(int i=0;i<spa.size();i++){
	//	System.out.println("spa"+spa.get(i).getIndex() );
	 int day= spa.get(i).getHour();
	 int supname=spa.get(i).getIndex();
	 supers_days.get(day)[supname-1]=spa.get(i);
	
	 
	}
	
	
	
	
	
	
	
	
	
	
	
		
		return supers_days;
		
	}



 






public ArrayList<Location[]> getEvenLocationDaysFromExcelFile(String excelLocation){
	Table eventtable=null;
	try {
		eventtable= Table.read().csv(excelLocation );
	} catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	
	ArrayList<Location[]> result=new ArrayList<Location[]>();
	Column daycol=eventtable.column("Day").unique();
	Column hourcol=eventtable.column("Hour").unique();
	int latIndex=eventtable.columnIndex("Latitude");
	int lonIndex=eventtable.columnIndex("Longitude");
	
	int daycount=daycol.size();
	int hourcount=hourcol.size();
	//ColumnReference statusRef = column("Day");
	
	for(int i=0;i<daycount;i++){
		int dayvalue=Integer.valueOf(daycol.getString(i)) ;
		 Table day=eventtable.selectWhere(   eventtable.shortColumn("Day").isEqualTo(dayvalue));
		 Location[] hourLocation=new Location[hourcount];
		for(int j=0;j<hourcount;j++){
		Double lat= Double.valueOf(day.get(j,latIndex )) ;
		Double lon=Double.valueOf( day.get(j,lonIndex )) ;
		hourLocation[j]=new Location(lat,lon);
		
		}
		
		result.add(hourLocation);
	}
	
	
	
	
	
	
	
	
	return result;
	
	
	
	
	
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



public ArrayList<Node> generateNodesRealData(int nodecount,double radius, Location center, Location eventLocation){
	ArrayList <Node> nodelist =new ArrayList <Node>();

	   for(int i=0;i<nodecount;i++){
		   
		   Node node=new Node();
		   
		   Location l=this.getLocationInLatLngRad(radius, center);
		   
		   node.setLocation(l);
		   node.setDemand(1);
		  double dis= this.getDistance(l, eventLocation)/10.0;
		 double weight= Math.exp(-dis);
		   node.setWeight(weight);
		   nodelist.add(node);
		  
	   }
	   
	return nodelist;
	
}


public Location getLocationInLatLngRad(double radiusInMiles, Location currentLocation) {
    double x0 = currentLocation.x;
    double y0 = currentLocation.y;
    double foundLatitude;
    double foundLongitude;
    Location copy = new Location();

    Random random = new Random();

    // Convert radius from meters to degrees.
    double radiusInDegrees = (radiusInMiles*1609.34) / 111320f;

    do{
    // Get a random distance and a random angle.
    double u = random.nextDouble();
    double v = random.nextDouble();
    double w = radiusInDegrees * Math.sqrt(u);
    double t = 2 * Math.PI * v;
    // Get the x and y delta values.
    double x = w * Math.cos(t);
    double y = w * Math.sin(t);

    // Compensate the x value.
    double new_x = x / Math.cos(Math.toRadians(y0));

    

    foundLatitude= x0 + new_x;
    foundLongitude= y0 + y;
     
   copy.x=foundLatitude;
   copy.y=foundLongitude;
    } while(this.distance(foundLatitude, foundLongitude, x0, y0, "M")>radiusInMiles);
    return copy;
}


public  double distance(double lat1, double lon1, double lat2, double lon2, String unit) {
	if ((lat1 == lat2) && (lon1 == lon2)) {
		return 0;
	}
	else {
		double theta = lon1 - lon2;
		double dist = Math.sin(Math.toRadians(lat1)) * Math.sin(Math.toRadians(lat2)) + Math.cos(Math.toRadians(lat1)) * Math.cos(Math.toRadians(lat2)) * Math.cos(Math.toRadians(theta));
		dist = Math.acos(dist);
		dist = Math.toDegrees(dist);
		dist = dist * 60 * 1.1515;
		if (unit == "K") {
			dist = dist * 1.609344;
		} else if (unit == "N") {
			dist = dist * 0.8684;
		}
		return (dist);
	}
}











}

