
public class FinalCell implements Timed{
	
	private String id = "Final";
	
	private int assem = 0;
	private int from = 0;
	private int to = 0;
	
	private int toAssemble;
	private int transferFromUAV;
	private int transferToUAV;
	
	private UAVController controller;
	
	private boolean hasS1 = false;
	private boolean hasS2 = false;
	private boolean requestedS1 = false;
	private boolean requestedS2 = false;
	private boolean hasFinal = false;
	private boolean assembling = false;
	private boolean deliveringS1 = false;
	private boolean deliveringS2 = false;
	private boolean pickingUp = false;
	
	FinalCell(int toAssemble, int transferFromUAV, int transferToUAV) {
		this.toAssemble = toAssemble;
		this.transferFromUAV = transferFromUAV;
		this.transferToUAV = transferToUAV; 
	}

	public void setController( UAVController controller ){
		this.controller = controller;
	}
	
	public void deliveringS1( UAV uav ){
		from = transferFromUAV;
		deliveringS1 = true;
		hasS1 = false;
		uav.deliveryFinishing(transferFromUAV);
	}
	
	public void deliveringS2( UAV uav ){
		from = transferFromUAV;
		deliveringS2 = true;
		hasS2 = false;
		uav.deliveryFinishing(transferFromUAV);
	}
	
	public void pickingUp(UAV uav){
		to = transferToUAV;
		pickingUp = true;
		uav.pickUpFinishing(transferToUAV);
		
	}
	
	private void assemble(){
		assembling = true;
		assem = toAssemble;
	}
	
	public void pretick() throws TimeStop {
		
		//System.out.println(!hasFinal +" "+ hasS1 +" "+ hasS2 +" "+ !assembling );
		
		if( !hasS1 && controller.isS1Ready() && !requestedS1){
			controller.requestP1(id);
			requestedS1 = true;
			System.out.println("Final Cell requested part S1.");
		}
		else if( !hasS2 && controller.isS2Ready() && !requestedS2 ){
			controller.requestP2(id);
			requestedS2 = true;
			System.out.println("Final Cell requested part S2.");
		}
		else if( !hasFinal && hasS1 && hasS2 && !assembling){
			System.out.println("Final Cell is beginning assembly.");
			assemble();
		}
		
		if( assem == 0 && assembling ){
			assembling = false;
			hasFinal = true;
			hasS1 = false;
			controller.setIsS1Ready();
			requestedS1 = false;
			hasS2 = false;
			controller.setIsS2Ready();
			requestedS2 = false;
			
			System.out.println("Final Cell is finished assembly.");
			controller.finishedFinalAssembly();
		}
		if( pickingUp && to == 0){
			hasFinal = false;
			pickingUp = false;
		}
		if( from == 0 && deliveringS2 ){
			deliveringS2 = false;
			hasS2 = true;
			
		}
		if( from == 0 && deliveringS1 ){
			deliveringS1 = false;
			hasS1 = true;
		}
		
	}

	public void tick() {
		
		assem--;
		from--;
		to--;
	}
	
}
