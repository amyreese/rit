
public class Factory {
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		UAV[] UAVs = new UAV[Settings.UAVCount];
		
		TimeManager clock = new TimeManager(Settings.TickLength);
		
		StoreRoom storeRoom = new StoreRoom(Settings.StoreRoomPickUpTick, Settings.StoreRoomDropOffTick);
		
		UAVController controller = new UAVController();
		
		
		Cell abCell = new Cell("AB", Settings.ABCellAssembleTick, 
				Settings.ABCellDropOffTick, Settings.ABCellPickUpTick);
		Cell yzCell = new Cell("YZ", Settings.YZCellAssembleTick,
				Settings.YZCellDropOffTick, Settings.YZCellPickUpTick);
		FinalCell finalCell = new FinalCell(Settings.FinalCellAssembleTick, 
				Settings.FinalCellDropOffTick, Settings.ABCellPickUpTick);
		
		for(int i=0; i<Settings.UAVCount; i++){
			UAVs[i] = new UAV(Settings.UAVBatteryTick, Settings.UAVStoreRoomToCellTick, 
					Settings.UAVCellToCellTick, Settings.UAVCellToFinalTick, 
					Settings.UAVFinalToStoreRoomTick, storeRoom, abCell, yzCell, finalCell);
			UAVs[i].setId(i);
			clock.addTimed(UAVs[i]);
		}
		
		controller.setUAVs(UAVs);
		
		abCell.setController(controller);
		yzCell.setController(controller);
		finalCell.setController(controller);
		
		clock.addTimed(abCell);
		clock.addTimed(yzCell);
		clock.addTimed(finalCell);
		
		clock.addTimed(storeRoom);
		
		clock.addTimed(controller);
		
		clock.start();
		
	}

	
}
