package edu.msoe.sefocus.core;

/**
 * This class defines the various pieces of a robot. It contains all of the
 * necessary items as well as allows for devices to obtain various pieces of
 * information about the robot.
 * 
 * @author schilling
 * 
 */
public class Robot {
	private iNetworkController nc;
	private iRobotPropulsionController pc;
	private iNavigationController navc;
	private iDiagnosticsController dc;

	/**
	 * This method will instantiate a new instance of the robot.
	 */
	public Robot(iNetworkController nc) {
		this.nc = nc;
		pc = new WallSEMotorController(nc);
	}
	
	public void setNavController(iNavigationController navc)
	{
		this.navc=navc;
	}
	
	public void setDiagController(iDiagnosticsController dc)
	{
		this.dc = dc;
	}
	
	

	/**
	 * This method will cause the robot to start operating in a normal fashion.
	 * It will start all subthreads with appropriate delays in between to ensure
	 * reliable operation.
	 */
	public void initiateRobotOperation() {

	}

	public iNetworkController getNc() {
		return nc;
	}

	public iRobotPropulsionController getPc() {
		return pc;
	}

	public iNavigationController getNavController() {
		return navc;
	}

	public iDiagnosticsController getDiagnosticController() {
		return dc;
	}
	
	
	
	






}
