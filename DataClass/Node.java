/**
 * 
 */
package DataClass;

import java.util.ArrayList;

/**
 * @author bairongw
 * This class is used to generate the node class for 
 */
public class Node {
int [] rValues;
double [] dValues; // the distance between the node to all centers
int demand;
double weight;
Location location;
int hour;


public void setHour(int hourvalue){
	this.hour=hourvalue;
	
	
}


public int getHour(){
	
	return this.hour;
}

public Location getLocation(){
	return this.location;
}

public double getWeight(){
	return this.weight;
	
}

public int getDemand(){
	
	return this.demand;
	
}
	
public int[] getRvalues(){
	return this.rValues;
}


public void setRvalues(int[] r){
	
	this.rValues=r;
}

public double[] getDistance(){
	return this.dValues;
}


public void setDistance(double[] d){
	
	this.dValues=d;
}

public void setLocation(Location l){
	this.location=l;
}

public void setWeight(double weight){
	 this.weight=weight;
	
}

public void setDemand(int dvalue){
	
	 this.demand=dvalue;
	
}
	



public void setdvalues(double[] d){
	
	this.dValues=d;
}





}
