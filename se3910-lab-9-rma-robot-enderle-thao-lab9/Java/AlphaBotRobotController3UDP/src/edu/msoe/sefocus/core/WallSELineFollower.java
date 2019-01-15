package edu.msoe.sefocus.core;

import java.io.IOException;

public class WallSELineFollower implements iNavigationController, iDiagnosticsController {
		private iNetworkController network;

		private static int START_WHITE_CALIBRATION = 0x00000001;
		private static int START_BLACK_CALIBRATION = 0x00000002;
		private static int START_LINE_FOLLOWING = 0x00000004;
		private static int STOP_LINE_FOLLOWING = 0x00000008;
		
		private static int DISPLAY_THREAD_DIAGNOSTICS = 0x00000001;
		private static int PRINT_BATTERY_VOLTAGE_MSG =  0x00000010;
		private static int RESET_THREAD_DIAGNOSTICS = 0x08000000;
		
		

		public WallSELineFollower(iNetworkController nw) {
			network = nw;
		}
	
	@Override
	public void startCalibrationWhite() {
		try {
			network.sendMessage(iNavigationController.NAVIGATION_CONTROL, START_WHITE_CALIBRATION);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void startCalibrationBlack() {
		try {
			network.sendMessage(iNavigationController.NAVIGATION_CONTROL, START_BLACK_CALIBRATION);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void startLineFollowing() {
		try {
			network.sendMessage(iNavigationController.NAVIGATION_CONTROL, START_LINE_FOLLOWING);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void stopLineFollowing() {
		try {
			network.sendMessage(iNavigationController.NAVIGATION_CONTROL, STOP_LINE_FOLLOWING);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void displayDiagnostics() {
		try {
			network.sendMessage(iDiagnosticsController.DIAGNOSTICS_CONTROL, DISPLAY_THREAD_DIAGNOSTICS);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

	@Override
	public void resetDiagnostics() {
		try {
			network.sendMessage(iDiagnosticsController.DIAGNOSTICS_CONTROL, RESET_THREAD_DIAGNOSTICS);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

	@Override
	public void printBatteryVoltage() {
		try {
			network.sendMessage(iDiagnosticsController.DIAGNOSTICS_CONTROL, PRINT_BATTERY_VOLTAGE_MSG);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	}

}
