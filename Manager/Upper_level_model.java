/**
 * 
 */
package Manager;
import java.util.ArrayList;
import java.util.Collections;
import java.util.concurrent.TimeUnit;

import DataClass.SuperArea;
import DataClass.UpperSolutions;

import ilog.concert.IloException;

import ilog.concert.IloIntVar;
import ilog.concert.IloLinearNumExpr;
import ilog.concert.IloNumExpr;

import ilog.cplex.IloCplex;

/**
 * @author bairongw
 * this class is used to genreate upper-level class
 */
public class Upper_level_model {
  
	
	
	public ArrayList<UpperSolutions>  solveMe(ArrayList<SuperArea[]> supers_days,int CH_count, double equity, int days, int b, int u_policy, double rbase){ // rbase means the U value
		
		int super_count=supers_days.get(0).length ;
		
		ArrayList<UpperSolutions> solutions=new ArrayList<UpperSolutions>();	
		
		try {
			//IloCplex.Param.MIP.Tolerances(0.2);
			IloCplex cplex=new IloCplex();
			
		 cplex.setParam(IloCplex.Param.MIP.Pool.RelGap,  0.01);
			
			cplex.setParam(IloCplex.Param.MIP.Pool.Capacity ,10);
			
			
			cplex.setParam(IloCplex.Param.MIP.Pool.Replace , 2);
			cplex.setParam(IloCplex.Param.ClockType ,2);
			cplex.setParam(IloCplex.Param.TimeLimit ,900);
			
			
			
			
			//System.out.println("parameter set"+cplex.getParameterSet().getParam(arg0));
			
			cplex.setOut(null);
			
			IloIntVar[][] x=new IloIntVar[super_count][];// the number of CHs assigned for each super area at day t
			IloIntVar[][] y=new IloIntVar[super_count][];// the total number of covered demands for each super area at day t
			// define the x variable, the nubmer of CHs in each sub-area within each super area in each day
			for (int i=0; i<super_count;i++){
				
				x[i]=cplex.intVarArray(days, 0, CH_count);
				y[i]=cplex.intVarArray(days, 0, Integer.MAX_VALUE ); 
				
			}
			
			// define the objective function
			
			IloLinearNumExpr obj;
			obj = cplex.linearNumExpr();
			//System.out.println(super_count);
			
			 for(int j1=0; j1< super_count;j1++){
				 // System.out.println("j1 value is"+ j1);
				 for(int i1=0;i1<days;i1++) {
					   // adding the obj terms 
					System.out.println("super"+j1+"day:"+i1);
					  System.out.println(" the weight value is"+ supers_days.get(i1)[j1].getWeight());
					
						double weight= supers_days.get(i1)[j1].getWeight();
					  obj.addTerm(weight, y[j1][i1]);	 // the values of each super area each day		  
				 }
				  
			  }
			
			
			
			 // adding the cons that y[i][t] <= d[i][t] for all i and t
			for(int i1=0;i1<days;i1++){
				for(int j1=0; j1< super_count;j1++){
			  IloLinearNumExpr k1= cplex.linearNumExpr();
			  k1.addTerm(1.0, y[j1][i1]);
			   cplex.addLe(k1, supers_days.get(i1)[j1].getDemand());
			}
			
			}
			
			
			// adding the constraint of y[i][t]<=x[i][t]*b
			
			for(int k0=0;k0<days;k0++){
					
				for(int km=0;km<super_count;km++){
						
					cplex.addLe(y[km][k0],cplex.prod(b, x[km][k0]) ) ;
					
					}
					
				}
			
			
			// adding the constraints of less than the N, this is for all t
			for(int k0=0;k0<days;k0++){
				 IloLinearNumExpr k1= cplex.linearNumExpr();
				for(int j1=0; j1< super_count;j1++){ 
				  k1.addTerm(1.0, x[j1][k0]);
				}	
		 cplex.addEq( k1, CH_count);
				
		
			}	
			

		/*	//  total number of demand for each super area for all 24 days
			int [] demand=new int[super_count];
		
			   for(int t1=0;t1<super_count;t1++){		 
				   for(int t=0; t<days;t++){
					//m[t1].addTerm(1.0, y[t1][t]);
					demand[t1]+= supers_days.get(t)[t1].getDemand();
					}
				   
				   
				  // System.out.println("the demand is"+demand[t1]);		 
			}
			 
			   
			   //this is for a 24 time period		   
			 for(int i=0;i<super_count-1;i++){
				for(int j=i+1;j<super_count;j++){
				 IloNumExpr u= cplex.prod(1/(double)demand[i],cplex.sum(y[i])); //(double) 
					//System.out.println(1.0/(double)demand[i] +" "+demand[i]);			 
					 IloNumExpr u1= cplex.prod(1/ (double)demand[j],cplex.sum(y[j])) ;
					 cplex.addLe(cplex.diff(u, u1), equity);
						cplex.addGe(cplex.diff(u, u1), -equity);
						
				}
			 }*/
			//IloLinearNumExpr[][][] sy=new IloLinearNumExpr[super_count][][];// the total number of covered demands for each super area at day t
			   
			
			int unit=days/u_policy;
			int unitm=Math.floorMod(days, u_policy);
			int [][] demand;
			IloNumExpr[][] gf;
			
			if(unitm>0){
				demand=new int[super_count][unit+1];
				gf=  new IloNumExpr[super_count][unit+1];
				
			}
			demand=new int[super_count][unit];
			gf=  new IloLinearNumExpr[super_count][unit];
			
			
			for(int t1=0;t1<super_count;t1++){	
				
				for(int tx=0;tx<unit;tx++){
					IloLinearNumExpr sy00=cplex.linearNumExpr();
							int u=0;
					int ts=tx*u_policy;
					
					while(u<u_policy){
					//m[t1].addTerm(1.0, y[t1][t]);
						int ind=ts+u++;
					demand[t1][tx]+= supers_days.get(ind)[t1].getDemand();
					sy00.addTerm(1.0, y[t1][ind] );
					
				}
					gf[t1][tx]=sy00;
				} 
				
				if(unitm>0){
					IloLinearNumExpr sy00=cplex.linearNumExpr();
					for(int ind2=unit*u_policy; ind2<days;ind2++ ){
						demand[t1][unit]+= supers_days.get(ind2)[t1].getDemand();
						sy00.addTerm(1.0, y[t1][ind2]);
					}
					gf[t1][unit]=sy00;
				}
				
			
			}
			
			 for(int i=0;i<super_count-1;i++){
					for(int j=i+1;j<super_count;j++){
						for(int ind=0;ind<unit;ind++ ){
					 IloNumExpr u= cplex.prod(1/(double)demand[i][ind],gf[i][ind] ); //(double) 
						//System.out.println(1.0/(double)demand[i] +" "+demand[i]);			 
						 IloNumExpr u1= cplex.prod(1/ (double)demand[j][ind],gf[j][ind]) ;
						 cplex.addLe(cplex.diff(u, u1), equity);
							cplex.addGe(cplex.diff(u, u1), -equity);
							
					}
					}
				 }
				
			 long start = System.currentTimeMillis();

			

			 
			cplex.addMaximize(obj);
			cplex.populate();
			long end = System.currentTimeMillis();
			long seconds = TimeUnit.NANOSECONDS.toSeconds(end - start);
			cplex.exportModel("file_name_upper.lp");
			
			double time=cplex.getCplexTime();
			int d=cplex.getSolnPoolNsolns() ;
			System.out.println("solutioin number is"+d+"solution time is"+time+"CPU time is"+seconds);
			cplex.getSolnPoolNsolns();
			
			
			
		
			
			if(cplex.solve()){
			//	System.out.println("obj= "+ cplex.getObjValue() );
				
				
				
				cplex.exportModel("file_name_upper.lp");
				solutions=new ArrayList<UpperSolutions>();
				for(int k=0;k<d;k++){  // k the index of the solutions number
			//System.out.println("obj= "+ cplex.getObjValue(k) );
			
			UpperSolutions ups=new UpperSolutions();
			ups.setValue(cplex.getObjValue(k));
				ups.setCapacity(b);
			ups.setCHcount(CH_count);
			ups.setEquity(equity);
			ups.setU(u_policy);
			ups.setRadius(rbase);
			ups.setUpperTime(time);
			
			
			ArrayList<ArrayList<Integer>> 	xvalue=new ArrayList<ArrayList<Integer>>();
			ArrayList<ArrayList<Integer>> 	yvalue=new ArrayList<ArrayList<Integer>>();
			ArrayList<ArrayList<Integer>> 	dvalue=new ArrayList<ArrayList<Integer>>();
			ArrayList<String> 	sindex=new ArrayList<String>();
			
			 for(int h=0;h<days;h++){
				 // the ind is S+ solution number+ capacity+ CH_count+ equity+day+u_policy
				 String ind="S-"+ String.format("%02d", k) +"-"+String.format("%02d", b) +  "-"+String.format("%02d", CH_count) +"-"+ equity+"-"+String.format("%02d", u_policy) +"-"+ rbase;
				 sindex.add(ind);
				 
				 ArrayList<Integer> cover=new ArrayList<Integer>();
				 ArrayList<Integer> CHs=new ArrayList<Integer>();
				 ArrayList<Integer> demands=new ArrayList<Integer>();
				 
				
				// System.out.println();
				// System.out.println("Day"+h);
				 
				 for(int l=0;l<super_count;l++){ 
					 int ch=(int) Math.round(cplex.getValue(x[l][h],k));
					 int covered= (int) Math.round(cplex.getValue(y[l][h],k)); 
				        int demandvalue= (int) Math.round( supers_days.get(h)[l].getDemand());
				       
			cover.add(covered);
			CHs.add(ch);
			demands.add(demandvalue);
			
					 
		         if(covered>ch*b){
		        	 System.out.print("abnormal!"+Math.round(cplex.getValue(x[l][h],k))+"original value"+cplex.getValue(x[l][h],k) );       
	         }
				}
				 
				 xvalue.add(CHs);
				 yvalue.add(cover);
				 dvalue.add(demands);
				 
				 
			}
			 
			ups.setX(xvalue);
			ups.setY(yvalue);
			ups.setD(dvalue);
			ups.setDaySolutionIndex(sindex);
			
			
			solutions.add(ups);
					}	
				
			//	System.out.println("the size of the solutions is: "+solutions.size());
				
				/*ResultstoExcel res= new ResultstoExcel();
				res.upper2excel("C://Users//nihao//Dropbox//Twitter Coverage//UpperResults//upper.xlsx",solutions);
			*/	}else{
				//System.out.println("no solutions found!");
				
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
