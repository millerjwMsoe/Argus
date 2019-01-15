package edu.msoe.sefocus.pcgui;

import java.awt.BorderLayout;
/**
 * This file is not copyrighted.  Others are free to copy, modify, or redistribute this file as is seen fit.
 * 
 * @author hornick
 * $Header: d:\cvs/webpage/msoe/se1020/GUI.java,v 1.1 2007/12/13 22:31:00 schilling Exp $
 * $Name:  $ 
 * $Revision: 1.1 $ 
 * $Date: 2007/12/13 22:31:00 $ 
 * $Log: GUI.java,v $
 * Revision 1.1  2007/12/13 22:31:00  schilling
 * Added archived to MSOE CVS repository.
 *
 * Revision 1.1  2007/11/30 23:01:57  wws
 * Updated SE1020 material on the website, as well as uploaded notes for SE-4831.
 *
 *
 *
 **/
import java.awt.Color;
import java.awt.Container;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.IOException;

import javax.swing.JFrame;

import edu.msoe.sefocus.core.CameraController;
import edu.msoe.sefocus.core.Robot;
import edu.msoe.sefocus.core.iNetworkController;


public class GUI {
	private Container contentPane;
	private JFrame jfMainWindow; // main window
	private JFrame imageDisplay; // image Display Frame.
	private OdometerDisplayPanel odometerDisplay;
	private RobotMotionControlPanel motionControlUI;
	private ConnectionGUIPanel connectionPanel;
	private CalibratePanel calibPanel;
	private ControlledCameraPanel ccp;
	private iNetworkController nwc;
	
	private final int NETWORK_PORT = 5000;

	public void setupImageDisplayFrame() throws IOException
	{
		CameraController cc = new CameraController(nwc);
		ccp = new ControlledCameraPanel(cc, NETWORK_PORT, 320, 180);
		
		imageDisplay = new JFrame("WALL-SE Camera Control");
		imageDisplay.setLayout(new BorderLayout());
		imageDisplay.add(ccp, BorderLayout.CENTER);
		
		imageDisplay.setSize(475, 315); // window size
		imageDisplay.setLocation(10, 10); // window location
		imageDisplay.setResizable(true); // not resizeable
		imageDisplay.setVisible(true);;
		
		Container frameContainer = imageDisplay.getContentPane();
		
		frameContainer.setLayout(new BorderLayout());
		frameContainer.add(ccp);
		
		frameContainer.validate();
		frameContainer.setVisible(true);
		frameContainer.repaint();
		
		imageDisplay.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

	}
	
	/**
	 * constructor for the GUI class creates the JFrame window and subcomponents
	 * @throws IOException 
	 */
	public GUI(Robot robot, iNetworkController nwc) throws IOException {
		this.nwc = nwc;
		
		// create a JFrame window and set its properties
		jfMainWindow = new JFrame("MSOE WALL-SE");
		jfMainWindow.setSize(500, 315); // window size
		jfMainWindow.setLocation(10, 10); // window location
		jfMainWindow.setResizable(true); // not resizeable
		/* !!!! */jfMainWindow.setVisible(true); // make visible!!!

		// EXIT_ON_CLOSE destroys all windows
		jfMainWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// get the container that is part of the JFrame
		contentPane = jfMainWindow.getContentPane();

		// we're using absolute positioning
		contentPane.setLayout(null);

		// override default background color
		contentPane.setBackground(Color.GRAY);

		motionControlUI = new RobotMotionControlPanel(robot.getPc(), jfMainWindow);
		motionControlUI.setBounds(5, 110, 300, 100);

		odometerDisplay = new OdometerDisplayPanel(null);
		odometerDisplay.setBounds(5, 5, 384, 100);

		connectionPanel = new ConnectionGUIPanel(nwc, jfMainWindow);
		connectionPanel.setBounds(5, 220, 250, 50);
		
		calibPanel = new CalibratePanel(robot.getNavController(), robot.getDiagnosticController());
		calibPanel.setBounds(310, 110, 150,150);


        
		contentPane.add(this.odometerDisplay);
		contentPane.add(motionControlUI);
		contentPane.add(connectionPanel);
		contentPane.add(calibPanel);
		
		// always call validate() after adding components
		// if the window is already visible
		contentPane.validate();
		// ...and this too; forces a refresh
		contentPane.repaint();
		contentPane.setFocusable(true);
		this.setDashColor(Color.CYAN);
		
		setupImageDisplayFrame();
		
		Thread t = new Thread(ccp);
		t.start();
		try {
			t.join();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/**
	 * This method will set the background color of all components on the display as is appropriate.
	 * @param c This is the color to be set.
	 */
	private void setDashColor(Color c) {
		this.contentPane.setBackground(c);
		this.jfMainWindow.setBackground(c);
	}

}
