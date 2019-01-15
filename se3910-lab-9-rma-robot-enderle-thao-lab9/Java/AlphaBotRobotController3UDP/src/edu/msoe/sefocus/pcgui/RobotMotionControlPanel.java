package edu.msoe.sefocus.pcgui;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import edu.msoe.sefocus.core.iRobotPropulsionController;


/**
 * This class defines the controls which will adjust how the robot moves.
 * @author schilling
 *
 */
public class RobotMotionControlPanel extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private iRobotPropulsionController motorController;
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
	 *            This is the instance of the robot propulsion motor controller
	 *            that is to be controlled by this panel.
	 */
	public RobotMotionControlPanel(iRobotPropulsionController pmctrl, JFrame jfMainWindow) {
		motorController = pmctrl;

		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BorderLayout());

		BorderLayout myLayout = new BorderLayout();
		this.setLayout(myLayout);

		JButton forwardButton = new JButton("/\\ \'W\'");
		JButton leftForwardButton = new JButton("|\\- \'Q\'");
		JButton rightForwardButton = new JButton("-/| \'E\'");
		
		JButton leftButton = new JButton("<- \'A\'");
		JButton rightButton = new JButton("-> \'D\'");
		JButton backwardButton = new JButton("\\/ \'S\'");
		JButton leftBackwardButton = new JButton("|//_ \'Z\'");
		JButton rightBackwardButton = new JButton("_\\| \'C\'");
		
		JButton stopButton = new JButton("STOP");
		
		forwardButton.setFocusable(false);
		leftForwardButton.setFocusable(false);
		rightForwardButton.setFocusable(false);
		leftButton.setFocusable(false);
		rightButton.setFocusable(false);
		backwardButton.setFocusable(false);
		leftBackwardButton.setFocusable(false);
		rightBackwardButton.setFocusable(false);
		stopButton.setFocusable(false);
		
		JPanel topPanel = new JPanel();
		topPanel.setLayout(new GridLayout(0,3));
		topPanel.add(leftForwardButton);
		topPanel.add(forwardButton);
		topPanel.add(rightForwardButton);
		
		JPanel bottomPanel = new JPanel();
		bottomPanel.setLayout(new GridLayout(0,3));
		bottomPanel.add(leftBackwardButton);
		bottomPanel.add(backwardButton);
		bottomPanel.add(rightBackwardButton);

		

		mainPanel.add(topPanel, BorderLayout.NORTH);
		
		mainPanel.add(leftButton, BorderLayout.WEST);
		mainPanel.add(rightButton, BorderLayout.EAST);
		mainPanel.add(bottomPanel, BorderLayout.SOUTH);
		mainPanel.add(stopButton, BorderLayout.CENTER);

		add(mainPanel, BorderLayout.WEST);
		final JSlider speedControl =  new JSlider(JSlider.VERTICAL, 0, 20, 10);
		speedControl.setMajorTickSpacing(5);
		speedControl.setPaintTicks(true);
		speedControl.setFocusable(false);
		
		final JLabel speedLabel = new JLabel("<html>Robot Speed<br/>" + 5*speedControl.getValue() + "%</html>");
		
		add(speedLabel, BorderLayout.CENTER);

		add(speedControl, BorderLayout.EAST);

		speedControl.addChangeListener(new ChangeListener(){

			@Override
			public void stateChanged(ChangeEvent e) {
				motorController.setVelocity(5*speedControl.getValue());
				switch( robotMotion ) {
				case STOP:
				default:
					break;
				case FORWARD:
					motorController.driveRobotForward();
					break;
				case BACKWARD:
					motorController.driveRobotBackward();
					break;
				case LEFT:
					motorController.turnRobotLeft();
					break;
				case RIGHT:
					motorController.turnRobotRight();
					break;
				}
				speedLabel.setText("<html>Robot Speed<br/>" + 5*speedControl.getValue() + "%</html>");
			}});


		stopButton.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				motorController.setVelocity(5*speedControl.getValue());
				motorController.stopRobotMotion();
				robotMotion = STOP;
			}});


		leftButton.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				motorController.setVelocity(5*speedControl.getValue());
				motorController.turnRobotLeft();
				robotMotion = LEFT;
			}});
		rightButton.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent e) {
				motorController.setVelocity(5*speedControl.getValue());
				motorController.turnRobotRight();
				robotMotion = RIGHT;
			}});

		forwardButton.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				motorController.setVelocity(5*speedControl.getValue());
				motorController.driveRobotForward();
				robotMotion = FORWARD;
			}});
		leftForwardButton.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				motorController.setVelocity(5*speedControl.getValue());
				motorController.driveRobotForwardLeft();
				robotMotion = FORWARD;
			}});

		rightForwardButton.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				motorController.setVelocity(5*speedControl.getValue());
				motorController.driveRobotForwardRight();
				robotMotion = FORWARD;
			}});

		leftBackwardButton.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				motorController.setVelocity(5*speedControl.getValue());
				motorController.driveRobotBackwardLeft();;
				robotMotion = BACKWARD;
			}});
	
		
		rightBackwardButton.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				motorController.setVelocity(5*speedControl.getValue());
				motorController.driveRobotBackwardRight();;
				robotMotion = BACKWARD;
			}});

		

		backwardButton.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				motorController.setVelocity(5*speedControl.getValue());
				motorController.driveRobotBackward();
				robotMotion = BACKWARD;
			}});
		
		jfMainWindow.addKeyListener(new KeyListener(){
			@Override
			public void keyPressed(KeyEvent key) {
				switch(key.getKeyChar()){
				case('q'):
					motorController.driveRobotForwardLeft();
					robotMotion = FORWARD;
					break;
				case('w'):
					motorController.driveRobotForward();
					robotMotion = FORWARD;
					break;
				case('e'):
					motorController.driveRobotForwardRight();
					robotMotion = FORWARD;
					break;
				case('a'):
					motorController.turnRobotLeft();
					robotMotion = LEFT;
					break;
				case('d'):
					motorController.turnRobotRight();
					robotMotion = RIGHT;
					break;
				case('z'):
					motorController.driveRobotBackwardLeft();;
					robotMotion = BACKWARD;
					break;
				case('s'):
					motorController.driveRobotBackward();
					robotMotion = BACKWARD;
					break;
				case('c'):
					motorController.driveRobotBackwardRight();;
					robotMotion = BACKWARD;
					break;
				}
			}

			@Override
			public void keyReleased(KeyEvent key) {
				if(key.getKeyChar() == 'q' ||
						key.getKeyChar() == 'w' ||
						key.getKeyChar() == 'e' ||
						key.getKeyChar() == 'a' ||
						key.getKeyChar() == 's' ||
						key.getKeyChar() == 'd' ||
						key.getKeyChar() == 'z' ||
						key.getKeyChar() == 'c') {
					motorController.stopRobotMotion();
					robotMotion = STOP;
				}
			}

			@Override
			public void keyTyped(KeyEvent arg0) {}
		});
		
		jfMainWindow.addMouseWheelListener(new MouseWheelListener(){

			@Override
			public void mouseWheelMoved(MouseWheelEvent wheel) {
				int newSpeed;
				
				if((wheel.getModifiers() & InputEvent.CTRL_MASK) == InputEvent.CTRL_MASK){
					newSpeed = speedControl.getValue() - (wheel.getWheelRotation() * 5);
				}else{
					newSpeed = speedControl.getValue() - wheel.getWheelRotation();
				}
				
				System.out.println("newSpeed is: " + newSpeed);
				
				speedControl.setValue(newSpeed);
			}
			
		});
	}
}
