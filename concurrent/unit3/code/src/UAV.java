
public class UAV implements Timed{

	private boolean free = true;
	private boolean freeing = false;
	private boolean moving = false;
	private boolean waiting = false;
	private boolean pickingUp = false;
	private boolean charging = false;
	private boolean returnToIdle = false;
	
	private StoreRoom storeroom;
	
	private int travel = 0;
	private int wait = 0;
	private int charge = 0;
	
	private String location = "storeroom";
	private String action;
	
	private String part;
	
	private int id;
	
	private int storeRoomToSubCell;
	private int subCellToSubCell;
	private int subCellToFinalCell;
	private int finalCellToStoreRoom;
	private int battery;
	private int batteryMax;
	
	private Cell abCell;
	private Cell yzCell;
	private FinalCell finalCell;
	
	UAV(int charge, int SR2Cell, int cell2Cell, int cell2Final, int final2SR, 
			StoreRoom storeroom, Cell abCell, Cell yzCell, FinalCell finalCell ){
		
		battery = charge;
		batteryMax = charge;
		storeRoomToSubCell = SR2Cell;
		subCellToSubCell = cell2Cell;
		subCellToFinalCell = cell2Final;
		finalCellToStoreRoom = final2SR;
		
		this.storeroom = storeroom;
		this.abCell = abCell;
		this.yzCell = yzCell;
		this.finalCell = finalCell;
	}
	
	public boolean isFree(){
		return free;
	}
	
	public void setFree(){
		System.out.println("UAV "+ id +" is now free.");
		freeing = true;
		wait = 1;
	}
	
	public void setId( int id ){
		this.id = id;
	}
	
	public int getId(){
		return id;
	}
	
	public String getPart(){
		return part;
	}
	
	public String getAction(){
		return action;
	}
	
	public void getPartFromStoreRoom(String part){
		
		free = false;
		action = "pickup";
		this.part = part;
		
		if(!location.equals("storeroom")){
			System.out.println("UAV "+ id +" is travelling from the "+ location+" to the storeroom.");
		}
		
		if( location.equals("storeroom")){
			travel = 1;
			moving = true;
		}
		else if( location.equals("ABCell") || location.equals("YZCell")){
			travel = storeRoomToSubCell;
			moving = true;
		}
		else if( location.equals("FinalCell") ){
			travel = finalCellToStoreRoom;
			moving = true;
		}
		else {
			System.err.println("Invalid UAV location.");
		}
		
		location = "storeroom";
	}
	
	public void getS1FromABCell(){
		
		free = false;
		action = "retrieve";
		this.part = "S1";
		
		if(!location.equals("ABCell")){
			System.out.println("UAV "+ id +" is travelling from the "+ location+" to the ABCell.");
		}
		
		if( location.equals("storeroom")){
			travel = storeRoomToSubCell;
			moving = true;
		}
		else if( location.equals("ABCell") ){
			travel = 1;
			moving = true;
		}
		else if( location.equals("YZCell") ){
			travel = subCellToSubCell;
			moving = true;
		}
		else if( location.equals("FinalCell") ){
			travel = subCellToFinalCell;
			moving = true;
		}
		else {
			System.err.println("Invalid UAV location.");
		}
		
		location = "ABCell";
	}
	
	public void getS2FromYZCell(){
		
		free = false;
		action = "retrieve";
		this.part = "S2";
		
		if(!location.equals("YZCell")){
			System.out.println("UAV "+ id +" is travelling from the "+ location+" to the YZCell.");
		}
		
		if( location.equals("storeroom")){
			travel = storeRoomToSubCell;
			moving = true;
		}
		else if( location.equals("YZCell") ){
			travel = 1;
			moving = true;
		}
		else if( location.equals("ABCell") ){
			travel = subCellToSubCell;
			moving = true;
		}
		else if( location.equals("FinalCell") ){
			travel = subCellToFinalCell;
			moving = true;
		}
		else {
			System.err.println("Invalid UAV location.");
		}
		
		location = "YZCell";
	}
	
	public void getFinalFromFinalCell(){
		free = false;
		action = "retrieve";
		moving = true;
		this.part = "FINAL";
		
		if(!location.equals("FinalCell")){
			System.out.println("UAV "+ id +" is travelling from the "+ location+" to the Final Cell.");
		}
		
		if( location.equals("storeroom")){
			travel = finalCellToStoreRoom;
		}
		else if( location.equals("YZCell") ){
			travel = subCellToFinalCell;
		}
		else if( location.equals("ABCell") ){
			travel = subCellToSubCell;
		}
		else if( location.equals("FinalCell") ){
			travel = 1;
		}
		
		location = "FinalCell";
	}
	
	public void deliverToCell(){
		travel = storeRoomToSubCell;
		moving = true;
		action = "delivering";
		
		if( part.equals("A") || part.equals("B")){
			location = "ABCell";
		}else{
			location = "YZCell";
		}
	}
	
	public void deliveryFinishing(int wait){
		this.wait = wait;
		moving = false;
		waiting = true;
	}
	
	public void pickUpFinishing(int wait){
		pickingUp = true;
		moving = false;
		this.wait = wait;
	}
	
	public void pretick() throws TimeStop {
		
		
		if(waiting && wait == 0){
			waiting = false;
			returnToIdle = true;
			System.out.println("Part "+ part +" delivery complete.");
			
			setFree();
			
		}
		else if( freeing && wait == 0){
			freeing = false;
			if(!charging){
				free = true;
			}else{
				returnToIdle = true;
			}
		}
		else if( pickingUp && wait == 0){
			pickingUp = false;
			moving = true;
			if(part.equals("S1") || part.equals("S2")){
				System.out.println("UAV "+ id +" has part "+part+".");
				travel = subCellToFinalCell;
				action = "delivering";
				location = "FinalCell";
			}
			else if( part.equals("FINAL")){
				System.out.println("UAV "+ id +" has FINAL product.");
				travel = finalCellToStoreRoom;
				action = "delivering";
				location = "storeroom";
			}
		}
		else if( moving && travel == 0 ){
			
			moving = false;
			
			if( location.equals("storeroom")){
				
				storeroom.enter(this);
			}
			else if( location.equals("ABCell") ){
				
				if( action.equals("delivering")){
				
					System.out.println("UAV "+ id +" is delivering part "+ part +" to ABCell.");
					
					if( part.equals("A") ){
						abCell.deliveringP1(this);
					}else{
						abCell.deliveringP2(this);
					}
				}
				else if( action.equals("retrieve") ){
					
					System.out.println("UAV "+ id +" is picking up part S1.");
					abCell.pickingUp(this);
					
				}
				
			}
			else if( location.equals("YZCell") ){
				
				if( action.equals("delivering")){
				
					System.out.println("UAV "+ id +" is delivering part "+ part +" to YZCell.");
					
					if( part.equals("Y") ){
						yzCell.deliveringP1(this);
					}else{
						yzCell.deliveringP2(this);
					}
				
				}
				else if( action.equals("retrieve") ){
					
					System.out.println("UAV "+ id +" is picking up part S2.");
					yzCell.pickingUp(this);
				}
				
			}
			else if( location.equals("FinalCell") ){
				
				if( action.equals("delivering")){
					
					System.out.println("UAV "+ id +" is delivering part "+ part +" to Final Cell.");
					
					if( part.equals("S1") ){
						finalCell.deliveringS1(this);
					}else{
						finalCell.deliveringS2(this);
					}
				
				}
				else if( action.equals("retrieve")){
					System.out.println("UAV "+ id +" is picking up FINAL product.");
					finalCell.pickingUp(this);
				}
			}
		}
		
		if( battery == 0 && !charging){
			returnToIdle = free;
			free = false;
			charging = true;
			charge = 2;
			System.out.println("UAV "+ id +" shut-down and started charging.");
			
			
		}
		
		else if( free && battery == 2 && !charging){
			free = false;
			returnToIdle = true;
			charging = true;
			charge = 2;
			System.out.println("UAV "+ id +" started charging.");
		
		}
		
		else if( charging && charge == 0){
			free = returnToIdle;
			charging = false;
			battery = batteryMax;
			System.out.println("UAV "+ id +" is fully charged.");
		}
		
	}

	public void tick() {
		
		if(!charging){
			travel--;
			if(travel > 0){
				System.out.println("UAV "+ id +" is moving to "+location+".");
			}
			battery--;
		}
		charge--;
		wait--;
		
	}

}
