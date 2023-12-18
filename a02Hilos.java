package basicos;

public class a02Hilos extends Thread {
    private int id;
    
    public a02Hilos(int id){
        this.id= id;
    }
    
    public void run(){
        //tarea(s) que realiza el hilo lanzado
        System.out.println("Tarea del hilo: " + id);
        //System.out.println( Thread.currentThread() );
    }
        
    
    public static void main(String[] args){
        //instanciar objetos de a02Hilos que heredan de Thread
        a02Hilos h1 = new a02Hilos(1);
        a02Hilos h2 = new a02Hilos(2);
        a02Hilos h3 = new a02Hilos(3);
        
        //lanzar hilos
        //No existe un orden de ejecución, 
        //depende de la planificación de la CPU
        h1.start();
        h2.start();
        h3.start();
        
        try{
            h1.join();
            h2.join();
            h3.join();
        }catch(Exception e){}
        
        
        System.out.println("Hilo principal (main)");
        
    }
}

