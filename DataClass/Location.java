package DataClass;

public class Location {

	public double x;
	public double y;
	
	public Location(double xvalue, double yvalue){
		this.x=xvalue;
		this.y=yvalue;
		
	}
	
	public Location(){
		
		
	}
	
	public double getX(){
		return this.x;
		
	}
	
	public double getY(){
		return this.y;
		
	}
	public void setX(double xvalue){
		
		this.x=xvalue;
		
		
	}
	
public void setY(double yvalue){
		
		this.y=yvalue;
	}
	
	
}
