package edu.msoe.sefocus.core;

public interface iDiagnosticsController {
	public static final int DIAGNOSTICS_CONTROL =  0x00000003;
	
	public void displayDiagnostics();
	public void resetDiagnostics();
	public void printBatteryVoltage();
}
