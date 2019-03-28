/**
 * 
 */
package Manager;
import java.util.ArrayList;
import java.util.Collections;

import DataClass.LowerSolutions;
import DataClass.Node;
import DataClass.SuperArea;
import DataClass.UpperSolutions;

import ilog.concert.IloException;
import ilog.concert.IloIntSetVar;
import ilog.concert.IloIntVar;
import ilog.concert.IloLinearNumExpr;
import ilog.concert.IloNumExpr;

import ilog.cplex.IloCplex;

/**
 * @author bairongw
 * this class is used to generate a lower-level solution
 */
public class Lower_level_model {
  
	
	
	public ArrayList<LowerSolutions>  solveMe(SuperArea spa, int CH_count, int capacity, int covered,String superIndex){
		
		int sub_count=spa.getCenters().length; 
		int fulCa=CH_count*capacity;
		
		ArrayList<LowerSolutions> solutions= new ArrayList<LowerSolutions>();	
		ArrayList<Node> nodes=spa.getNodes();
		
		int nodeSize=spa.nodeArray.size();
		int day=spa.getHour();
		
		
		try {
			//IloCplex.Param.MIP.Tolerances(0.2);
			IloCplex cplex=new IloCplex();
			
			 cplex.setParam(IloCplex.Param.MIP.Pool.RelGap,  0.01);
				
				cplex.setParam(IloCplex.Param.MIP.Pool.Capacity ,10);
				cplex.setParam(IloCplex.Param.MIP.Pool.Replace , 2);
				
				cplex.setParam(IloCplex.Param.ClockType ,2);
				cplex.setParam(IloCplex.Param.TimeLimit ,900);
				
				
				
			cplex.setOut(null);
			
			IloIntVar[] x=new IloIntVar[sub_count];// the number of CHs assigned for each super area at day t
			IloIntVar[][] y=new IloIntVar[nodeSize][];// the total number of covered demands for each super area at day t
			// define the x variable, the nubmer of CHs in each sub-area within each super area in each day
			for (int i=0; i<nodeSize;i++){
				y[i]=cplex.intVarArray(sub_count, 0, 1); 
			}
			for(int j=0;j<sub_count;j++){
			x[j]=cplex.intVar(0,CH_count);
			}
			
			
			// define the objective function
			
			IloLinearNumExpr obj;
			obj = cplex.linearNumExpr();
			
			//// the values of each super area each day		  
			 for(int j=0; j< nodeSize;j++){
						  obj.addTerm(nodes.get(j).getWeight(), y[j][0]);	 
			  }
			
			
			
			 // adding the cons that y[i][t] <= d[i][t] for all i and t, covered demand less than the required
			 IloLinearNumExpr k2= cplex.linearNumExpr(); 
			 IloLinearNumExpr k3= cplex.linearNumExpr();
			for(int i=0;i<nodeSize;i++){
				 IloLinearNumExpr k1= cplex.linearNumExpr();
				
				 
				for(int j=0; j< sub_count;j++){
					
			  k1.addTerm(nodes.get(i).getRvalues()[j] , x[j]); // r[k][i]*x[i] whether there will be some
			  
			  k2.addTerm(1.0, y[i][j]); // cover traffic, for all nodes and their times
			 
			}
				k3.addTerm(y[i][0],1.0);  // whether the node is covered or not
				
				cplex.addLe(cplex.sum(y[i]), k1); // actually covered is less than could be covered
			
			
			}
			
			
			cplex.addLe(k2, fulCa);     // never exceed the capacity
				cplex.addLe(k3, covered );  // never exceed the covered value
			cplex.addLe(cplex.sum(x), CH_count); // sum xi<=n never exceed the available CHs
			
			
			cplex.addMaximize(obj);
			cplex.populate();
			
			int solutionSize=cplex.getSolnPoolNsolns() ;
			double time=cplex.getCplexTime();
			//System.out.println("solutioin number is"+d);
			cplex.getSolnPoolNsolns();
			
			
		
			
			if(cplex.solve()){
			//	System.out.println("lower solutioin number is"+solutionSize+"solution time is"+time);
			//	System.out.println("obj= "+ cplex.getObjValue() );
			//	cplex.exportModel("file_name_lower.lp");
				
	
				for(int k=0;k<solutionSize;k++){  // k the index of the solutions number
					
				String lowerIndexStr="S-"+String.format("%02d", k)+"-"+String.format("%02d", spa.getIndex())+"-"+String.format("%02d", spa.getHour()) ;
			LowerSolutions los=new LowerSolutions();
			los.setCoverage(cplex.getObjValue(k));
			los.setSuperCover(covered);
			los.setSolutionsIndex(lowerIndexStr);
			los.setCH_count(CH_count);
			los.setSuperSolutionIndex(superIndex);
			los.setLowerTime(time);
		//System.out.println("super Index"+superIndex);	
			
				int[] xvalue=new int[sub_count];
			int[][]	yvalue=new int [nodeSize][sub_count];
			
			int sumtotal=0;
			for(int i=0;i<nodeSize;i++){
				int sum=0;
				for(int j=0;j<sub_count;j++){
					
					yvalue[i][j]=(int) cplex.getValue(y[i][j]);
					
					sum=sum+yvalue[i][j];
				}
				sumtotal=sumtotal+sum;
			}
			
			for(int j=0;j<sub_count;j++){
				
				xvalue[j]=(int) cplex.getValue(x[j]);
				
			}
			los.setCover(sumtotal);
			los.setX(xvalue);
			los.setY(yvalue);
			los.setNodes(spa.getNodes());
		
			
			solutions.add(los);
					}	
				
				//System.out.println("the size of the solutions is: "+solutions.size());
				
				/*ResultstoExcel res= new ResultstoExcel();
				res.upper2excel("C://Users//nihao//Dropbox//Twitter Coverage//UpperResults//upper.xlsx",solutions);
			*/	}else{
				System.out.println("no solutions found!");
				
			}
			
			
			
		} catch (IloException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		
		
		return solutions;
		  
		
		
		




		
		
		
	}
	
	
	public ArrayList<Integer> findFactors(int num) {        
	    ArrayList<Integer> factors = new ArrayList<Integer>();

	    // Skip two if the number is odd
	    int incrementer = num % 2 == 0 ? 1 : 2;

	    for (int i = 1; i <= Math.sqrt(num); i += incrementer) {

	        // If there is no remainder, then the number is a factor.
	        if (num % i == 0) {
	        	
	            factors.add(i);
	        	

	            // Skip duplicates
	            if (i != num / i) {
	            	
	                factors.add(num / i);
	            }

	        }
	    }

	    // Sort the list of factors
	    Collections.sort(factors);

	    return factors;
	}
	

	
	
}
