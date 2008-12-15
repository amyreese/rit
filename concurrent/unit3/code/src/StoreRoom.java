
import java.util.*;

public class StoreRoom implements Timed{

	private int t = 0;
	
	private List<UAV> waitingToEnter = new LinkedList<UAV>();
	
	private UAV curUAVinStoreroom;
	
	private boolean pickingUp = false;
	private boolean droppingOff = false;
	private boolean UAVinStoreRoom = false;
	
	private int pickUp;
	private int dropOff;
	
	StoreRoom( int pickUp, int dropOff ){
		this.pickUp = pickUp;
		this.dropOff = dropOff;
	}
	
	public void enter( UAV uav){
		waitingToEnter.add(uav);
	}
	
	private void pickUp(){
		t = pickUp;
		pickingUp = true;
		
	}
	
	private void dropOff(){
		t = dropOff;
		droppingOff = true;
		
	}
	
	public void pretick() throws TimeStop {
		
		if( waitingToEnter.size() > 0 && !UAVinStoreRoom){
	
			curUAVinStoreroom = waitingToEnter.remove(0);
			UAVinStoreRoom = true;
			
			if( curUAVinStoreroom.getAction().equals("pickup") ){
				pickUp();
				System.out.println("UAV "+ curUAVinStoreroom.getId() +" is in the storeroom transfering part "+ curUAVinStoreroom.getPart()+".");
				
			}else if( curUAVinStoreroom.getAction().equals("dropoff") ){
				dropOff();
				System.out.println("UAV "+ curUAVinStoreroom.getId() +" is in the storeroom transfering product.");
			}
			else if( curUAVinStoreroom.getAction().equals("delivering") ){
				dropOff();
				System.out.println("UAV "+ curUAVinStoreroom.getId() +" is in the storeroom transfering product.");
			}
			
		}
		
		if( t == 0 && pickingUp ){
			
			curUAVinStoreroom.deliverToCell();
			pickingUp = false;
			UAVinStoreRoom = false;
			System.out.println("UAV "+ curUAVinStoreroom.getId() + " has part "+ curUAVinStoreroom.getPart()+".");
		}
		
		if( t == 0 && droppingOff ){
			
			curUAVinStoreroom.setFree();
			droppingOff = false;
			UAVinStoreRoom = false;
			System.out.println("UAV "+ curUAVinStoreroom.getId() + " delivered product to storeroom.");
		}
		
	}

	public void tick() {
		t--;
	}

}
