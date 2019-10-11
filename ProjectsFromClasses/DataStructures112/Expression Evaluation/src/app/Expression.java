package app;

import java.io.*;
import java.util.*;
import java.util.regex.*;

import structures.Stack;

public class Expression {

	public static String delims = " \t*+-/()[]";
			
    /**
     * Populates the vars list with simple variables, and arrays lists with arrays
     * in the expression. For every variable (simple or array), a SINGLE instance is created 
     * and stored, even if it appears more than once in the expression.
     * At this time, values for all variables and all array items are set to
     * zero - they will be loaded from a file in the loadVariableValues method.
     * 
     * @param expr The expression
     * @param vars The variables array list - already created by the caller
     * @param arrays The arrays array list - already created by the caller
     */
    public static void 
    makeVariableLists(String expr, ArrayList<Variable> vars, ArrayList<Array> arrays) {
    	/** COMPLETE THIS METHOD **/
    	/** DO NOT create new vars and arrays - they are already created before being sent in
    	 ** to this method - you just need to fill them in.
    	 **/
    	StringTokenizer st = new StringTokenizer(expr, delims);
    	String str;
    	int index = 0;
    	while(st.hasMoreTokens()) {
    		str = st.nextToken();
    		if(!str.equals("") && !(str.charAt(0) >= '0' && str.charAt(0) <= '9')) {
    			index = expr.indexOf(str, 0) + str.length();
    			if(index < expr.length() && expr.charAt(index) == '[' && !arrays.contains(new Array(str))) {
    				arrays.add(new Array(str));
    			}
    			else if(!vars.contains(new Variable(str)) && !arrays.contains(new Array(str))) {
    				vars.add(new Variable(str));
    			}
    		}
    	}
    }
    
    /**
     * Loads values for variables and arrays in the expression
     * 
     * @param sc Scanner for values input
     * @throws IOException If there is a problem with the input 
     * @param vars The variables array list, previously populated by makeVariableLists
     * @param arrays The arrays array list - previously populated by makeVariableLists
     */
    public static void 
    loadVariableValues(Scanner sc, ArrayList<Variable> vars, ArrayList<Array> arrays) 
    throws IOException {
        while (sc.hasNextLine()) {
            StringTokenizer st = new StringTokenizer(sc.nextLine().trim());
            int numTokens = st.countTokens();
            String tok = st.nextToken();
            Variable var = new Variable(tok);
            Array arr = new Array(tok);
            int vari = vars.indexOf(var);
            int arri = arrays.indexOf(arr);
            if (vari == -1 && arri == -1) {
            	continue;
            }
            int num = Integer.parseInt(st.nextToken());
            if (numTokens == 2) { // scalar symbol
                vars.get(vari).value = num;
            } else { // array symbol
            	arr = arrays.get(arri);
            	arr.values = new int[num];
                // following are (index,val) pairs
                while (st.hasMoreTokens()) {
                    tok = st.nextToken();
                    StringTokenizer stt = new StringTokenizer(tok," (,)");
                    int index = Integer.parseInt(stt.nextToken());
                    int val = Integer.parseInt(stt.nextToken());
                    arr.values[index] = val;              
                }
            }
        }
    }
    
    /**
     * Evaluates the expression.
     * 
     * @param vars The variables array list, with values for all variables in the expression
     * @param arrays The arrays array list, with values for all array items
     * @return Result of evaluation
     */
    public static float 
    evaluate(String expr, ArrayList<Variable> vars, ArrayList<Array> arrays) {
    	/** COMPLETE THIS METHOD **/
    	// following line just a placeholder for compilation
    	expr.trim();
    	for (Variable var : vars) {
    		expr = expr.replaceAll(var.name, Integer.toString(var.value));
        }
    	while(expr.contains("[")) {
    		int start = 0, end = 0;
    		for(int i = 0; i < expr.length(); i++) {
    			if(expr.charAt(i) == '[') start = i;
    		}
    		for(int j = 0; j < expr.length(); j++) {
    			if(expr.charAt(j) == ']' ) {
    				end = j;
    				if(start < end) break;
    			}
    		}
    		String temp = expr.substring(start+1, end);
    		int value = (int) eval(temp); 
    		expr = expr.substring(0, start) + "%" + expr.substring(end + 1);
            for (Array array : arrays) {
                if (expr.contains(array.name + "%")) {
                    expr = expr.replaceAll(array.name + "%", Integer.toString(array.values[value]));
                }
            }
    	}
    	return eval(expr);
    }
    
    private static float eval(String expr) {
    	StringTokenizer st = new StringTokenizer(expr, delims, true);
    	String current;
    	Stack<Float> vals = new Stack<Float>();
    	Stack<String> ops = new Stack<String>();
    	while(st.hasMoreTokens()) {
    		current = st.nextToken();
    		if(isANumber(current)) vals.push(Float.parseFloat(current));
    		else if(current.equals("(")) ops.push(current);
    		else if(current.equals(")")) {
    			while(!ops.peek().equals("(")) {
    				vals.push(operate(ops.pop(), vals.pop(), vals.pop()));
    			}
    			if(!ops.isEmpty()) ops.pop();
    		}
    		else if(current.equals("+") || current.equals("-") || current.equals("*") || current.equals("/")) {
    			while(!ops.isEmpty() && prec(ops.peek()) >= prec(current)) {
    				vals.push(operate(ops.pop(), vals.pop(), vals.pop()));
    			}
    			ops.push(current);
    		}	
    	}
    	while(!ops.isEmpty() && vals.size() > 1 && (ops.peek()  != "(" || ops.peek() == ")" )) {
    		vals.push(operate(ops.pop(), vals.pop(), vals.pop()));
    	}
    	return vals.pop();
    }
    public static int prec(String s) {
    	if (s.equals("*") || s.equals("/")) return 2;
        else if (s.equals("+") || s.equals("-")) return 1;
        return 0;
    }
    public static float operate(String op, float y, float x) {
    	if(op.equals("+")) return x+y;
    	else if(op.equals("-")) return x-y;
    	else if(op.equals("*")) return x*y;
    	else if(op.equals("/")) {
    		if(y == 0) throw new UnsupportedOperationException("Cannot divide by zero");
    		return x/y;
    	}
    	return 0;
    }
    public static boolean isANumber(String s) {
    	try {
    		int num = Integer.parseInt(s);
    	}
    	catch(NumberFormatException nfe){
    		return false;
    	}
    	return true;
    }
}