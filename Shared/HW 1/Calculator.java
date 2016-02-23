import java.io.*;

class Calculator {
    private static Reader r = new InputStreamReader(System.in);
    private static BufferedReader br = new BufferedReader(r);
    
    public static void main(String[] args) {
        float amt = 0.0F;  // the current value of the calculator
        char op;           // the operation to be performed
        float val;         // the value of the operation
        
        System.out.println("CS 2271 Calculator");
        while (true) {
            // Read an input line. The first char of each line is the operation.
            // Arithmetic operations are followed by whitespace and a number.
            try {
                int ic = br.read();
                if (ic < 0) break;   //EOF
                op = (char) ic;
                if (op == 'Q') break;
                
                String s = br.readLine();
                if (takesNoArgs(op))
                    val = 0.0F;
                else
                    val = Float.parseFloat(s);
            }
            catch (IOException e) {  // abort on any IO exception
                throw new RuntimeException("Something bad happened");
            }
            
            // Call a fn to process the op and its val.
            amt = processOp(amt, op, val);
        }
        System.out.println("Thank you and goodbye!");
    }
    
    static boolean takesNoArgs(char op) {
        return (op == 'C') || (op == '=');
    }
    
    static float processOp(float amt, char op, float val) {
        if (op == '+')
            return processPlus(amt, val);
        else if (op == '-')
            return processMinus(amt, val);
        else if (op == '*')
            return processTimes(amt, val);
        else if (op == '/')
            return processDivide(amt, val);
        else if (op == '=')
            return processPrint(amt);
        else if (op == 'C')
            return processClear();
        else {
            System.out.println("Bad Operator");
            return amt;
        }
    }
    
    static float processPlus(float amt, float val) {
        return amt + val;
    }
    
    static float processMinus(float amt, float val) {
        return amt - val;
    }
    
    static float processTimes(float amt, float val) {
        return amt * val;
    }
    
    static float processDivide(float amt, float val) {
        return amt / val;
    }
    
    static float processPrint(float amt) {
        System.out.println(amt);
        return amt;
    }
    
    static float processClear() {
        return 0;
    }
}
