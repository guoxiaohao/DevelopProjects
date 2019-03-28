/**
 * 
 */
package DataClass;

import java.util.ArrayList;

/**
 * @author bairongw
 * This class is used to generate the data type for super solutions
 */
public class UpperSolutions {
	
	public ArrayList<ArrayList<Integer>>	X;
	public ArrayList<ArrayList<Integer>>	Y;
	public ArrayList<ArrayList<Integer>> 	D;
	public ArrayList<String> solutionIndex;
	public double value;
	public int capacity;
	public double radius;
	public int CHcount;
	public double equity;
	public int u_policy;
	public int cover;
	public double time;

	 
 	 public double getUpperTime(){
		 
		 return this.time;
	 }
    public void setUpperTime(double eltime){
	
	this.time=eltime;
   }
	
	
	public void setCover(int covervalue){
		this.cover=covervalue;
	}
	
public void setRadius(double r){
		
		this.radius=r;
	}
	
	
	public void setX(ArrayList<ArrayList<Integer>> xvalue){
		
		this.X=xvalue;
	}
	
public void setY(ArrayList<ArrayList<Integer>> yvalues){
		
		this.Y=yvalues;
	}

public void setD(ArrayList<ArrayList<Integer>> dvalues){
	
	this.D=dvalues;
}
	
public void setDaySolutionIndex(ArrayList<String> sindex){
	this.solutionIndex=sindex;
}
	
public void setValue(double cplexValue){
	this.value=cplexValue;
}
public void setCapacity(int capacityValue){
	this.capacity=capacityValue;
	
}

public void setCHcount(int chcount){
	this.CHcount=chcount;
}
public void setU(int uvalue){
	this.u_policy=uvalue;
}
public void setEquity(double evalue){
	this.equity=evalue;
}
	



public ArrayList<ArrayList<Integer>> getX(){
	
	return this.X;
}

public ArrayList<ArrayList<Integer>>  getY(){
	
	return this.Y;
}

public ArrayList<ArrayList<Integer>>  getD(){

return this.D;
}

public ArrayList<String> getDaySolutionIndex(){
return this.solutionIndex;
}

public double getValue(){
 return this.value;
}
public int getCapacity(){
return this.capacity;

}

public int getCHcount(){
return this.CHcount;
}
public int getU(){
return this.u_policy;
}
public double getEquity(){
return this.equity;
}

public double getRadius(){
	
	return this.radius;
}


public int getCover(){
	return this.cover;
}
	
}
