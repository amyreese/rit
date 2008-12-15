
import java.util.*;

public class UAVController implements Timed{

	private UAV[] UAVs;
	
	private boolean s1Ready = false;
	private boolean s2Ready = false;
	
	private Cell ab;
	private Cell yz;
	
	private List<String> requests = new LinkedList<String>();
	
	UAVController(){
	}
	
	public void setUAVs(UAV[] UAVs){
		this.UAVs = UAVs;
	}
	
	public void requestP1( String cell ){
		if(cell.equals("Final")){
			requests.add("S1");
		}
		else{ requests.add(cell.substring(0, 1)); }
	}
	
	public void requestP2( String cell ){
		if(cell.equals("Final")){
			requests.add("S2");
		}
		else {requests.add(cell.substring(1));}
	}
	
	public void finishedSubAssembly( Cell fromCell ){
		if( fromCell.getId().equals("AB") ){
			s1Ready = true;
			ab = fromCell;
		}else{
			s2Ready = true;
			yz = fromCell;
		}
	}
	
	public void finishedFinalAssembly(){
		requests.add("FINAL");
	}
	
	public boolean isS1Ready(){
		return s1Ready;
	}
	
	public boolean isS2Ready(){
		return s2Ready;
	}
	
	public void setIsS1Ready(){
		s1Ready = ab.isProdReady();
	}
	public void setIsS2Ready(){
		s2Ready = yz.isProdReady();
	}
	

	public void pretick() throws TimeStop {
		
		//System.out.println(requests.size());
		
		if(requests.size() > 0 ){
			
			for( int i=0; i < UAVs.length; i++){
				
				if( UAVs[i].isFree() ){
					
					String command = requests.remove(0);
					
					if(command.equals("A") || command.equals("B") || command.equals("Y") || command.equals("Z")){
						UAVs[i].getPartFromStoreRoom(command);
					}
					else if( command.equals("S1")){
						UAVs[i].getS1FromABCell();
					}
					else if( command.equals("S2")){
						UAVs[i].getS2FromYZCell();
					}
					else if( command.equals("FINAL")){
						UAVs[i].getFinalFromFinalCell();
					}
				
					i = UAVs.length + 1;
				}
				
			}
		}
		
	}

	public void tick() {
		// TODO Auto-generated method stub
		
	}
	
}
