/**
 * 
 */
package DataClass;

import java.util.ArrayList;

/**
 * @author bairongw
 * This class is used to package the lower solutions data
 */
public class LowerSolutions {

	public int[]	X;
	public int[][]	Y; // whether the node is covered by at least CHs
	public ArrayList<ArrayList<Integer>> D;
	public String solutionIndex;
	public double coverage;
	public int CH_count;
	public ArrayList<Node> nodes;
	public double superCoverage;
	public int supercover;
	public int cover;
	public String superSoulationIndex;
	public double time;
	 
	 public double getLowerTime(){
		 
		 return this.time;
	 }
   public void setLowerTime(double eltime){
	
	this.time=eltime;
  }
	
	public void setSuperSolutionIndex(String supIndex){
		
		this.superSoulationIndex=supIndex;
	}
public String getSuperSolutionIndex(){
		
		return this.superSoulationIndex;
	}
	
	
	
	public void setCover(int covervalue){
		
		this.cover=covervalue;
		
	}
	
public int getCover(){
		
		return this.cover;
		
	}
	
	public void setSuperCover(int supcover){
		
		this.supercover=supcover;
		
	}
	
public int getSuperCover(){
		
		return this.supercover;
		
	}
	
	
public void setSuperCoverage(double supercover){
		
		this.superCoverage=supercover;
	}
public double getSuperCoverage(){
	return this.superCoverage;
		
		
	}
	
	
	
	
public void setNodes(ArrayList<Node> node){
		
		this.nodes =node;
	}
public ArrayList<Node> getNodes(){
	return this.nodes;
		
		
	}
	
	
	
	
	
	
	
	
	
	
	
	public void setCoverage(double cover){
		
		this.coverage=cover;
	}
public double getCoverage(){
	return this.coverage;
		
		
	}
	
	
	
	public String getSolutionIndex(){
		
		return this.solutionIndex;
	}
	public void setSolutionsIndex(String indexValue){
		this.solutionIndex=indexValue;
	}
	
	public int[] getX(){
		return this.X;
	}
	
	public void setX(int[] Xvalue){
		this.X=Xvalue;
	}
	public int[][] getY(){
		return this.Y;
	}
	
	public void setY(int[][] Yvalue){
		this.Y=Yvalue;
	}
	
	public int getCH_count(){
		return this.CH_count;
	}
	
	public void setCH_count (int ct){
		this.CH_count=ct;
	}
	
}
