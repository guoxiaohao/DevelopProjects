/**
 * 
 */
package DataClass;

import java.util.ArrayList;

/**
 * @author bairongw
 *
 */
public class SuperArea {
	
	public Location[] Centers;
	public int demand;
	public int CH_count;
	public double covered_demand;
	public int index;
	public int hour;
	public double weight;
	public String solutionName;
	 public ArrayList<Node> nodeArray;
	 public String day;
	


	 
	 public String getSolutionnName(){
		 return this.solutionName;
	 }
	 public void setSolutionName(String solutionNameValue){
		 this.solutionName=solutionNameValue;
	 }
	
	 public String getDay(){
		 return this.day;	 
	 }
	 
	 public void setDay(String dayValue){
		 this.day=dayValue;
		 
	 }
	 
	 
	 
	 public int getHour(){
		 return this.hour;
	 }
	 public void setHour(int hourvalue){
		 this.hour=hourvalue;
	 }
	 
	
	 public SuperArea(int CenterCount){
		 
		 Centers=new Location[CenterCount];
		 this.nodeArray=new ArrayList<Node>();
	 }
	 
	 
	 
	 
	 public Location[] getCenters(){
			
			return this.Centers ;
			
		}
		
	   public void setCenters(Location[] locations){
			
			this.Centers=locations;		
		}

	
	public ArrayList<Node> getNodes(){
		
		return this.nodeArray;
		
	}
	
   public void setNodes(ArrayList<Node> nodes){
		
		this.nodeArray=nodes;		
	}


   public double getWeight(){
		
		return this.weight;
	}
   
	public void setWeight(double w){
		
		this.weight=w;
		
	}
	
	 public int getDemand(){
			
			return this.demand ;
		}
	   
    public void setDemand(int d){
			
			this.demand=d ;
			
		}
	
	 public int getCH_count(){
			
			return this.CH_count ;
		}
	   
 public void setCH_count(int ch){
			
			this.CH_count=ch ;
			
		}
	
	public int getIndex(){
		
		return this.index;
	}
	
public void setIndex(int indexValue){
		
		 this.index=indexValue;
	
	
}
	
	
	
	
public double getCoveredDemand(){
	
		return this.covered_demand;
	}
 
	public void setCoveredDemand(double d){
		
		this.covered_demand=d;
		
	}
	
	
	
	
}
