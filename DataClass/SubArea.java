package DataClass;

import java.util.ArrayList;

public class SubArea {
	
	

	public Location Center;
	public int demand;
	public int CH_count;
	double weight;
	public int superarea;
	public int hour;
	public String name;
	double radius;
	public int day;
	
	 ArrayList<Node> nodeArray;
	 
	 public int getDay(){
		 return this.day;
	 }
	 
	 public void setDay(int dayvalue){
		 
		 this.day=dayvalue;
		 
	 }
	 
	 
	 
	 
	 
	 public double getRadius(){
		 return this.radius;
	 }
	 
	 
	
	 public String getName(){
		 return this.name;
	 }
	 
	 
	 
	 
	 public void  setName(String subname){
		 
		 this.name=subname;
	 }
	 
	 
	 public void setRadius(double r){
		 this.radius=r;
	 }
	 
	 
	 
	 
	 
	 
	 
	 public int getHour(){
		 return this.hour;
	 }
	 
	 public void setHour(int d){
		 
		 this.hour=d;
		 
	 }
	 
	 
	 public int getSuperName(){
		 
		 	 
		 return this.superarea;
	 }
	 
	 public void setSuperName(int sup){
		 
		 this.superarea=sup;
	 }
	 
	 
	 public Location getCenters(){
			
			return this.Center ;
			
		}
		
	   public void setCenters(Location center){
			
			this.Center=center;		
		}

	
	public ArrayList<Node> getNodes(){
		
		return this.nodeArray;
		
	}
	
   public void setNodes( ArrayList<Node> nodes){
		
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
			
			return this.getCH_count();
		}
	   
 public void setCH_count(int ch){
			
			this.CH_count=ch ;
			
		}
	
	
	
	
	

	
	
	
	

}
