package edu.msoe.sefocus.core;

public interface iNavigationController {
	/**
	 * The following constants will define destinations for messages within the robot control system.
	 * 
	 */
	public static final int NAVIGATION_CONTROL =  0x00000002;

	public void startCalibrationWhite();
public void startCalibrationBlack();
public void startLineFollowing();
public void stopLineFollowing();

}
