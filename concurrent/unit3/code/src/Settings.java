
public class Settings {
	
	// How long between Ticks
	public static final int TickLength = 1000;
	
	// How many UAVs are available
	public static final int UAVCount = 2;
	
	// How many ticks to pick up or drop off parts
	public static final int StoreRoomPickUpTick = 1;
	public static final int StoreRoomDropOffTick = 2;
	
	// How many ticks to interact with AB Cell
	public static final int ABCellAssembleTick = 2;
	public static final int ABCellDropOffTick = 1;
	public static final int ABCellPickUpTick = 2;
	
	// How many ticks to interact with YZ Cell
	public static final int YZCellAssembleTick = 3;
	public static final int YZCellDropOffTick = 1;
	public static final int YZCellPickUpTick = 2;
	
	// How many ticks to interact with Final Cell
	public static final int FinalCellAssembleTick = 2;
	public static final int FinalCellDropOffTick = 2;
	public static final int FinalCellPickUpTick = 2;
	
	// How many ticks for various UAV interactions
	public static final int UAVBatteryTick = 10;
	public static final int UAVStoreRoomToCellTick = 2;
	public static final int UAVCellToCellTick = 1;
	public static final int UAVCellToFinalTick = 1;
	public static final int UAVFinalToStoreRoomTick = 3;
}
