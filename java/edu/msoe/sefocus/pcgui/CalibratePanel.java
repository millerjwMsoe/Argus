package edu.msoe.sefocus.pcgui;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JPanel;

import edu.msoe.sefocus.core.iDiagnosticsController;
import edu.msoe.sefocus.core.iNavigationController;

/**
 * This class defines the controls which will adjust how the robot moves.
 * 
 * @author schilling
 *
 */
public class CalibratePanel extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private iNavigationController motorController;
	private iDiagnosticsController diagController;
	private final int FORWARD = 1;
	private final int BACKWARD = 2;
	private final int RIGHT = 3;
	private final int LEFT = 4;
	private final int STOP = 0;
	private int robotMotion = STOP;

	/**
	 * This constructor will instantiate a new instance of the robot motion
	 * controller, which will control the operation of the robot.
	 * 
	 * @param pmctrl
	 *            This is the instance of the robot propulsion motor controller that
	 *            is to be controlled by this panel.
	 */
	public CalibratePanel(iNavigationController navctrl, final iDiagnosticsController diagController) {
		motorController = navctrl;
		this.diagController =  diagController;

		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BorderLayout());

		this.setLayout(new GridLayout(7,1));

		JButton whiteCal = new JButton("Cal White");
		JButton blackCal = new JButton("Cal Black");
		JButton startLineFollow = new JButton("Start Follow");
		JButton stopLineFollow = new JButton("Stop Follow");
		JButton printDiagnostics = new JButton("Print Diagnostics");
		JButton resetDiagnostics = new JButton("Reset Diagnostics");
		JButton printBatteryVoltage = new JButton("Print Battery Voltage");
		

		whiteCal.setAlignmentX(Component.CENTER_ALIGNMENT);
		blackCal.setAlignmentX(Component.CENTER_ALIGNMENT);
		startLineFollow.setAlignmentX(Component.CENTER_ALIGNMENT);
		stopLineFollow.setAlignmentX(Component.CENTER_ALIGNMENT);
		printDiagnostics.setAlignmentX(Component.CENTER_ALIGNMENT);
		resetDiagnostics.setAlignmentX(Component.CENTER_ALIGNMENT);
		printBatteryVoltage.setAlignmentX(Component.CENTER_ALIGNMENT);
		
		

		this.add(whiteCal);
		this.add(blackCal);
		this.add(startLineFollow);
		this.add(stopLineFollow);
		this.add(printDiagnostics);
		this.add(resetDiagnostics);
		this.add(printBatteryVoltage);

		whiteCal.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				motorController.startCalibrationWhite();
			}
		});

		blackCal.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				motorController.startCalibrationBlack();
			}
		});
		startLineFollow.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				motorController.startLineFollowing();
			}
		});

		stopLineFollow.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				motorController.stopLineFollowing();
			}
		});
		
		printDiagnostics.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				diagController.displayDiagnostics();
			}
		});
		
		resetDiagnostics.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				diagController.resetDiagnostics();
			}
		});
		
		printBatteryVoltage.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				diagController.printBatteryVoltage();;
			}
		});

	}
}
