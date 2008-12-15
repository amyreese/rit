
import java.util.*;

public class Cell implements Timed {

	private int assem = 0;
	private int from = 0;
	private int to = 0;
	
	private String id;
	
	private UAVController controller;
	
	private Random generator = new Random();
	
	private int toAssemble;
	private int transferFromUAV;
	private int transferToUAV;
	
	private boolean assembling = false;
	private boolean delivering = false;
	private boolean pickingUp = false;
	
	private boolean hasP1 = false;
	private boolean hasP2 = false;
	private boolean hasProd = false;
	
	private boolean requestedP1 = false;
	private boolean requestedP2 = false;
	
	Cell(String id, int toAssemble, int transferFromUAV, int transferToUAV ){
		this.id = id;
		
		this.toAssemble = toAssemble;
		this.transferFromUAV = transferFromUAV ;
		this.transferToUAV = transferToUAV; 
	}
	
	public void setController( UAVController controller ){
		this.controller = controller;
	}
	
	private void assemble(){
		assembling = true;
		assem = toAssemble;
	}
	
	public String getId(){
		return id;
	}
	
	public boolean isProdReady(){
		return hasProd;
	}
	
	public void deliveringP1( UAV uav ){
		from = transferFromUAV;
		delivering = true;
		hasP1 = true;
		uav.deliveryFinishing(transferFromUAV);
	}
	
	public void deliveringP2( UAV uav ){
		from = transferFromUAV;
		delivering = true;
		hasP2 = true;
		uav.deliveryFinishing(transferFromUAV);
	}
	
	public void pickingUp(UAV uav){
		to = transferToUAV;
		pickingUp = true;
		uav.pickUpFinishing(transferToUAV);
		
	}
	
	public void pretick() throws TimeStop {
		
		//System.out.println(!hasProd +" "+ hasP1 +" "+ hasP2 +" "+ !assembling +" "+ !delivering);
		
		if(!hasProd && hasP1 && hasP2 && !assembling && !delivering){
			System.out.println("Cell "+ id +" beginning assembly.");
			assemble();
		}
		
		if(!hasP1 && !hasP2 && !requestedP1 && !requestedP2){
			
			int r = generator.nextInt(2);
			
			if( r == 0){
				controller.requestP1(id);
				requestedP1 = true;
				System.out.println("Cell "+ id +" requested part "+ id.charAt(0)+"." );
				
			}else{
				controller.requestP2(id);
				requestedP2 = true;
				System.out.println("Cell "+ id +" requested part "+ id.charAt(1)+ ".");
				
			}
			
		}
		
		else if(!hasP1 && !requestedP1){
			controller.requestP1(id);
			requestedP1 = true;
			System.out.println("Cell "+ id +" requested part "+ id.charAt(0)+"." );
		}
		else if( !hasP2 && !requestedP2){
			controller.requestP2(id);
			requestedP2 = true;
			System.out.println("Cell "+ id +" requested part "+ id.charAt(1)+ ".");
		}
		
		
		if( assem == 0 && assembling ){
			assembling = false;
			hasProd = true;
			hasP1 = false;
			requestedP1 = false;
			hasP2 = false;
			requestedP2 = false;
			
			System.out.println("Cell "+ id +" finished assembly.");
			controller.finishedSubAssembly(this);
			
		}
		
		if( pickingUp && to == 0){
			hasProd = false;
			pickingUp = false;
		}
		
		if( from == 0 && delivering ){
			delivering = false;
			
		}
		
		
		
	}

	public void tick() {
		// TODO Auto-generated method stub
		assem--;
		from--;
		to--;
	}

}
