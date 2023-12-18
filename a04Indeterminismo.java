package basicos;

public class a04Indeterminismo extends Thread {
    /*Cont (static) será compartido para todos los hilos*/
    private static int cont = 0;
    
    public void run(){
        //tarea(s) que realiza el hilo lanzado
        for (int i=0; i< 10000; i++){ 
            cont++; 
        }
    }
    
    public static void main(String[] args){
        a04Indeterminismo[] hVector = new a04Indeterminismo[5];
        
        for (int i=0; i<= hVector.length - 1; i++){
            //instanciar objetos de a04Indeterminismo que heredan de Thread
            hVector[i] = new a04Indeterminismo();
            hVector[i].start();
        }
        
        try{
            //hilo principal esperará hasta que termine de ejecutarse el hilo[i]
            for (int i=0; i<= hVector.length - 1; i++){
                hVector[i].join();
            }
            
        }catch(Exception e){}
        
        System.out.println("Contador: " + cont);
        
    }
}

